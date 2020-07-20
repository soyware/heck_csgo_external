#pragma once

enum ItemDefinitionIndex
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFE_GG,
	WEAPON_KNIFE_CT,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	//WEAPON_MELEE = 74,	// prefab
	WEAPON_AXE = 75,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER
};

// change to array value table?
inline const char* GetWeaponClassName(int itemDefIndex)
{
	switch (itemDefIndex)
	{
	case WEAPON_DEAGLE: return "weapon_deagle";
	case WEAPON_ELITE: return "weapon_elite";
	case WEAPON_FIVESEVEN: return "weapon_fiveseven";
	case WEAPON_GLOCK: return "weapon_glock";
	case WEAPON_AK47: return "weapon_ak47";
	case WEAPON_AUG: return "weapon_aug";
	case WEAPON_AWP: return "weapon_awp";
	case WEAPON_FAMAS: return "weapon_famas";
	case WEAPON_G3SG1: return "weapon_g3sg1";
	case WEAPON_GALILAR: return "weapon_galilar";
	case WEAPON_M249: return "weapon_m249";
	case WEAPON_M4A1: return "weapon_m4a1";
	case WEAPON_MAC10: return "weapon_mac10";
	case WEAPON_P90: return "weapon_p90";
	case WEAPON_MP5SD: return "weapon_mp5sd";
	case WEAPON_UMP45: return "weapon_ump45";
	case WEAPON_XM1014: return "weapon_xm1014";
	case WEAPON_BIZON: return "weapon_bizon";
	case WEAPON_MAG7: return "weapon_mag7";
	case WEAPON_NEGEV: return "weapon_negev";
	case WEAPON_SAWEDOFF: return "weapon_sawedoff";
	case WEAPON_TEC9: return "weapon_tec9";
	case WEAPON_TASER: return "weapon_taser";
	case WEAPON_HKP2000: return "weapon_hkp2000";
	case WEAPON_MP7: return "weapon_mp7";
	case WEAPON_MP9: return "weapon_mp9";
	case WEAPON_NOVA: return "weapon_nova";
	case WEAPON_P250: return "weapon_p250";
	case WEAPON_SCAR20: return "weapon_scar20";
	case WEAPON_SG556: return "weapon_sg556";
	case WEAPON_SSG08: return "weapon_ssg08";
	case WEAPON_KNIFE_CT:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFE_GG:
	case WEAPON_KNIFE_GHOST:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_URSUS:
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case WEAPON_KNIFE_STILETTO:
	case WEAPON_KNIFE_WIDOWMAKER:
		return "weapon_knife";
	case WEAPON_FLASHBANG: return "weapon_flashbang";
	case WEAPON_HEGRENADE: return "weapon_hegrenade";
	case WEAPON_SMOKEGRENADE: return "weapon_smokegrenade";
	case WEAPON_MOLOTOV: return "weapon_molotov";
	case WEAPON_DECOY: return "weapon_decoy";
	case WEAPON_INCGRENADE: return "weapon_incgrenade";
	case WEAPON_C4: return "weapon_c4";
	case WEAPON_M4A1_SILENCER: return "weapon_m4a1_silencer";
	case WEAPON_USP_SILENCER: return "weapon_usp_silencer";
	case WEAPON_CZ75A: return "weapon_cz75a";
	case WEAPON_REVOLVER: return "weapon_revolver";
	case WEAPON_TAGRENADE: return "weapon_tagrenade";
	case WEAPON_HEALTHSHOT: return "weapon_healthshot";
	case WEAPON_FISTS: return "weapon_fists";
	case WEAPON_BREACHCHARGE: return "weapon_breachcharge";
	case WEAPON_TABLET: return "weapon_tablet";
	//case WEAPON_MELEE: return "weapon_melee";
	case WEAPON_AXE: return "weapon_axe";
	case WEAPON_HAMMER: return "weapon_hammer";
	case WEAPON_SPANNER: return "weapon_spanner";
	case WEAPON_FIREBOMB: return "weapon_firebomb";
	case WEAPON_DIVERSION: return "weapon_diversion";
	case WEAPON_FRAG_GRENADE: return "weapon_frag_grenade";
	default:
		std::cout << "Warning: GetWpnClassName got unexpected ItemDefIndex " << itemDefIndex << '\n';
		return "";
	}
}

