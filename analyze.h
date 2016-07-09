#pragma once

#include "common.h"

void analyze_getFuncs( list headerFilePathList, list funcs );
void analyze_getCallFuncs( sourceFilePathList, funcs );
void analyze_addSignal( sequence* seq, list funcs );

