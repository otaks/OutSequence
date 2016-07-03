
#include <stdio.h>
#include "list.h"

int main() {

	list l = list_create(STRING);

	list_add( l, "chance." );
	list_add( l, "victory" );

	for( int i = 0; i < list_getNum( l ); i++ ) {
		printf( "%s\n", (char *)list_getNode(l, i) );
	}

	list_delete( l );

	return 0;
}