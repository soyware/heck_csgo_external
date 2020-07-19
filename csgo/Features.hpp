#pragma once

bool g_bInGame = false;
bool g_bDangerZone = false;
uintptr_t g_NetChannel;
float g_IntervalPerTick = (1.f / 64.f);

inline void SleepTicks(float ticks)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(g_IntervalPerTick * 1000.f * ticks)));
}

inline bool IsMouseActive()
{
	return (Mem::Read<uint32_t>(Signatures::cl_mouseenableInt) ^ Signatures::cl_mouseenable) && !Mem::Read<bool>(Signatures::bOverlayActivated) && Mem::Read<bool>(Signatures::m_fMouseActive);
}

namespace ModelIndexes
{
	short Flashbang;
	short Smoke;
	short Grenade;
	short Molotov;
	short Incendiary;
	short C4;

	void Init()
	{
		Flashbang = GetModelIndex("models/weapons/w_eq_flashbang_dropped.mdl");
		Smoke = GetModelIndex("models/weapons/w_eq_smokegrenade_thrown.mdl");
		Grenade = GetModelIndex("models/weapons/w_eq_fraggrenade_dropped.mdl");
		Molotov = GetModelIndex("models/weapons/w_eq_molotov_dropped.mdl");
		Incendiary = GetModelIndex("models/weapons/w_eq_incendiarygrenade_dropped.mdl");
		C4 = GetModelIndex("models/weapons/w_ied_dropped.mdl");
	}
}

namespace Features
{
	// Credits: nuggah
	void ChangeUserCmd(vec2* viewangles, int buttons, int tick_count)
	{
#ifdef NDEBUG
		Mem::Write<double>(Signatures::m_flNextCmdTime, DBL_MAX);
#else
		Mem::Write<bool>(Signatures::bSendPacket, false);
#endif // NDEBUG
		const int iDesiredCmdNum = Mem::Read<int>(Signatures::m_nLastOutgoingCommand) + 2;
		uintptr_t pCommands;
		Mem::Read<uintptr_t>(Signatures::m_pCommands, pCommands);
		const uintptr_t pOldCmd = pCommands + ((iDesiredCmdNum - 1) % 150) * sizeof(CUserCmd);
		const uintptr_t pOldVerifiedCmd = Mem::Read<uintptr_t>(Signatures::m_pVerifiedCommands) + ((iDesiredCmdNum - 1) % 150) * sizeof(CVerifiedUserCmd);

		while (Mem::Read<int>(g_NetChannel + Signatures::m_nOutSequenceNr) < iDesiredCmdNum)
			std::this_thread::yield();

		CUserCmd OldCmd;
		Mem::Read<CUserCmd>(pOldCmd, OldCmd);
		if (viewangles)
		{
			ClampAngle(&viewangles->x);
			OldCmd.viewangles.x = viewangles->x;
			OldCmd.viewangles.y = viewangles->y;
		}
		if (buttons) OldCmd.buttons |= buttons;
		if (tick_count) OldCmd.tick_count = tick_count;
		Mem::Write<CUserCmd>(pOldCmd, OldCmd);
		Mem::Write<CUserCmd>(pOldVerifiedCmd, OldCmd);
#ifdef NDEBUG
		Mem::Write<double>(Signatures::m_flNextCmdTime, 0.0);
#else
		Mem::Write<bool>(Signatures::bSendPacket, true);
#endif // NDEBUG
	}
}