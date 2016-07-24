#pragma once

#include "sysCommon.h"

typedef struct _list* list;

//データ種別
typedef enum dataType_t {
	STRING = 0,	//文字列
	STRUCT_SIGNAL,		//信号構造体
	STRUCT_FUNC	//関数構造体
}dataType;	

/**
 *リスト作成。
 *
 *@param type データ種別
 *@retern 作成したリスト
*/
list list_create( dataType type );

/**
 *リスト削除。
 *リストを追加終わった時に呼ぶこと
 *
 *@param t リスト
*/
void list_delete( list t );

/**
 *ノード追加。
 *vをディープコピーして追加
 *
 *@param t リスト
 *@param v 追加ノード
 *@return 成否
*/
int list_add( list t, void* v );

/**
 *ノード数取得。
 *
 *@param t リスト
 *@return ノード数
*/
int list_getNum( list t );

/**
 *ノード取得。
 *
 *@param t リスト
 *@param i インデックス
 *@return ノード
*/
void* list_getNode( list t, int i );

/**
 *文字列ノード取得。
 *データ種別が文字列の場合のみ使用可
 *
 *@param t リスト
 *@param i インデックス
 *@return 文字列ノード
*/
char* list_getCharNode( list t, int i );

