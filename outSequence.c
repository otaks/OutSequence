
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "findFile.h"
#include "analyzeCtl.h"
#include<conio.h>

static void init( char* dir, list* headerFilePathList, list* sourceFilePathList, sequence* seq );
static void fin( list headerFilePathList, list sourceFilePathList, sequence* seq );
static void output( char* dirName, sequence* seq );

int main( int argc, char *argv[] ) {

	sequence seq;	//シーケンス図
	list headerFilePathList;	//ヘッダファイルパスリスト
	list sourceFilePathList;	//ソースファイルパスリスト

#if _DEBUG
	printf( "debug timing. press any key." );
	getch();
	printf( "\n" );
#endif

	if( argc != 2 ) {
		return -1;
	}
	
	//初期化
	char t[ 1000 ] = { 0 };
	sprintf(t, "%s\\", argv[1]);
	//init( argv[1], &headerFilePathList, &sourceFilePathList, &seq );
	init( t, &headerFilePathList, &sourceFilePathList, &seq );

	//解析
	analyzeCtl_analyze( headerFilePathList, sourceFilePathList, &seq );

	//出力
	output( argv[ 1 ], &seq );

	//終了処理
	fin( headerFilePathList, sourceFilePathList, &seq );

	//printf( "カレントディレクトリにresult.txtを出力しました。" );
	printf( "result.txt is generated in the current dirctory.\n" );
	return 0;
}

//初期化
static void init( char* dir, list* headerFilePathList, list* sourceFilePathList, sequence* seq ) {

	*headerFilePathList = list_create( STRING );
	*sourceFilePathList = list_create( STRING );

	memset( seq, 0x00, sizeof( seq ) );
	seq->moduleNameList = list_create( STRING );

	seq->signalList = list_create( STRUCT_SIGNAL );

	//ヘッダファイルリスト取得
	findFile_find( ".h", dir, *headerFilePathList );
	//ソースファイルリスト取得
	findFile_find( ".c", dir, *sourceFilePathList );
}

//終了処理
static void fin( list headerFilePathList, list sourceFilePathList, sequence* seq ) {
	list_delete( headerFilePathList );
	list_delete( sourceFilePathList );
	list_delete( seq->moduleNameList );
	list_delete( seq->signalList );
}


static void output( char* dirName, sequence* seq ) {

	FILE *fp;

	if( ( fp = fopen( "result.txt", "w" ) ) == NULL ) {
		printf( "file open error!!\n" );
		exit( EXIT_FAILURE );
	}

	fprintf(fp, "@startuml\n");
	for( int i = 0; i < list_getNum( seq->moduleNameList ); i++ ) {
		fprintf( fp, "actor %s\n", list_getCharNode( seq->moduleNameList, i ) );
	}
	for( int i = 0; i < list_getNum( seq->signalList ); i++ ) {
		signal* s = ( signal* )list_getNode( seq->signalList, i );
		fprintf( fp, "%s %s %s : %s\n", s->sendModuleName, ((s->isReq==1)?"->":"-->"), s->receiveModuleName, s->name );
	}
	fprintf( fp, "@enduml\n" );

	fclose( fp );
}

