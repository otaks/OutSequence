#pragma once

#include <stdlib.h>

typedef enum _bool {
	FALSE = 0,
	TRUE
}bool;

#define FREE(X) free(X);X=NULL;