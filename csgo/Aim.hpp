#pragma once

namespace Features
{
	struct CBone
	{
		float _pad1[3];
		float x;
		float _pad2[3];
		float y;
		float _pad3[3];
		float z;

		operator vec3() const { return { x, y, z }; }

		CBone& operator+=(const vec3& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
	};

	bool GetBestBone(const CWeapon& weapon, const Config::Aimbot::CWpnCfg* weaponCfg, const vec2& viewangles, const vec3& localHead, const CPlayer& Player, bool bodyAim, vec3& out)
	{
		if (bodyAim || Config::Aimbot::Hitscan::Enable)
		{
			const int* const hitboxBones = Studio::GetHitboxBones(Player);

			CBone Bones[128];
			Mem::Read<CBone[128]>(Player.m_pBones, Bones);

			Bones[hitboxBones[HITBOX_HEAD]].z += 2.4f;

			std::vector<int> hitscanBones;
			if (bodyAim)
			{
				hitscanBones.push_back(hitboxBones[HITBOX_PELVIS]);
				hitscanBones.push_back(hitboxBones[HITBOX_UPPER_CHEST]);
			}
			else
			{
				hitscanBones.push_back(weaponCfg->PriorityBone);

				if (Config::Aimbot::Hitscan::Head)
					hitscanBones.push_back(hitboxBones[HITBOX_HEAD]);

				if (Config::Aimbot::Hitscan::Body)
				{
					hitscanBones.push_back(hitboxBones[HITBOX_PELVIS]);
					hitscanBones.push_back(hitboxBones[HITBOX_UPPER_CHEST]);
				}

				if (Config::Aimbot::Hitscan::Shoulders)
				{
					hitscanBones.push_back(hitboxBones[HITBOX_LEFT_UPPER_ARM]);
					hitscanBones.push_back(hitboxBones[HITBOX_RIGHT_UPPER_ARM]);
				}

				if (Config::Aimbot::Hitscan::Legs)
				{
					hitscanBones.push_back(hitboxBones[HITBOX_LEFT_CALF]);
					hitscanBones.push_back(hitboxBones[HITBOX_RIGHT_CALF]);
				}

				if (Config::Aimbot::Hitscan::Toes)
				{
					hitscanBones.push_back(hitboxBones[HITBOX_LEFT_FOOT]);
					hitscanBones.push_back(hitboxBones[HITBOX_RIGHT_FOOT]);
				}
			}

			float bestFov = FLT_MAX;

			for (size_t i = 0; i < hitscanBones.size(); ++i)
			{
				Bones[hitscanBones[i]] += Player.m_vecVelocity * g_IntervalPerTick;

				if (BSP::CanHit(localHead, Bones[hitscanBones[i]], weapon.m_iItemDefinitionIndex))
				{
					if (!Config::Aimbot::Rage::Enable)
					{
						const vec3 posDelta(Bones[hitscanBones[i]] - localHead);
						const float distance = posDelta.Length();
						const float fov = GetFOV(viewangles, CalcAngle(localHead, Bones[hitscanBones[i]]));
						if (fov > weaponCfg->FOV)
							continue;

						if (weaponCfg->FovDistBased && (fov > RAD2DEG(atan2(weaponCfg->FOV, distance))))
							continue;

						if ((i != 0) && (Config::Aimbot::Hitscan::Priority == 2)) // what did i mean by this
						{
							if (fov < bestFov)
							{
								bestFov = fov;
								out = Bones[hitscanBones[i]];
							}
							continue;
						}
					}
					out = Bones[hitscanBones[i]];
					return true;
				}
			}

			if (bestFov != FLT_MAX)
				return true;
		}
		else
		{
			vec3 bone = Mem::Read<CBone>(Player.m_pBones + (weaponCfg->PriorityBone * sizeof(CBone)));
			if (weaponCfg->PriorityBone == 8)
				bone.z += 2.4f;

			bone += Player.m_vecVelocity * g_IntervalPerTick;

			if (BSP::CanHit(localHead, bone, weapon.m_iItemDefinitionIndex))
			{
				out = bone;
				return true;
			}
		}
		return false;
	}

	bool HitChance(const CWeapon& weapon, CSWeaponType weaponType, float dist)
	{
		int leftHits = Config::GetWpnHitchance(weapon.m_iItemDefinitionIndex, weaponType);
		if (leftHits <= 0)
			return true;
		leftHits *= (255.f / 100.f);

		Random::SetSeed((MD5_PseudoRandom(Mem::Read<int>(Signatures::m_nLastOutgoingCommand) + 1) & 0x7fffffff) & 0xff + 1);
		for (int i = 255; i > 0; --i)
		{
			const float aRandom[4] = {
				Random::RandomFloat(0.f, M_PI_F * 2.f),
				Random::RandomFloat(0.f, 1.f) * weapon.GetInaccuracy(g_LocalPlayer),
				Random::RandomFloat(0.f, M_PI_F * 2.f),
				Random::RandomFloat(0.f, 1.f) * weapon.GetSpread()
			};

			const vec2 vSpread(cos(aRandom[0]) * aRandom[1] + cos(aRandom[2]) * aRandom[3],
				sin(aRandom[0]) * aRandom[1] + sin(aRandom[2]) * aRandom[3]);

			const vec2 angSpread(RAD2DEG(atan(-vSpread.y / sqrt(1.f + -vSpread.x * -vSpread.x))),
				RAD2DEG(atan(-vSpread.x)));

			const float distBasedFOV = RAD2DEG(atan2(10.f, dist));
			if (angSpread.Length() < distBasedFOV)
			{
				if (--leftHits <= 0)
					return true;
			}
			else if (leftHits > i)
				return false;
		}
		return false;
	}

	namespace Backtrack
	{
		struct CRecord
		{
			float	SimTime = 0.f;
			vec3	Head;
			vec3	Body;
		};
		CRecord Records[64][12];

		void Record()
		{
			for (UINT i = 0; i < g_PlayersCount; ++i)
			{
				if ((!Config::Aimbot::TeamCheck || g_LocalPlayer.IsEnemy(g_Players[i])) && g_Players[i].IsGoodTarget())
				{
					CBone Bones[9];
					Mem::Read<CBone[9]>(g_Players[i].m_pBones, Bones);
					Records[i][g_LocalPlayer.m_nTickBase % Config::Backtrack::Max] = { g_Players[i].m_flSimulationTime, Bones[8], Bones[5] };
				}
			}
		}

		float GetSimTime(const vec2& viewangles)
		{
			vec3 localHead(g_LocalPlayer.m_vecOrigin);
			localHead.z += g_LocalPlayer.m_vecViewOffset.z;
			localHead += g_LocalPlayer.m_vecVelocity * g_IntervalPerTick;

			float bestSimTime = 0.f;
			float bestFov = FLT_MAX;

			for (UINT i = 0; i < g_PlayersCount; ++i)
			{
				if (!Config::Aimbot::TeamCheck || g_LocalPlayer.IsEnemy(g_Players[i]))
				{
					for (int j = 0; j < Config::Backtrack::Max; ++j)
					{
						if ((g_LocalPlayer.m_flSimulationTime - Records[i][j].SimTime) <= 0.2f) // sv_maxunlag = 0.2
						{
							for (UINT k = 0; k < 2 && bestFov == FLT_MAX; ++k)
							{
								const vec3 posDelta((k == 0 ? Records[i][j].Head : Records[i][j].Body) - localHead);
								const float distance = posDelta.Length();
								const float fov = GetFOV(viewangles, CalcAngle(posDelta, distance));
								if (fov < bestFov)
								{
									const float distBasedFOV = RAD2DEG(atan2((k == 0 ? 5.f : 10.f), distance));
									if (fov <= distBasedFOV)
									{
										bestSimTime = Records[i][j].SimTime;
										bestFov = fov;
									}
								}
							}
						}
					}
				}
			}
#ifndef NDEBUG
			if (bestSimTime != 0.f)
				std::cout << "Backtrack delta - " << static_cast<int>(TIME_TO_TICKS(g_LocalPlayer.m_flSimulationTime - bestSimTime)) << '\n';
			else
				std::cout << "Can't backtrack\n";
#endif
			return bestSimTime;
		}
	}

