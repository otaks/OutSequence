
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//ŠÖ”–¼ˆê——æ“¾
	analyze_getFuncs( headerFilePathList, funcs );

	//ŠÖ”ŒÄ‚Ño‚µˆê——æ“¾
	analyze_getCallFuncs( sourceFilePathList, funcs );

	//M†’Ç‰Á
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}