
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyze.h"


static void analyze_getFuncName_s( char* line, char* t );
static void analyze_getModuleName_s( char* t2, char* h );
static int analyze_isDefineLine_s( char* line );
static void analyze_addSignalRec_s( sequence* seq, func* f, func* preF, list funcs );
static func* analyze_getTargetFunc_s( list funcs, char* targetFuncName );
static void analyze_gettypeAndName_s( char* line, char* t2 );
static void analyze_getCallFuncsCore_s( char* src, list funcs, func* f );
static void analyze_isFunc_s( char* line, list funcs, func* f );
static char* analyze_findSrc_s( char* typeAndName, list sourceFilePathList );
int analyze_hasModule_s( sequence* seq, char* mName );

//関数名一覧取得
void analyze_getFuncs( list headerFilePathList, list funcs ) {
	for( int i = 0; i < list_getNum( headerFilePathList ); i++ ) {
		char* h = list_getCharNode( headerFilePathList, i );
		FILE *fp;	
		char s[ 1000 ];

		if( ( fp = fopen( h, "r" ) ) == NULL ) {
			printf( "file open error!!\n" );
			exit( EXIT_FAILURE );	
		}

		while( fgets( s, 1000, fp ) != NULL ) {
			if( analyze_isDefineLine_s( s ) ) {	//関数プロトタイプ宣言行か
				func f;
				memset( &f, 0x00, sizeof( f ) );
				char t[ 1000 ] = { 0 };
				char t2[ 1000 ] = { 0 };
				memset( t, 0x00, sizeof( t ) );
				memset( t2, 0x00, sizeof( t2 ) );

				analyze_getFuncName_s( s, t );
				if( strlen( t ) == 0 )continue;
				f.name = t;
				analyze_gettypeAndName_s( s, t2 );
				f.typeAndName = t2;

				list_add( funcs, &f );
			}
		}
		fclose( fp );	
	}
}

static void analyze_gettypeAndName_s( char* line, char* t2 ) {
	int i, j;
	for( i = 0; i < strlen( line ); i++ ) {
		if( line[ i ] == '(' ) {
			break;
		}
	}
	i--;

	int l = 0;
	int k;
	if( strstr( line, "extern " ) != NULL ) {
		k = 7;
	}else{
		k = 0;
	}
	for( ; k <= i; k++ ) {
		t2[ l++ ] = line[ k ];
	}
}

static void analyze_getModuleName_s( char* t2, char* h ) {
	int i, j;
	for( i = strlen( h ) - 1; i >= 0; i-- ) {
		if( h[ i ] == '.' ) {
			break;
		}
	}
	i--;

	for( j = i; j >= 0; j-- ) {
		if( h[ j ] == '\\' ) {
			break;
		}
	}
	j++;

	int l = 0;
	for( int k = j; k <= i; k++ ) {
		t2[ l++ ] = h[ k ];
	}
}

static int analyze_isDefineLine_s( char* line ) {
	if( ( strchr( line, '(' ) != NULL ) &&
		( strchr( line, ')' ) != NULL ) &&
		( strchr( line, ';' ) != NULL ) &&
		(line[0] != '#')) {
		return TRUE;
	}
	return FALSE;
}


/*  解析例：lily_options *lily_new_default_options(void); */
/*
debug

void *lily_mallock(size_t);

111111111122222222223333333333
0123456789012345678901234567890123456789


*/
static void analyze_getFuncName_s( char* line, char* t ) {
	int i, j;
	for( i = 0; i < strlen( line ); i++ ) {
		if( line[ i ] == '(' ) {
			break;
		}
	}
	i--;

	for( j = i; j >= 0; j-- ) {
		if( line[ j ] == ' ' ) {
			break;
		}
	}
	j++;

	if( line[ j ] == '*' ) {
		j++;
	}

	int l = 0;
	for( int k = j; k <= i; k++ ) {
		t[ l++ ] = line[ k ];
	}
}


void analyze_addSignal( sequence* seq, list funcs ) {
	analyze_addSignalRec_s( seq, ( func* )list_getNode( funcs, 0 ), NULL, funcs );
}


static void analyze_addSignalRec_s( sequence* seq, func* f, func* preF, list funcs ) {
	//printf( "%s\n", f->name );

	//シーケンス図に信号追加
	signal s;
	memset( &s, 0x00, sizeof( s ) );
	if( f->mName == NULL )return;
	s.name = f->name;
	s.receiveModuleName = f->mName;
	
	s.sendModuleName = ( preF == NULL ? f->mName : preF->mName );
	s.isReq = 1;
	//if( f->mName == NULL )return;
	list_add( seq->signalList, &s );

	if( list_getNum( f->callFuncs ) != 0 ) {
		//当該関数からの呼び出しあり？
		for( int i = 0; i < list_getNum( f->callFuncs ); i++ ) {
			func* targetF = analyze_getTargetFunc_s( funcs, list_getCharNode( f->callFuncs, i ) );
			analyze_addSignalRec_s( seq, targetF, f, funcs );
		}
	}

	//シーケンス図に信号追加
	signal s2;
	memset( &s2, 0x00, sizeof( s ) );
	s2.name = " ";
	s2.receiveModuleName = ( preF == NULL ? f->mName : preF->mName );
	s2.sendModuleName = f->mName;
	//if( strcmp( s2.receiveModuleName, s2.sendModuleName ) != 0 ) {
		//送信元、送信先モジュールが同一の場合、戻りの線を出ないように
		list_add( seq->signalList, &s2 );
	//}
}