	void Aimbot(const CWeapon& weapon, CSWeaponType weaponType, vec2& cmdViewangles, bool& outShoot, bool& outHaveTarget)
	{
		Config::Aimbot::CWpnCfg* wpnCfg = Config::GetWeaponCfg(weapon.m_iItemDefinitionIndex, weaponType);
		if (wpnCfg && 
			((!Config::Aimbot::Rage::Enable && !weapon.IsLowFirerate()) || (ROUND_TO_TICKS(weapon.m_flNextPrimaryAttack) <= TICKS_TO_TIME(g_LocalPlayer.m_nTickBase))) &&
			(!wpnCfg->CheckIfFlashed || (g_LocalPlayer.m_flFlashAlpha <= 120.f)) &&
			(GetAsyncKeyState(Config::Aimbot::Key) & 0x8000))
		{
			vec2 bulletAngle(cmdViewangles);
			bulletAngle.x += g_LocalPlayer.m_aimPunchAngle.x * 2.f; // adding recoil to our viewangles
			bulletAngle.y += g_LocalPlayer.m_aimPunchAngle.y * 2.f; // (expecting player is compensating them)
			ClampAngle(&bulletAngle.x);

			vec3 localHead(g_LocalPlayer.m_vecOrigin);
			localHead.z += g_LocalPlayer.m_vecViewOffset.z;
			localHead += g_LocalPlayer.m_vecVelocity * g_IntervalPerTick;

			const bool bBodyAim = (weapon.m_iItemDefinitionIndex == WEAPON_TASER) || // taser gets here only if raging so not checking
				(Config::Aimbot::Rage::Enable && Config::Aimbot::Rage::BodyAWP && (weapon.m_iItemDefinitionIndex == WEAPON_AWP));

			vec2 bestAngleDelta;
			float bestFov = wpnCfg->FOV;
			for (UINT i = 0; i < g_PlayersCount; ++i)
			{
				if ((!Config::Aimbot::TeamCheck || g_Players[i].IsEnemy(g_LocalPlayer)) && g_Players[i].IsGoodTarget() && (!wpnCfg->IgnoreInAir || (g_Players[i].m_fFlags & FL_ONGROUND)))
				{
					vec3 aimPoint;
					if (!GetBestBone(weapon, wpnCfg, bulletAngle, localHead, g_Players[i], bBodyAim, aimPoint))
						continue;

					const vec3 posDelta(aimPoint - localHead);
					const float distance = posDelta.Length();

					vec2 angleDelta(CalcAngle(posDelta, distance) - bulletAngle);
					ClampAngle(&angleDelta.x);

					if (weapon.m_iItemDefinitionIndex == WEAPON_TASER)
					{
						if (distance <= 182.f)
						{
							bestFov = 0.f;
							bestAngleDelta = angleDelta;
							break;
						}
						else
							continue;
					}

					float fov = angleDelta.Length();
					if (fov > 180.f)
						fov = 360.f - fov;

					if (fov < bestFov)
					{
						if (Config::Aimbot::Rage::Enable)
						{
							if (Config::Aimbot::Rage::AutoScope && !weapon.m_zoomLevel && weapon.CanScope())
							{
								Mem::Write<uint8_t>(Signatures::Attack2, 6);
								return;
							}

							if (Config::Aimbot::Rage::HitChance::Enable && !HitChance(weapon, weaponType, distance))
								continue;
						}
						else if (wpnCfg->FovDistBased)
						{
							const float distBasedFOV = RAD2DEG(atan2(wpnCfg->FOV, distance)); // clamp dist fov by min value?
							if (distBasedFOV < fov)
								continue;
						}

						bestFov = fov;
						bestAngleDelta = angleDelta;
					}
				}
			}

			if (bestFov != wpnCfg->FOV)
			{
				outHaveTarget = true;
				cmdViewangles += bestAngleDelta * wpnCfg->Speed;
				ClampAngle(&cmdViewangles.x);

				if (!wpnCfg->Silent)
				{
					Mem::Write<bool>(Signatures::m_fMouseActive, false);
					Mem::Write<vec2>(Signatures::m_vecViewAngles, cmdViewangles);
				}

				if (Config::Aimbot::AutoFire)
					outShoot = true;
			}
		}
	}

	void Triggerbot(bool& outShoot)
	{
		if (0 < g_LocalPlayer.m_iIDEntIndex &&
			g_LocalPlayer.m_iIDEntIndex <= 64 && (!Config::Triggerbot::CheckIfFlashed || (g_LocalPlayer.m_flFlashAlpha <= 120.f)) &&
			(GetAsyncKeyState(Config::Triggerbot::Key) & 0x8000))
		{
			for (UINT i = 0; i < g_PlayersCount; ++i)
			{
				if (g_Players[i].index == g_LocalPlayer.m_iIDEntIndex)
				{
					if (g_Players[i].IsEnemy(g_LocalPlayer))
						outShoot = true;
					break;
				}
			}
		}
	}

