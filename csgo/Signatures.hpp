#pragma once

namespace Signatures
{
	uintptr_t g_pClientClassHead,
		m_pStudioHdr,
		m_Hits,
		m_bDidSmokeEffectPlus,

		Attack,
		Attack2,
		Jump,
		Forward,
		Back,
		Right,
		Left,

		EntityList,
		GlobalVars,
#ifndef NDEBUG
		bSendPacket,
#endif
		nameChangeCallbacks,

		ClientState,
		m_nSignonState,
#ifdef NDEBUG
		m_flNextCmdTime,
#endif
		m_nDeltaTick,
		m_nPlayerSlot,
		m_szLevelName,
		m_vecViewAngles,
		m_nLastOutgoingCommand,
		m_NetChannel,
		m_nOutSequenceNr = 0x18,

		GlowObjectManager,
		GameRulesProxy,
		//RadarBase,
		s_bOverridePostProcessing,
		Callback__IsReady,
		ConfirmedReservationCallback,
		Spec_Show_Xray_Callback,
		SmokeCount,
		//m_iMaxUsedServerIndex,
		//SendClanTag,
		//SetInfo_part,
		g_bVoiceRecording,

		Input,
		m_fMouseActive,
		m_pCommands,
		m_pVerifiedCommands,

		ServerRankRevealAll,
		ClientCmd_Unrestricted,
		ModelInfoClient,
		bOverlayActivated,
		LoadNamedSkys,

		cl_mouseenable,
		cl_mouseenableInt,
		weapon_recoil_view_punch_extra,
		weapon_recoil_view_punch_extraFloat,
		weapon_recoil_scale,
		weapon_recoil_scaleFloat,
		//weapon_air_spread_scale,
		//weapon_air_spread_scaleFloat,
		//sv_jump_impulse,
		//sv_jump_impulseFloat,
		viewmodel_fov,
		viewmodel_fovFloat,
		mat_force_tonemap_scale,
		mat_force_tonemap_scaleFloat;