inline const char* GetWeaponName(int itemDefIndex)
{
	switch (itemDefIndex)
	{
	case WEAPON_DEAGLE: return "Deagle";
	case WEAPON_ELITE: return "Dual Berettas";
	case WEAPON_FIVESEVEN: return "Five-SeveN";
	case WEAPON_GLOCK: return "Glock-18";
	case WEAPON_AK47: return "AK-47";
	case WEAPON_AUG: return "AUG";
	case WEAPON_AWP: return "AWP";
	case WEAPON_FAMAS: return "FAMAS";
	case WEAPON_G3SG1: return "G3SG1";
	case WEAPON_GALILAR: return "Galil AR";
	case WEAPON_M249: return "M249";
	case WEAPON_M4A1: return "M4A4";
	case WEAPON_MAC10: return "MAC-10";
	case WEAPON_P90: return "P90";
	case WEAPON_MP5SD: return "MP5-SD";
	case WEAPON_UMP45: return "UMP-45";
	case WEAPON_XM1014: return "XM1014";
	case WEAPON_BIZON: return "PP-Bizon";
	case WEAPON_MAG7: return "MAG-7";
	case WEAPON_NEGEV: return "Negev";
	case WEAPON_SAWEDOFF: return "Sawed-off";
	case WEAPON_TEC9: return "Tec-9";
	case WEAPON_TASER: return "Zeus";
	case WEAPON_HKP2000: return "P2000";
	case WEAPON_MP7: return "MP7";
	case WEAPON_MP9: return "MP9";
	case WEAPON_NOVA: return "Nova";
	case WEAPON_P250: return "P250";
	case WEAPON_SCAR20: return "SCAR-20";
	case WEAPON_SG556: return "SG 553";
	case WEAPON_SSG08: return "SSG 08";
	case WEAPON_KNIFE_CT:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFE_GG:
	case WEAPON_KNIFE_GHOST:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_URSUS:
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case WEAPON_KNIFE_STILETTO:
	case WEAPON_KNIFE_WIDOWMAKER:
		return "knife";
	case WEAPON_FLASHBANG: return "flashbang";
	case WEAPON_HEGRENADE:
	case WEAPON_FRAG_GRENADE:
		return "grenade";
	case WEAPON_SMOKEGRENADE: return "smoke";
	case WEAPON_MOLOTOV:
	case WEAPON_INCGRENADE:
	case WEAPON_FIREBOMB:
		return "molotov";
	case WEAPON_DECOY:
	case WEAPON_DIVERSION:
		return "decoy";
	case WEAPON_C4: return "bomb";
	case WEAPON_M4A1_SILENCER: return "M4A1-S";
	case WEAPON_USP_SILENCER: return "USP-S";
	case WEAPON_CZ75A: return "CZ75-A";
	case WEAPON_REVOLVER: return "Revolver";
	case WEAPON_TAGRENADE: return "ta grenade";
	case WEAPON_HEALTHSHOT: return "healthshot";
	case WEAPON_FISTS: return "fists";
	case WEAPON_BREACHCHARGE: return "breach charge";
	case WEAPON_TABLET: return "tablet";
	//case WEAPON_MELEE: return "melee";
	case WEAPON_AXE: return "axe";
	case WEAPON_HAMMER: return "hammer";
	case WEAPON_SPANNER: return "spanner";
	default:
		std::cout << "Warning: GetWpnName got unexpected ItemDefIndex " << itemDefIndex << '\n';
		return "";
	}
}

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE = 9,
	WEAPONTYPE_STACKABLE = 11,
	WEAPONTYPE_FISTS,
	WEAPONTYPE_BREACHCHARGE,
	WEAPONTYPE_TABLET,
	WEAPONTYPE_MELEE,
	WEAPONTYPE_UNKNOWN
};

