#pragma once
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ランレングス符号化                                                        */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2020/01/24  西岡  和輝   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
/* 定数定義	                                                                 */
/* ------------------------------------------------------------------------- */

#define SYSTEMCODE_FILED   (   0 )
#define SYSTEMCODE_SUCCSES (   1 )

#define FIGURECOUNT_MAX    ( 255 )

#define EXTENSION          ( ".kazuzip" )

/* デバック時、下のdefineを有効 */
// #define RUN_LENGTH_DEBUG (  0 ) // デバッグ可否

/* ------------------------------------------------------------------------- */
/* typedef宣言                                                               */
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
/* 構造体定義                                                                */
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