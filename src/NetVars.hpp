#pragma once

#ifdef GetProp
#undef GetProp
#endif

namespace NetVars
{
	RecvTable* GetTable(const char* name)
	{
		ClientClass cc;
		Mem::Read<ClientClass>(Signatures::g_pClientClassHead, cc);

		while (true)
		{
			char varname[64];
			Mem::Read<char[64]>(reinterpret_cast<uintptr_t>(cc.m_pNetworkName), varname);

			if (!strcmp(varname, name))
				return cc.m_pRecvTable;

			if (cc.m_pNext == 0)
				break;

			Mem::Read<ClientClass>(reinterpret_cast<uintptr_t>(cc.m_pNext), cc);
		}

		return nullptr;
	}

	int GetProp(RecvTable* pTable, const char* name)
	{
		RecvTable table;
		Mem::Read<RecvTable>(reinterpret_cast<uintptr_t>(pTable), table);

		int offset = 0;
		for (int i = 0; i < table.m_nProps; ++i)
		{
			RecvProp prop;
			Mem::Read<RecvProp>(reinterpret_cast<uintptr_t>(table.m_pProps) + i * sizeof(RecvProp), prop);
			if (prop.m_RecvType == DPT_DataTable)
			{
				int extra = GetProp(prop.m_pDataTable, name);
				if (extra)
					offset += prop.m_Offset + extra;
			}
			else
			{
				char varname[64];
				Mem::Read<char[64]>(reinterpret_cast<uintptr_t>(prop.m_pVarName), varname);

				if (!strcmp(varname, name))
					return prop.m_Offset;
			}
		}
		return offset;
	}

	int GetOffset(const char* tableName, const char* varName)
	{
		RecvTable* table = GetTable(tableName);
		if (!table)
			ErrorExit("Failed to find a netvar");

		int offset = GetProp(table, varName);
		if (!offset)
			ErrorExit("Failed to find a netvar");

#ifdef _DEBUG
		std::cout << "Found " << varName << " -> 0x" << std::hex << offset << '\n';
#endif
		return offset;
	}

	int m_clrRender,
		m_iTeamNum,
		m_vecOrigin,
		m_nModelIndex,
		m_flSimulationTime,
		m_bSpotted,

		m_pBones,

		m_iHealth,
		m_fFlags,
		m_vecViewOffset,
		m_vecVelocity,
		m_lifeState,
		m_aimPunchAngle,
		m_iDefaultFOV,
		m_nTickBase,

		m_hActiveWeapon,

		m_bIsScoped,
		m_bIsWalking,
		m_bGunGameImmunity,
		m_iShotsFired,
		m_nSurvivalTeam,
		m_flFlashAlpha,
		m_flFlashMaxAlpha,
		m_angEyeAngles,
		m_iIDEntIndex,

		m_iItemDefinitionIndex,
		m_flNextPrimaryAttack,
		m_iClip1,
		m_bInReload,
		m_weaponMode,
		m_fAccuracyPenalty,
		m_zoomLevel,

		m_bFreezePeriod,
		m_bWarmupPeriod,
		m_bIsQueuedMatchmaking;

	void Find()
	{
#ifdef _DEBUG
		std::cout << '\n';
#endif // _DEBUG

		m_clrRender					= GetOffset("CBaseEntity", "m_clrRender");
		m_iTeamNum					= GetOffset("CBaseEntity", "m_iTeamNum");
		m_vecOrigin					= GetOffset("CBaseEntity", "m_vecOrigin");
		m_nModelIndex				= GetOffset("CBaseEntity", "m_nModelIndex");
		m_flSimulationTime			= GetOffset("CBaseEntity", "m_flSimulationTime");
		m_bSpotted					= GetOffset("CBaseEntity", "m_bSpotted");

		m_pBones					= GetOffset("CBaseAnimating", "m_nForceBone") + 28;

		m_iHealth					= GetOffset("CBasePlayer", "m_iHealth");
		m_fFlags					= GetOffset("CBasePlayer", "m_fFlags");
		m_vecViewOffset				= GetOffset("CBasePlayer", "m_vecViewOffset[0]");
		m_vecVelocity				= GetOffset("CBasePlayer", "m_vecVelocity[0]");
		m_lifeState					= GetOffset("CBasePlayer", "m_lifeState");
		m_aimPunchAngle				= GetOffset("CBasePlayer", "m_aimPunchAngle");
		m_iDefaultFOV				= GetOffset("CBasePlayer", "m_iDefaultFOV");
		m_nTickBase					= GetOffset("CBasePlayer", "m_nTickBase");

		m_hActiveWeapon				= GetOffset("CBaseCombatCharacter", "m_hActiveWeapon");

		m_bIsScoped					= GetOffset("CCSPlayer", "m_bIsScoped");
		m_bIsWalking				= GetOffset("CCSPlayer", "m_bIsWalking");
		m_bGunGameImmunity			= GetOffset("CCSPlayer", "m_bGunGameImmunity");
		m_iShotsFired				= GetOffset("CCSPlayer", "m_iShotsFired");
		m_nSurvivalTeam				= GetOffset("CCSPlayer", "m_nSurvivalTeam");
		m_flFlashMaxAlpha			= GetOffset("CCSPlayer", "m_flFlashMaxAlpha");
		m_flFlashAlpha				= m_flFlashMaxAlpha - 12;
		m_angEyeAngles				= GetOffset("CCSPlayer", "m_angEyeAngles[0]");
		m_iIDEntIndex				= GetOffset("CCSPlayer", "m_bHasDefuser") + 92;

		m_iItemDefinitionIndex		= GetOffset("CEconEntity", "m_iItemDefinitionIndex");
		m_flNextPrimaryAttack		= GetOffset("CBaseCombatWeapon", "m_flNextPrimaryAttack");
		m_iClip1					= GetOffset("CBaseCombatWeapon", "m_iClip1");
		m_bInReload					= GetOffset("CBaseCombatWeapon", "m_flTimeWeaponIdle") + 49;
		m_weaponMode				= GetOffset("CWeaponCSBase", "m_weaponMode");
		m_fAccuracyPenalty			= GetOffset("CWeaponCSBase", "m_fAccuracyPenalty");
		m_zoomLevel					= GetOffset("CWeaponCSBaseGun", "m_zoomLevel");

		m_bFreezePeriod				= GetOffset("CCSGameRulesProxy", "m_bFreezePeriod");
		m_bWarmupPeriod				= GetOffset("CCSGameRulesProxy", "m_bWarmupPeriod");
		m_bIsQueuedMatchmaking		= GetOffset("CCSGameRulesProxy", "m_bIsQueuedMatchmaking");
	}
}