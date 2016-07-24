#pragma once

#include "list.h"

/**
* ソース解析。
*
* @param headerFilePathList ヘッダファイルパスリスト
* @param sourceFilePathList ソースファイルパスリスト
* @param seq シーケンス図
*/
void analyzeCtl_analyze( list headerFilePathList, list sourceFilePathList, sequence* seq );
