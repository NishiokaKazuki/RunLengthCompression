#pragma once
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ������Q���l���ݕϊ�                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/10/01  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
/* �萔��`	                                                                 */
/* ------------------------------------------------------------------------- */
/* �G���[�l */
#define STR_ERR       ( -1 ) // �ُ픭��
#define STR_NML       (  0 ) // ����I��

/* �f�o�b�N���A����define��L�� */
// #define STRCONV_DEBUG (  0 ) // �f�o�b�O��

/* ------------------------------------------------------------------------- */
/* typedef�錾                                                               */
/* ------------------------------------------------------------------------- */

typedef signed   int   SINT;
typedef unsigned int   UINT;
typedef signed   long  SLNG;
typedef unsigned long  ULNG;
typedef signed   short SSHT;
typedef unsigned short USHT;
typedef signed   char  SCHR;
typedef unsigned char  UCHR;
typedef double         DBLE;
typedef float          FLOT;


class StrConv {

public:
    StrConv();                /* �R���X�g���N�^ */
    ~StrConv();               /* �f�X�g���N�^   */

    SCHR * ItoS     ( SINT   );
    SCHR * UtoS     ( UINT   );
    SCHR * FtoS     ( FLOT   );
    SINT   StoI     ( SCHR * );
    FLOT   StoF     ( SCHR * );
    SINT   si_Errchk;
    
private:
    SINT   digitschk( UINT   );
    SINT   strconv  ( UINT   , SCHR * , SINT   );

};
