#pragma once

#include "common.h"

/**
 * �֐������X�g�擾�B
 * �w�b�_�[�t�@�C������O���[�o���֐����A
 * �\�[�X�t�@�C������X�^�e�B�b�N�֐������擾����B
 *
 * @param headerFilePathList �w�b�_�t�@�C���p�X���X�g
 * @param sourceFilePathList �\�[�X�t�@�C���p�X���X�g
 * @param funcs �֐����X�g
 */
void analyze_getFuncs( list headerFilePathList, list sourceFilePathList, list funcs );

/**
* �Ăяo���֐����X�g�擾�B
* �֐������X�g�����Ƀ\�[�X�t�@�C������A
* �֐����̌Ăяo���֐����X�g���擾����B
*
* @param headerFilePathList �w�b�_�t�@�C���p�X���X�g
* @param funcs �֐����X�g
*/
void analyze_getCallFuncs( sourceFilePathList, funcs );

/**
* ���W���[�����X�g�쐬�B
* �V�[�P���X�}�Ƀ��W���[�����X�g���쐬����B
*
* @param seq �V�[�P���X�}
* @param funcs �֐����X�g
*/
void analyze_createModuleList( sequence* seq, list funcs );

/**
* �M���ǉ��B
* �V�[�P���X�}�ɐM����ǉ�����B
*
* @param seq �V�[�P���X�}
* @param funcs �֐����X�g
*/
void analyze_addSignal( sequence* seq, list funcs );

