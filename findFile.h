#pragma once

#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )

#include "list.h"

/**
 * �t�@�C�����X�g�擾�B
 * lpszDir�z��(�T�u�t�H���_�܂�)���Ńt�@�C������
 * ptn�ŏI���S�t�@�C���̃t���p�X��l�Ɋi�[����B
 * 
 * @param ptn �g���q
 * @param lpszDir �e�f�B���N�g��
 * @param l �i�[�惊�X�g
*/
void findFile_find( char * ptn, char* lpszDir, list l );