	void AutoPistol(const CWeapon& weapon, CSWeaponType weaponType, bool& outShoot)
	{
		if ((weapon.m_iItemDefinitionIndex != WEAPON_CZ75A) && (weaponType == WEAPONTYPE_PISTOL) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			outShoot = (g_LocalPlayer.m_nTickBase % 2);
	}

	void RCS(const CWeapon& weapon, vec2& viewangles, bool bHaveTarget)
	{
		static vec2 prevPunch;
		if (!weapon.m_bInReload &&
			(Config::RCS::AlwaysOn ? (GetAsyncKeyState(VK_LBUTTON) & 0x8000) : bHaveTarget) &&
			(g_bChangingUserCmd ? !weapon.IsLowFirerate() : (g_LocalPlayer.m_iShotsFired > 1)))
		{
			viewangles.x -= (g_LocalPlayer.m_aimPunchAngle.x - prevPunch.x) * ((2.f / 100.f) * Config::RCS::Vertical);
			viewangles.y -= (g_LocalPlayer.m_aimPunchAngle.y - prevPunch.y) * ((2.f / 100.f) * Config::RCS::Horizontal);
			ClampAngle(&viewangles.x);
			Mem::Write<vec2>(Signatures::m_vecViewAngles, viewangles);
		}
		prevPunch = { g_LocalPlayer.m_aimPunchAngle.x, g_LocalPlayer.m_aimPunchAngle.y };
	}

	void Aim()
	{
		bool bHold = false;
		while (true)
		{
			CWeapon weapon;
			if (g_bInGame && (Config::Aimbot::Enable || Config::Triggerbot::Enable || Config::AutoPistol) && IsMouseActive() && g_LocalPlayer.GetWeapon(weapon))
			{
				const CSWeaponType weaponType = GetWeaponType(weapon.m_iItemDefinitionIndex);
				vec2 cmdViewangles;
				Mem::Read<vec2>(Signatures::m_vecViewAngles, cmdViewangles);
				bool bShoot = g_bChangingUserCmd && (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
				if ((0 < weapon.m_iClip1) && (weapon.m_iItemDefinitionIndex != WEAPON_BREACHCHARGE))
				{
					bool bHaveTarget = false;
					if (!weapon.m_bInReload && Config::Aimbot::Enable)
						Aimbot(weapon, weaponType, cmdViewangles, bShoot, bHaveTarget);

					if (Config::RCS::Enable)
						RCS(weapon, cmdViewangles, bHaveTarget);

					if (!weapon.m_bInReload && (ROUND_TO_TICKS(weapon.m_flNextPrimaryAttack) <= TICKS_TO_TIME(g_LocalPlayer.m_nTickBase)))
					{
						if (!bShoot && Config::Triggerbot::Enable)
							Triggerbot(bShoot);

						if (Config::AutoPistol)
							AutoPistol(weapon, weaponType, bShoot);

						if (bShoot)
						{
							bool bWriteViewangles = false;
							if (Config::Aimbot::Enable)
							{
								Config::Aimbot::CWpnCfg* wpnCfg = Config::GetWeaponCfg(weapon.m_iItemDefinitionIndex, weaponType);
								if (wpnCfg && wpnCfg->Silent && (GetAsyncKeyState(Config::Aimbot::Key) & 0x8000))
									bWriteViewangles = true;
							}

							float simTime = (Config::Backtrack::Enable && 
								((weapon.m_iItemDefinitionIndex != WEAPON_TASER) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))) ? Backtrack::GetSimTime(cmdViewangles) : 0.f;

							if (bWriteViewangles || simTime)
							{
#ifndef NDEBUG
								std::cout << "Changing UserCmd\n";
#endif
								ChangeUserCmd(bWriteViewangles ? &cmdViewangles : nullptr,
									IN_ATTACK,
									simTime ? TIME_TO_TICKS(simTime) : 0);
								bShoot = false;
							}
						}
					}
				}

				if (bShoot)
				{
#ifndef NDEBUG
					std::cout << "Writing attack\n";
#endif
					if (!bHold)
					{
						if ((weapon.m_iItemDefinitionIndex == WEAPON_C4) || (weaponType == WEAPONTYPE_GRENADE))
						{
							bHold = true;
							Mem::Write<uint8_t>(Signatures::Attack, 5);
						}
						else
						{
							Mem::Write<uint8_t>(Signatures::Attack, 6);

							if (Config::FakeLag::Enabled && Config::FakeLag::DisableWhenShoot)
#ifdef NDEBUG
								Mem::Write<double>(Signatures::m_flNextCmdTime, 0.0);
#else
								Mem::Write<bool>(Signatures::bSendPacket, true);
#endif // NDEBUG
						}
					}
				}
				else if (bHold)
				{
					bHold = false;
					Mem::Write<uint8_t>(Signatures::Attack, 4);
				}
				Backtrack::Record();

				if (Config::Hitsound::Enable)
				{
					static int prevTotalHits = g_LocalPlayer.m_Hits.m_Size;
					if (prevTotalHits < g_LocalPlayer.m_Hits.m_Size)
					{
						char szFile[16] = "hitsounds\\0.wav";
						szFile[10] = '0' + Config::Hitsound::Style;
						PlaySound(szFile, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
					}
					prevTotalHits = g_LocalPlayer.m_Hits.m_Size;
				}
			}
			SleepTicks(1.f);
		}
	}
}