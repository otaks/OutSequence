
#include "common.h"
#include "analyze.h"

void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	list funcs = list_create( STRUCT_FUNC );

	//mainŠÖ”•ª’Ç‰Á
	func f = {NULL, "int main", "main", NULL};
	//memset( &f, 0x00, sizeof( f ) );
	//strcpy( f.name, "main" );
	//strcpy( f.typeAndName, "int main" );
	list_add( funcs, &f );

	//ŠÖ”–¼ˆê——æ“¾
	analyze_getFuncs( headerFilePathList, funcs );

	//ŠÖ”ŒÄ‚Ño‚µˆê——æ“¾
	analyze_getCallFuncs( sourceFilePathList, funcs );

	//M†’Ç‰Á
	analyze_addSignal( seq, funcs );

	list_delete( funcs );
}