/* ------------------------------------------------------------------------- */
/*                                                                           */
/* 文字列＿数値相互変換                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  番号    更新内容                                更新日      名前         */
/* ------------------------------------------------------------------------- */
/* 000000   新規作成                                2019/10/03  西岡  和輝   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル                                                           */
/* ------------------------------------------------------------------------- */

#include "strconv.h"

/* コンストラクタ           */
/* エラー値を正常値にセット */
StrConv:: StrConv() { 
    si_Errchk = STR_NML; 
// デバッグ時、prinfをclass宣言を通知 
#ifdef STRCONV_DEBUG
    printf("class:StrConvの使用を開始します...\n");
#endif
}

/* デストラクタ             */
StrConv::~StrConv() {
// デバッグ時、prinfをclass終了を通知 
#ifdef STRCONV_DEBUG
    printf("class:StrConvの使用を終了します...\n");
#endif
}

/* ------------------------------------------------------------------------- */
/* 関数名   : SItoS                                                          */
/* 機能名   : 数値を文字列に変換する                                         */
/* 機能概要 : SINT型の数値をSCHR型の文字列に変換                             */
/* 引数	    : SINT   : si_Num      : 変換前数値                              */
/* 戻り値   : SCHR   : 正常値      : 変換後文字列                            */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::ItoS ( SINT si_Num ) {

    /* 変数宣言 ------------------------------------------------------------ */
    SINT   si_Digit    = 0;                    /* 引数の桁数                 */
    SCHR * p_NumString = NULL;                 /* 変換後の文字列             */
    SCHR * p_Result    = NULL;                 /* 変換後の文字列(返却用)     */

    si_Digit    = digitschk( abs ( si_Num ) );             // 桁数計算
    if ( si_Num < 0 ) { si_Digit ++; }                     // 負数なら確保するメモリを増やす
    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) ,  si_Digit + 1 );               

    /* メモリ確保失敗していたら異常終了 */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS メモリ確保失敗\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;
    
    }

    p_Result = p_NumString;

    /* 負数なら一文字目に`-`を格納 */
    /* 数値を絶対値に変換          */
    if ( si_Num < 0 ) { 
        * p_NumString = '-';
        p_NumString ++;        
        si_Digit --;
    }

    strconv( ( UINT )abs( si_Num ), p_NumString , si_Digit );

    return p_Result;
}

/* ------------------------------------------------------------------------- */
/* 関数名   : ItoS                                                           */
/* 機能名   : 数値を文字列に変換する                                         */
/* 機能概要 : UINT型の数値をSCHR型の文字列に変換                             */
/* 引数	    : UINT   : ui_Num      : 変換前数値                              */
/* 戻り値   : SCHR   : 正常値      : 変換後文字列                            */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::UtoS ( UINT ui_Num  ) {

    /* 変数宣言 ------------------------------------------------------------ */
    SINT   si_Digit    = 0;                    /* 引数の桁数                 */
    SCHR * p_NumString = NULL;                 /* 変換後の文字列             */
    SCHR * p_Result    = NULL;                 /* 変換後の文字列(返却用)     */

    si_Digit    = digitschk( ui_Num );                     // 桁数計算
    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) ,  si_Digit + 1 );    

    /* メモリ確保失敗していたら異常終了 */
    if ( p_NumString == NULL ) {

#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS メモリ確保失敗\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;

    }

    p_Result = p_NumString;

    strconv( ui_Num , p_NumString , si_Digit );

    return p_Result;
}

/* ------------------------------------------------------------------------- */
/* 関数名   : ItoS                                                           */
/* 機能名   : 数値を文字列に変換する                                         */
/* 機能概要 : FLOT型の数値をSCHR型の文字列に変換                             */
/* 引数	    : FLOT   : fl_Num      : 変換前数値                              */
/* 戻り値   : SCHR   : 正常値      : 変換後文字列                            */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::FtoS ( FLOT fl_Num ){

    /* 変数宣言 ------------------------------------------------------------ */
    SINT   si_InDigit  = 0;                    /* 変換対象の整数部の桁数     */
    SINT   si_DeDigit  = 0;                    /* 変換対象の小数部の桁数     */
    SINT   si_Integer  = 0;                    /* 変換対象の整数部           */
    SINT   si_Decimal  = 0;                    /* 変換対象の小数部           */
    SCHR * p_Integer   = NULL;                 /* 変換対象の整数部の文字列   */
    SCHR * p_Decimal  = NULL;                  /* 変換対象の小数部の文字列   */
    SCHR * p_NumString = NULL;                 /* 変換後の文字列             */

    /* 整数部と小数部に振り分け */
    /* 整数部作成               */
    si_Integer = ( SINT )fl_Num;
    fl_Num    -= ( FLOT )si_Integer;
    /* 小数部作成               */
    /* 小数部が無くなるまで10進数シフト */
    for ( ; ( FLOT )( ( SINT )fl_Num ) != fl_Num ; fl_Num = fl_Num * ( FLOT )10 ){ } // 小数部が無くなるまで10進数シフト
    si_Decimal = ( SINT )fl_Num;

    /* 桁数計算 */
    si_InDigit = digitschk( si_Integer );
    si_DeDigit = digitschk( si_Decimal );

    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) , si_InDigit + 1 + si_DeDigit + 1 );    

    /* メモリ確保失敗していたら異常終了 */
    if ( p_NumString == NULL ) {

#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS メモリ確保失敗\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;

    }

    /* 整数部小数部それぞれ文字列変換 */
    p_Integer  = ItoS( si_Integer );
    p_Decimal  = ItoS( si_Decimal );

    /* 文字列コピー */
    if ( si_Integer < 0 ) { si_InDigit ++; }
    strcpy( ( char * )p_NumString , ( char * )p_Integer );
    * ( p_NumString + si_InDigit ) = '.';
    strcpy( ( char * )p_NumString + si_InDigit + 1 , ( char * )p_Decimal );
    
    /* メモリ解放 */
    free ( p_Integer );
    free ( p_Decimal );
    
    return p_NumString;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : StoI                                                           */
