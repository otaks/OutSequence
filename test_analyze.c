
#include <stdio.h>
#include "findFile.h"
#include "analyze.h"

int main() {
#if 1
	{
		list headerFilePathList = list_create( STRING );
		list sourceFilePathList = list_create( STRING );	//ソースファイルパスリスト
		list funcs = list_create( STRUCT_FUNC );


		findFile_find( ".h", "D:\\00.data\\06.一次解凍先\\lily-master\\src\\", headerFilePathList );
		findFile_find( ".c", "D:\\00.data\\06.一次解凍先\\lily-master\\src\\", sourceFilePathList );

		analyze_getFuncs( headerFilePathList, funcs );

		for( int i = 0; i < list_getNum( funcs ); i++ ) {
			//printf("%s %s\n", ( ( func* )list_getNode( funcs, i ) )->mName, (( func* )list_getNode(funcs, i))->name);
			printf( "%s\n", ( ( func* )list_getNode( funcs, i ) )->name );
		}

		printf( "\n\n" );

		//関数呼び出し一覧取得
		analyze_getCallFuncs( sourceFilePathList, funcs );

		for( int i = 0; i < list_getNum( funcs ); i++ ) {
			printf("%s %s\n", ( ( func* )list_getNode( funcs, i ) )->mName, (( func* )list_getNode(funcs, i))->name);
			for( int j = 0; j < list_getNum( ( ( func* )list_getNode( funcs, i ) )->callFuncs ); j++ ) {
				printf( "  %s\n", list_getCharNode( ( ( func* )list_getNode( funcs, i ) )->callFuncs , j ));
			}
		}

	}
#endif

	return 0;
}


