#ifndef _INCLUDED_ASW_EQUIPMENT_LIST_H
#define _INCLUDED_ASW_EQUIPMENT_LIST_H
#pragma once

class CASW_WeaponInfo;

enum ASW_Equip_Regular
{
	ASW_EQUIP_RIFLE,
	ASW_EQUIP_PRIFLE,
	ASW_EQUIP_AUTOGUN,
	ASW_EQUIP_VINDICATOR,
	ASW_EQUIP_PISTOL,
	ASW_EQUIP_SENTRY,
	ASW_EQUIP_HEAL_GRENADE,
	ASW_EQUIP_AMMO_SATCHEL,

	ASW_EQUIP_SHOTGUN,
	ASW_EQUIP_TESLA_GUN,
	ASW_EQUIP_RAILGUN,
	ASW_EQUIP_HEAL_GUN,
	ASW_EQUIP_PDW,
	ASW_EQUIP_FLAMER,
	ASW_EQUIP_SENTRY_FREEZE,
	ASW_EQUIP_MINIGUN,
	ASW_EQUIP_SNIPER_RIFLE,
	ASW_EQUIP_SENTRY_FLAMER,
	ASW_EQUIP_CHAINSAW,
	ASW_EQUIP_SENTRY_CANNON,
	ASW_EQUIP_GRENADE_LAUNCHER,
	ASW_EQUIP_DEAGLE,
	ASW_EQUIP_DEVASTATOR,
	ASW_EQUIP_COMBAT_RIFLE,
	ASW_EQUIP_HEALAMP_GUN,
	ASW_EQUIP_HEAVY_RIFLE,
	ASW_EQUIP_MEDRIFLE,

	ASW_EQUIP_FIRE_EXTINGUISHER,
	ASW_EQUIP_MINING_LASER,
	ASW_EQUIP_50CALMG,
	ASW_EQUIP_FLECHETTE,
	ASW_EQUIP_RICOCHET,
	ASW_EQUIP_AMMO_BAG,
	ASW_EQUIP_MEDICAL_SATCHEL,
	ASW_EQUIP_AR2,
#ifdef RD_7A_WEAPONS
	ASW_EQUIP_CRYO_CANNON,
	ASW_EQUIP_PLASMA_THROWER,
	ASW_EQUIP_HACK_TOOL,
	ASW_EQUIP_SENTRY_RAILGUN,
	ASW_EQUIP_ENERGY_SHIELD,
	ASW_EQUIP_REVIVE_TOOL,
#endif

	ASW_NUM_EQUIP_REGULAR,
	ASW_FIRST_HIDDEN_EQUIP_REGULAR = ASW_EQUIP_FIRE_EXTINGUISHER,
};

enum ASW_Equip_Extra
{
	ASW_EQUIP_MEDKIT,
	ASW_EQUIP_WELDER,
	ASW_EQUIP_FLARES,
	ASW_EQUIP_LASER_MINES,

	ASW_EQUIP_NORMAL_ARMOR,
	ASW_EQUIP_BUFF_GRENADE,
	ASW_EQUIP_HORNET_BARRAGE,
	ASW_EQUIP_FREEZE_GRENADES,
	ASW_EQUIP_STIM,
	ASW_EQUIP_TESLA_TRAP,
	ASW_EQUIP_ELECTRIFIED_ARMOR,
	ASW_EQUIP_MINES,
	ASW_EQUIP_FLASHLIGHT,
	ASW_EQUIP_FIST,
	ASW_EQUIP_GRENADES,
	ASW_EQUIP_NIGHT_VISION,
	ASW_EQUIP_SMART_BOMB,
	ASW_EQUIP_GAS_GRENADES,

	ASW_EQUIP_T75,
	ASW_EQUIP_BLINK,
	ASW_EQUIP_JUMP_JET,
	ASW_EQUIP_BAIT,
#ifdef RD_7A_WEAPONS
	ASW_EQUIP_STUN_GRENADES,
	ASW_EQUIP_INCENDIARY_GRENADES,
	ASW_EQUIP_SPEED_BURST,
	ASW_EQUIP_SHIELD_BUBBLE,
#endif

