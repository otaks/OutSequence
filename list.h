#pragma once

#include "sysCommon.h"

typedef struct _list* list;

//�f�[�^���
typedef enum dataType_t {
	STRING = 0,	//������
	STRUCT_SIGNAL,		//�M���\����
	STRUCT_FUNC	//�֐��\����
}dataType;	

//���X�g�쐬
list list_create( dataType type );

//���X�g�폜
void list_delete( list t );

//�m�[�h�ǉ�
//	v���f�B�[�v�R�s�[���Ēǉ�
//bool_ list_add( list t, void* v );
int list_add( list t, void* v );

//�m�[�h���擾
int list_getNum( list t );

//�m�[�h�擾
void* list_getNode( list t, int i );

char* list_getCharNode( list t, int i );

