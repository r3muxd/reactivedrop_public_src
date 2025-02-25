#ifndef ASW_3D_MARINE_NAMES
#define ASW_3D_MARINE_NAMES
#ifdef _WIN32
#pragma once
#endif

#include "asw_input.h"
#include "iinput.h"
#include "hud.h"
#include <vgui_controls/Label.h>

using namespace vgui;

#include "asw_hudelement.h"

#include "c_asw_marine.h"

//-----------------------------------------------------------------------------
// Purpose: Shows the marines names drawn on top of the 3D view
//-----------------------------------------------------------------------------
class CASWHud3DMarineNames : public vgui::Panel, public CASW_HudElement
{
	DECLARE_CLASS_SIMPLE( CASWHud3DMarineNames, vgui::Panel );

public:
	CASWHud3DMarineNames( const char *pElementName );
	~CASWHud3DMarineNames();
	virtual void Init( void );
	virtual void VidInit( void );
	virtual void Reset( void );
	virtual void Paint();
	virtual void OnThink();
	virtual void PaintMarineNameLabels();
	virtual void PaintAimingDebug();
	virtual void PaintMarineLabel( int index, C_ASW_Marine *pMarine, C_ASW_Marine_Resource *pMR, bool bLocal );
	void PaintTrackedHealth();
	void PaintBoxesAroundUseEntities();
	void PaintBoxAround(C_BaseEntity* pEnt, int padding);
	virtual void ApplySchemeSettings(IScheme *pScheme);
	virtual bool ShouldDraw( void );
	virtual void PaintAutoaimCrosshairOn(C_BaseEntity *pEnt);
	bool PaintHealthBar( C_ASW_Marine *pMarine, float xPos, float yPos, bool bOnScreen );
	void PaintFontTest();
	void PaintTalkingIcon( C_ASW_Marine *pMarine, float xPos, float yPos );

	float GetUsingFraction( C_ASW_Marine *pMarine );

	// ugh, these really need to be pulled out into another class
	// aliens are calling into this, which is just bad.
	bool PaintUsingBar( C_ASW_Marine *pMarine, float xPos, float yPos );
	bool PaintReloadBar( C_ASW_Weapon *pWeapon, float xPos, float yPos );
	bool PaintAmmoBar( C_ASW_Weapon *pWeapon, float ammoPercentage, float xPos, float yPos );
	bool PaintGenericBar( Vector vWorldPos, float flProgress, Color rgbaBarColor = Color( 255, 255, 255, 255 ), float flSizeMultiplier = 1.0f, const Vector2D &offset = Vector2D(0, 0)  );
	bool PaintGenericText( Vector vWorldPos, char *pText, Color vTextColor = Color( 255, 255, 255, 255 ), float flSizeMultiplier = 1.0f, const Vector2D &offset = Vector2D(0, 0) );

	// marine health tooltip stuff	
	void UpdateHealthTooltip();
	void SetHealthMarine(C_ASW_Marine *pMarine);
	float m_fHealthAlpha;
	CHandle<C_ASW_Marine> m_hHealthQueuedMarine;
	CHandle<C_ASW_Marine> m_hHealthMarine;
	bool m_bHealthQueuedMarine;

	struct StrangeDeviceNotification_t
	{
		CHandle<C_ASW_Player> m_hOwner;
		CHandle<C_ASW_Inhabitable_NPC> m_hNPC;
		SteamItemDef_t m_iItemDefID;
		SteamItemDef_t m_iAccessoryID;
		int m_iPropertyIndex;
		int64_t m_iCounter;
		float m_flStartTime;

		int64_t m_iStartCounter;
		int64_t m_iCurrentCounter;
		wchar_t m_wszCounterNumber[32];
		int m_iCounterNumberWide;
		wchar_t m_wszItemName[128];
		int m_iItemNameWide;
		wchar_t m_wszAccessoryName[128];
		int m_iAccessoryNameWide;

		void Init( CASWHud3DMarineNames *pParent );
	};
	CUtlVectorAutoPurge<StrangeDeviceNotification_t *> m_StrangeDeviceNotifications;
	void OnStrangeDeviceTierNotification( C_ASW_Player *pOwner, C_ASW_Inhabitable_NPC *pNPC, SteamItemDef_t iItemDefID, SteamItemDef_t iAccessoryID, int iPropertyIndex, int64_t iCounter );
	void MsgFunc_RDStrangeDeviceTier( bf_read &msg );
	void PaintStrangeDeviceNotifications();

