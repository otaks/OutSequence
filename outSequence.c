
#include "common.h"

int main( int argc, char *argv[] ) {

	sequence seq;	//シーケンス図
	list headerFilePathList;	//ヘッダファイルパスリスト
	list sourceFilePathList;	//ソースファイルパスリスト

	if( argc != 1 ) {
		return -1;
	}
	
	//初期化
	init( argv[1], headerFilePathList, sourceFilePathList, &seq );

	//解析
	analyze( headerFilePathList, sourceFilePathList, seq );

	//出力
	output( seq );

	//終了処理
	fin( headerFilePathList, sourceFilePathList, &seq );

	return 0;
}

//初期化
static void init( char* dir, list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	headerFilePathList = list_create( STRING );
	sourceFilePathList = list_create( STRING );

	memset( seq, 0x00, sizeof( seq ) );
	seq->moduleNameList = list_create( STRING );
	seq->signalList = list_create( STRUCT_SIGNAL );

	//親dir解析


}