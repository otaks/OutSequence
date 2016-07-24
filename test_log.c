
#include "log.h"


void case1() {
	LOG_ERR( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_WRN( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_INFO( "%s %s %s\n", "test1", "test2", "test3" )
	LOG_DEBUG( "%s %s %s\n", "test1", "test2", "test3" )
}

void case2() {

}

void case3() {

}



int main() {

	case1();
	case2();
	case3();

	return 0;
}