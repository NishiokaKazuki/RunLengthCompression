/* ------------------------------------------------------------------------- */
/*                                                                           */
/* �t�@�C������                                                              */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2020/01/24  ����  �a�P   */
/* 000001   �X�V                                    2020/01/26  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#include "FileUtils.h"

FileUtils::FileUtils() {
    /* �N���X�ϐ������� */
    ulfileSize = 0;
    scerrCode    = SYSTEMCODE_SUCCSES;
    scerrMessage = NULL;
    fp           = NULL;
}

FileUtils::~FileUtils() {
    /* ��������� */
    Close();
    FreeMemory();
    freeErrMsg();
}

/* ------------------------------------------------------------------------- */
/* �֐���   : OpenReadMode                                                   */
/* �@�\��   : �t�@�C���ǂݍ���                                               */
/* �@�\�T�v : �t�@�C����ǂݎ�胂�[�h�œǂݍ��݁A                           */
/*            ���̐擪�A�h���X���N���X�ϐ�fp�Ɋi�[����                       */  
/* ����     : SCHR* : scFilePath : �t�@�C���ւ̃p�X                          */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::OpenReadMode ( SCHR* scFilePath ) {
    /* �����`�F�b�N                                                          */
    if ( fp != NULL  ) { Close(); }     /* ���Ƀt�@�C�����J���Ă���ꍇ      */
    if ( !CheckErr() ) { return;  }

    open( scFilePath,  ( SCHR* )"rb" );

    setFileSize();
}

/* ------------------------------------------------------------------------- */
/* �֐���   : OpenReadMode                                                   */
/* �@�\��   : �t�@�C���ǂݍ���                                               */
/* �@�\�T�v : �t�@�C�����������݃��[�h�œǂݍ��݂������͐V�K�쐬���A         */
/*            ���̐擪�A�h���X���N���X�ϐ�fp�Ɋi�[����                       */
/* ����     : SCHR* : scFileName : �t�@�C���ւ̃p�X                          */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::OpenWriteMode ( SCHR* scFilePath ) {
    /* �����`�F�b�N                                                          */
    if ( fp != NULL  ) { Close(); }     /* ���Ƀt�@�C�����J���Ă���ꍇ      */
    if ( !CheckErr() ) { return;  }

    open( scFilePath,  ( SCHR* )"wb+" );
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Close                                                          */
/* �@�\��	: �t�@�C���N���[�Y                                               */
/* �@�\�T�v	: �N���X�ϐ�fp���J���Ă���t�@�C�������                       */
/* �߂�l	: ULNG* : ����       : �t�@�C���T�C�Y                            */
/*          :       : ���s       : NULL                                      */
/* �쐬��	: 2020/01/24		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void  FileUtils::Close (){
    /* �����`�F�b�N                                                          */
    if ( fp == NULL  ) { return; }      /* ���݃t�@�C�����J���Ă��Ȃ��ꍇ    */

    fclose( fp );
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Out                                                            */
/* �@�\��	: �t�@�C���o��                                                   */
/* �@�\�T�v	: �N���X�ϐ�fp���J���Ă���t�@�C���Ɉ���scStr���o��              */
/*            �p�X���w�肳��Ă���ꍇ�͐V���Ƀt�@�C�����J��                 */
/* ����		: SCHR* : scFileName : �t�@�C���ւ̃p�X                          */
/* ����		: SCHR* : scStr      : �o�͕�����                                */
/* �쐬��	: 2020/01/24		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void  FileUtils::Out ( SCHR* scFilePath, SCHR* scStr, ULNG ulFileSize ) {
    /* �����`�F�b�N                                                          */
    if ( !CheckErr() ) { return; }

    /* �p�X���w�肳��Ă���ꍇ */
    if ( scFilePath != NULL ) {
        OpenWriteMode ( scFilePath );
    }
    fwrite( ( const char* )scStr, sizeof( SCHR ), ulFileSize , fp );
}

/* ------------------------------------------------------------------------- */
/* �֐���	: GetSize                                                        */
/* �@�\��	: �t�@�C���T�C�Y����                                             */
/* �@�\�T�v	: �N���X�ϐ�fp����t�@�C���T�C�Y���擾��return����               */
/* �߂�l	: ULNG* : ����       : �t�@�C���T�C�Y                            */
/*          :       : ���s       : NULL                                      */
/* �쐬��	: 2020/01/24		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
ULNG  FileUtils::GetFileSize() {
    /* �����`�F�b�N                                                          */
    if ( fp == NULL  ) { setErr(); }
    if ( !CheckErr() ) { return 0; }
    
    return ulfileSize;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : GetMemory                                                      */
