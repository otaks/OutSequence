#pragma once

#include "list.h"

//信号
typedef struct signal_t {
	char* sendModuleName;	//送信モジュール名
	char* receiveModuleName;	//受信モジュール名
	char* name;	//信号名
	int isReq;	//1:true, 0:false
}signal;

//シーケンス図
typedef struct sequence_t {
	int moduleNum;	//モジュール数
	list moduleNameList;	//モジュール名

	int signalNum;	//信号数
	list signalList;	//信号
}sequence;



//関数
typedef struct _func {
	char* mName;	//モジュール名
	char* typeAndName;	//戻り値の型と関数名
	char* name;	//関数名
	list callFuncs;	//呼び出し関数群
}func;	