inline CSWeaponType GetWeaponType(int itemDefIndex)
{
	switch (itemDefIndex)
	{
	case WEAPON_TASER:
	case WEAPON_KNIFE_GG:
	case WEAPON_KNIFE_CT:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFE_GHOST:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_URSUS:
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case WEAPON_KNIFE_STILETTO:
	case WEAPON_KNIFE_WIDOWMAKER:
		return WEAPONTYPE_KNIFE;
	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_GLOCK:
	case WEAPON_TEC9:
	case WEAPON_HKP2000:
	case WEAPON_P250:
	case WEAPON_USP_SILENCER:
	case WEAPON_CZ75A:
	case WEAPON_REVOLVER:
		return WEAPONTYPE_PISTOL;
	case WEAPON_MAC10:
	case WEAPON_P90:
	case WEAPON_MP5SD:
	case WEAPON_UMP45:
	case WEAPON_BIZON:
	case WEAPON_MP7:
	case WEAPON_MP9:
		return WEAPONTYPE_SUBMACHINEGUN;
	case WEAPON_AK47:
	case WEAPON_AUG:
	case WEAPON_FAMAS:
	case WEAPON_GALILAR:
	case WEAPON_M4A1:
	case WEAPON_SG556:
	case WEAPON_M4A1_SILENCER:
		return WEAPONTYPE_RIFLE;
	case WEAPON_XM1014:
	case WEAPON_MAG7:
	case WEAPON_SAWEDOFF:
	case WEAPON_NOVA:
		return WEAPONTYPE_SHOTGUN;
	case WEAPON_AWP:
	case WEAPON_G3SG1:
	case WEAPON_SCAR20:
	case WEAPON_SSG08:
		return WEAPONTYPE_SNIPER_RIFLE;
	case WEAPON_M249:
	case WEAPON_NEGEV:
		return WEAPONTYPE_MACHINEGUN;
	case WEAPON_C4:
		return WEAPONTYPE_C4;
	case WEAPON_FLASHBANG:
	case WEAPON_HEGRENADE:
	case WEAPON_SMOKEGRENADE:
	case WEAPON_MOLOTOV:
	case WEAPON_DECOY:
	case WEAPON_INCGRENADE:
	case WEAPON_TAGRENADE:
	case WEAPON_FIREBOMB:
	case WEAPON_DIVERSION:
	case WEAPON_FRAG_GRENADE:
		return WEAPONTYPE_GRENADE;
	case WEAPON_FISTS:
		return WEAPONTYPE_FISTS;
	case WEAPON_BREACHCHARGE:
		return WEAPONTYPE_BREACHCHARGE;
	case WEAPON_TABLET:
		return WEAPONTYPE_TABLET;
	case WEAPON_AXE:
	case WEAPON_HAMMER:
	case WEAPON_SPANNER:
		return WEAPONTYPE_MELEE;
	default:
		return WEAPONTYPE_UNKNOWN;
	}
}

struct CWeaponScript
{
	float flSpread,
		flSpreadAlt;

	float flInaccuracyMove,
		flInaccuracyMoveAlt;

	float flInaccuracyJumpInitial;

	float flMaxPlayerSpeed,
		flMaxPlayerSpeedAlt;

