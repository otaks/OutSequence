
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//main�֐����ǉ�
	func f = {NULL, "int main", "main", NULL};
	//memset( &f, 0x00, sizeof( f ) );
	//strcpy( f.name, "main" );
	//strcpy( f.typeAndName, "int main" );
	list_add( funcs, &f );

	//�֐����ꗗ�擾
	analyze_getFuncs( headerFilePathList, funcs );

	//�֐��Ăяo���ꗗ�擾
	analyze_getCallFuncs( sourceFilePathList, funcs );

	//�M���ǉ�
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}