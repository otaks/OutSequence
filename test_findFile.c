#include <stdio.h>
#include "list.h"
#include "findFile.h"

int main() {

	list l = list_create( STRING );
	list l2 = list_create( STRING );

	findFile_find( ".c", "D:\\99.work\\30\\", l );
	findFile_find( ".h", "D:\\99.work\\30\\", l2 );

	for( int i = 0; i < list_getNum( l ); i++ ) {
		printf( "%s\n", ( char* )list_getNode( l, i ) );
	}

	for( int i = 0; i < list_getNum( l2 ); i++ ) {
		printf( "%s\n", ( char* )list_getNode( l2, i ) );
	}


	list_delete( l );
	list_delete( l2 );
	
	return 0;
}