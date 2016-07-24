
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//main�֐����ǉ�
	func f = {NULL, "int main", "main", NULL};
	list_add( funcs, &f );

	//�֐����ꗗ�擾
	analyze_getFuncs( headerFilePathList, sourceFilePathList, funcs );

	//�֐��Ăяo���ꗗ�擾
	analyze_getCallFuncs( sourceFilePathList, funcs );


	//���W���[�����X�g�쐬
	analyze_createModuleList( seq, funcs );

	//�M���ǉ�
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}