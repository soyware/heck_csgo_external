#pragma once

namespace Features
{
	struct GlowObjectDef
	{
	public:
		uintptr_t	m_pEntity; //0x0000 
		float		m_GlowColor[4]; //0x0004 
	private:
		DWORD somehandle; //0x0014 
		float somefloat; //0x0018 
	public:
		float		m_flBloomAmount; //0x001C 
		float		m_flNoise; //0x0020 
		bool		m_bRenderWhenOccluded; //0x0024 
		bool		m_bRenderWhenUnoccluded; //0x0025 
		bool		m_bFullBloomRender; //0x0026 
	private:
		BYTE pad_0x0027[0x1]; //0x0027
	public:
		int			m_nFullBloomStencilTestValue; //0x0028 
		int			m_nGlowStyle; //0x002C 
		int			m_nSplitScreenSlot; //0x0030 
		int			m_nNextFreeSlot; //0x0034 

		inline void SetColor(float r, float g, float b, float a)
		{
			m_GlowColor[0] = r;
			m_GlowColor[1] = g;
			m_GlowColor[2] = b;
			m_GlowColor[3] = a;
		}
	};

	void Visuals()
	{
		while (true)
		{
			if (g_bInGame && (Config::GlowESP::Players || Config::GlowESP::DroppedC4 || Config::GlowESP::Grenades || Config::Radar || Config::clrRender::Enable || Config::NoSmoke))
			{
				if (Config::NoSmoke)
					Mem::Write<int>(Signatures::SmokeCount, 0);

				if (Config::GlowESP::PatchFlicker && Config::GlowESP::Players)
					Mem::Write<int>(Signatures::Spec_Show_Xray_Callback, (g_LocalPlayer.m_lifeState ? 1 : 65)); // TODO: improve

				CUtlVector GlowObjectManager;
				Mem::Read<CUtlVector>(Signatures::GlowObjectManager, GlowObjectManager);
				GlowObjectDef* Objects = new GlowObjectDef[GlowObjectManager.m_Size];
				ReadProcessMemory(Mem::Process, reinterpret_cast<LPCVOID>(GlowObjectManager.m_pMemory), Objects, sizeof(GlowObjectDef) * GlowObjectManager.m_Size, 0);
				for (int i = 0; i < GlowObjectManager.m_Size; ++i)
				{
					if (Objects[i].m_pEntity && !Objects[i].m_bRenderWhenOccluded)
					{
						int playerIdx = -1;
						for (unsigned int j = 0; j < g_PlayersCount; ++j)
						{
							if (g_Players[j].Address == Objects[i].m_pEntity)
							{
								playerIdx = j;
								break;
							}
						}

						if (playerIdx != -1)
						{
							if ((!Config::VisualsTeamCheck || g_Players[playerIdx].IsEnemy(g_LocalPlayer)) && !g_Players[playerIdx].m_bDormant && !g_Players[playerIdx].m_lifeState)
							{
								if (Config::GlowESP::Players)
								{
									Objects[i].m_nGlowStyle = Config::GlowESP::Style;

									if (Config::GlowESP::HealthBased)
									{
										const float Scale = (g_Players[playerIdx].m_iHealth < 100) ? g_Players[playerIdx].m_iHealth / 100.f : 1.f;

										for (unsigned int j = 0; j < 4; ++j)
											Objects[i].m_GlowColor[j] = Config::GlowESP::Color0hp[j] + (Config::GlowESP::Color100hp[j] - Config::GlowESP::Color0hp[j]) * Scale;

										Objects[i].m_bRenderWhenOccluded = true;
									}
									else if (!Objects[i].m_bRenderWhenOccluded)
									{
										for (unsigned int j = 0; j < 4; ++j)
											Objects[i].m_GlowColor[j] = Config::GlowESP::Color[j];

										Objects[i].m_bRenderWhenOccluded = true;
									}
									else if (Config::GlowESP::ShowVunerable)
									{
										for (unsigned int j = 0; j < 4; ++j)
											Objects[i].m_GlowColor[j] = Config::GlowESP::Color[j];
									}
									else continue;

									if (Config::GlowESP::ShowVunerable)
									{
										if (g_Players[playerIdx].m_flFlashAlpha > 120.f)
										{
											const float Scale = (g_Players[playerIdx].m_flFlashAlpha - 120.f) / 135.f;
											for (UINT j = 0; j < 4; ++j)
												Objects[i].m_GlowColor[j] += (Config::GlowESP::ColorVunerable[j] - Objects[i].m_GlowColor[j]) * Scale;
										}
										else
										{
											CWeapon Weapon;
											g_Players[playerIdx].GetWeapon(Weapon);
											if ((Weapon.m_iClip1 < 1) || (GetWeaponType(Weapon.m_iItemDefinitionIndex) > WEAPONTYPE_MACHINEGUN))
											{
												for (UINT j = 0; j < 4; ++j)
													Objects[i].m_GlowColor[j] = Config::GlowESP::ColorVunerable[j];
											}
										}
									}

									Mem::Write<GlowObjectDef>(GlowObjectManager.m_pMemory + sizeof(GlowObjectDef) * i, Objects[i]);
								}

								if (Config::Radar && !g_Players[playerIdx].m_bSpotted)
									Mem::Write<bool>(g_Players[playerIdx].Address + NetVars::m_bSpotted, true);

								if (Config::clrRender::Enable && (g_Players[playerIdx].m_clrRender != Config::clrRender::Color))
									Mem::Write<uint32_t>(g_Players[playerIdx].Address + NetVars::m_clrRender, Config::clrRender::Color);
							}
						}
						else
						{
							struct
							{
								short m_nModelIndex;
								std::byte _pad[2];
								UCHAR m_MoveType;
							} s;
							Mem::Read(Objects[i].m_pEntity + NetVars::m_nModelIndex, s);

							if (s.m_nModelIndex == ModelIndexes::C4)
							{
								if (Config::GlowESP::DroppedC4 && (s.m_MoveType == MOVETYPE_VPHYSICS))
								{
									Objects[i].m_bRenderWhenOccluded = true;
									Objects[i].SetColor(1.f, 0.f, 0.f, 1.f);
									Mem::Write<GlowObjectDef>(GlowObjectManager.m_pMemory + sizeof(GlowObjectDef) * i, Objects[i]);
								}
							}
							else if ((Config::NoSmoke || Config::GlowESP::Grenades) && (s.m_MoveType == MOVETYPE_FLYGRAVITY))
							{
								if (s.m_nModelIndex == ModelIndexes::Smoke)
								{
									if (Config::NoSmoke)
										Mem::Write<bool>(Objects[i].m_pEntity + Signatures::m_bDidSmokeEffectPlus, true);
								}
								else if (Config::GlowESP::Grenades)
								{
									if (s.m_nModelIndex == ModelIndexes::Flashbang)
									{
										Objects[i].m_bRenderWhenOccluded = true;
										Objects[i].SetColor(1.f, 1.f, 1.f, 1.f);
										Mem::Write<GlowObjectDef>(GlowObjectManager.m_pMemory + sizeof(GlowObjectDef) * i, Objects[i]);
									}
									else if ((s.m_nModelIndex == ModelIndexes::Grenade) || (s.m_nModelIndex == ModelIndexes::Molotov) || (s.m_nModelIndex == ModelIndexes::Incendiary))
									{
										Objects[i].m_bRenderWhenOccluded = true;
										Objects[i].SetColor(1.f, 0.f, 0.f, 1.f);
										Mem::Write<GlowObjectDef>(GlowObjectManager.m_pMemory + sizeof(GlowObjectDef) * i, Objects[i]);
									}
								}
							}
						}
					}
				}
				delete[] Objects;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(Config::VisualsSleep));
		}
	}
}