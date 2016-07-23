#pragma once


/*
・ログレベル
・-log…ファイル出力あり、-verbose…ログレベル調整　等
*/

/*
ログレベル
4                   ERR
3              WRN, ERR
2        INFO, WRN, ERR
1 DEBUG, INFO, WRN, ERR
*/
//#define LOG_LEVEL 5	//リリース時(ログなし)
//#define LOG_LEVEL 3	//リリース時(-verboseなし)
//#define LOG_LEVEL 2	//リリース時(-verboseあり)
#define LOG_LEVEL 1	//デバッグ時

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


