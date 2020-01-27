/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ������Q���l���ݕϊ�                                                      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*  �ԍ�    �X�V���e                                �X�V��      ���O         */
/* ------------------------------------------------------------------------- */
/* 000000   �V�K�쐬                                2019/10/03  ����  �a�P   */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��                                                           */
/* ------------------------------------------------------------------------- */

#include "strconv.h"

/* �R���X�g���N�^           */
/* �G���[�l�𐳏�l�ɃZ�b�g */
StrConv:: StrConv() { 
    si_Errchk = STR_NML; 
// �f�o�b�O���Aprinf��class�錾��ʒm 
#ifdef STRCONV_DEBUG
    printf("class:StrConv�̎g�p���J�n���܂�...\n");
#endif
}

/* �f�X�g���N�^             */
StrConv::~StrConv() {
// �f�o�b�O���Aprinf��class�I����ʒm 
#ifdef STRCONV_DEBUG
    printf("class:StrConv�̎g�p���I�����܂�...\n");
#endif
}

/* ------------------------------------------------------------------------- */
/* �֐���   : SItoS                                                          */
/* �@�\��   : ���l�𕶎���ɕϊ�����                                         */
/* �@�\�T�v : SINT�^�̐��l��SCHR�^�̕�����ɕϊ�                             */
/* ����	    : SINT   : si_Num      : �ϊ��O���l                              */
/* �߂�l   : SCHR   : ����l      : �ϊ��㕶����                            */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::ItoS ( SINT si_Num ) {

    /* �ϐ��錾 ------------------------------------------------------------ */
    SINT   si_Digit    = 0;                    /* �����̌���                 */
    SCHR * p_NumString = NULL;                 /* �ϊ���̕�����             */
    SCHR * p_Result    = NULL;                 /* �ϊ���̕�����(�ԋp�p)     */

    si_Digit    = digitschk( abs ( si_Num ) );             // �����v�Z
    if ( si_Num < 0 ) { si_Digit ++; }                     // �����Ȃ�m�ۂ��郁�����𑝂₷
    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) ,  si_Digit + 1 );               

    /* �������m�ێ��s���Ă�����ُ�I�� */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS �������m�ێ��s\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;
    
    }

    p_Result = p_NumString;

    /* �����Ȃ�ꕶ���ڂ�`-`���i�[ */
    /* ���l���Βl�ɕϊ�          */
    if ( si_Num < 0 ) { 
        * p_NumString = '-';
        p_NumString ++;        
        si_Digit --;
    }

    strconv( ( UINT )abs( si_Num ), p_NumString , si_Digit );

    return p_Result;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : ItoS                                                           */
/* �@�\��   : ���l�𕶎���ɕϊ�����                                         */
/* �@�\�T�v : UINT�^�̐��l��SCHR�^�̕�����ɕϊ�                             */
/* ����	    : UINT   : ui_Num      : �ϊ��O���l                              */
/* �߂�l   : SCHR   : ����l      : �ϊ��㕶����                            */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::UtoS ( UINT ui_Num  ) {

    /* �ϐ��錾 ------------------------------------------------------------ */
    SINT   si_Digit    = 0;                    /* �����̌���                 */
    SCHR * p_NumString = NULL;                 /* �ϊ���̕�����             */
    SCHR * p_Result    = NULL;                 /* �ϊ���̕�����(�ԋp�p)     */

    si_Digit    = digitschk( ui_Num );                     // �����v�Z
    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) ,  si_Digit + 1 );    

    /* �������m�ێ��s���Ă�����ُ�I�� */
    if ( p_NumString == NULL ) {

#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS �������m�ێ��s\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;

    }

    p_Result = p_NumString;

    strconv( ui_Num , p_NumString , si_Digit );

    return p_Result;
}

