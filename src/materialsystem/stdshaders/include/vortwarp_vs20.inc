// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( $DOWATERFOG == 0 ) && ( $DOPIXELFOG && $HARDWAREFOGBLEND )
// ( $DOWATERFOG == 0 ) && ( $HARDWAREFOGBLEND == 0 ) && ( $DOPIXELFOG == 0 )
// $DOWATERFOG
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#pragma once
#include "shaderlib/cshader.h"
class vortwarp_vs20_Static_Index
{
	unsigned int m_nHALFLAMBERT : 2;
	unsigned int m_nDOPIXELFOG : 2;
	unsigned int m_nHARDWAREFOGBLEND : 2;
#ifdef _DEBUG
	bool m_bHALFLAMBERT : 1;
#endif	// _DEBUG
public:
	void SetHALFLAMBERT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nHALFLAMBERT = i;
#ifdef _DEBUG
		m_bHALFLAMBERT = true;
#endif	// _DEBUG
	}

	void SetDOPIXELFOG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDOPIXELFOG = i;
	}

	void SetHARDWAREFOGBLEND( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nHARDWAREFOGBLEND = i;
	}

	vortwarp_vs20_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nHALFLAMBERT = 0;
		m_nDOPIXELFOG = g_pHardwareConfig->SupportsPixelShaders_2_b() ;
		m_nHARDWAREFOGBLEND = !g_pHardwareConfig->SupportsPixelShaders_2_b() ;
#ifdef _DEBUG
		m_bHALFLAMBERT = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bHALFLAMBERT );
		return ( 8 * m_nHALFLAMBERT ) + ( 16 * m_nDOPIXELFOG ) + ( 32 * m_nHARDWAREFOGBLEND ) + 0;
	}
};

#define shaderStaticTest_vortwarp_vs20 vsh_forgot_to_set_static_HALFLAMBERT


class vortwarp_vs20_Dynamic_Index
{
	unsigned int m_nCOMPRESSED_VERTS : 2;
	unsigned int m_nDOWATERFOG : 2;
	unsigned int m_nSKINNING : 2;
#ifdef _DEBUG
	bool m_bCOMPRESSED_VERTS : 1;
	bool m_bSKINNING : 1;
#endif	// _DEBUG
public:
	void SetCOMPRESSED_VERTS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCOMPRESSED_VERTS = i;
#ifdef _DEBUG
		m_bCOMPRESSED_VERTS = true;
#endif	// _DEBUG
	}

	void SetDOWATERFOG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDOWATERFOG = i;
	}

	void SetSKINNING( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSKINNING = i;
#ifdef _DEBUG
		m_bSKINNING = true;
#endif	// _DEBUG
	}

	vortwarp_vs20_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nCOMPRESSED_VERTS = 0;
		m_nDOWATERFOG = ( pShaderAPI->GetSceneFogMode() == MATERIAL_FOG_LINEAR_BELOW_FOG_Z ) ;
		m_nSKINNING = 0;
#ifdef _DEBUG
		m_bCOMPRESSED_VERTS = false;
		m_bSKINNING = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bCOMPRESSED_VERTS && m_bSKINNING );
		AssertMsg( !m_nDOWATERFOG, "Invalid combo combination DOWATERFOG" );
		return ( 1 * m_nCOMPRESSED_VERTS ) + ( 2 * m_nDOWATERFOG ) + ( 4 * m_nSKINNING ) + 0;
	}
};

#define shaderDynamicTest_vortwarp_vs20 vsh_forgot_to_set_dynamic_COMPRESSED_VERTS + vsh_forgot_to_set_dynamic_SKINNING