	void Find()
	{
		// Unknown entity update received by ProcessSpottedEntityUpda
		Mem::Read<uintptr_t>(		  Mem::FindSignature("client.dll", "\x33\xDB\xD3\xE0\x89\x5D\xF4\x09\x84\x97\x00\x00\x00\x00\xA1",	"xxxxxxxxxx????x",	15), g_pClientClassHead);
		m_pStudioHdr				= Mem::FindSignature("client.dll", "\x8B\xB6\x00\x00\x00\x00\x85\xF6\x74\x05\x83\x3E\x00\x75\x02\x33\xF6\xF3\x0F\x10\x44\x24", "xx????xxxxxxxxxxxxxxxx", 2);
		m_Hits						= Mem::FindSignature("client.dll", "\x8D\x88\x00\x00\x00\x00\xF3\x0F\x11\x45\xE4", "xx??xxxxxxx", 2);
		m_bDidSmokeEffectPlus		= Mem::FindSignature("client.dll", "\xC6\x87\x00\x00\x00\x00\x01\x66\x0F\xD6\x45\xF4", "xx??xxxxxxxx", 2);

		Attack						= Mem::FindSignature("client.dll", "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x01",			"xx????xxxxxxx",	2);
		Attack2						= Mem::FindSignature("client.dll", "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x81\xCA\x00\x08",		"xx????xxxxxxxx",	2);
		Jump						= Mem::FindSignature("client.dll", "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02",			"xx????xxxxxxx",	2);
		Forward						= Mem::FindSignature("client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08",								"xxxxxxxx");
		Mem::Read<uintptr_t>(Forward + 0x11F, Back);
		Mem::Read<uintptr_t>(Forward + 0x1D1, Left);
		Mem::Read<uintptr_t>(Forward + 0x200, Right);
		Mem::Read<uintptr_t>(Forward + 0xF5, Forward);

		EntityList					= Mem::FindSignature("client.dll", "\xBE\x01\x00\x00\x00\xBB\x00\x00\x00\x00\x0F\x1F\x00",			"xxxxxx????xxx",	6);
		Mem::Read<uintptr_t>(		  Mem::FindSignature("client.dll", "\xA1\x00\x00\x00\x00\x8B\x4D\xFC\x8B\x40\x10",					"x????xxxxxx",		1), GlobalVars);

		GlowObjectManager			= Mem::FindSignature("client.dll", "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B",							"x????xxxx",		1) + 0x4;
		GameRulesProxy				= Mem::FindSignature("client.dll", "\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x85\xC9\x74\x07",			"xxxxx????xxxx",	5);
		//Mem::Read<uintptr_t>(
		//	Mem::Read<uintptr_t>(	  Mem::FindSignature("client.dll", "\x00\xA1\x00\x00\x00\x00\x8B\x0C\xB0\x8B\x01\xFF\x50\x00\x46",	"xx????xxxxxxx?x",	2)) + 0x74, RadarBase);	RadarBase += 0x180;
		s_bOverridePostProcessing	= Mem::FindSignature("client.dll", "\x80\x3D\x00\x00\x00\x00\x00\x53\x56\x57\x0F\x85",				"xx????xxxxxx",		2);
		Callback__IsReady			= Mem::FindSignature("client.dll", "\x56\x8B\x35\x00\x00\x00\x00\x57\x83\xBE",						"xxx????xxx"		) - 0x4;
		ConfirmedReservationCallback = Mem::Read<uintptr_t>(Callback__IsReady + 0x7);
		Spec_Show_Xray_Callback		= Mem::FindSignature("client.dll", "\x53\x56\x57\xBE\x01\x00\x00\x00\xBF",							"xxxx?xxxx"			) + 0x4;
		SmokeCount					= Mem::FindSignature("client.dll", "\xA3\x00\x00\x00\x00\x57\x8B\xCB",								"x????xxx",			1);
		//m_iMaxUsedServerIndex		= Mem::FindSignature("client.dll", "\xB9\x00\x00\x00\x00\x53\x56\xFF\x50\x18",						"x????xxxxx",		1) + 0x24;

		Input						= Mem::FindSignature("client.dll", "\xB9\x00\x00\x00\x00\xF3\x0F\x11\x04\x24\xFF\x50\x10",			"x????xxxxxxxx",	1);
		m_fMouseActive = Input + 0xE;
		m_pCommands = Input + 0xF4;
		m_pVerifiedCommands = m_pCommands + 0x4;

		ServerRankRevealAll			= Mem::FindSignature("client.dll", "\x8D\x4E\x74\x8B\xC4\xC7\x40\x04\x00\x00\x00\x00\xC7\x00",		"xxxxxxxx????xx",	14);

		cl_mouseenable				= Mem::FindSignature("client.dll", "\xB9\x00\x00\x00\x00\xFF\x50\x34\x85\xC0\x75\x10\x8B",			"x????xxxxxxxx",	1);		cl_mouseenableInt = cl_mouseenable + 0x30;
		weapon_recoil_view_punch_extra = Mem::FindSignature("client.dll", "\xFF\x90\x00\x05\x00\x00\x8B\x0D\x00\x00\x00\x00\x81\xF9",	"xx?xxxxx????xx",	14);	weapon_recoil_view_punch_extraFloat = weapon_recoil_view_punch_extra + 0x2C;
		weapon_recoil_scale			= Mem::FindSignature("client.dll", "\xF3\x0F\x59\xC1\xEB\x3E\x8B\x0D\x00\x00\x00\x00\x81\xF9",		"xxxxxxxx????xx",	14);	weapon_recoil_scaleFloat = weapon_recoil_scale + 0x2C;
		//weapon_air_spread_scale		= Mem::FindSignature("client.dll", "\xF3\x0F\x10\x92\x00\x01\x00\x00",								"xxxx?xxx",		22);	weapon_air_spread_scaleFloat = weapon_air_spread_scale + 0x2C;
		//sv_jump_impulse				= Mem::FindSignature("client.dll", "\xF3\x0F\x59\x54\x24\x10\x8B\x0D",								"xxxxxxxx",		20);	sv_jump_impulseFloat = sv_jump_impulse + 0x2C;
		viewmodel_fov				= Mem::FindSignature("client.dll", "\xF3\x0F\x11\x45\xF8\x81\x75\xF8\x00\x00\x00\x00\xD9",			"xxxxxxxx????x",	8);		viewmodel_fovFloat = viewmodel_fov + 0x2C;
		// reading parent of client's convar cos original (engine one) doesnt have references
		Mem::Read<uintptr_t>(		  Mem::FindSignature("client.dll","\x81\xF9\x00\x00\x00\x00\x75\x2B\xF3\x0F",						"xx????xxxx",		2) + 0x1C, mat_force_tonemap_scale);	mat_force_tonemap_scaleFloat = mat_force_tonemap_scale + 0x2C;

		#ifndef NDEBUG
		bSendPacket					= Mem::FindSignature("engine.dll",		"\xB3\x01\x8B\x01\x8B\x40\x10\xFF\xD0\x84\xC0\x74\x0F",				"xxxxxxxxxxxxx"		) + 0x1;
#endif // !NDEBUG
		nameChangeCallbacks			= Mem::FindSignature("engine.dll",		"\x68\x80\x86\x00\x10\x68",											"xxxxxx",			-11) + 0x44;

		Mem::Read<uintptr_t>(		  Mem::FindSignature("engine.dll",		"\x8B\x3D\x00\x00\x00\x00\x8A\xF9\xF3\x0F\x11\x45\xFC",				"xx????xxxxxxx",	2), ClientState);
		m_nSignonState				= Mem::FindSignature("engine.dll",		"\x83\xB8\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3",						"xx?????xxxx",		2) + ClientState;
#ifdef NDEBUG
		m_flNextCmdTime				= Mem::FindSignature("engine.dll",		"\xF2\x0F\x10\x87\x00\x00\x00\x00\x66\x0F\x2F\x05",					"xxxx????xxxx",		4) + ClientState;
#endif // NDEBUG
		m_nDeltaTick				= Mem::FindSignature("engine.dll",		"\x83\xBE\x00\x00\x00\x00\xFF\x74\x00\x8D",							"xx??xxxx?x",		2) + ClientState;
		m_nPlayerSlot				= Mem::FindSignature("engine.dll",		"\x8B\x80\x00\x00\x00\x00\x40\xC3",									"xx????xx",			2) + ClientState;
		m_szLevelName				= Mem::FindSignature("engine.dll",		"\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x80\x3D",		"x????xxxxxxxxxx",	1) + ClientState;
		m_vecViewAngles				= Mem::FindSignature("engine.dll",		"\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05",				"xxxx????xxxxx",	4) + ClientState;
		m_nLastOutgoingCommand		= Mem::FindSignature("engine.dll",		"\x8B\x8F\x00\x00\x00\x00\x8B\x87\x00\x00\x00\x00\x41",				"xx??xxxx??xxx",	2) + ClientState;
		m_NetChannel				= Mem::FindSignature("engine.dll",		"\x8B\x8F\x00\x00\x00\x00\x8B\x01\x8B\x40\x18",						"xx????xxxxx",		2) + ClientState;

		//SendClanTag				= Mem::FindSignature("engine.dll",		"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15",								"xxxxxxxxx"			);
		//SetInfo_part				= Mem::FindSignature("engine.dll",		"\x8D\x4C\x24\x1C\xE8\x00\x00\x00\x00\x56\x57",						"xxxxx????xx"		);
		g_bVoiceRecording			= Mem::FindSignature("engine.dll",		"\x80\x3D\x00\x00\x00\x00\x00\x75\x0C\x6A",							"xx????xxxx",		2);
		ClientCmd_Unrestricted		= Mem::FindSignature("engine.dll",		"\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x81\xF9", "xxxxxxxxxxxxxxx????xx") + 0xA;
		ModelInfoClient				= Mem::FindSignature("engine.dll",		"\x8D\x44\x24\x3C\x8B\xF1\x50\x8D\x44\x24\x3C\xB9",					"xxxxxxxxxxxx"		) + 0xC;
		bOverlayActivated			= Mem::FindSignature("engine.dll",		"\x50\x51\x8D\x85\x00\x00\x00\x00\xB9",								"xxxx????x",		9) + // CSteam3Client
									Mem::FindSignature("engine.dll",		"\x88\x86\x00\x00\x00\x00\x5E\x84",									"xx??xxxx",			2);
		LoadNamedSkys				= Mem::FindSignature("engine.dll",		"\x55\x8B\xEC\x81\xEC\x34\x01\x00\x00\x56",							"xxxxxxxxxx"		);

		Mem::UnallocContentCache();
	}
}