static func* analyze_getTargetFunc_s( list funcs, char* targetFuncName ) {
	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		func* f = ( func * )list_getNode( funcs, i );
		if( strcmp( f->name, targetFuncName ) == 0 ) {
			return f;
		}
	}
}

//関数リストの 呼び出し関数[]部 を埋める
void analyze_getCallFuncs( list sourceFilePathList, list funcs ) {
	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		func* f = ( func* )list_getNode( funcs, i );

		//その関数が定義されているソースファイルを見つける
		char* src = analyze_findSrc_s( f->typeAndName, sourceFilePathList );
		if( src == NULL )continue;
		//ソースファイル名からモジュール名取得
		char t2[ 1000 ] = { 0 };
		memset( t2, 0x00, sizeof( t2 ) );
		analyze_getModuleName_s( t2, src );
		f->mName = calloc( strlen( t2 ) + 1, 1 );
		strcpy( f->mName, t2 );
		
		//呼び出し関数取得
		analyze_getCallFuncsCore_s(src, funcs, f);
	}

}

//呼び出し関数取得
static void analyze_getCallFuncsCore_s( char* src, list funcs, func* f ) {

	FILE *fp;
	char line[ 1000 ];

	if( ( fp = fopen( src, "r" ) ) == NULL ) {
		printf( "file open error!!\n" );
		exit( EXIT_FAILURE );
	}

	int sNum = 0;	//{数
	int eNum = 0;	//}数

	int flg = 0;
	while( fgets( line, 1000, fp ) != NULL ) {
		char t[ 1000 ];
		memset( t, 0x00, sizeof( t ) );
		sprintf( t, "%s(", f->typeAndName );
		//if( strstr( line, f->typeAndName ) != NULL ) {
			if( strstr( line, t ) != NULL ) {
			//return src;
			flg = 1;
		}
		if( flg == 1 ) {
			//ブランケットカウント
			{
				if( strchr( line, '{' ) != NULL ) {
					sNum++;
				}
				if( strchr( line, '}' ) != NULL ) {
					eNum++;
				}
			}

			if( sNum == eNum && sNum != 0) {
				//その関数内は見終わった
				break;
			}

			analyze_isFunc_s( line, funcs, f );
		}
	}
	fclose( fp );
}

//static char* analyze_isFunc_s( char* line, list funcs, func* f ) {
static void analyze_isFunc_s( char* line, list funcs, func* f ) {
	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		func* tf = list_getNode( funcs, i );
		//char* name = list_getCharNode( funcs, i );
		char t[ 1000 ] = { 0 };
		char t2[ 1000 ] = { 0 };
		memset( t, 0x00, sizeof( t ) );
		memset( t2, 0x00, sizeof( t2 ) );
		sprintf( t, " %s(", tf->name );
		sprintf( t2, "\t%s(", tf->name );
		//if( (strstr(line, tf->name) != NULL) && (strcmp(f->name, tf->name) != 0)) {
		if( (( strstr( line, t ) != NULL ) || ( strstr( line, t2 ) != NULL ) )
			&& ( strcmp( f->name, tf->name ) != 0 ) ) {
			list_add( f->callFuncs, tf->name );
		}
	}
}

//その関数が定義されているソースファイルを見つける
static char* analyze_findSrc_s( char* typeAndName, list sourceFilePathList ) {
	for( int i = 0; i < list_getNum( sourceFilePathList ); i++ ) {
		char* src = list_getCharNode( sourceFilePathList, i );
		FILE *fp;
		char line[ 1000 ];

		if( ( fp = fopen( src, "r" ) ) == NULL ) {
			printf( "file open error!!\n" );
			exit( EXIT_FAILURE );
		}

		while( fgets( line, 1000, fp ) != NULL ) {
			char t[ 1000 ] = { 0 };
			memset( t, 0x00, sizeof( t ) );
			sprintf( t, "%s(", typeAndName );
			//if( strstr( line, typeAndName ) != NULL ) {
			if( strstr( line, t ) != NULL ) {
				return src;
			}
		}
		fclose( fp );
	}
	return NULL;
}

/**
* モジュールリスト作成。
* シーケンス図にモジュールリストを作成する。
*
* @param seq シーケンス図
* @param funcs 関数リスト
*/
void analyze_createModuleList( sequence* seq, list funcs ) {

	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		char* mName = ( ( func * )list_getNode( funcs, i ) )->mName;

		if( ( mName != NULL ) && (analyze_hasModule_s(seq, mName) == -1)) {
			list_add( seq->moduleNameList, mName );
		}
	}


}

int analyze_hasModule_s( sequence* seq, char* mName ) {
	int ret = -1;
	for( int i = 0; i < list_getNum( seq->moduleNameList ); i++ ) {
		if( strcmp(mName, list_getCharNode( seq->moduleNameList, i)) == 0 ) {
			ret = 0;
			break;
		}
	}

	return ret;
}