	CPanelAnimationVar( vgui::HFont, m_hMarineNameFont, "MarineNameFont", "Default" );
	CPanelAnimationVar( vgui::HFont, m_hSmallMarineNameFont, "SmallMarineNameFont", "DefaultSmall" );
	CPanelAnimationVar( vgui::HFont, m_hPlayerNameFont, "PlayerNameFont", "DefaultSmall" );
	CPanelAnimationVar( vgui::HFont, m_hMarineHealthFont, "MarineHealthFont", "Default" );
	CPanelAnimationVar( vgui::HFont, m_hNumberCounterFont, "NumberCounterFont", "DefaultVerySmall" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationNameFont, "NotificationNameFont", "DefaultMedium" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationNameBlurFont, "NotificationNameBlurFont", "DefaultMediumBlur" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationSmallNameFont, "NotificationSmallNameFont", "Default" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationSmallNameBlurFont, "NotificationSmallNameBlurFont", "DefaultBlur" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationNumberFont, "NotificationNumberFont", "DefaultExtraLarge" );
	CPanelAnimationVar( vgui::HFont, m_hNotificationNumberBlurFont, "NotificationNumberBlurFont", "DefaultExtraLargeBlur" );
	CPanelAnimationVarAliasType( int, m_nMarinePointerTexture, "MarinePointerTexture", "vgui/swarm/HUD/MarinePointer", "textureid" );
	CPanelAnimationVarAliasType( int, m_nBlackBarTexture, "BlackBarTexture", "vgui/swarm/HUD/ASWHUDBlackBar", "textureid" );	
	CPanelAnimationVarAliasType( int, m_nAutoaimCrosshairTexture, "AutoaimCrosshairTexture", "vgui/swarm/HUD/AutoAimCrosshair", "textureid" );	
	CPanelAnimationVarAliasType( int, m_nWhiteTexture, "WhiteTexture", "vgui/white", "textureid" );
	CPanelAnimationVarAliasType( int, m_nHorizHealthBar, "HealthBarTexture", "vgui/swarm/HUD/HorizHealthBar", "textureid" );
	CPanelAnimationVarAliasType( int, m_nVertAmmoBar, "VertAmmoBarTexture", "vgui/swarm/HUD/VertAmmoBar", "textureid" );
	CPanelAnimationVarAliasType( int, m_nOfficerClassIcon, "OfficerClassIcon", "vgui/swarm/ClassIcons/NCOClassIcon", "textureid" );
	CPanelAnimationVarAliasType( int, m_nSWClassIcon, "SWClassIcon", "vgui/swarm/ClassIcons/SpecialWeaponsClassIcon", "textureid" );
	CPanelAnimationVarAliasType( int, m_nMedicClassIcon, "MedicClassIcon", "vgui/swarm/ClassIcons/MedicClassIcon", "textureid" );
	CPanelAnimationVarAliasType( int, m_nTechClassIcon, "TechClassIcon", "vgui/swarm/ClassIcons/TechClassIcon", "textureid" );
	CPanelAnimationVarAliasType( int, m_nTalkingIcon, "TalkingIcon", "voice/voice_icon_hud", "textureid" );
	CPanelAnimationVarAliasType( int, m_nFastReloadBarBG, "FastReloadBarBG", "vgui/swarm/HUD/HorizHealthBar", "textureid" );
	CPanelAnimationVarAliasType( int, m_nMedicTexture, "MedicEmoteTexture", "vgui/swarm/Emotes/EmoteMedic", "textureid" );
	CPanelAnimationVarAliasType( int, m_nAmmoTexture, "AmmoEmoteTexture", "vgui/swarm/Emotes/EmoteAmmo", "textureid" );

private:
	inline float GetHealthBarMaxWidth( bool bKnockedOut )		const;
	inline float GetHealthBarMaxHeight( bool bKnockedOut )	const;
	inline float GetUsingBarMaxHeight()		const;
	inline float GetUsingBarMaxWidth()		const;
	inline float GetClassIconSize( bool bOnScreen );
	inline float GetTalkingIconSize();
	CPlayerBitVec m_3DSpeakingList;
	float		m_flLastTalkingTime[ASW_MAX_PLAYERS];

	float m_flLastReloadProgress;
	float m_flLastNextAttack;
	float m_flLastFastReloadStart;
	float m_flLastFastReloadEnd;

	// automatic calls for help (player2k's HUD mod)
	float m_flUnderMarineMagazineLastTime;
	float m_flUnderMarineMedicLastTime;
};


#endif // ASW_3D_MARINE_NAMES