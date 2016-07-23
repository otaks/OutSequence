
#include "log.h"

int main() {
	LOG_ERR( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_WRN( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_INFO( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_DEBUG( "%s %s %s\n", "test1", "test2", "test3" )

	return 0;
}