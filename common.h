#pragma once

#include "list.h"

//�M��
typedef struct signal_t {
	char* sendModuleName;	//���M���W���[����
	char* receiveModuleName;	//��M���W���[����
	char* name;	//�M����
}signal;

//�V�[�P���X�}
typedef struct sequence_t {
	int moduleNum;	//���W���[����
	list moduleNameList;	//���W���[����

	int signalNum;	//�M����
	list signalList;	//�M��
}sequence;



