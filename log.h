#pragma once


/*
�E���O���x��
�E-log�c�t�@�C���o�͂���A-verbose�c���O���x�������@��
*/

/*
���O���x��
4                   ERR
3              WRN, ERR
2        INFO, WRN, ERR
1 DEBUG, INFO, WRN, ERR
*/
//#define LOG_LEVEL 5	//�����[�X��(���O�Ȃ�)
//#define LOG_LEVEL 3	//�����[�X��(-verbose�Ȃ�)
//#define LOG_LEVEL 2	//�����[�X��(-verbose����)
#define LOG_LEVEL 1	//�f�o�b�O��

#ifdef LOG_LEVEL <= 4
#define LOG_ERR(...)  DEBUG_PRINT("ERR", __VA_ARGS__, "")
#else
#define DEBUG_PRINT(...)
#endif

#ifdef LOG_LEVEL <= 3
#define LOG_WRN(...)  DEBUG_PRINT("WRN", __VA_ARGS__, "")
#else
#define DEBUG_PRINT(...)
#endif

#ifdef LOG_LEVEL <= 2
#define LOG_INFO(...)  DEBUG_PRINT("INFO", __VA_ARGS__, "")
#else
#define DEBUG_PRINT(...)
#endif

#ifdef LOG_LEVEL <= 1
#define LOG_DEBUG(...)  DEBUG_PRINT("DEBUG", __VA_ARGS__, "")
#else
#define DEBUG_PRINT(...)
#endif


#define DEBUG_PRINT(lv, fmt, ...)  \
		printf( "[%s]", lv);\
		if ( strcmp(lv, "DEBUG") == 0 ){ \
			printf("%s(%d) ", __func__, __LINE__);	\
		}\
		printf( fmt, __VA_ARGS__ );


