#pragma once

#include <stdlib.h>

//typedef enum _bool {
//	FALSE = 0,
//	TRUE
//}bool_;

#define FALSE 0
#define TRUE 1


#define FREE(X) free(X);X=NULL;