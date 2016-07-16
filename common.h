#pragma once

#include "list.h"

//�M��
typedef struct signal_t {
	char* sendModuleName;	//���M���W���[����
	char* receiveModuleName;	//��M���W���[����
	char* name;	//�M����
	int isReq;	//1:true, 0:false
}signal;

//�V�[�P���X�}
typedef struct sequence_t {
	int moduleNum;	//���W���[����
	list moduleNameList;	//���W���[����

	int signalNum;	//�M����
	list signalList;	//�M��
}sequence;



//�֐�
typedef struct _func {
	char* mName;	//���W���[����
	char* typeAndName;	//�߂�l�̌^�Ɗ֐���
	char* name;	//�֐���
	list callFuncs;	//�Ăяo���֐��Q
}func;	