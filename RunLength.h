#pragma once
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ���������O�X������                                                        */
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

#define FIGURECOUNT_MAX    ( 255 )

#define EXTENSION          ( ".kazuzip" )

/* �f�o�b�N���A����define��L�� */
// #define RUN_LENGTH_DEBUG (  0 ) // �f�o�b�O��

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

typedef struct _compression {
    SCHR scFigure;
    UCHR ucFigureCnt;
}COMP;

class RunLength {

public:
    RunLength();
    ~RunLength();
    SCHR  scErrCode;
    void  FileCompression    ( SCHR* );
    void  FileDeCompression  ( SCHR* );
    void* StringCompression  ( SCHR* );
    SCHR* StringDeCompression( void* );

private:
    ULNG  ulfileSize;
    SCHR* inExtension ( SCHR* );
    SCHR* outExtension( SCHR* );
    void  setFileSize ( COMP**);
    void  getFileSize ( COMP**);
    void  setErr  ();
    SCHR  cheakErr();
};