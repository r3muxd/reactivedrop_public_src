#include "cbase.h"
#include "c_asw_sentry_top.h"
#include "c_asw_sentry_base.h"
#include "c_asw_sentry_top_flamer.h"
#include <vgui/ISurface.h>
#include <vgui_controls/Panel.h>
#include "c_te_legacytempents.h"
#include "c_asw_fx.h"
#include "c_asw_generic_emitter.h"
#include "c_user_message_register.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "soundenvelope.h"
#include "ai_debug_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT(C_ASW_Sentry_Top_Flamer, DT_ASW_Sentry_Top_Flamer, CASW_Sentry_Top_Flamer)
RecvPropInt( RECVINFO( m_bFiring ) ),	
RecvPropFloat( RECVINFO( m_flPitchHack ) ),
END_RECV_TABLE()

BEGIN_PREDICTION_DATA( C_ASW_Sentry_Top_Flamer )
END_PREDICTION_DATA()


ConVar asw_sentry_emitter_test("asw_sentry_emitter_test", "0", FCVAR_CHEAT | FCVAR_DEVELOPMENTONLY, "Set to 1 to test turret emitters being on");


C_ASW_Sentry_Top_Flamer::C_ASW_Sentry_Top_Flamer() : 
	//m_OldStyleEmitters( 0, 0 ),
	m_pFlamerLoopSound( NULL ), 
	m_szBeginFireSoundScriptName( NULL ),
	m_szDuringFireSoundScriptName( NULL ),
	m_szEndFireSoundScriptName( NULL ),
	m_bFiringShadow( false )
{

	m_szParticleEffectFireName = "asw_flamethrower";

	m_szDuringFireSoundScriptName = "ASW_Sentry.FlameLoop" ;
	m_szEndFireSoundScriptName = "ASW_Sentry.FlameStop" ;
}

void C_ASW_Sentry_Top_Flamer::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );

	if ( updateType == DATA_UPDATE_CREATED )
	{
		m_bFiringShadow = m_bFiring;

		if ( HasPilotLight() && !m_hPilotLight )
		{
			m_hPilotLight = ParticleProp()->Create( "asw_flamethrower_pilot_sml", PATTACH_POINT_FOLLOW, "pilot_light" );
			
			if ( m_hPilotLight )
				m_hPilotLight->SetControlPoint( 1, Vector( 1, 0, 0 ) );
		}
	}	
	else
	{
		// what was changed?
		if ( m_bFiring != m_bFiringShadow )
		{
			if ( m_bFiring )
			{
				OnStartFiring();
			}
			else
			{
				OnStopFiring();
			}

			m_bFiringShadow = m_bFiring;
		}
	}
}

void C_ASW_Sentry_Top_Flamer::OnStartFiring()
{
	if ( m_szBeginFireSoundScriptName )
	{
		EmitSound("ASW_Sentry.FlameStop");
	}

	if ( !IsPlayingFiringLoopSound() && m_szDuringFireSoundScriptName )
	{
		CPASAttenuationFilter filter( this );
		CSoundEnvelopeController &controller = CSoundEnvelopeController::GetController();
		m_pFlamerLoopSound = controller.SoundCreate( filter, entindex(), m_szDuringFireSoundScriptName );
		CSoundEnvelopeController::GetController().Play( m_pFlamerLoopSound, 1.0, 100 );
	}

	if ( HasPilotLight() && m_hPilotLight )
	{
		m_hPilotLight->SetControlPoint( 1, Vector( 0, 0, 0 ) );
	}

	if ( !m_hFiringEffect )
	{
		m_hFiringEffect = ParticleProp()->Create( m_szParticleEffectFireName, PATTACH_POINT_FOLLOW, "muzzle" );
	}

	ResetSequence( SelectWeightedSequence( ACT_OBJ_RUNNING ) );
}

void C_ASW_Sentry_Top_Flamer::OnStopFiring()
{
	if ( IsPlayingFiringLoopSound() )
	{
		//Msg("Ending flamer loop!\n");
		CSoundEnvelopeController &controller = CSoundEnvelopeController::GetController();
		controller.SoundDestroy( m_pFlamerLoopSound );
		m_pFlamerLoopSound = NULL;
	}

	EmitSound( m_szEndFireSoundScriptName );

	if ( m_hFiringEffect )
	{
		m_hFiringEffect->StopEmission();
		m_hFiringEffect = NULL;
	}

	if ( m_hPilotLight )
		m_hPilotLight->SetControlPoint( 1, Vector( 1, 0, 0 ) );

	if ( GetSentryBase() && GetSentryBase()->GetAmmo() <= 1 && m_hPilotLight )
		m_hPilotLight->SetControlPoint( 1, Vector( 0, 0, 0 ) );

	ResetSequence( SelectWeightedSequence( ACT_OBJ_IDLE ) );
}

void C_ASW_Sentry_Top_Flamer::UpdateOnRemove()
{
	OnStopFiring();

	BaseClass::UpdateOnRemove();
}