	ASW_NUM_EQUIP_EXTRA,
	ASW_FIRST_HIDDEN_EQUIP_EXTRA = ASW_EQUIP_T75,
};

class CASW_EquipItem
{
public:
	DECLARE_CLASS_NOBASE( CASW_EquipItem );

	CASW_EquipItem( int iItemIndex, const char *szEquipClass, const char *szShortName, const char *szLongName,
		const char *szDescription1, const char *szAltFireDescription, const char *szAttributeDescription,
		bool bSelectableInBriefing, bool bIsExtra, const char *szAmmo1, const char *szAmmo2,
		const char *szEquipIcon, ConVar *pDefaultAmmo1, ConVar *pMaxAmmo1, ConVar *pDefaultAmmo2, ConVar *pMaxAmmo2,
		int iRequiredClass = -1, bool bIsUnique = false, bool bViewModelIsMarineAttachment = false, bool bViewModelHidesMarineBodyGroup1 = false );

	int DefaultAmmo1() const;
	int MaxAmmo1() const;
	int DefaultAmmo2() const;
	int MaxAmmo2() const;

	void LevelInitPreEntity();

	// the items index in the list of equipment
	const int m_iItemIndex;
	const int m_iRequiredClass;
	int m_iAmmo1;
	int m_iAmmo2;
	ConVar *const m_pDefaultAmmo1;
	ConVar *const m_pMaxAmmo1;
	ConVar *const m_pDefaultAmmo2;
	ConVar *const m_pMaxAmmo2;
	const char *const m_szEquipClass;
	const char *const m_szShortName;
	const char *const m_szLongName;
	const char *const m_szDescription1;
	const char *const m_szAltFireDescription;
	const char *const m_szAttributeDescription;
	const char *const m_szAmmo1;
	const char *const m_szAmmo2;
	const char *const m_szEquipIcon;
	const bool m_bSelectableInBriefing : 1; // if false, this item won't show up on the loadout screen unless an inventory item is equipped
	const bool m_bIsExtra : 1;
	const bool m_bIsUnique : 1;
	const bool m_bViewModelIsMarineAttachment : 1;
	const bool m_bViewModelHidesMarineBodyGroup1 : 1;
	string_t m_EquipClass;
};

// This class describes the fixed data about the weapons available on the loadout screen

class CASW_EquipmentList : public CAutoGameSystem
{
public:
	CASW_EquipmentList();

	void LevelInitPreEntity() override;

	// return info on a particular weapon data
	CASW_WeaponInfo *GetWeaponDataFor( const char *szWeaponClass );
	CASW_EquipItem *GetEquipItemFor( const char *szWeaponClass );

	// find the index of a particular item
	int GetRegularIndex( const char *szWeaponClass );
	int GetExtraIndex( const char *szWeaponClass );

	// Automatically returns a regular or extra item based on wpnslot
	int GetIndexForSlot( int iWpnSlot, const char *szWeaponClass );

	CASW_EquipItem *GetRegular( int index );
	int GetNumRegular( bool bIncludeHidden );
	CASW_EquipItem *GetExtra( int index );
	int GetNumExtra( bool bIncludeHidden );

	// Automatically returns a regular or extra item based on wpnslot
	CASW_EquipItem *GetItemForSlot( int iWpnSlot, int index );

#ifdef CLIENT_DLL
	void LoadTextures();
	void LoadTextures( CUtlVector<int> &TextureIDs, CASW_EquipItem *pEquipItems, int nEquipItems );
	int GetEquipIconTexture( bool bRegular, int iIndex );
	bool m_bLoadedTextures;
	CUtlVector<int> m_iRegularTexture;
	CUtlVector<int> m_iExtraTexture;
#endif
};

extern CASW_EquipmentList g_ASWEquipmentList;

#endif /* _INCLUDED_ASW_EQUIPMENT_LIST_H */