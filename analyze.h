#pragma once

#include "common.h"

/**
 * 関数名リスト取得。
 * ヘッダーファイルからグローバル関数名、
 * ソースファイルからスタティック関数名を取得する。
 *
 * @param headerFilePathList ヘッダファイルパスリスト
 * @param sourceFilePathList ソースファイルパスリスト
 * @param funcs 関数リスト
 */
void analyze_getFuncs( list headerFilePathList, list sourceFilePathList, list funcs );

/**
* 呼び出し関数リスト取得。
* 関数名リストを元にソースファイルから、
* 関数毎の呼び出し関数リストを取得する。
*
* @param headerFilePathList ヘッダファイルパスリスト
* @param funcs 関数リスト
*/
void analyze_getCallFuncs( sourceFilePathList, funcs );

/**
* モジュールリスト作成。
* シーケンス図にモジュールリストを作成する。
*
* @param seq シーケンス図
* @param funcs 関数リスト
*/
void analyze_createModuleList( sequence* seq, list funcs );

/**
* 信号追加。
* シーケンス図に信号を追加する。
*
* @param seq シーケンス図
* @param funcs 関数リスト
*/
void analyze_addSignal( sequence* seq, list funcs );

