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
#include "RunLength.h"
#include "FileUtils.h"

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言                                                          */
/* ------------------------------------------------------------------------- */


RunLength::RunLength( ) {
    ulfileSize = 0;
    scErrCode = SYSTEMCODE_SUCCSES;
}

RunLength::~RunLength( ) {

}

void  RunLength::FileCompression  ( SCHR* scFileName ) {
    SCHR*     scStr       = NULL;
    SCHR*     scCompPt    = NULL;
    FileUtils file;

    file.OpenReadMode( scFileName );
    if ( !( file.CheckErr() ) ) { return; }

    scStr      = file.SetMemory();
    if ( !( file.CheckErr() ) ) { return; }

    ulfileSize = file.GetFileSize();
    scCompPt = ( SCHR* )StringCompression( scStr );
    file.Out( inExtension( scFileName ), scCompPt, ulfileSize );
    if ( !( file.CheckErr() ) ) { return; }

    file.Close();
    free( scCompPt );
}

void  RunLength::FileDeCompression ( SCHR* scFileName ) {
    SCHR*     scStr = NULL;
    FileUtils file;

    file.OpenReadMode( scFileName );
    scStr = StringDeCompression( file.SetMemory() );
    file.Out( outExtension( scFileName ), scStr, ulfileSize);

    file.Close();
    free( scStr );
}

void* RunLength::StringCompression( SCHR* scStr ) {
    if ( scStr == NULL ) { setErr( ); }
    if ( !cheakErr()   ) { return NULL; }

    /* 変数宣言 ------------------------------------------------------------ */
    UCHR  ucFigureCnt = 0;
    ULNG  ulStrIdx    = 0;
    ULNG  ulAfterSize = 0;
    COMP* RtPt        = NULL;
    COMP* CompPt      = NULL;

    if ( ulfileSize == 0 ) {
        ulfileSize = strlen( ( char* )scStr );
    }

    // 先頭にファイルサイズ格納のため +sizeof( ULNG )
    CompPt = RtPt = ( COMP* )calloc( sizeof( COMP ), ulfileSize + sizeof( ULNG ) + 1 );
    setFileSize( &CompPt );
    if ( !cheakErr() ) { return NULL; }

    /* ランレングス圧縮 主処理        */
    /* 圧縮対象終端アクセスまでループ */
    for ( ; ulStrIdx < ulfileSize; CompPt++ ) {
        
        for ( 
            ucFigureCnt = 0, CompPt->scFigure = *scStr; true; 
            ulStrIdx++, 
            ucFigureCnt++, 
            scStr++
            ) {
            if ( CompPt->scFigure != *scStr         ) { break; } // 文字が一致しない場合
            if ( !( ucFigureCnt < FIGURECOUNT_MAX ) ) { break; } // unsigned charの表現可能数を超える場合
            if ( !( ulStrIdx    <  ulfileSize     ) ) { break; } // 文字列の終端にアクセスした場合
        }

        CompPt->ucFigureCnt = ucFigureCnt;
        ulAfterSize += sizeof( COMP );
    }
    ulfileSize = ulAfterSize;

    return RtPt;
}

SCHR* RunLength::StringDeCompression( void* targetPt ){
    if ( targetPt == NULL ) { setErr( ); }
    if ( !cheakErr() )      { return NULL; }

    ULNG  ulStrIdx = 0;
    SCHR* scStr    = NULL;
    SCHR* scRtPt   = NULL;
    COMP* CompPt   = ( COMP* )targetPt;
    
    getFileSize( &CompPt );
    scRtPt = scStr = ( SCHR* )calloc( sizeof( SCHR ), ulfileSize );

    for ( ulStrIdx = 0; ulStrIdx < ulfileSize; ulStrIdx++, CompPt++ ) {
        memset( scStr, CompPt->scFigure, CompPt->ucFigureCnt );
        scStr    += CompPt->ucFigureCnt;
        ulStrIdx += CompPt->ucFigureCnt;
    }

    return scRtPt;
}

void RunLength::setFileSize( COMP** CompPt ) {
    if ( CompPt == NULL ) { setErr(); }
    if ( !cheakErr()    ) { return;   }

    *( ULNG* )*CompPt = ulfileSize;
    *CompPt += sizeof( ULNG ) / sizeof( COMP );
}

void RunLength::getFileSize( COMP** CompPt ) {
    if ( CompPt == NULL ) { setErr(); }
    if ( !cheakErr()    ) { return;   }

    ulfileSize = *( ULNG* )*CompPt;
    *CompPt += sizeof( ULNG ) / sizeof( COMP );
}

SCHR* RunLength::inExtension( SCHR* scFileName ) {
    SCHR* scFileNametmp = NULL;

    scFileNametmp = ( SCHR* )calloc( sizeof( SCHR ), strlen( ( char* )scFileName ) + strlen( EXTENSION ) );

    strcpy( ( char* )scFileNametmp, ( char* )scFileName );

    strcat( ( char* )scFileNametmp , EXTENSION );
    return scFileNametmp;
}

SCHR* RunLength::outExtension( SCHR* scFileName ) {
    SCHR* scFileNametmp = NULL;
    UCHR  ucNewNameSize = strlen( ( char* )scFileName ) - strlen( EXTENSION );

    scFileNametmp = ( SCHR* )calloc( sizeof( SCHR ), ucNewNameSize + 1 );
    strncpy( ( char* )scFileNametmp, ( char* )scFileName, ucNewNameSize );
    
    return scFileNametmp;
}

void  RunLength::setErr  () { scErrCode = SYSTEMCODE_FILED; }
SCHR  RunLength::cheakErr() { return scErrCode; }


/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */