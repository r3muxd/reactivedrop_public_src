// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// $PERPARTICLEOUTLINE && ( $ORIENTATION == 3 )
// $DUALSEQUENCE && ( $PERPARTICLEOUTLINE || ( $ORIENTATION == 3 ) )
// $HARDWAREFOGBLEND && !SPRITECARDVERTEXFOG
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#pragma once
#include "shaderlib/cshader.h"
class spritecard_vs20_Static_Index
{
	unsigned int m_nDUALSEQUENCE : 2;
	unsigned int m_nADDBASETEXTURE2 : 2;
	unsigned int m_nEXTRACTGREENALPHA : 2;
	unsigned int m_nDEPTHBLEND : 1;
	unsigned int m_nANIMBLEND_OR_MAXLUMFRAMEBLEND1 : 2;
	unsigned int m_nCROP : 2;
	unsigned int m_nPACKED_INTERPOLATOR : 2;
	unsigned int m_nSPRITECARDVERTEXFOG : 2;
	unsigned int m_nHARDWAREFOGBLEND : 2;
	unsigned int m_nPERPARTICLEOUTLINE : 2;
#ifdef _DEBUG
	bool m_bDUALSEQUENCE : 1;
	bool m_bADDBASETEXTURE2 : 1;
	bool m_bEXTRACTGREENALPHA : 1;
	bool m_bDEPTHBLEND : 1;
	bool m_bANIMBLEND_OR_MAXLUMFRAMEBLEND1 : 1;
	bool m_bCROP : 1;
	bool m_bPACKED_INTERPOLATOR : 1;
	bool m_bSPRITECARDVERTEXFOG : 1;
	bool m_bHARDWAREFOGBLEND : 1;
	bool m_bPERPARTICLEOUTLINE : 1;
#endif	// _DEBUG
public:
	void SetDUALSEQUENCE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDUALSEQUENCE = i;
#ifdef _DEBUG
		m_bDUALSEQUENCE = true;
#endif	// _DEBUG
	}

	void SetADDBASETEXTURE2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nADDBASETEXTURE2 = i;
#ifdef _DEBUG
		m_bADDBASETEXTURE2 = true;
#endif	// _DEBUG
	}

	void SetEXTRACTGREENALPHA( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nEXTRACTGREENALPHA = i;
#ifdef _DEBUG
		m_bEXTRACTGREENALPHA = true;
#endif	// _DEBUG
	}

	void SetDEPTHBLEND( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nDEPTHBLEND = i;
#ifdef _DEBUG
		m_bDEPTHBLEND = true;
#endif	// _DEBUG
	}

	void SetANIMBLEND_OR_MAXLUMFRAMEBLEND1( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nANIMBLEND_OR_MAXLUMFRAMEBLEND1 = i;
#ifdef _DEBUG
		m_bANIMBLEND_OR_MAXLUMFRAMEBLEND1 = true;
#endif	// _DEBUG
	}

	void SetCROP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCROP = i;
#ifdef _DEBUG
		m_bCROP = true;
#endif	// _DEBUG
	}

	void SetPACKED_INTERPOLATOR( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPACKED_INTERPOLATOR = i;
#ifdef _DEBUG
		m_bPACKED_INTERPOLATOR = true;
#endif	// _DEBUG
	}

	void SetSPRITECARDVERTEXFOG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSPRITECARDVERTEXFOG = i;
#ifdef _DEBUG
		m_bSPRITECARDVERTEXFOG = true;
#endif	// _DEBUG
	}

	void SetHARDWAREFOGBLEND( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nHARDWAREFOGBLEND = i;
#ifdef _DEBUG
		m_bHARDWAREFOGBLEND = true;
#endif	// _DEBUG
	}

	void SetPERPARTICLEOUTLINE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPERPARTICLEOUTLINE = i;
#ifdef _DEBUG
		m_bPERPARTICLEOUTLINE = true;
#endif	// _DEBUG
	}

	spritecard_vs20_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nDUALSEQUENCE = 0;
		m_nADDBASETEXTURE2 = 0;
		m_nEXTRACTGREENALPHA = 0;
		m_nDEPTHBLEND = 0;
		m_nANIMBLEND_OR_MAXLUMFRAMEBLEND1 = 0;
		m_nCROP = 0;
		m_nPACKED_INTERPOLATOR = 0;
		m_nSPRITECARDVERTEXFOG = 0;
		m_nHARDWAREFOGBLEND = 0;
		m_nPERPARTICLEOUTLINE = 0;
#ifdef _DEBUG
		m_bDUALSEQUENCE = false;
		m_bADDBASETEXTURE2 = false;
		m_bEXTRACTGREENALPHA = false;
		m_bDEPTHBLEND = false;
		m_bANIMBLEND_OR_MAXLUMFRAMEBLEND1 = false;
		m_bCROP = false;
		m_bPACKED_INTERPOLATOR = false;
		m_bSPRITECARDVERTEXFOG = false;
		m_bHARDWAREFOGBLEND = false;
		m_bPERPARTICLEOUTLINE = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bDUALSEQUENCE && m_bADDBASETEXTURE2 && m_bEXTRACTGREENALPHA && m_bDEPTHBLEND && m_bANIMBLEND_OR_MAXLUMFRAMEBLEND1 && m_bCROP && m_bPACKED_INTERPOLATOR && m_bSPRITECARDVERTEXFOG && m_bHARDWAREFOGBLEND && m_bPERPARTICLEOUTLINE );
		return ( 4 * m_nDUALSEQUENCE ) + ( 8 * m_nADDBASETEXTURE2 ) + ( 16 * m_nEXTRACTGREENALPHA ) + ( 32 * m_nDEPTHBLEND ) + ( 32 * m_nANIMBLEND_OR_MAXLUMFRAMEBLEND1 ) + ( 64 * m_nCROP ) + ( 128 * m_nPACKED_INTERPOLATOR ) + ( 256 * m_nSPRITECARDVERTEXFOG ) + ( 512 * m_nHARDWAREFOGBLEND ) + ( 1024 * m_nPERPARTICLEOUTLINE ) + 0;
	}
};

#define shaderStaticTest_spritecard_vs20 vsh_forgot_to_set_static_DUALSEQUENCE + vsh_forgot_to_set_static_ADDBASETEXTURE2 + vsh_forgot_to_set_static_EXTRACTGREENALPHA + vsh_forgot_to_set_static_DEPTHBLEND + vsh_forgot_to_set_static_ANIMBLEND_OR_MAXLUMFRAMEBLEND1 + vsh_forgot_to_set_static_CROP + vsh_forgot_to_set_static_PACKED_INTERPOLATOR + vsh_forgot_to_set_static_SPRITECARDVERTEXFOG + vsh_forgot_to_set_static_HARDWAREFOGBLEND + vsh_forgot_to_set_static_PERPARTICLEOUTLINE


class spritecard_vs20_Dynamic_Index
{
	unsigned int m_nORIENTATION : 3;
#ifdef _DEBUG
	bool m_bORIENTATION : 1;
#endif	// _DEBUG
public:
	void SetORIENTATION( int i )
	{
		Assert( i >= 0 && i <= 3 );
		m_nORIENTATION = i;
#ifdef _DEBUG
		m_bORIENTATION = true;
#endif	// _DEBUG
	}

	spritecard_vs20_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nORIENTATION = 0;
#ifdef _DEBUG
		m_bORIENTATION = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bORIENTATION );
		return ( 1 * m_nORIENTATION ) + 0;
	}
};

#define shaderDynamicTest_spritecard_vs20 vsh_forgot_to_set_dynamic_ORIENTATION