/* 機能名   : 文字列を数値に変換する                                         */
/* 機能概要 : SCHR型の文字列をSINT型の数値に変換                             */
/* 引数	    : SCHR * : p_NumString : 変換前文字列                            */
/* 戻り値   : SINT   : 正常値      : 変換後数値                              */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SINT   StrConv::StoI ( SCHR * p_NumString ) {
    
    /* 引数チェック -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::StoIにNULLポインタが渡されました\n");
#endif
        si_Errchk = STR_ERR; 
        return STR_ERR;
    }

    /* 変数宣言 ------------------------------------------------------------ */ 
    SINT   si_Result = 0;
    SINT   si_Index  = 1;
    SINT   si_Mag    = 1;

    /* 負数の場合 */
    if ( * p_NumString == '-' ) { 
        si_Mag = -1; 
        p_NumString ++;
    }
    /* 桁ごとの重みを作成 */
    for ( si_Index ; si_Index < strlen( ( char * )p_NumString ) ; si_Index ++ ) { si_Mag = si_Mag * 10; }

    /* 数値を文字列へ変換 */
    for ( ; si_Mag != 0 ; si_Mag = si_Mag / 10 ) {
        si_Result += ( SINT )( ( * p_NumString ) - 0x30 ) * si_Mag;
        p_NumString ++;
    }

    return si_Result;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : StoF                                                           */
/* 機能名   : 文字列を数値に変換する                                         */
/* 機能概要 : SCHR型の文字列をFLOT型の数値に変換                             */
/* 引数	    : SCHR * : p_NumString : 変換前文字列                            */
/* 戻り値   : FLOT   : 正常値      : 変換後数値                              */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
FLOT   StrConv::StoF ( SCHR * p_NumString ) {
    
    /* 引数チェック -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::StoIにNULLポインタが渡されました\n");
#endif
        si_Errchk = STR_ERR; 
        return STR_ERR;
    }

    /* 変数宣言 ------------------------------------------------------------ */ 
    FLOT   fo_Result  = 0;
    SINT   si_Strsize = 0;
    SINT   si_Index   = 1;
    SINT   si_Mag     = 1;
    SINT   si_Sign    = 1;

    /* 負数の場合 */
    if ( * p_NumString == '-' ) { 
        si_Sign = -1;
        p_NumString ++;
    }

    si_Strsize = strlen( ( char * )p_NumString );

    /* 桁ごとの重みを作成 */
    for ( si_Mag = si_Mag * si_Sign ; * ( p_NumString + si_Index ) != '.' ; si_Index ++ ) { si_Mag = si_Mag * 10; }

    /* 数値を文字列へ変換 */
    for ( si_Index = 0 ; si_Mag != 0 ; si_Mag = si_Mag / 10 , si_Index ++ ) {
        fo_Result += ( FLOT )( ( * p_NumString ) - 0x30 ) * ( FLOT ) si_Mag;
        p_NumString ++;
    }
    p_NumString ++;
    si_Index    ++;
    for ( si_Mag = 10 * si_Sign ; si_Index < si_Strsize ; si_Mag = si_Mag * 10 , si_Index ++ ) {
        fo_Result += ( FLOT )( ( * p_NumString ) - 0x30 ) / ( FLOT ) si_Mag;
        p_NumString ++;
    }

    return fo_Result;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : strconv                                                        */
/* 機能名   : 数値を文字列に変換する                                         */
/* 機能概要 :                              */
/* 引数	    : UINT   : ui_Num      : 変換前数値                              */
/* 戻り値   : SCHR   : 正常値      : 変換後文字列                            */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SINT   StrConv::strconv  ( UINT ui_Num , SCHR * p_NumString , SINT si_Digit ) {

    /* 引数チェック -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::strconvにNULLポインタが渡されました...\n");
#endif
        si_Errchk = STR_ERR; 
        return STR_ERR;
    }

    for ( si_Digit -= 1 ; si_Digit >= 0 ; si_Digit -- ) {
    
        * ( p_NumString + si_Digit ) = ( SCHR ) ( ui_Num % 10 ) + 0x30;
        ui_Num = ui_Num / 10;

    }

    return STR_NML;

}

/* ------------------------------------------------------------------------- */
/* 関数名   : digitschk                                                      */
/* 機能名   : 数字の桁数を求める                                             */
/* 機能概要 : 引数として渡された数字の桁数を、                               */
/*            10による除算により求め、returnする。                           */
/* 引数	    : SINT   : si_Num      : 桁数計算対象の数字                      */
/* 戻り値   : SINT   : 正常値      : si_Numの桁数                            */
/* 作成日   : 2019/10/03       西岡  和輝       新規作成                     */
/* ------------------------------------------------------------------------- */
SINT StrConv::digitschk( UINT si_Num ){

    /* 引数チェック -------------------------------------------------------- */
    // 引数が0の場合
    if ( si_Num == 0 ) { return 1 ; }

    /* 変数宣言 ------------------------------------------------------------ */
    SINT   si_Digit = 0;                                 /* 引数の桁数を格納 */
    
    /* 引数を10で除算し続け、0になるまでループ */
    for ( si_Digit = 0 ; si_Num != 0 ; si_Digit ++ ) {
    
        si_Num = si_Num / 10;

    }

    return si_Digit;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */