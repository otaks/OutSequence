
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//�֐����ꗗ�擾
	analyze_getFuncs( headerFilePathList, funcs );

	//�֐��Ăяo���ꗗ�擾
	analyze_getCallFuncs( sourceFilePathList, funcs );

	//�M���ǉ�
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}