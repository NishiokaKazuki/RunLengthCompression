#pragma once
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* 文字列＿数値相互変換                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/10/01  西岡  和輝   */
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
/* エラー値 */
#define STR_ERR       ( -1 ) // 異常発生
#define STR_NML       (  0 ) // 正常終了

/* デバック時、下のdefineを有効 */
// #define STRCONV_DEBUG (  0 ) // デバッグ可否

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
typedef double         DBLE;
typedef float          FLOT;


class StrConv {

public:
    StrConv();                /* コンストラクタ */
    ~StrConv();               /* デストラクタ   */

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