/* �@�\��   : �t�@�C�����e�擾                                               */
/* �@�\�T�v : �������ɏ������܂ꂽ�t�@�C���̃o�C�i�����擾                   */
/* �߂�l   : SCHR* : ����       : �t�@�C�����e                              */
/*          :       : ���s       : NULL                                      */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR* FileUtils::GetMemory() {
    /* �G���[�`�F�b�N                                                        */
    if ( scfileOnMem == NULL ) { return NULL; }
    if ( !CheckErr() )         { return NULL; }
    
    return scfileOnMem;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : SetMemory                                                      */
/* �@�\��   : �t�@�C�����烁������������                                     */
/* �@�\�T�v : �N���X�ϐ�fp������e���擾���A�������ɃR�s�[����               */
/* �߂�l   : SCHR* : ����       : �t�@�C�����e                              */
/*          :       : ���s       : NULL                                      */
/* �쐬��   : 2020/01/24        ����  �a�P      �V�K�쐬                     */
/*          : 2020/01/26        ����  �a�P      �X�V                         */
/* ------------------------------------------------------------------------- */
SCHR* FileUtils::SetMemory() {
    /* �G���[�`�F�b�N                                                        */
    if ( fp == NULL  ) { setErr(); }
    if ( !CheckErr() ) { return NULL; }

    FreeMemory();

    scfileOnMem = ( SCHR* )malloc( sizeof( SCHR ) * ulfileSize ); /* �������m��  */
    fread ( scfileOnMem, sizeof( SCHR ), ulfileSize, fp );   /* �������֏������� */
    
    return scfileOnMem;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : FreeMemory                                                     */
/* �@�\��   : �t�@�C�����珑�����܂ꂽ�������̉��                           */
/* �@�\�T�v : �N���X�ϐ�scfileOnMem���������������                          */
/* �߂�l   : SCHR* : ����       : �t�@�C�����e                              */
/*          :       : ���s       : NULL                                      */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::FreeMemory() {
    /* �G���[�`�F�b�N                                                        */
    if ( scfileOnMem == NULL ) { return; }

    free( scfileOnMem );
    scfileOnMem == NULL;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : CheckErr                                                       */
/* �@�\��   : �G���[���������Ă��邩�̃`�F�b�N                               */
/* �@�\�T�v : �G���[���������Ă���ꍇfalse�A���Ă��Ȃ��ꍇ��true��return    */
/* �߂�l	: SCHR  : ����       : false                                     */
/*          :       : ������     : true                                      */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR  FileUtils::CheckErr() {

    // wip:�G���[�R�[�h�̃o�����G�[�V����
    switch ( scerrCode ) {
    
    case SYSTEMCODE_SUCCSES:
        return true;
    
    case SYSTEMCODE_FILED:
    default:
        return false;
    }
}

/* ------------------------------------------------------------------------- */
/* �֐���   : GetErrMsg                                                      */
/* �@�\��   : �G���[���b�Z�[�W�̎擾                                         */
/* �@�\�T�v : �N���X�ϐ�scerrMessage�̎擾(�G���[�������̏ꍇNULL)           */
/* �߂�l	: SCHR  :            : scerrMessage                              */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR* FileUtils::GetErrMsg() {
    return scerrMessage;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Open      													 */
/* �@�\��	: �t�@�C���ǂݍ���												 */
/* �@�\�T�v	: �t�@�C����ǂݍ��݁A���̐擪�A�h���X���N���X�ϐ�fp�Ɋi�[����   */
/* ����		: SCHR* : scFileName : �t�@�C���ւ̃p�X                          */
/* �쐬��	: 2020/01/24		�����@�a�P		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void  FileUtils::open ( SCHR* scFilePath, SCHR* scOpenMode ) {
    /* �ϐ��錾                                                              */
    errno_t	 err   = NULL;		        /* �G���[                            */

    /* �p�X����t�@�C�����J���A���ۂ̊m�F                                    */
    err = fopen_s( &fp , ( char * )scFilePath , ( char* )scOpenMode );
	if ( err != NULL ) {
        setErrMsg( ( SCHR* )"cannot open file" );
        setErr();
	}

    return;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : setSize                                                        */
/* �@�\��   : �t�@�C���T�C�Y�̊i�[                                           */
/* �@�\�T�v : �N���X�ϐ�fp����t�@�C���T�C�Y���擾���A                       */
/*          : �N���X�ϐ�ulfileSize�Ɋi�[                                     */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::setFileSize() {
    if ( fp == NULL  ) { setErr(); }
    if ( !CheckErr() ) { return;   }

    fseek( fp , 0 , SEEK_END );
	ulfileSize = ftell( fp );
	fseek( fp , 0 , SEEK_SET );
}

/* ------------------------------------------------------------------------- */
/* �֐���   : setErr                                                         */
/* �@�\��   : �G���[�������̏���                                             */
/* �@�\�T�v : �N���X�ϐ�scerrCode�ɃG���[�R�[�h���i�[                        */ 
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::setErr() {
    // wip:�G���[�R�[�h�̃o�����G�[�V�����̑����ɂ��킹�Ĉ����̎擾?
    scerrCode = SYSTEMCODE_FILED;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : setErrMsg                                                      */
/* �@�\��   : �G���[�������̏���                                             */
/* �@�\�T�v : �N���X�ϐ�scerrMessage�ɃG���[���e���i�[                       */
/* ����		: SCHR* : scErrMessage : �G���[���e                              */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::setErrMsg( SCHR* scErrMessage ) {
    /* �G���[�`�F�b�N                                                        */
    if ( scErrMessage == NULL ) { return; }
    setErr();
    freeErrMsg();
    scerrMessage = scErrMessage;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : freeErrMsg                                                     */
/* �@�\��   : �G���[���b�Z�[�W�̍폜                                         */
/* �@�\�T�v : �N���X�ϐ�scerrMessage�̃��������                             */
/* �쐬��   : 2020/01/26        ����  �a�P      �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
void  FileUtils::freeErrMsg() {
    /* �G���[�`�F�b�N                                                        */
    if ( scerrMessage == NULL ) { return; }
    free( scerrMessage );
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */