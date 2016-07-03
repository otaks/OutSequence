
#include "common.h"

int main( int argc, char *argv[] ) {

	sequence seq;	//�V�[�P���X�}
	list headerFilePathList;	//�w�b�_�t�@�C���p�X���X�g
	list sourceFilePathList;	//�\�[�X�t�@�C���p�X���X�g

	if( argc != 1 ) {
		return -1;
	}
	
	//������
	init( argv[1], headerFilePathList, sourceFilePathList, &seq );

	//���
	analyze( headerFilePathList, sourceFilePathList, seq );

	//�o��
	output( seq );

	//�I������
	fin( headerFilePathList, sourceFilePathList, &seq );

	return 0;
}

//������
static void init( char* dir, list headerFilePathList, list sourceFilePathList, sequence* seq ) {

	headerFilePathList = list_create( STRING );
	sourceFilePathList = list_create( STRING );

	memset( seq, 0x00, sizeof( seq ) );
	seq->moduleNameList = list_create( STRING );
	seq->signalList = list_create( STRUCT_SIGNAL );

	//�edir���


}