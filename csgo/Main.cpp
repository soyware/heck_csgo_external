#include "stdafx.h"

#include "Common.hpp"
#include "Vector.hpp"
#ifndef NCURL
#include <curl/curl.h>
#endif // !NCURL
#include "Memory.hpp"
#include "SDK/Random.hpp"
#include "SDK/checksum_md5.hpp"
#include "SDK/UserCmd.hpp"
#include "SDK/Client.hpp"
#include "Signatures.hpp"
#include "NetVars.hpp"
#include "CPlayer.hpp"
#include "CWeapon.hpp"
#include "Shellcodes.hpp"
#include "Config.hpp"
#include "SDK/BSP.hpp"
#include "SDK/Studio.hpp"

#include "Features.hpp"
#include "Aim.hpp"
#include "Visuals.hpp"
#include "Misc.hpp"

void ErrorExit(const char* szErr)
{
	std::cerr << "Error: " << szErr;
	MessageBeep(MB_ICONERROR);
	Mem::Detach();
#ifndef NDEBUG
	__debugbreak();
#elif defined(NDEBUG)
	_getch();
	exit(EXIT_FAILURE);
#endif // NDEBUG
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		Mem::Detach();
#ifndef NDEBUG
		if (Config::FakeLag::Enabled)
			Mem::Write<bool>(Signatures::bSendPacket, true);
#endif
	}
	return FALSE;
}

int main()
{
	std::cout << "csgo heck by hirus (" << __DATE__ << " build)" << "\n1. Legit\n2. Rage\n3. Custom\nEnter config index: ";

	do std::cin >> Config::curConfig; while (1 > Config::curConfig || Config::curConfig > 3);

	std::cout << '\n' << std::left << std::setw(23) << std::setfill('.') << "Reading config";
	Config::Read(Config::curConfig);
	std::cout << std::setw(28) << "done\nAttaching";
	Mem::Attach();
	std::cout << std::setw(28) << "done\nReading items script";
	ReadWeaponsScript();
	std::cout << std::setw(28) << "done\nFinding offsets";
	Signatures::Find();
	std::cout << std::setw(28) << "done\nFinding netvars";
	NetVars::Find();
	std::cout << std::setw(28) << "done\nApplying config";

	if (!SetConsoleCtrlHandler(HandlerRoutine, TRUE))
		std::clog << "Warning: SetConsoleCtrlHandler failed.\n";

	if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK)
		std::clog << "Warning: CoInitializeEx could have failed.\n";

	Config::Apply();
	std::cout << "done\n\n";
	Config::PrintHotkeys();

#ifndef NCURL
	curl_global_init(CURL_GLOBAL_DEFAULT);
#endif // !NCURL

	std::thread (Features::Aim).detach();
	std::thread (Features::AutoJump).detach();
	std::thread (Features::FakeLag).detach();
	std::thread (Features::Visuals).detach();
	std::thread (Features::Misc).detach();

	while (Mem::IsProcessRunning())
	{
		int SignonState;
		Mem::Read<int>(Signatures::m_nSignonState, SignonState);

		if (SignonState == 6)
		{
			if (Config::clrRender::Enable && g_bInGame && Config::VisualsTeamCheck)
			{
				for (UINT i = 0; i < g_PlayersCount; ++i)
				{
					if (g_LocalPlayer.m_iTeamNum == g_Players[i].m_iTeamNum)
					{
						if (g_Players[i].m_clrRender != 0xFFFFFFFF)
							Mem::Write<int>(Signatures::m_nDeltaTick, -1);
						break;
					}
				}
			}

			CEntInfo EntInfoList[64];
			ReadProcessMemory(Mem::Process, reinterpret_cast<LPCVOID>(Signatures::EntityList), EntInfoList, sizeof(EntInfoList) - 12, 0);

			int PlayerSlot;
			Mem::Read<int>(Signatures::m_nPlayerSlot, PlayerSlot);
			g_LocalPlayer.Update(EntInfoList[PlayerSlot].m_pEntity);
			EntInfoList[PlayerSlot].m_pEntity = 0; // don't add LocalPlayer to g_Players

			g_PlayersCount = 0;

			for (UINT i = 0; i < 64; ++i)
			{
				if (EntInfoList[i].m_pEntity)
				{
					g_Players[g_PlayersCount].Update(EntInfoList[i].m_pEntity);
					++g_PlayersCount;
				}
			}

			if (g_LocalPlayer.m_iTeamNum != 0)
				g_bInGame = true;
		}
		else
			g_bInGame = false;

		SleepTicks(0.5f);
	}

	g_bInGame = false;
	Mem::Detach();
	return 0;
}