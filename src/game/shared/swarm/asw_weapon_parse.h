#ifndef _INCLUDED_ASW_WEAPON_PARSE_H
#define _INCLUDED_ASW_WEAPON_PARSE_H
#ifdef _WIN32
#pragma once
#endif

#include "weapon_parse.h"
#include "networkvar.h"

enum ASW_Offhand_Order_t
{
	ASW_OFFHAND_USE_IMMEDIATELY,		// AI marine can just use this item immediately, without caring about facing/position
	ASW_OFFHAND_THROW,					// AI marine needs to get line of sight to throw this item at the order destination
	ASW_OFFHAND_DEPLOY,					// AI marine needs to walk up to the deploy spot
};

//--------------------------------------------------------------------------------------------------------
class CASW_WeaponInfo : public FileWeaponInfo_t
{
public:
	DECLARE_CLASS_GAMEROOT( CASW_WeaponInfo, FileWeaponInfo_t );
	
	CASW_WeaponInfo();
	
	virtual void Parse( ::KeyValues *pKeyValuesData, const char *szWeaponName );


public:
	// asw:
	float				flReloadTime;
	float				m_flBaseDamage;
	float				m_flFireRate;
	float				m_flSecondaryFireRate;
	int					m_iNumPellets;
	int					m_iDisplayClipSize;
	float				m_flDisplayReloadTime;
	int					m_iPlayerModelSkin;
	int					m_iDisplayModelSkin;
	char				szDisplayModel[64];  // the model displayed in the loadout screen
	char				szDisplayModel2[64];  // the second model shown in addition to the first in the loadout screen
	float				m_flModelPanelZOffset;
	bool				m_bShowCharges;	//whether this item shows charges on the left side HUD thing or not
	bool				m_bShowBatteryCharge;		// show a battery charge progress under the icon
	bool				m_bShowLocalPlayerHotkey;
	bool				m_bShowMultiplayerHotkey;
	bool				m_bOffhandActivate;	// can you activate this weapon even when it isn't your current
	bool				m_bHUDPlayerActivate;
	bool				m_bOffhandSwitch;		// should we switch to this weapon when we press our offhand key
	ASW_Offhand_Order_t m_nOffhandOrderType;
	int					m_iHUDIconOffsetX, m_iHUDIconOffsetY;
	int					m_iHUDNumberOffsetX, m_iHUDNumberOffsetY;
	bool				m_bZoomHotbarIcon;		// zoom this icon on the squad hotbar

	float		m_fFlinchChance;		// chance of this weapon putting the drone into a flinch
	float		m_fStoppingPowerFlinchBonus;	// bonus to the flinch chance per stopping power skill point
	int			m_iShowBulletsOnHUD;
	int			m_iShowClipsOnHUD;
	int			m_iShowGrenadesOnHUD;
	int			m_iShowSecondaryBulletsOnHUD;
	bool		m_bOrientToLaser;		// if true, this weapon will orient itself along the laser sight
	bool		m_bShowClipsInWeaponDetail;
	bool		m_bShowClipsDoubled;

	int			m_iSquadEmote;

	Vector m_vecStrangeDeviceOffset[5];
	QAngle m_angStrangeDeviceAngle[5];
	char m_szStrangeDeviceBone[5][64];
	bool m_bUseStrangeDeviceWorldOffsets;
	Vector m_vecStrangeDeviceOffsetWorld[5];
	QAngle m_angStrangeDeviceAngleWorld[5];
	char m_szStrangeDeviceBoneWorld[5][64];
};


#endif // _INCLUDED_ASW_WEAPON_PARSE_H
