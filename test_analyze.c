
#include <stdio.h>
#include "findFile.h"
#include "analyze.h"

int main() {
	{
		list headerFilePathList = list_create( STRING );
		list funcs = list_create( STRUCT_FUNC );

		//ヘッダファイルリスト取得
		findFile_find( ".h", "D:\\00.data\\06.一次解凍先\\lily-master\\src\\", headerFilePathList );

		analyze_getFuncs( headerFilePathList, funcs );

		for( int i = 0; i < list_getNum( funcs ); i++ ) {
			printf("%s %s\n", ( ( func* )list_getNode( funcs, i ) )->mName, (( func* )list_getNode(funcs, i))->name);
		}
	}

	return 0;
}


