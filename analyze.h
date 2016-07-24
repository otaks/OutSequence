#pragma once

#include "common.h"

/**
 * �֐������X�g�擾�B
 * �w�b�_�[�t�@�C������֐������擾����B
 *
 * @param headerFilePathList �w�b�_�t�@�C���p�X���X�g
 * @param funcs �֐����X�g
 */
void analyze_getFuncs( list headerFilePathList, list funcs );

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
* �M���ǉ��B
* �V�[�P���X�}�ɐM����ǉ�����B
*
* @param seq �V�[�P���X�}
* @param funcs �֐����X�g
*/
void analyze_addSignal( sequence* seq, list funcs );

