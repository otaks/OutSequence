#pragma once

#include "list.h"

//信号
typedef struct signal_t {
	char* sendModuleName;	//送信モジュール名
	char* receiveModuleName;	//受信モジュール名
	char* name;	//信号名
}signal;

//シーケンス図
typedef struct sequence_t {
	int moduleNum;	//モジュール数
	list moduleNameList;	//モジュール名

	int signalNum;	//信号数
	list signalList;	//信号
}sequence;



