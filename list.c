
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "common.h"

//�m�[�h
typedef struct _node node;
struct _node {
	void* data;
	node* next;
};

//���X�g
struct _list {
	int num;
	dataType type;
	node* first;
};


//���X�g�쐬
list list_create( dataType type ) {
	list t = calloc( sizeof( struct _list ), 1 );
	t->type = type;
	return t;
}

//���X�g�폜
void list_delete( list t ) {

	node* n = t->first;
	while( n != NULL ) {
		node* a = n;
		n = n->next;	

		//�f�[�^��ʌʏ���
		switch( t->type )
		{
		case STRING:
			FREE( a->data );
			break;
		case STRUCT_SIGNAL:
			FREE( ( ( signal* )a->data )->name );
			FREE( ( ( signal* )a->data )->sendModuleName );
			FREE( ( ( signal* )a->data )->receiveModuleName );
			FREE( a->data );
			break;
		case STRUCT_FUNC:
			FREE( ( ( func* )a->data )->name );
			list_delete( ( ( func* )a->data )->callFuncs );
			FREE( a->data );
			break;
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

//�m�[�h�ǉ�
//bool_ list_add( list t, void* v) {
int list_add( list t, void* v ) {

	//�m�[�h�쐬�A
	node* newNode = ( node* )calloc( sizeof( struct _node ), 1 );

	//�f�[�^�ݒ�
	switch( t->type )
	{
	case STRING:
		newNode->data = ( char* )calloc( strlen( ( char* )v ) + 1, 1 );
		strcpy( (char*)newNode->data, ( char* )v );
		break;
	case STRUCT_SIGNAL:
		newNode->data = ( signal* )calloc( sizeof( signal ), 1 );
		//�M����
		(( signal* )newNode->data)->name = ( char* )calloc( strlen((( signal* )v )->name) + 1, 1 );
		strcpy( ( char* )(( signal* )newNode->data)->name, ( ( signal* )v )->name );
		//���M���W���[����
		( ( signal* )newNode->data )->sendModuleName = ( char* )calloc( strlen( ( ( signal* )v )->sendModuleName ) + 1, 1 );
		strcpy( ( char* )( ( signal* )newNode->data )->sendModuleName, ( ( signal* )v )->sendModuleName );
		//��M���W���[����
		( ( signal* )newNode->data )->receiveModuleName = ( char* )calloc( strlen( ( ( signal* )v )->receiveModuleName ) + 1, 1 );
		strcpy( ( char* )( ( signal* )newNode->data )->receiveModuleName, ( ( signal* )v )->receiveModuleName );
		break;
	case STRUCT_FUNC:
		newNode->data = ( func* )calloc( sizeof( func ), 1 );
		//���W���[����
		( ( func* )newNode->data )->mName = ( char* )calloc( strlen( ( ( func* )v )->mName ) + 1, 1 );
		strcpy( ( char* )( ( func* )newNode->data )->mName, ( ( func* )v )->mName );
		//�֐���
		( ( func* )newNode->data )->name = ( char* )calloc( strlen( ( ( func* )v )->name ) + 1, 1 );
		strcpy( ( char* )( ( func* )newNode->data )->name, ( ( func* )v )->name );
		//�Ăяo���֐��Q
		( ( func* )newNode->data )->callFuncs = list_create( STRING );
		break;
	default:
		break;
	}

	//�����m�[�h�ɂȂ�
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


//�m�[�h���擾
int list_getNum( list t ) {
	return t->num;
}

//�m�[�h�擾
void* list_getNode( list t, int i ) {
	node* n = t->first;
	if( i < t->num ) {
		for( int j = 0; j < i; j++ ) {
			n = n->next;
		}
	}
	return n->data;
}

//������m�[�h�擾
char* list_getCharNode( list t, int i ) {
	return ( char * )list_getNode(t, i);
}