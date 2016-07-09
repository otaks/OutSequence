
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyze.h"


//typedef struct _funcs {
//	int num;	//関数総数
//	list f;
//}funcs;



static void analyze_getFuncName_s( char* line, char* t );
static void analyze_getModuleName_s( char* t2, char* h );
static int analyze_isDefineLine_s( char* line );
static void analyze_addSignalRec_s( sequence* seq, func* f, func* preF, list funcs );
static func* analyze_getTargetFunc_s( list funcs, char* targetFuncName );

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

				analyze_getFuncName_s( s, t );
				f.name = t;
				analyze_getModuleName_s( t2, h );
				f.mName = t2;
				list_add( funcs, &f );
			}
		}
		fclose( fp );	
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
		( strchr( line, ';' ) != NULL ) ) {
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
	for( i = strlen( line ) - 1; i >= 0; i-- ) {
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
	if( list_getNum( f->callFuncs ) != 0 ) {
		//当該関数からの呼び出しあり？
		for( int i = 0; i < list_getNum( f->callFuncs ); i++ ) {
			func* targetF = analyze_getTargetFunc_s( funcs, list_getCharNode( f->callFuncs, i ) );
			analyze_addSignalRec_s( seq, targetF, f, funcs );
		}
	}
	else {
		//シーケンス図に信号追加
		signal s;
		memset( &s, 0x00, sizeof( s ) );
		s.name = f->name;
		s.receiveModuleName = f->mName;
		s.sendModuleName = preF->mName;
		list_add( seq->signalList, &s );
	}
}

static func* analyze_getTargetFunc_s( list funcs, char* targetFuncName ) {
	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		func* f = ( func * )list_getNode( funcs, i );
		if( strcmp( f->name, targetFuncName ) == 0 ) {
			return f;
		}
	}
}

//関数リストの呼び出し関数[]部を埋める
void analyze_getCallFuncs( list sourceFilePathList, list funcs ) {
	for( int i = 0; i < list_getNum( funcs ); i++ ) {
		func* f = ( func* )list_getNode( funcs, i );

		
	}

}