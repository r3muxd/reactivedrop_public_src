// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW
#include "shaderlib/cshader.h"
class shadow_ps20_Static_Index
{
private:
	int m_nDEFERRED_SHADOWS;
#ifdef _DEBUG
	bool m_bDEFERRED_SHADOWS;
#endif
public:
	void SetDEFERRED_SHADOWS( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nDEFERRED_SHADOWS = i;
#ifdef _DEBUG
		m_bDEFERRED_SHADOWS = true;
#endif
	}
	void SetDEFERRED_SHADOWS( bool i )
	{
		m_nDEFERRED_SHADOWS = i ? 1 : 0;
#ifdef _DEBUG
		m_bDEFERRED_SHADOWS = true;
#endif
	}
private:
	int m_nBLOBBY_SHADOWS;
#ifdef _DEBUG
	bool m_bBLOBBY_SHADOWS;
#endif
public:
	void SetBLOBBY_SHADOWS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBLOBBY_SHADOWS = i;
#ifdef _DEBUG
		m_bBLOBBY_SHADOWS = true;
#endif
	}
	void SetBLOBBY_SHADOWS( bool i )
	{
		m_nBLOBBY_SHADOWS = i ? 1 : 0;
#ifdef _DEBUG
		m_bBLOBBY_SHADOWS = true;
#endif
	}
public:
	// CONSTRUCTOR
	shadow_ps20_Static_Index( IShaderShadow *pShaderShadow, IMaterialVar **params )
	{
#ifdef _DEBUG
		m_bDEFERRED_SHADOWS = false;
#endif // _DEBUG
		m_nDEFERRED_SHADOWS = 0;
#ifdef _DEBUG
		m_bBLOBBY_SHADOWS = false;
#endif // _DEBUG
		m_nBLOBBY_SHADOWS = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bDEFERRED_SHADOWS && m_bBLOBBY_SHADOWS;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 2 * m_nDEFERRED_SHADOWS ) + ( 2 * m_nBLOBBY_SHADOWS ) + 0;
	}
};
#define shaderStaticTest_shadow_ps20 psh_forgot_to_set_static_DEFERRED_SHADOWS + psh_forgot_to_set_static_BLOBBY_SHADOWS
class shadow_ps20_Dynamic_Index
{
private:
	int m_nPIXELFOGTYPE;
#ifdef _DEBUG
	bool m_bPIXELFOGTYPE;
#endif
public:
	void SetPIXELFOGTYPE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPIXELFOGTYPE = i;
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif
	}
	void SetPIXELFOGTYPE( bool i )
	{
		m_nPIXELFOGTYPE = i ? 1 : 0;
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif
	}
public:
	// CONSTRUCTOR
	shadow_ps20_Dynamic_Index( IShaderDynamicAPI *pShaderAPI )
	{
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif // _DEBUG
		m_nPIXELFOGTYPE = ( pShaderAPI->GetSceneFogMode() == MATERIAL_FOG_LINEAR_BELOW_FOG_Z ) ;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bPIXELFOGTYPE;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nPIXELFOGTYPE ) + 0;
	}
};
#define shaderDynamicTest_shadow_ps20 1
