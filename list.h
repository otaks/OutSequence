#pragma once

#include "sysCommon.h"

typedef struct _list* list;

//�f�[�^���
typedef enum dataType_t {
	STRING = 0,	//������
	STRUCT_SIGNAL,		//�M���\����
	STRUCT_FUNC	//�֐��\����
}dataType;	

/**
 *���X�g�쐬�B
 *
 *@param type �f�[�^���
 *@retern �쐬�������X�g
*/
list list_create( dataType type );

/**
 *���X�g�폜�B
 *���X�g��ǉ��I��������ɌĂԂ���
 *
 *@param t ���X�g
*/
void list_delete( list t );

/**
 *�m�[�h�ǉ��B
 *v���f�B�[�v�R�s�[���Ēǉ�
 *
 *@param t ���X�g
 *@param v �ǉ��m�[�h
 *@return ����
*/
int list_add( list t, void* v );

/**
 *�m�[�h���擾�B
 *
 *@param t ���X�g
 *@return �m�[�h��
*/
int list_getNum( list t );

/**
 *�m�[�h�擾�B
 *
 *@param t ���X�g
 *@param i �C���f�b�N�X
 *@return �m�[�h
*/
void* list_getNode( list t, int i );

/**
 *������m�[�h�擾�B
 *�f�[�^��ʂ�������̏ꍇ�̂ݎg�p��
 *
 *@param t ���X�g
 *@param i �C���f�b�N�X
 *@return ������m�[�h
*/
char* list_getCharNode( list t, int i );

