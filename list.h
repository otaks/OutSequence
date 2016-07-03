#pragma once

#include "sysCommon.h"

typedef struct _list* list;

//データ種別
typedef enum dataType_t {
	STRING = 0,	//文字列
	STRUCT_SIGNAL		//信号構造体
}dataType;	

//リスト作成
list list_create( dataType type );

//リスト削除
void list_delete( list t );

//ノード追加
//	vをディープコピーして追加
bool list_add( list t, void* v );

//ノード数取得
int list_getNum( list t );

//ノード取得
void* list_getNode( list t, int i );

