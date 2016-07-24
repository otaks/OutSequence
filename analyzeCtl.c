
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//main関数分追加
	func f = {NULL, "int main", "main", NULL};
	list_add( funcs, &f );

	//関数名一覧取得
	analyze_getFuncs( headerFilePathList, sourceFilePathList, funcs );

	//関数呼び出し一覧取得
	analyze_getCallFuncs( sourceFilePathList, funcs );


	//モジュールリスト作成
	analyze_createModuleList( seq, funcs );

	//信号追加
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}