#pragma once
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* �t�@�C������                                                              */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2020/01/24  ����  �a�P   */
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

#define SYSTEMCODE_FILED   (   0 )
#define SYSTEMCODE_SUCCSES (   1 )

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

/* ------------------------------------------------------------------------- */
/* �\���̒�`                                                                */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* �O���[�o���ϐ�                                                            */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
/* ------------------------------------------------------------------------- */

class FileUtils {

public:
    FileUtils();        /* �R���X�g���N�^ */
    ~FileUtils();       /* �f�X�g���N�^   */
    /* �ϐ� */
    
    /* �֐� */
    void  OpenReadMode  ( SCHR* );
    void  OpenWriteMode ( SCHR* );
    void  Close         ();
    void  Out           ( SCHR*, SCHR* , ULNG ); 
    ULNG  GetFileSize   ();
    SCHR* GetMemory     ();
    SCHR* SetMemory     ();
    void  FreeMemory    ();
    SCHR  CheckErr      ();
    SCHR* GetErrMsg     ();

private:
    /* �ϐ� */
    ULNG  ulfileSize;   /* �t�@�C���T�C�Y                         */
    SCHR  scerrCode;    /* �G���[�R�[�h                           */
    SCHR* scerrMessage; /* �G���[���e                             */
    SCHR* scfileOnMem;  /* �������ɏ������܂ꂽ�t�@�C���̃o�C�i�� */
    FILE* fp;           /* �t�@�C���|�C���^                       */

    /* �֐� */
    void  open        ( SCHR*, SCHR* );
    void  setFileSize ();
    void  setErr      ();
    void  setErrMsg   ( SCHR* );
    void  freeErrMsg  ();
};