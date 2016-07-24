#include <stdio.h>
#include "findFile.h"

static void findFile_findRec_s( char * ptn, char* lpszDir, list l );
static int findFile_checkPtn( char* fileName, char* ptn );


void findFile_find( char * ptn, char* lpszDir, list l ) {
	char t[ 1000 ];
	memset( t, 0x00, 1000 );
	sprintf( t, "%s*", lpszDir );
	findFile_findRec_s( ptn, t, l );
}

static void findFile_findRec_s( char * ptn, char* lpszDir, list l )
{
	char subpath[ _MAX_PATH ];
	char temp[ _MAX_PATH ];
	WIN32_FIND_DATA lp;

	strcpy( temp, lpszDir );
	HANDLE h = FindFirstFile( temp, &lp );

	temp[ strlen( temp ) - 1 ] = '\0';//*を消している
	do
	{
		if( ( lp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			&& strcmp( lp.cFileName, ".." ) != 0 && strcmp( lp.cFileName, "." ) != 0 )
		{
			//ディレクトリか
			sprintf( subpath, "%s%s\\*", temp, lp.cFileName );
			findFile_findRec_s( ptn, subpath, l );

		}
		else if( ( lp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			!= FILE_ATTRIBUTE_DIRECTORY )
		{
			//ファイルか

			if(findFile_checkPtn( lp.cFileName, ptn)){	//パターン適合か
				//フルパス生成
				char t[ 1000 ];
				memset( t, 0x00, 1000 );
				sprintf( t, "%s%s", temp, lp.cFileName );
				
				list_add( l, t );
			}
			//こちらはファイルサイズ
			//size+=lp.nFileSizeHigh*MAXDWORD+lp.nFileSizeLow ;
		}
	} while( FindNextFile( h, &lp ) );

	FindClose( h );
}

//パターン適合か
static int findFile_checkPtn( char* fileName, char* ptn ) {
	int ret = TRUE;

	int plen = strlen( ptn );
	int flen = strlen( fileName );

	int j = plen - 1;
	for( int i = strlen( fileName ) - 1; i >= (flen - plen); i-- ) {
		if( fileName[ i ] != ptn[ j ] ) {
			ret = FALSE;
			break;
		}

		j--;
	}
	return ret;
}

