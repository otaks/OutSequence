
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "common.h"

//ノード
typedef struct _node node;
struct _node {
	void* data;
	node* next;
};

//リスト
struct _list {
	int num;
	dataType type;
	node* first;
};


//リスト作成
list list_create( dataType type ) {
	list t = calloc( sizeof( struct _list ), 1 );
	t->type = type;
	return t;
}

//リスト削除
void list_delete( list t ) {

	node* n = t->first;
	while( n != NULL ) {
		node* a = n;
		n = n->next;	

		//データ種別個別処理
		switch( t->type )
		{
		case STRING:
			FREE( a->data );
		case STRUCT_SIGNAL:
			FREE( ( ( signal* )a->data )->name );
			FREE( ( ( signal* )a->data )->sendModuleName );
			FREE( ( ( signal* )a->data )->receiveModuleName );
			FREE( a->data );
		default:
			break;
		}

		FREE( a );
	}

	FREE( t );
}

node* list_getLastNode_s( list t ) {
	node* n = t->first;
	while( n != NULL ) {
		if( n->next == NULL ) {
			return n;
		}
		n = n->next;
	}
}

//ノード追加
bool list_add( list t, void* v) {

	//ノード作成、
	node* newNode = ( node* )calloc( sizeof( struct _node ), 1 );

	//データ設定
	switch( t->type )
	{
	case STRING:
		newNode->data = ( char* )calloc( strlen( ( char* )v ) + 1, 1 );
		strcpy( (char*)newNode->data, ( char* )v );
		break;
	case STRUCT_SIGNAL:
		newNode->data = ( signal* )calloc( sizeof( signal ), 1 );
		//信号名
		(( signal* )newNode->data)->name = ( char* )calloc( strlen((( signal* )v )->name) + 1, 1 );
		strcpy( ( char* )(( signal* )newNode->data)->name, ( ( signal* )v )->name );
		//送信モジュール名
		( ( signal* )newNode->data )->sendModuleName = ( char* )calloc( strlen( ( ( signal* )v )->sendModuleName ) + 1, 1 );
		strcpy( ( char* )( ( signal* )newNode->data )->sendModuleName, ( ( signal* )v )->sendModuleName );
		//受信モジュール名
		( ( signal* )newNode->data )->receiveModuleName = ( char* )calloc( strlen( ( ( signal* )v )->receiveModuleName ) + 1, 1 );
		strcpy( ( char* )( ( signal* )newNode->data )->receiveModuleName, ( ( signal* )v )->receiveModuleName );
		break;
	default:
		break;
	}

	//末尾ノードにつなぐ
	if( t->num != 0 ) {
		node* n = list_getLastNode_s( t );
		n->next = newNode;
	}
	else {
		t->first = newNode;
	}
	( t->num )++;

	return TRUE;
}


//ノード数取得
int list_getNum( list t ) {
	return t->num;
}

//ノード取得
void* list_getNode( list t, int i ) {
	node* n = t->first;
	if( i < t->num ) {
		for( int j = 0; j < i; j++ ) {
			n = n->next;
		}
	}
	return n->data;
}