	void Parse(const char* in, const char* name)
	{
		char prefab[32];
		strcpy_s(prefab, sizeof(prefab), name);
		strcat_s(prefab, sizeof(prefab), "_prefab");

		const char* script = strstr(in, prefab);
		if (!script)
		{
			char err[64] = "Failed to find a script for ";
			strcat_s(err, sizeof(err), name);
			ErrorExit(err);
		}

		GetKeyValue(script, "spread\"", flSpread);
		GetKeyValue(script, "spread alt", flSpreadAlt);
		GetKeyValue(script, "inaccuracy move\"", flInaccuracyMove);
		GetKeyValue(script, "inaccuracy move alt", flInaccuracyMoveAlt);
		GetKeyValue(script, "inaccuracy jump initial", flInaccuracyJumpInitial);
		GetKeyValue(script, "max player speed\"", flMaxPlayerSpeed);
		GetKeyValue(script, "max player speed alt", flMaxPlayerSpeedAlt);
	}
} g_WeaponScript[65];
// we also can read type, weaponid etc..
void ReadWeaponsScript()
{
	char Path[MAX_PATH];
	strcpy_s(Path, sizeof(Path), Mem::GetDir());
	strcat_s(Path, sizeof(Path), "csgo\\scripts\\items\\items_game.txt");

	std::ifstream File(Path, std::ios::ate);
	if (File.fail())
		ErrorExit("Failed to open the weapons script");

	const int len = File.tellg();
	File.seekg(0, File.beg);

	char* Content = new char[len];
	File.read(Content, len);
	File.close();

	for (UINT i = WEAPON_DEAGLE; i < WEAPON_REVOLVER; ++i)
	{
		const CSWeaponType type = GetWeaponType(i);
		if ((WEAPONTYPE_PISTOL <= type) && (type <= WEAPONTYPE_MACHINEGUN))
		{
			const char* className = GetWeaponClassName(i);
			if (!className)
				ErrorExit("Failed to get weapon's classname");

			g_WeaponScript[i].Parse(Content, className);
			g_WeaponScript[i].flSpread *= 0.001f;
			g_WeaponScript[i].flSpreadAlt *= 0.001f;
			g_WeaponScript[i].flInaccuracyMove *= 0.001f;
			g_WeaponScript[i].flInaccuracyMoveAlt *= 0.001f;
			g_WeaponScript[i].flInaccuracyJumpInitial *= 0.001f;
		}
	}

	delete[] Content;
}

class CWeapon
{
public:
	int		m_iItemDefinitionIndex;
	float	m_flNextPrimaryAttack;
	int		m_iClip1;
	bool	m_bInReload;
	int		m_weaponMode;
	float	m_fAccuracyPenalty;
	int		m_zoomLevel;

	inline void SetFromChunk(std::byte* chunk)
	{
		CHUNKTONETVAR(chunk, m_iItemDefinitionIndex);
		CHUNKTONETVAR(chunk, m_flNextPrimaryAttack);
		CHUNKTONETVAR(chunk, m_iClip1);
		CHUNKTONETVAR(chunk, m_bInReload);
		CHUNKTONETVAR(chunk, m_weaponMode);
		CHUNKTONETVAR(chunk, m_fAccuracyPenalty);
		CHUNKTONETVAR(chunk, m_zoomLevel);
	}

	inline bool CanScope() const
	{
		return (m_iItemDefinitionIndex == WEAPON_SG556) ||
			(m_iItemDefinitionIndex == WEAPON_AUG) ||
			(m_iItemDefinitionIndex == WEAPON_SSG08) ||
			(m_iItemDefinitionIndex == WEAPON_AWP) ||
			(m_iItemDefinitionIndex == WEAPON_G3SG1) ||
			(m_iItemDefinitionIndex == WEAPON_SCAR20);
	}

	inline float GetSpread() const
	{
		return m_weaponMode ? g_WeaponScript[m_iItemDefinitionIndex].flSpreadAlt : g_WeaponScript[m_iItemDefinitionIndex].flSpread;
	}

	float GetInaccuracy(const CPlayer& pOwner) const
	{
		float flInaccuracyMove, flMaxPlayerSpeed;
		if (m_weaponMode)
		{
			flInaccuracyMove = g_WeaponScript[m_iItemDefinitionIndex].flInaccuracyMoveAlt;
			flMaxPlayerSpeed = g_WeaponScript[m_iItemDefinitionIndex].flMaxPlayerSpeedAlt;
		}
		else
		{
			flInaccuracyMove = g_WeaponScript[m_iItemDefinitionIndex].flInaccuracyMove;
			flMaxPlayerSpeed = g_WeaponScript[m_iItemDefinitionIndex].flMaxPlayerSpeed;
		}

		float flInaccuracy = m_fAccuracyPenalty;

		//						(flVelocity - (MaxPlayerSpeed * 0.34)) / ((MaxPlayerSpeed * 0.95) - (MaxPlayerSpeed * 0.34))
		const float someScale = (pOwner.m_vecAbsVelocity.Length2D() - (flMaxPlayerSpeed * 0.34f)) / (flMaxPlayerSpeed * 0.61f);
		if (someScale > 0.f)
		{
			if (someScale >= 1.f)
				flInaccuracy += flInaccuracyMove;
			else
				flInaccuracy += flInaccuracyMove * (pOwner.m_bIsWalking ? someScale : sqrt(sqrt(someScale)));
		}

		if (!(pOwner.m_fFlags & FL_ONGROUND))
		{
			//uint32_t dwJumpImpulse;
			//Mem::Read<uint32_t>(Offsets::sv_jump_impulseFloat, dwJumpImpulse);
			//dwJumpImpulse ^= Offsets::sv_jump_impulse;

			const float sqrtVelocityZ = sqrt(abs(pOwner.m_vecAbsVelocity.z));
			const float inaccJumpInitial = g_WeaponScript[m_iItemDefinitionIndex].flInaccuracyJumpInitial/* * HexToFloat(Mem::Read<uint32_t>(Offsets::weapon_air_spread_scaleFloat) ^ Offsets::weapon_air_spread_scale)*/;

			//if (!dwJumpImpulse)
			//{
			//	if (sqrtVelocityZ < 0.f)
			//	{
			//		const float someInaccuracy2x = someInaccuracy * 2.f;
			//		if (0.f > someInaccuracy2x)
			//			flInaccuracy += someInaccuracy2x;
			//	}
			//	else if (someInaccuracy > 0.f)
			//		flInaccuracy += someInaccuracy;
			//}
			//else
			{
				const float sqrtJumpImpulse = 17.37795664052595108787552411148f/*sqrt(HexToFloat(dwJumpImpulse))*/;
				const float sqrtJumpImpulse025 = sqrtJumpImpulse * 0.25f;
				const float someScale2 = ((sqrtVelocityZ - sqrtJumpImpulse025) * inaccJumpInitial) / (sqrtJumpImpulse - sqrtJumpImpulse025);
				if (someScale2 >= 0.f)
				{
					const float inaccJumpInitialx2 = inaccJumpInitial * 2.f;
					flInaccuracy += (someScale2 > inaccJumpInitialx2) ? inaccJumpInitialx2 : someScale2;
				}
			}
		}

		if (flInaccuracy > 1.f)
			return 1.f;
		else
			return flInaccuracy;
	}
	
	bool IsLowFirerate() const
	{
		switch (m_iItemDefinitionIndex)
		{
		case WEAPON_CZ75A:
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_MP5SD:
		case WEAPON_UMP45:
		case WEAPON_BIZON:
		case WEAPON_MP7:
		case WEAPON_MP9:
		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_FAMAS:
		case WEAPON_GALILAR:
		case WEAPON_M4A1:
		case WEAPON_SG556:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_M249:
		case WEAPON_NEGEV:
			return false;
		default:
			return true;
		}
	}

};

inline bool CPlayer::GetWeapon(CWeapon& out) const
{
	if (m_hActiveWeapon == -1)
		return false;

	uintptr_t pWeapon = Mem::Read<uintptr_t>(Signatures::EntityList + ((m_hActiveWeapon & 0xFFF) - 1) * sizeof(CEntInfo));

	std::byte* chunk = new std::byte[NetVars::m_zoomLevel + sizeof(int)];
	ReadProcessMemory(Mem::Process, reinterpret_cast<LPCVOID>(pWeapon), chunk, NetVars::m_zoomLevel + sizeof(int), 0);
	out.SetFromChunk(chunk);
	delete[] chunk;

	return true;
}
