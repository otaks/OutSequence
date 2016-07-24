
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "findFile.h"
#include "analyzeCtl.h"
#include<conio.h>

static void init( char* dir, list* headerFilePathList, list* sourceFilePathList, sequence* seq );
static void fin( list headerFilePathList, list sourceFilePathList, sequence* seq );
static void output( char* dirName, sequence* seq );

int main( int argc, char *argv[] ) {

	sequence seq;	//�V�[�P���X�}
	list headerFilePathList;	//�w�b�_�t�@�C���p�X���X�g
	list sourceFilePathList;	//�\�[�X�t�@�C���p�X���X�g

#if _DEBUG
	printf( "debug timing. press any key." );
	getch();
	printf( "\n" );
#endif

	if( argc != 2 ) {
		return -1;
	}
	
	//������
	char t[ 1000 ] = { 0 };
	sprintf(t, "%s\\", argv[1]);
	//init( argv[1], &headerFilePathList, &sourceFilePathList, &seq );
	init( t, &headerFilePathList, &sourceFilePathList, &seq );

	//���
	analyzeCtl_analyze( headerFilePathList, sourceFilePathList, &seq );

	//�o��
	output( argv[ 1 ], &seq );

	//�I������
	fin( headerFilePathList, sourceFilePathList, &seq );

	//printf( "�J�����g�f�B���N�g����result.txt���o�͂��܂����B" );
	printf( "result.txt is generated in the current dirctory.\n" );
	return 0;
}

//������
static void init( char* dir, list* headerFilePathList, list* sourceFilePathList, sequence* seq ) {

	*headerFilePathList = list_create( STRING );
	*sourceFilePathList = list_create( STRING );

	memset( seq, 0x00, sizeof( seq ) );
	seq->moduleNameList = list_create( STRING );

	seq->signalList = list_create( STRUCT_SIGNAL );

	//�w�b�_�t�@�C�����X�g�擾
	findFile_find( ".h", dir, *headerFilePathList );
	//�\�[�X�t�@�C�����X�g�擾
	findFile_find( ".c", dir, *sourceFilePathList );
}

//�I������
static void fin( list headerFilePathList, list sourceFilePathList, sequence* seq ) {
	list_delete( headerFilePathList );
	list_delete( sourceFilePathList );
	list_delete( seq->moduleNameList );
	list_delete( seq->signalList );
}


static void output( char* dirName, sequence* seq ) {

	FILE *fp;

	if( ( fp = fopen( "result.txt", "w" ) ) == NULL ) {
		printf( "file open error!!\n" );
		exit( EXIT_FAILURE );
	}

	fprintf(fp, "@startuml\n");
	for( int i = 0; i < list_getNum( seq->moduleNameList ); i++ ) {
		fprintf( fp, "actor %s\n", list_getCharNode( seq->moduleNameList, i ) );
	}
	for( int i = 0; i < list_getNum( seq->signalList ); i++ ) {
		signal* s = ( signal* )list_getNode( seq->signalList, i );
		fprintf( fp, "%s %s %s : %s\n", s->sendModuleName, ((s->isReq==1)?"->":"-->"), s->receiveModuleName, s->name );
	}
	fprintf( fp, "@enduml\n" );

	fclose( fp );
}