/* ------------------------------------------------------------------------- */
/* �֐���   : ItoS                                                           */
/* �@�\��   : ���l�𕶎���ɕϊ�����                                         */
/* �@�\�T�v : FLOT�^�̐��l��SCHR�^�̕�����ɕϊ�                             */
/* ����	    : FLOT   : fl_Num      : �ϊ��O���l                              */
/* �߂�l   : SCHR   : ����l      : �ϊ��㕶����                            */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SCHR * StrConv::FtoS ( FLOT fl_Num ){

    /* �ϐ��錾 ------------------------------------------------------------ */
    SINT   si_InDigit  = 0;                    /* �ϊ��Ώۂ̐������̌���     */
    SINT   si_DeDigit  = 0;                    /* �ϊ��Ώۂ̏������̌���     */
    SINT   si_Integer  = 0;                    /* �ϊ��Ώۂ̐�����           */
    SINT   si_Decimal  = 0;                    /* �ϊ��Ώۂ̏�����           */
    SCHR * p_Integer   = NULL;                 /* �ϊ��Ώۂ̐������̕�����   */
    SCHR * p_Decimal  = NULL;                  /* �ϊ��Ώۂ̏������̕�����   */
    SCHR * p_NumString = NULL;                 /* �ϊ���̕�����             */

    /* �������Ə������ɐU�蕪�� */
    /* �������쐬               */
    si_Integer = ( SINT )fl_Num;
    fl_Num    -= ( FLOT )si_Integer;
    /* �������쐬               */
    /* �������������Ȃ�܂�10�i���V�t�g */
    for ( ; ( FLOT )( ( SINT )fl_Num ) != fl_Num ; fl_Num = fl_Num * ( FLOT )10 ){ } // �������������Ȃ�܂�10�i���V�t�g
    si_Decimal = ( SINT )fl_Num;

    /* �����v�Z */
    si_InDigit = digitschk( si_Integer );
    si_DeDigit = digitschk( si_Decimal );

    p_NumString = ( SCHR * )calloc( sizeof( SCHR ) , si_InDigit + 1 + si_DeDigit + 1 );    

    /* �������m�ێ��s���Ă�����ُ�I�� */
    if ( p_NumString == NULL ) {

#ifdef STRCONV_DEBUG
        printf("StrConv::ItoS �������m�ێ��s\n");
#endif
        si_Errchk = STR_ERR;
        return NULL;

    }

    /* ���������������ꂼ�ꕶ����ϊ� */
    p_Integer  = ItoS( si_Integer );
    p_Decimal  = ItoS( si_Decimal );

    /* ������R�s�[ */
    if ( si_Integer < 0 ) { si_InDigit ++; }
    strcpy( ( char * )p_NumString , ( char * )p_Integer );
    * ( p_NumString + si_InDigit ) = '.';
    strcpy( ( char * )p_NumString + si_InDigit + 1 , ( char * )p_Decimal );
    
    /* ��������� */
    free ( p_Integer );
    free ( p_Decimal );
    
    return p_NumString;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : StoI                                                           */
/* �@�\��   : ������𐔒l�ɕϊ�����                                         */
/* �@�\�T�v : SCHR�^�̕������SINT�^�̐��l�ɕϊ�                             */
/* ����	    : SCHR * : p_NumString : �ϊ��O������                            */
/* �߂�l   : SINT   : ����l      : �ϊ��㐔�l                              */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SINT   StrConv::StoI ( SCHR * p_NumString ) {
    
    /* �����`�F�b�N -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::StoI��NULL�|�C���^���n����܂���\n");
#endif
        si_Errchk = STR_ERR; 
        return STR_ERR;
    }

    /* �ϐ��錾 ------------------------------------------------------------ */ 
    SINT   si_Result = 0;
    SINT   si_Index  = 1;
    SINT   si_Mag    = 1;

    /* �����̏ꍇ */
    if ( * p_NumString == '-' ) { 
        si_Mag = -1; 
        p_NumString ++;
    }
    /* �����Ƃ̏d�݂��쐬 */
    for ( si_Index ; si_Index < strlen( ( char * )p_NumString ) ; si_Index ++ ) { si_Mag = si_Mag * 10; }

    /* ���l�𕶎���֕ϊ� */
    for ( ; si_Mag != 0 ; si_Mag = si_Mag / 10 ) {
        si_Result += ( SINT )( ( * p_NumString ) - 0x30 ) * si_Mag;
        p_NumString ++;
    }

    return si_Result;

}

/* ------------------------------------------------------------------------- */
/* �֐���   : StoF                                                           */
/* �@�\��   : ������𐔒l�ɕϊ�����                                         */
/* �@�\�T�v : SCHR�^�̕������FLOT�^�̐��l�ɕϊ�                             */
/* ����	    : SCHR * : p_NumString : �ϊ��O������                            */
/* �߂�l   : FLOT   : ����l      : �ϊ��㐔�l                              */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
FLOT   StrConv::StoF ( SCHR * p_NumString ) {
    
    /* �����`�F�b�N -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::StoI��NULL�|�C���^���n����܂���\n");
#endif
        si_Errchk = STR_ERR; 
        return STR_ERR;
    }

    /* �ϐ��錾 ------------------------------------------------------------ */ 
    FLOT   fo_Result  = 0;
    SINT   si_Strsize = 0;
    SINT   si_Index   = 1;
    SINT   si_Mag     = 1;
    SINT   si_Sign    = 1;

    /* �����̏ꍇ */
    if ( * p_NumString == '-' ) { 
        si_Sign = -1;
        p_NumString ++;
    }

    si_Strsize = strlen( ( char * )p_NumString );

    /* �����Ƃ̏d�݂��쐬 */
    for ( si_Mag = si_Mag * si_Sign ; * ( p_NumString + si_Index ) != '.' ; si_Index ++ ) { si_Mag = si_Mag * 10; }

    /* ���l�𕶎���֕ϊ� */
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
/* �֐���   : strconv                                                        */
/* �@�\��   : ���l�𕶎���ɕϊ�����                                         */
/* �@�\�T�v :                              */
/* ����	    : UINT   : ui_Num      : �ϊ��O���l                              */
/* �߂�l   : SCHR   : ����l      : �ϊ��㕶����                            */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SINT   StrConv::strconv  ( UINT ui_Num , SCHR * p_NumString , SINT si_Digit ) {

    /* �����`�F�b�N -------------------------------------------------------- */
    if ( p_NumString == NULL ) {
#ifdef STRCONV_DEBUG
        printf("StrConv::strconv��NULL�|�C���^���n����܂���...\n");
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
/* �֐���   : digitschk                                                      */
/* �@�\��   : �����̌��������߂�                                             */
/* �@�\�T�v : �����Ƃ��ēn���ꂽ�����̌������A                               */
/*            10�ɂ�鏜�Z�ɂ�苁�߁Areturn����B                           */
/* ����	    : SINT   : si_Num      : �����v�Z�Ώۂ̐���                      */
/* �߂�l   : SINT   : ����l      : si_Num�̌���                            */
/* �쐬��   : 2019/10/03       ����  �a�P       �V�K�쐬                     */
/* ------------------------------------------------------------------------- */
SINT StrConv::digitschk( UINT si_Num ){

    /* �����`�F�b�N -------------------------------------------------------- */
    // ������0�̏ꍇ
    if ( si_Num == 0 ) { return 1 ; }

    /* �ϐ��錾 ------------------------------------------------------------ */
    SINT   si_Digit = 0;                                 /* �����̌������i�[ */
    
    /* ������10�ŏ��Z�������A0�ɂȂ�܂Ń��[�v */
    for ( si_Digit = 0 ; si_Num != 0 ; si_Digit ++ ) {
    
        si_Num = si_Num / 10;

    }

    return si_Digit;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */