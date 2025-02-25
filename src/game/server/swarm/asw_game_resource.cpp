#include "cbase.h"
#include "asw_game_resource.h"
#include "asw_objective.h"
#include "asw_marine_resource.h"
#include "asw_scanner_info.h"
#include "asw_player.h"
#include "asw_campaign_save.h"
#include "asw_marine_profile.h"
#include "asw_gamerules.h"
#include "asw_deathmatch_mode.h"
#ifdef RD_7A_DROPS
#include "asw_marine_hint.h"
#include "asw_spawn_manager.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static char s_szLastLeaderNetworkID[ASW_LEADERID_LEN] = {0};

#ifdef RD_7A_DROPS
ConVar rd_debug_material_spawns( "rd_debug_material_spawns", "0", FCVAR_NONE );
#endif

LINK_ENTITY_TO_CLASS( asw_game_resource, CASW_Game_Resource );

extern void SendProxy_String_tToString( const SendProp *pProp, const void *pStruct, const void *pData, DVariant *pOut, int iElement, int objectID );

IMPLEMENT_SERVERCLASS_ST( CASW_Game_Resource, DT_ASW_Game_Resource )
	SendPropArray3( SENDINFO_ARRAY3( m_MarineResources ), SendPropEHandle( SENDINFO_ARRAY( m_MarineResources ) ) ),
	SendPropArray3( SENDINFO_ARRAY3( m_Objectives ), SendPropEHandle( SENDINFO_ARRAY( m_Objectives ) ) ),
	SendPropArray3( SENDINFO_ARRAY3( m_bPlayerReady ), SendPropBool( SENDINFO_ARRAY( m_bPlayerReady ) ) ),

	SendPropEHandle( SENDINFO( m_Leader ) ),
	SendPropEHandle( SENDINFO( m_hScannerInfo ) ),
	SendPropInt( SENDINFO( m_iCampaignGame ), 2 ),
	SendPropEHandle( SENDINFO( m_hCampaignSave ) ),
	SendPropBool( SENDINFO( m_bOneMarineEach ) ),
	SendPropInt( SENDINFO( m_iMaxMarines ) ),
	SendPropBool( SENDINFO( m_bOfflineGame ) ),

	// marine skills
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlot0 ), 3, SPROP_UNSIGNED ), m_iSkillSlot0 ),
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlot1 ), 3, SPROP_UNSIGNED ), m_iSkillSlot1 ),
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlot2 ), 3, SPROP_UNSIGNED ), m_iSkillSlot2 ),
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlot3 ), 3, SPROP_UNSIGNED ), m_iSkillSlot3 ),
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlot4 ), 3, SPROP_UNSIGNED ), m_iSkillSlot4 ),
	SendPropArray( SendPropInt( SENDINFO_ARRAY( m_iSkillSlotSpare ), 3, SPROP_UNSIGNED ), m_iSkillSlotSpare ),

	// player specific medals
	SendPropArray( SendPropString( SENDINFO_ARRAY( m_iszPlayerMedals ), 0, SendProxy_String_tToString ), m_iszPlayerMedals ),

	SendPropArray3( SENDINFO_ARRAY3( m_iKickVotes ), SendPropInt( SENDINFO_ARRAY( m_iKickVotes ), NumBitsForCount( ASW_MAX_READY_PLAYERS ), SPROP_UNSIGNED ) ),
	SendPropArray3( SENDINFO_ARRAY3( m_iLeaderVotes ), SendPropInt( SENDINFO_ARRAY( m_iLeaderVotes ), NumBitsForCount( ASW_MAX_READY_PLAYERS ), SPROP_UNSIGNED ) ),

	SendPropInt( SENDINFO( m_iMoney ) ),
	SendPropInt( SENDINFO( m_iNextCampaignMission ) ),
	SendPropInt( SENDINFO( m_nDifficultySuggestion ), 2, SPROP_UNSIGNED ),

	SendPropFloat( SENDINFO( m_fMapGenerationProgress ) ),
	SendPropString( SENDINFO( m_szMapGenerationStatus ) ),
	SendPropInt( SENDINFO( m_iRandomMapSeed ) ),

#ifdef RD_7A_DROPS
	SendPropDataTable( SENDINFO_DT( m_CraftingMaterialInfo ), &REFERENCE_SEND_TABLE( DT_RD_CraftingMaterialInfo ) ),
#endif
END_SEND_TABLE()

//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC( CASW_Game_Resource )
	DEFINE_AUTO_ARRAY( m_MarineResources, FIELD_EHANDLE ),
	DEFINE_AUTO_ARRAY( m_Objectives, FIELD_EHANDLE ),
	DEFINE_AUTO_ARRAY( m_bPlayerReady, FIELD_BOOLEAN ),
	DEFINE_AUTO_ARRAY( m_iCampaignVote, FIELD_INTEGER ),
	DEFINE_FIELD( m_Leader, FIELD_EHANDLE ),
	DEFINE_FIELD( m_hScannerInfo, FIELD_EHANDLE ),
	DEFINE_FIELD( m_NumObjectives, FIELD_INTEGER ),
	DEFINE_FIELD( m_iCampaignGame, FIELD_INTEGER ),
	DEFINE_FIELD( m_hCampaignSave, FIELD_EHANDLE ),
	DEFINE_FIELD( m_iNumMarinesSelected, FIELD_INTEGER ),

	DEFINE_FIELD( m_iszPlayerMedals[0], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[1], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[2], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[3], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[4], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[5], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[6], FIELD_STRING ),
	DEFINE_FIELD( m_iszPlayerMedals[7], FIELD_STRING ),
END_DATADESC()

CASW_Game_Resource *g_pASWGameResource = NULL;

extern bool g_bOfflineGame;

int CASW_Game_Resource::s_nNumConsecutiveFailures = 0;
bool CASW_Game_Resource::s_bLeaderGivenDifficultySuggestion = false;

CASW_Game_Resource::CASW_Game_Resource()
{
	g_pASWGameResource = this;
	m_iNumEnumeratedMarines = NULL;
	m_iMaxMarines = ASW_MAX_MARINE_RESOURCES; // reactivedrop: was 4
	m_bOneMarineEach = false;
	m_iNumMarinesSelected = 0;
	m_iRandomMapSeed = 0;
	m_iNextCampaignMission = -1;
	m_iEggsHatched = 0;
	m_iEggsKilled = 0;
	m_iStartingEggsInMap = -1;
	m_bAwardedDamageAmpAchievement = false;
	m_iAliensKilledWithDamageAmp = 0;
	m_iElectroStunnedAliens = 0;
	for ( int i = 0; i < ASW_MAX_READY_PLAYERS; i++ )
	{
		m_bPlayerReady.Set( i, false );
		m_iKickVotes.Set( i, 0 );
		m_iLeaderVotes.Set( i, 0 );
		m_iCampaignVote[i] = -1;
	}
	for ( int i = 0; i < ASW_MAX_MARINE_RESOURCES; i++ )
	{
		m_MarineResources.Set( i, NULL );
	}
	for ( int i = 0; i < ASW_MAX_OBJECTIVES; i++ )
	{
		m_Objectives.Set( i, NULL );
	}
	CASW_Scanner_Info *pScanner = ( CASW_Scanner_Info * )CreateEntityByName( "asw_scanner_info" );
	if ( pScanner )
	{
		pScanner->Spawn();
		m_hScannerInfo = pScanner;
	}

	m_bOfflineGame = g_bOfflineGame;
	m_iCampaignGame = 0;
	m_szCampaignSaveName[0] = '\0';
	// query map's launch options to see if we're in campaign mode
	KeyValues *pLaunchOptions = engine->GetLaunchOptions();
	if ( pLaunchOptions )
	{
		KeyValues *pKey = pLaunchOptions->GetFirstSubKey();
		while ( pKey )
		{
			if ( !Q_stricmp( pKey->GetString(), "campaign" ) || !Q_stricmp( pKey->GetString(), "single_mission" ) )
			{
				m_iCampaignGame = !Q_stricmp( pKey->GetString(), "campaign" );
				KeyValues *pCampaignSaveName = pKey->GetNextKey();
				if ( pCampaignSaveName )
					Q_snprintf( m_szCampaignSaveName, sizeof( m_szCampaignSaveName ), "%s", pCampaignSaveName->GetString() );
				break;
			}
			pKey = pKey->GetNextKey();
		}
	}

	// make skills default for single mission
	UpdateMarineSkills( NULL );
}

CASW_Game_Resource::~CASW_Game_Resource()
{
	if ( m_hScannerInfo.Get() )
	{
		UTIL_Remove( m_hScannerInfo.Get() );
	}

	if ( g_pASWGameResource == this )
	{
		g_pASWGameResource = NULL;
	}
}

// always send this info to players
int CASW_Game_Resource::ShouldTransmit( const CCheckTransmitInfo *pInfo )
{
	return FL_EDICT_ALWAYS;
}

CASW_Objective *CASW_Game_Resource::GetObjective( int i )
{
	if ( i < 0 || i >= ASW_MAX_OBJECTIVES )
		return NULL;

	return m_Objectives[i];
}

void CASW_Game_Resource::FindObjectivesOfClass( const char *szClass )
{
	CBaseEntity *pEntity = NULL;
	while ( ( pEntity = gEntList.FindEntityByClassname( pEntity, szClass ) ) != NULL )
	{
		if ( m_NumObjectives >= ASW_MAX_OBJECTIVES )
		{
			Warning( "Missions cannot have more than %d objectives!\n", ASW_MAX_OBJECTIVES );
			continue;
		}

		m_Objectives.Set( m_NumObjectives, assert_cast< CASW_Objective * >( pEntity ) );
		m_NumObjectives++;
	}
}

void CASW_Game_Resource::FindObjectives()
{
	// search through all entities and populate the objectives array
	m_NumObjectives = 0;

	FindObjectivesOfClass( "asw_objective_dummy" );
	FindObjectivesOfClass( "asw_objective_kill_eggs" );
	FindObjectivesOfClass( "asw_objective_destroy_goo" );
	FindObjectivesOfClass( "asw_objective_triggered" );
	FindObjectivesOfClass( "asw_objective_escape" );
	FindObjectivesOfClass( "asw_objective_survive" );
	FindObjectivesOfClass( "asw_objective_countdown" );
	FindObjectivesOfClass( "asw_objective_kill_aliens" );
	FindObjectivesOfClass( "asw_objective_kill_queen" );

	// bubble sort objectives by their Y coord
	for ( int i = 0; i < m_NumObjectives; i++ )
	{
		for ( int j = i + 1; j < m_NumObjectives; j++ )
		{
			if ( GetObjective( j )->GetAbsOrigin().y > GetObjective( i )->GetAbsOrigin().y )
			{
				CASW_Objective *pObjective = GetObjective( j );
				m_Objectives.Set( j, GetObjective( i ) );
				m_Objectives.Set( i, pObjective );
			}
		}
	}
}

// unselects a single marine
// tries to pick the player with the most marines selected
void CASW_Game_Resource::RemoveAMarine()
{
	int iHighest = 0;
	CASW_Player *pChosen = NULL;

	for ( int i = 1; i <= gpGlobals->maxClients; i++ )
	{
		CASW_Player *pOtherPlayer = ToASW_Player( UTIL_PlayerByIndex( i ) );

		if ( pOtherPlayer && pOtherPlayer->IsConnected() )
		{
			int iMarines = GetNumMarines( pOtherPlayer );
			if ( iHighest == 0 || iMarines > iHighest )
			{
				iHighest = iMarines;
				pChosen = pOtherPlayer;
			}
		}
	}
	RemoveAMarineFor( pChosen );
}

void CASW_Game_Resource::RemoveAMarineFor( CASW_Player *pPlayer )
{
	if ( !pPlayer || !ASWGameRules() )
		return;

	// find this player's first marine and remove it
	int m = GetMaxMarineResources();
	for ( int i = 0; i < m; i++ )
	{
		if ( GetMarineResource( i ) && GetMarineResource( i )->GetCommander() == pPlayer )
		{
			ASWGameRules()->RosterDeselect( pPlayer, GetMarineResource( i )->GetProfileIndex() );
			return;
		}
	}
}

bool CASW_Game_Resource::AddMarineResource( CASW_Marine_Resource *m, int nPreferredSlot )
{
	if ( nPreferredSlot != -1 )
	{
		CASW_Marine_Resource *pExisting = static_cast< CASW_Marine_Resource * >( m_MarineResources[nPreferredSlot].Get() );
		if ( pExisting != NULL )
		{
			// if the existing is owned by someone else, then we abort
			if ( pExisting->GetCommander() != m->GetCommander() )
				return false;

			m_iNumMarinesSelected--;
			UTIL_Remove( pExisting );
		}

		m_iNumMarinesSelected++;
		m_MarineResources.Set( nPreferredSlot, m );

		// the above causes strange cases where the client copy of this networked array is incorrect
		// so we flag each element dirty to cause a complete update, which seems to fix the problem
		for ( int k = 0; k < ASW_MAX_MARINE_RESOURCES; k++ )
		{
			m_MarineResources.GetForModify( k );
		}
		return true;
	}

	for ( int i = 0; i < ASW_MAX_MARINE_RESOURCES; i++ )
	{
		if ( m_MarineResources[i] == NULL )	// found a free slot
		{
			m_iNumMarinesSelected++;
			m_MarineResources.Set( i, m );

			// the above causes strange cases where the client copy of this networked array is incorrect
			// so we flag each element dirty to cause a complete update, which seems to fix the problem
			for ( int k = 0; k < ASW_MAX_MARINE_RESOURCES; k++ )
			{
				m_MarineResources.GetForModify( k );
			}
			return true;
		}
	}
	Msg( "Couldn't add new marine resource to list as no free slots\n" );
	return false;
}

void CASW_Game_Resource::DeleteMarineResource( CASW_Marine_Resource *m )
{
	for ( int i = 0; i < ASW_MAX_MARINE_RESOURCES; i++ )
	{
		if ( GetMarineResource( i ) == m )
		{
			m_iNumMarinesSelected--;
			m_MarineResources.Set( i, NULL );
			UTIL_Remove( m );
			// need to shuffle all others up
			for ( int k = i; k < ( ASW_MAX_MARINE_RESOURCES - 1 ); k++ )
			{
				CASW_Marine_Resource *other = GetMarineResource( k + 1 );
				m_MarineResources.Set( k, other );
				m_MarineResources.Set( k + 1, NULL );
			}
		}
	}
	// the above causes strange cases where the client copy of this networked array is incorrect
	// so we flag each element dirty to cause a complete update, which seems to fix the problem
	for ( int i = 0; i < ASW_MAX_MARINE_RESOURCES; i++ )
	{
		m_MarineResources.GetForModify( i );
	}
}

CASW_Marine_Resource *CASW_Game_Resource::GetMarineResource( int i )
{
	Assert( i >= 0 && i < ASW_MAX_MARINE_RESOURCES );
	if ( i >= 0 && i < ASW_MAX_MARINE_RESOURCES )
		return m_MarineResources[i].Get();

	return NULL;
}

CASW_Scanner_Info* CASW_Game_Resource::GetScannerInfo()
{
	return m_hScannerInfo.Get();
}

void CASW_Game_Resource::SetLeader(CASW_Player *pPlayer)
{
	extern ConVar rd_ready_mark_override;
	// check for auto-readying our old leader
	if ( m_Leader.Get() && m_Leader.Get() != pPlayer && ASWGameRules() &&
		( m_Leader->m_bRequestedSpectator || rd_ready_mark_override.GetBool() ) )
	{
		int iPlayerIndex = m_Leader->entindex() - 1;
		if ( ASWGameRules()->GetGameState() == ASW_GS_BRIEFING || ASWGameRules()->GetGameState() == ASW_GS_DEBRIEF )
		{
			// player index is out of range
			if ( iPlayerIndex >= 0 && iPlayerIndex < ASW_MAX_READY_PLAYERS )
			{
				//Msg("Autoreadying old leader, who wanted to be a spectator\n");
				m_bPlayerReady.Set( iPlayerIndex, true );
			}
		}
		else if ( ASWGameRules()->GetGameState() == ASW_GS_CAMPAIGNMAP && ASWGameRules()->GetCampaignSave() )
		{
			Msg( " old leader telling campaign save that we're spectating\n", iPlayerIndex );
			ASWGameRules()->GetCampaignSave()->PlayerSpectating( m_Leader.Get() );
		}
	}

	if ( !pPlayer )
	{
		m_Leader = NULL;
		return;
	}

	Assert( pPlayer->CanBeLeader() );
	if ( !pPlayer->CanBeLeader() )
	{
		Warning( "Tried to set lobby leader to '%s'!\n", pPlayer->GetPlayerName() );
		return;
	}

	m_Leader = pPlayer;
	
	if ( ASWGameRules() && (ASWGameRules()->GetGameState() == ASW_GS_BRIEFING || ASWGameRules()->GetGameState() == ASW_GS_DEBRIEF) )
	{
		// unready leader
		int iPlayerIndex = pPlayer->entindex() - 1;
		Assert( iPlayerIndex >= 0 && iPlayerIndex < ASW_MAX_READY_PLAYERS );
		if ( iPlayerIndex >= 0 && iPlayerIndex < ASW_MAX_READY_PLAYERS )
		{
			m_bPlayerReady.Set( iPlayerIndex, false );
		}
	}
}

CASW_Campaign_Save *CASW_Game_Resource::GetCampaignSave()
{
	return m_hCampaignSave.Get();
}

CASW_Campaign_Save* CASW_Game_Resource::CreateCampaignSave()
{
	CASW_Campaign_Save* pSave = (CASW_Campaign_Save*)CreateEntityByName("asw_campaign_save");
	if (pSave)
	{
		pSave->Spawn();
		m_hCampaignSave = pSave;
	}
	m_hCampaignSave = pSave;
	pSave = GetCampaignSave();
	return pSave;
}

void CASW_Game_Resource::UpdateMarineSkills( CASW_Campaign_Save *pCampaign )
{
	if ( !pCampaign || pCampaign->UsingFixedSkillPoints() )
	{
		// update skills with defaults
		for ( int iProfileIndex = 0; iProfileIndex < ASW_NUM_MARINE_PROFILES; iProfileIndex++ )
		{
			CASW_Marine_Profile *pProfile = MarineProfileList()->GetProfile( iProfileIndex );
			if ( pProfile )
			{
				m_iSkillSlot0.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_0 ) );
				m_iSkillSlot1.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_1 ) );
				m_iSkillSlot2.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_2 ) );
				m_iSkillSlot3.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_3 ) );
				m_iSkillSlot4.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_4 ) );
				m_iSkillSlotSpare.Set( iProfileIndex, pProfile->GetStaticSkillPoints( ASW_SKILL_SLOT_SPARE ) );
			}
			else
			{
				m_iSkillSlot0.Set( iProfileIndex, 0 );
				m_iSkillSlot1.Set( iProfileIndex, 0 );
				m_iSkillSlot2.Set( iProfileIndex, 0 );
				m_iSkillSlot3.Set( iProfileIndex, 0 );
				m_iSkillSlot4.Set( iProfileIndex, 0 );
				m_iSkillSlotSpare.Set( iProfileIndex, 0 );
			}
		}
	}
	else
	{
		// get skills from the campaign save
		for ( int iProfileIndex = 0; iProfileIndex < ASW_NUM_MARINE_PROFILES; iProfileIndex++ )
		{
			m_iSkillSlot0.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_0] );
			m_iSkillSlot1.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_1] );
			m_iSkillSlot2.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_2] );
			m_iSkillSlot3.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_3] );
			m_iSkillSlot4.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_4] );
			m_iSkillSlotSpare.Set( iProfileIndex, pCampaign->m_iMarineSkill[iProfileIndex][ASW_SKILL_SLOT_SPARE] );
		}
	}
}

bool CASW_Game_Resource::SetMarineSkill( int nProfileIndex, int nSkillSlot, int nValue )
{
	if ( nProfileIndex < 0 || nProfileIndex >= ASW_NUM_MARINE_PROFILES )
		return false;
	if ( nValue < 0 || nValue > 5 )
		return false;

	switch ( nSkillSlot )
	{
		case ASW_SKILL_SLOT_0: m_iSkillSlot0.Set( nProfileIndex, nValue ); break;
		case ASW_SKILL_SLOT_1: m_iSkillSlot1.Set( nProfileIndex, nValue ); break;
		case ASW_SKILL_SLOT_2: m_iSkillSlot2.Set( nProfileIndex, nValue ); break;
		case ASW_SKILL_SLOT_3: m_iSkillSlot3.Set( nProfileIndex, nValue ); break;
		case ASW_SKILL_SLOT_4: m_iSkillSlot4.Set( nProfileIndex, nValue ); break;
		case ASW_SKILL_SLOT_SPARE: m_iSkillSlotSpare.Set( nProfileIndex, nValue ); break;
		default: return false; break;
	}

	return true;
}

CASW_Player* CASW_Game_Resource::GetLeader()
{
	return m_Leader.Get();
}

CASW_Marine *CASW_Game_Resource::FindMarineByVoiceType( ASW_Voice_Type voice )
{
	int m = GetMaxMarineResources();
	for ( int i = 0; i < m; i++ )
	{
		if ( GetMarineResource( i ) && GetMarineResource( i )->GetProfile() && GetMarineResource( i )->GetProfile()->m_VoiceType == voice )
		{
			return GetMarineResource( i )->GetMarineEntity();
		}
	}
	return NULL;
}

void CASW_Game_Resource::RememberLeaderID()
{
	if ( GetLeader() )
	{
		SetLastLeaderNetworkID( GetLeader()->GetASWNetworkID() );
	}
}

const char *CASW_Game_Resource::GetLastLeaderNetworkID()
{
	return s_szLastLeaderNetworkID;
}

void CASW_Game_Resource::SetLastLeaderNetworkID( const char *szID )
{
	V_strncpy( s_szLastLeaderNetworkID, szID, sizeof( s_szLastLeaderNetworkID ) );
}

int CASW_Game_Resource::GetAliensKilledInThisMission()
{
	int nCount = 0;
	int m = GetMaxMarineResources();
	for ( int i = 0; i < m; i++ )
	{
		CASW_Marine_Resource *pMR = GetMarineResource( i );
		if ( !pMR )
			continue;

		nCount += pMR->m_iAliensKilled.Get();
	}
	return nCount;
}

void CASW_Game_Resource::OnMissionFailed( void )
{
	s_nNumConsecutiveFailures++;

	if ( !s_bLeaderGivenDifficultySuggestion && s_nNumConsecutiveFailures >= 4 )
	{
		s_bLeaderGivenDifficultySuggestion = true;
		m_nDifficultySuggestion = 2;
	}
}

void CASW_Game_Resource::OnMissionCompleted( bool bWellDone )
{
	if ( !s_bLeaderGivenDifficultySuggestion && s_nNumConsecutiveFailures == 0 && bWellDone )
	{
		s_bLeaderGivenDifficultySuggestion = true;
		m_nDifficultySuggestion = 1;
	}
	else
	{
		m_nDifficultySuggestion = 0;
	}

	s_nNumConsecutiveFailures = 0;
}

#ifdef RD_7A_DROPS
BEGIN_SEND_TABLE_NOBASE( CRD_CraftingMaterialInfo, DT_RD_CraftingMaterialInfo )
	SendPropInt( SENDINFO( m_nSpawnLocations ), NumBitsForCount( RD_MAX_CRAFTING_MATERIAL_SPAWN_LOCATIONS ), SPROP_UNSIGNED ),
	SendPropArray( SendPropVector( SENDINFO_ARRAY( m_SpawnLocationOrigins ) ), m_SpawnLocationOrigins ),
END_SEND_TABLE()

CRD_CraftingMaterialInfo::CRD_CraftingMaterialInfo()
{
	m_nSpawnLocations.Set( 0 );

	for ( int i = 0; i < RD_MAX_CRAFTING_MATERIAL_SPAWN_LOCATIONS; i++ )
	{
		m_SpawnLocationOrigins.Set( 0, vec3_origin );
	}
}

void CRD_CraftingMaterialInfo::GenerateSpawnLocations()
{
	CASW_Marine_Hint_Manager *pMarineHintManager = MarineHintManager();
	if ( !pMarineHintManager )
	{
		DevWarning( "Could not generate material spawn locations: missing marine hint manager\n" );
		return;
	}

	if ( pMarineHintManager->GetHintCount() == 0 )
	{
		DevWarning( "Could not generate material spawn locations: no marine hints in level\n" );
		return;
	}

	constexpr float flMinDistanceFromStart = 1536.0f;
	constexpr float flMinSpacing = 768.0f;
	constexpr int nDirections = 8;
	constexpr float flMaxOffset = 128.0f;
	constexpr float flSweepDist = 20.0f;

	CUtlVector<int> HintOrder;
	HintOrder.SetCount( pMarineHintManager->GetHintCount() );
	FOR_EACH_VEC( HintOrder, i )
	{
		HintOrder[i] = i;
	}

	// shuffle hint order
	FOR_EACH_VEC_BACK( HintOrder, i )
	{
		if ( i )
		{
			int j = RandomInt( 0, i );
			V_swap( HintOrder[i], HintOrder[j] );
		}
	}

	string_t iszInfoPlayerStart = AllocPooledString( "info_player_start" );

	m_nSpawnLocations = 0;
	FOR_EACH_VEC( HintOrder, iHintOrder )
	{
		if ( m_nSpawnLocations >= RD_MAX_CRAFTING_MATERIAL_SPAWN_LOCATIONS )
			break;

		int iHint = HintOrder[iHintOrder];
		// ignore hints that can move or hints that no longer exist
		if ( pMarineHintManager->GetHintFlags( iHint ) & ( HintData_t::HINT_DELETED | HintData_t::HINT_DYNAMIC ) )
			continue;

		Vector vecHintOrigin = pMarineHintManager->GetHintPosition( iHint );

		// ignore hints that are too close to marine spawn locations
		if ( CBaseEntity *pEnt = gEntList.FindEntityByClassnameNearestFast( iszInfoPlayerStart, vecHintOrigin, flMinDistanceFromStart ) )
		{
			if ( rd_debug_material_spawns.GetBool() )
			{
				NDebugOverlay::Line( vecHintOrigin, pEnt->GetAbsOrigin(), 255, 127, 127, false, 120.0f );
				NDebugOverlay::Text( vecHintOrigin, "Too close to marine spawn location", false, 120.0f );
			}

			continue;
		}
		// check for an active escape trigger (some maps use disabled escape triggers covering the entire playable space)
		if ( CTriggerMultiple *pEnt = ASWSpawnManager()->EscapeTriggerAtPoint( vecHintOrigin, false ) )
		{
			if ( rd_debug_material_spawns.GetBool() )
			{
				NDebugOverlay::Line( vecHintOrigin, pEnt->GetAbsOrigin(), 255, 127, 127, false, 120.0f );
				NDebugOverlay::Text( vecHintOrigin, "Within bounds of escape trigger", false, 120.0f );
			}

			continue;
		}
		// another material spawn point
		bool bTooClose = false;
		for ( int i = 0; i < m_nSpawnLocations; i++ )
		{
			if ( m_SpawnLocationOrigins[i].DistToSqr( vecHintOrigin ) < flMinSpacing * flMinSpacing )
			{
				bTooClose = true;

				if ( rd_debug_material_spawns.GetBool() )
				{
					NDebugOverlay::Line( vecHintOrigin, m_SpawnLocationOrigins[i], 255, 127, 127, false, 120.0f );
					NDebugOverlay::Text( vecHintOrigin, "Too close to other material spawn", false, 120.0f );
				}

				break;
			}
		}
		if ( bTooClose )
			continue;

		trace_t tr;
		Vector vecBestPos = vecHintOrigin;
		float flBestFraction = 1.0f;

		for ( int dir = 0; dir < nDirections; dir++ )
		{
			float flSin, flCos;
			SinCos( dir * M_PI * 2.0f / nDirections, &flSin, &flCos );

			// marine hull with padded sides and trimmed top and bottom
			Vector vecOffsetOrigin = vecHintOrigin + Vector( flCos * flMaxOffset, flSin * flMaxOffset, 0.0f );
			UTIL_TraceHull( vecHintOrigin, vecOffsetOrigin, Vector( -16, -16, 16 ), Vector( 16, 16, 56 ), MASK_PLAYERSOLID, NULL, COLLISION_GROUP_PLAYER_MOVEMENT, &tr );

			if ( tr.startsolid || tr.allsolid || tr.fraction >= 1.0f )
				continue;

			if ( flBestFraction > tr.fraction )
			{
				vecBestPos = tr.endpos;
				flBestFraction = tr.fraction;
			}
		}

		if ( flBestFraction >= 1.0f )
		{
			NDebugOverlay::Text( vecHintOrigin, "No nearby walls", false, 120.0f );
			continue;
		}

		// now we sweep towards the place we found, making sure we have relatively level floor the entire way
		int nIterations = Ceil2Int( flBestFraction * flMaxOffset / flSweepDist );
		bool bSweepFailed = false;
		for ( int i = 0; i < nIterations; i++ )
		{
			Vector vecStepStart = Lerp( ( i + 0.5f ) / nIterations, vecHintOrigin, vecBestPos ) + Vector( 0.0f, 0.0f, 48.0f );
			UTIL_TraceHull( vecStepStart, vecStepStart - Vector( 0.0f, 0.0f, 64.0f ), Vector( -12.0f, -12.0f, 0.0f ), Vector( 12.0f, 12.0f, 24.0f ), MASK_PLAYERSOLID, NULL, COLLISION_GROUP_PLAYER_MOVEMENT, &tr );

			if ( tr.startsolid || tr.allsolid || tr.fraction >= 1.0f )
			{
				bSweepFailed = true;

				if ( rd_debug_material_spawns.GetBool() )
				{
					NDebugOverlay::Text( vecHintOrigin, "Floor check failed", false, 120.0f );
				}

				break;
			}
		}

		if ( bSweepFailed )
			continue;

		if ( rd_debug_material_spawns.GetBool() )
		{
			NDebugOverlay::Box( tr.endpos, Vector( -12, -12, 0 ), Vector( 12, 12, 24 ), 255, 255, 255, false, 120.0f );
		}

		m_SpawnLocationOrigins.Set( m_nSpawnLocations, tr.endpos );
		m_nSpawnLocations++;
	}
}

CON_COMMAND( rd_debug_material_spawn_locations, "Generate and display crafting material spawn locations (requires developer and listen server)." )
{
	// doesn't work for non-listen server host anyway, so don't waste time generating positions
	if ( engine->IsDedicatedServer() || !UTIL_IsCommandIssuedByServerAdmin() )
		return;

	CRD_CraftingMaterialInfo info;

	info.GenerateSpawnLocations();

	Msg( "Generated %d/%d locations:\n", info.m_nSpawnLocations.Get(), RD_MAX_CRAFTING_MATERIAL_SPAWN_LOCATIONS );
	for ( int i = 0; i < info.m_nSpawnLocations; i++ )
	{
		Msg( "(%f, %f, %f)\n", VectorExpand( info.m_SpawnLocationOrigins[i] ) );
	}
}
#endif
