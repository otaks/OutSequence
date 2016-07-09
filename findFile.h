#pragma once

#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )

#include "list.h"

/**
 * ファイルリスト取得。
 * lpszDir配下(サブフォルダ含む)内でファイル名が
 * ptnで終わる全ファイルのフルパスをlに格納する。
 * 
 * @param ptn 拡張子
 * @param lpszDir 親ディレクトリ
 * @param l 格納先リスト
*/
void findFile_find( char * ptn, char* lpszDir, list l );

