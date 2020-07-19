#pragma once

namespace Features
{
	void AutoAccept()
	{
		static bool bFound = false;
		static bool bAccepted = false;
		static uintptr_t prevCallback = 0;
		uintptr_t Callback;
		Mem::Read<uintptr_t>(Signatures::ConfirmedReservationCallback, Callback);
		if (Callback)
		{
			if (prevCallback != Callback)
			{
				prevCallback = Callback;
				bFound = false;
				bAccepted = false;
			}

			if (!bFound)
			{
				bFound = true;
				std::this_thread::sleep_for(5s);
			}
			else if (!bAccepted)
			{
				bAccepted = true;
				Mem::CreateThread(Signatures::Callback__IsReady);
				std::cout << "Tried to accept the match\n";
			}
		}
		else
		{
			bFound = false;
			bAccepted = false;
		}
	}

#ifndef NCURL
	void SayInsult()
	{
		CURL* curl;
		CURLcode code;
		CURLCallback data;
		curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, "https://www.rappad.co/api/battles/random_insult");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&data);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

			code = curl_easy_perform(curl);
			if (code == CURLE_OK)
			{
				// {"insult":"YOU SHOULDN'T PLAY HIDE AND SEEK, NO ONE WOULD LOOK FOR YOU.","email":"amir@rappad.co"}
				// {"insult":"YO MAMA IS SO STUPID THAT SHE SHOVED A AA BATTERY UP HER BUTT AND SAID \"I GOT THE POWER!\"","email":"amir@rappad.co"} -- SANITIZE
				char* Command = &data.data[6];
				Command[0] = 's';
				Command[1] = 'a';
				Command[2] = 'y';
				Command[3] = ' ';

				if (data.data[data.size - 28] == '.')
				{
					data.data[data.size - 28] = '\"';
					data.data[data.size - 27] = '\0';
				}
				else
					data.data[data.size - 26] = '\0';

				while (char* ss = strstr(Command, "\\\""))
					ss[1] = '\'';

				for (char* c = &Command[5]; *c != '\"'; ++c)
					*c = tolower(*c);

				ClientCmd_Unrestricted(Command);
			}
#ifndef NDEBUG
			else
				std::cerr << "curl_easy_perform failed: " << curl_easy_strerror(code) << std::endl;
#endif // NDEBUG
			curl_easy_cleanup(curl);
		}
	}
