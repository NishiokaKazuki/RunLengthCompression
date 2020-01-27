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
#include "RunLength.h"
#include "FileUtils.h"

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾                                                          */
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

    /* �ϐ��錾 ------------------------------------------------------------ */
    UCHR  ucFigureCnt = 0;
    ULNG  ulStrIdx    = 0;
    ULNG  ulAfterSize = 0;
    COMP* RtPt        = NULL;
    COMP* CompPt      = NULL;

    if ( ulfileSize == 0 ) {
        ulfileSize = strlen( ( char* )scStr );
    }

    // �擪�Ƀt�@�C���T�C�Y�i�[�̂��� +sizeof( ULNG )
    CompPt = RtPt = ( COMP* )calloc( sizeof( COMP ), ulfileSize + sizeof( ULNG ) + 1 );
    setFileSize( &CompPt );
    if ( !cheakErr() ) { return NULL; }

    /* ���������O�X���k �又��        */
    /* ���k�ΏۏI�[�A�N�Z�X�܂Ń��[�v */
    for ( ; ulStrIdx < ulfileSize; CompPt++ ) {
        
        for ( 
            ucFigureCnt = 0, CompPt->scFigure = *scStr; true; 
            ulStrIdx++, 
            ucFigureCnt++, 
            scStr++
            ) {
            if ( CompPt->scFigure != *scStr         ) { break; } // ��������v���Ȃ��ꍇ
            if ( !( ucFigureCnt < FIGURECOUNT_MAX ) ) { break; } // unsigned char�̕\���\���𒴂���ꍇ
            if ( !( ulStrIdx    <  ulfileSize     ) ) { break; } // ������̏I�[�ɃA�N�Z�X�����ꍇ
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