#endif // !NCURL

	void BotMount()
	{
		static int target = -1;
		vec3 bestPosDelta;
		float bestDist = FLT_MAX;

		if (target != -1)
		{
			bestPosDelta = g_Players[target].m_vecOrigin - g_LocalPlayer.m_vecOrigin;
			bestDist = bestPosDelta.Length2D();
		}
		
		if (32.f < bestDist)
		{
			target = -1;
			bestDist = 32.f;

			for (UINT i = 0; i < g_PlayersCount; ++i)
			{
				vec3 posDelta = g_Players[i].m_vecOrigin - g_LocalPlayer.m_vecOrigin;
				float dist = posDelta.Length2D();
				if (dist < bestDist)
				{
					bestPosDelta = posDelta;
					bestDist = dist;
					target = i;
				}
			}
		}

		Mem::Write<int8_t>(Signatures::Forward, 4);
		Mem::Write<int8_t>(Signatures::Back, 4);
		Mem::Write<int8_t>(Signatures::Right, 4);
		Mem::Write<int8_t>(Signatures::Left, 4);

		if (target != -1 && 15.f < bestDist)
		{
			vec3 curAngle;
			Mem::Read<vec3>(Signatures::m_vecViewAngles, curAngle);

			vec3 aimAngle(curAngle.x, RAD2DEG(atan2(bestPosDelta.y, bestPosDelta.x)), curAngle.z);
			ClampAngle(&aimAngle.x);

			vec2 svFwd, svRgh;
			AngleVectors(curAngle, &svFwd, &svRgh, nullptr);

			VectorNormalize(svFwd);
			VectorNormalize(svRgh);


			vec2 clFwd, clRgh;
			AngleVectors(aimAngle, &clFwd, &clRgh, nullptr);

			VectorNormalize(clFwd);
			VectorNormalize(clRgh);


			float divider = (svFwd.x*svRgh.y - svFwd.y*svRgh.x);
			if (divider == 0.f)
				return;
			float fmove = ((clFwd.x*svRgh.y - clFwd.y*svRgh.x)*450.f/* + (clRgh.x*svRgh.y - clRgh.y*svRgh.x)*450.f*/) / divider;
			float smove = -((clFwd.x*svFwd.y - clFwd.y*svFwd.x)*450.f/* + (clRgh.x*svFwd.y - clRgh.y*svFwd.x)*450.f*/) / divider;

			if (fmove > 0.f)
				Mem::Write<int8_t>(Signatures::Forward, 5);
			else if (fmove < 0.f)
				Mem::Write<int8_t>(Signatures::Back, 5);

			if (smove > 0.f)
				Mem::Write<int8_t>(Signatures::Right, 5);
			else if (smove < 0.f)
				Mem::Write<int8_t>(Signatures::Left, 5);
		}
	}

	void Misc()
	{
		char prevMap[64] = {};
		bool bHoldingTab = false;
		bool bRevealedWarmup = false;
		bool bRevealedGame = false;
		bool bChangedSky = false;
		bool bBotMount = false;

		while (true)
		{
			if (GetAsyncKeyState(Config::LoadNextConfigKey) & 0x8000)
			{
				Config::ReadNext();
				std::this_thread::sleep_for(1s);
				bChangedSky = false;
			}

			if (g_bInGame)
			{
				Mem::Read<float>(Signatures::GlobalVars + 32, g_IntervalPerTick);
				Mem::Read<uintptr_t>(Signatures::m_NetChannel, g_NetChannel);

				char curMap[_countof(prevMap)];
				Mem::Read<char[_countof(prevMap)]>(Signatures::m_szLevelName, curMap);
				if (curMap[0] != '\0' && strcmp(prevMap, curMap) != 0)
				{
					strcpy_s(prevMap, sizeof(prevMap), curMap);
					BSP::Load(curMap);
					g_bDangerZone = (curMap[5] == 'd' && curMap[6] == 'z' && curMap[7] == '_');
					ModelIndexes::Init();
				}

				if (!bChangedSky)
				{
					if (Config::Skyname[0] != '\0')
						R_LoadNamedSkys(Config::Skyname);
					bChangedSky = true;
				}

				if (GetAsyncKeyState(Config::BotMountKey) & 0x8000)
				{
					bBotMount = !bBotMount;
					std::cout << "Bot mount: " << (bBotMount ? "on" : "off") << "\n\a";
					std::this_thread::sleep_for(1s);
				}
#ifndef NCURL
				else if (GetAsyncKeyState(Config::InsultKey) & 0x8000)
				{
					SayInsult();
					std::this_thread::sleep_for(1s);
				}
#endif // !NCURL

				if (bBotMount)
					BotMount(); // todo: improve this shit

				if (Config::RevealRanks && !bRevealedGame)
				{
					uintptr_t GameRules;
					Mem::Read<uintptr_t>(Signatures::GameRulesProxy, GameRules);
					if (bRevealedWarmup || Mem::Read<bool>(GameRules + NetVars::m_bIsQueuedMatchmaking))
					{
						if (GetAsyncKeyState(VK_TAB) & 0x8000)
						{
							bHoldingTab = true;
						}
						else if (bHoldingTab)
						{
							bHoldingTab = false;
							if (Mem::Read<bool>(GameRules + NetVars::m_bWarmupPeriod))
							{
								if (!bRevealedWarmup)
								{
									bRevealedWarmup = true;
									RankReveal();
								}
							}
							else
							{
								if (!bRevealedGame && !Mem::Read<bool>(GameRules + NetVars::m_bFreezePeriod))
								{
									bRevealedGame = true;
									RankReveal();
								}
							}
						}
					}
				}

				static bool bFovChanged = true;
				CWeapon weapon;
				if (g_LocalPlayer.GetWeapon(weapon))
				{
					if (Config::NoScope && g_LocalPlayer.m_bIsScoped && 
						weapon.m_iItemDefinitionIndex != WEAPON_SG556 && weapon.m_iItemDefinitionIndex != WEAPON_AUG && 
						(1 <= weapon.m_zoomLevel) && (weapon.m_zoomLevel <= 2))
					{
						bFovChanged = true;
						Mem::Write<int>(g_LocalPlayer.Address + NetVars::m_iDefaultFOV, (weapon.m_zoomLevel == 1 ? 40 : 25));
					}
					else if (bFovChanged)
					{
						bFovChanged = false;
						Mem::Write<int>(g_LocalPlayer.Address + NetVars::m_iDefaultFOV, (Config::ViewFov ? Config::ViewFov : 90));
					}
				}

				if (g_LocalPlayer.m_flFlashMaxAlpha != Config::MaxFlashEffect)
					Mem::Write<float>(g_LocalPlayer.Address + NetVars::m_flFlashMaxAlpha, Config::MaxFlashEffect);
			}
			else
			{
				bHoldingTab = bRevealedWarmup = bRevealedGame = bChangedSky = false;

				if (Config::AutoAccept)
					AutoAccept();
			}

			std::this_thread::sleep_for(100ms);
		}
	}

	void AutoJump()
	{
		bool bSpacePressedFirstTime = true;
		while (true)
		{
			if (g_bInGame && Config::AutoJump::Enable && IsMouseActive())
			{
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					if (g_LocalPlayer.m_fFlags & FL_ONGROUND)
					{
						Mem::Write<uint8_t>(Signatures::Jump, 6);
						if (Config::AutoJump::Legit)
							std::this_thread::sleep_for(500ms); // so we dont get stuck when we hit roof with the head
					}
					else if (bSpacePressedFirstTime)
					{
						bSpacePressedFirstTime = false;
						Mem::Write<uint8_t>(Signatures::Jump, 4);
					}
				}
				else
					bSpacePressedFirstTime = true;
			}
			SleepTicks(Config::AutoJump::Legit ? 1.f : 0.5f);
		}
	}

	void FakeLag()
	{
		bool bToggled = false;
		while (true)
		{
			if (Config::FakeLag::Enabled)
			{
				if ((GetAsyncKeyState(Config::FakeLag::ToggleKey) & 0x8000) && IsMouseActive())
				{
					bToggled = !bToggled;
					std::cout << "FakeLag: " << (bToggled ? "on" : "off") << "\n\a";
					std::this_thread::sleep_for(500ms);
				}

				if (g_bInGame && !g_LocalPlayer.m_lifeState && bToggled &&
					(!Config::FakeLag::OnlyInAir || !(g_LocalPlayer.m_fFlags & FL_ONGROUND)) &&
					(!Config::FakeLag::DisableWhenShoot || !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) && !Mem::Read<bool>(Signatures::g_bVoiceRecording))
				{
#ifdef NDEBUG
					Mem::Write<double>(Signatures::m_flNextCmdTime, FLT_MAX);
#else
					Mem::Write<bool>(Signatures::bSendPacket, false);
#endif // NDEBUG
					SleepTicks(Config::FakeLag::TicksLag);
#ifdef NDEBUG
					Mem::Write<double>(Signatures::m_flNextCmdTime, 0.0);
#else
					Mem::Write<bool>(Signatures::bSendPacket, true);
#endif // NDEBUG
				}
			}
			SleepTicks(Config::FakeLag::TicksPass);
		}
	}
}