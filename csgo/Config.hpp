#pragma once

bool g_bChangingUserCmd = false;

namespace Config
{
	const char* const configNames[] = {
		"legit",
		"rage",
		"custom"
	};

	UINT	curConfig;

	namespace Aimbot
	{
		bool	Enable;
		int		Key;
		bool	TeamCheck;
		bool	AutoFire;
		namespace Hitscan
		{
			bool	Enable;
			int		Priority;
			bool	Head;
			bool	Body;
			bool	Shoulders;
			bool	Legs;
			bool	Toes;
		}
		bool	PseudoAwall;
		//bool	ResolveByLBY;

		namespace Rage
		{
			bool	Enable;
			bool	AutoScope;
			bool	BodyAWP;

			namespace HitChance
			{
				bool	Enable;
				int		Percentages[8];
			}
		}

		struct CWpnCfg
		{
			int		PriorityBone;
			bool	FovDistBased;
			float	FOV;
			float	Speed;
			bool	IgnoreInAir;
			bool	CheckIfFlashed;
			bool	Silent;
		} WpnCfgs[8];
	}

	namespace RCS
	{
		bool	Enable;
		bool	AlwaysOn;
		int		Vertical;
		int		Horizontal;
	}

	namespace Triggerbot
	{
		bool	Enable;
		int		Key;
		bool	CheckIfFlashed;
	}

	bool	AutoPistol;
	namespace Backtrack
	{
		bool	Enable;
		int		Max;
	}

	bool	VisualsTeamCheck;
	namespace GlowESP
	{
		bool	Players;
		int		Style;
		bool	PatchFlicker;
		float	Color[4];
		bool	HealthBased;
		float	Color0hp[4];
		float	Color100hp[4];
		bool	ShowVunerable;
		float	ColorVunerable[4];
		bool	DroppedC4;
		bool	Grenades;
	}

	namespace clrRender
	{
		bool	Enable;
		uint32_t Color;
	}

	bool	Radar;
	int		VisualsSleep;

	namespace AutoJump
	{
		bool	Enable;
		bool	Legit;
	}

	namespace FakeLag
	{
		bool	Enabled;
		int		ToggleKey;
		int		TicksLag;
		int		TicksPass;
		bool	DisableWhenShoot;
		bool	OnlyInAir;
	}

	namespace Hitsound
	{
		bool	Enable;
		int		Style;
		float	Volume;
	}

	namespace Nightmode
	{
		bool	Enable;
		float	Lightscale;
	}

	char	Skyname[48];
	bool	EnableName;
	bool	AutoAccept;
	bool	RevealRanks;
	bool	NoPostProcess;
	bool	NoSmoke;
	bool	NoScope;
	int		NoRecoil;
	float	MaxFlashEffect;
	int		ViewmodelFov;
	int		ViewFov;
	int		LoadNextConfigKey;
	int		InsultKey;
	int		BotMountKey;

	void ReadColorFloat(std::ifstream &File, float out[4])
	{
		File.ignore(80, '[');
		File >> out[0]; File.ignore();
		File >> out[1]; File.ignore();
		File >> out[2]; File.ignore();
		File >> out[3];
		for (UINT i = 0; i < 4; ++i)
			out[i] /= 255.f;
	}

	void ReadColorHex(std::ifstream &File, uint32_t &out)
	{
		File.ignore(80, '[');
		int rgb[3];
		File >> rgb[0]; File.ignore();
		File >> rgb[1]; File.ignore();
		File >> rgb[2];
		out = (rgb[0]) |
			(rgb[1] << 8) |
			(rgb[2] << 16) |
			(0xFF << 24);
	}

	void Read(const unsigned int id)
	{
		std::ifstream File;
		switch (id)
		{
		case 1:
			File.open("legit.txt");
			break;
		case 2:
			File.open("rage.txt");
			break;
		case 3:
			File.open("custom.txt");
			break;
		}

		if (File.fail())
			ErrorExit("Failed to open the config");

#define ReadNextSetting(s) File.ignore(80, '='); File >> s

		ReadNextSetting(Aimbot::Enable);
		ReadNextSetting(Aimbot::Key);
		ReadNextSetting(Aimbot::TeamCheck);
		ReadNextSetting(Aimbot::AutoFire);
		ReadNextSetting(Aimbot::Hitscan::Enable);
		ReadNextSetting(Aimbot::Hitscan::Priority);
		ReadNextSetting(Aimbot::Hitscan::Head);
		ReadNextSetting(Aimbot::Hitscan::Body);
		ReadNextSetting(Aimbot::Hitscan::Shoulders);
		ReadNextSetting(Aimbot::Hitscan::Legs);
		ReadNextSetting(Aimbot::Hitscan::Toes);
		ReadNextSetting(Aimbot::PseudoAwall);
		//ReadNextSetting(Aimbot::ResolveByLBY);

		Aimbot::WpnCfgs[0].FovDistBased = false;
		Aimbot::WpnCfgs[0].Speed = 1.f;
		Aimbot::WpnCfgs[0].IgnoreInAir = false;
		Aimbot::WpnCfgs[0].CheckIfFlashed = false;
		ReadNextSetting(Aimbot::Rage::Enable);
		ReadNextSetting(Aimbot::WpnCfgs[0].PriorityBone);
		ReadNextSetting(Aimbot::WpnCfgs[0].FOV);
		ReadNextSetting(Aimbot::Rage::AutoScope);
		ReadNextSetting(Aimbot::Rage::BodyAWP);
		ReadNextSetting(Aimbot::WpnCfgs[0].Silent);
		ReadNextSetting(Aimbot::Rage::HitChance::Enable);
		for (UINT i = 0; i < 8; ++i)
		{
			ReadNextSetting(Aimbot::Rage::HitChance::Percentages[i]);
		}

		for (UINT i = 1; i < 8; ++i)
		{
			ReadNextSetting(Aimbot::WpnCfgs[i].PriorityBone);
			ReadNextSetting(Aimbot::WpnCfgs[i].FovDistBased);
			ReadNextSetting(Aimbot::WpnCfgs[i].FOV);
			ReadNextSetting(Aimbot::WpnCfgs[i].Speed);
			ReadNextSetting(Aimbot::WpnCfgs[i].IgnoreInAir);
			ReadNextSetting(Aimbot::WpnCfgs[i].CheckIfFlashed);
			ReadNextSetting(Aimbot::WpnCfgs[i].Silent);
		}

		ReadNextSetting(RCS::Enable);
		ReadNextSetting(RCS::AlwaysOn);
		ReadNextSetting(RCS::Vertical);
		ReadNextSetting(RCS::Horizontal);

		ReadNextSetting(Triggerbot::Enable);
		ReadNextSetting(Triggerbot::Key);
		ReadNextSetting(Triggerbot::CheckIfFlashed);

		ReadNextSetting(AutoPistol);
		ReadNextSetting(Backtrack::Enable);
		ReadNextSetting(Backtrack::Max);
		if (Backtrack::Max > 12) Backtrack::Max = 12;

		ReadNextSetting(VisualsTeamCheck);
		ReadNextSetting(GlowESP::Players);
		ReadNextSetting(GlowESP::Style);
		ReadNextSetting(GlowESP::PatchFlicker);
		ReadColorFloat(File, GlowESP::Color);
		ReadNextSetting(GlowESP::HealthBased);
		ReadColorFloat(File, GlowESP::Color0hp);
		ReadColorFloat(File, GlowESP::Color100hp);
		ReadNextSetting(GlowESP::ShowVunerable);
		ReadColorFloat(File, GlowESP::ColorVunerable);
		ReadNextSetting(GlowESP::DroppedC4);
		ReadNextSetting(GlowESP::Grenades);

		ReadNextSetting(clrRender::Enable);
		ReadColorHex(File, clrRender::Color);

		ReadNextSetting(Radar);
		ReadNextSetting(VisualsSleep);
		if (VisualsSleep < 1) VisualsSleep = 1;

		ReadNextSetting(AutoJump::Enable);
		ReadNextSetting(AutoJump::Legit);

		ReadNextSetting(FakeLag::Enabled);
		ReadNextSetting(FakeLag::ToggleKey);
		ReadNextSetting(FakeLag::TicksLag);
		ReadNextSetting(FakeLag::TicksPass);
		ReadNextSetting(FakeLag::DisableWhenShoot);
		ReadNextSetting(FakeLag::OnlyInAir);

		ReadNextSetting(Hitsound::Enable);
		ReadNextSetting(Hitsound::Style);
		ReadNextSetting(Hitsound::Volume);
		Hitsound::Volume *= 0.01f;

		ReadNextSetting(Nightmode::Enable);
		ReadNextSetting(Nightmode::Lightscale);
		File.ignore(80, '\"'); File.getline(Skyname, sizeof(Skyname), '\"');

		ReadNextSetting(EnableName);
		ReadNextSetting(AutoAccept);
		ReadNextSetting(RevealRanks);
		ReadNextSetting(NoPostProcess);
		ReadNextSetting(NoSmoke);
		ReadNextSetting(NoScope);
		ReadNextSetting(NoRecoil);
		ReadNextSetting(MaxFlashEffect);
		MaxFlashEffect *= 2.55f;
		ReadNextSetting(ViewmodelFov);
		ReadNextSetting(ViewFov);
		ReadNextSetting(LoadNextConfigKey);
		ReadNextSetting(InsultKey);
		ReadNextSetting(BotMountKey);

#undef ReadNextSetting
		// Prev. features: TriggerbotType, C4 Timer, CalloutsEnable, CalloutEnemies
		File.close();
	}

	void Apply()
	{
		Mem::Write<int>(Signatures::nameChangeCallbacks + offsetof(CUtlVector, m_Size), (EnableName ? 0 : 1));
		Mem::Write<bool>(Signatures::s_bOverridePostProcessing, NoPostProcess);
		Mem::Write<uint32_t>(Signatures::weapon_recoil_view_punch_extraFloat, (NoRecoil > 0 ? Signatures::weapon_recoil_view_punch_extra : (Signatures::weapon_recoil_view_punch_extra ^ FloatToHex(0.055f))));
#ifdef NDEBUG
		Mem::Write<uint32_t>(Signatures::weapon_recoil_scaleFloat, (NoRecoil > 1 ? Signatures::weapon_recoil_scale : (Signatures::weapon_recoil_scale ^ FloatToHex(2.f))));
#endif
		if (ViewmodelFov)
			Mem::Write<uint32_t>(Signatures::viewmodel_fovFloat, (Signatures::viewmodel_fov ^ FloatToHex(ViewmodelFov)));
		if (!GlowESP::Players || !GlowESP::PatchFlicker)
			Mem::Write<int>(Signatures::Spec_Show_Xray_Callback, 1);
		Mem::Write<uint32_t>(Signatures::mat_force_tonemap_scaleFloat, (Nightmode::Enable ? (Signatures::mat_force_tonemap_scale ^ FloatToHex(Config::Nightmode::Lightscale)) : (Signatures::mat_force_tonemap_scale ^ FloatToHex(1.f))));

		bool bUsingSilent = false;
		for (UINT i = 0; i < 8; ++i)
		{
			if (Aimbot::WpnCfgs[i].Silent && ((i != 0) || Config::Aimbot::Rage::Enable))
			{
				bUsingSilent = true;
				break;	
			}
		}
		g_bChangingUserCmd = (Aimbot::Enable && bUsingSilent) || Backtrack::Enable;
		ClientCmd_Unrestricted(g_bChangingUserCmd ? "unbind mouse1" : "bind mouse1 +attack");

		if (Hitsound::Enable && !ChangeVolume(Hitsound::Volume))
			std::cout << "Warning: Failed to set hitsound volume.\n";
	}

	void PrintHotkeys()
	{
		struct CHotkey
		{
			int code;
			const char* desc;
		};

		CHotkey hotkeys[] = {
			{ Config::Aimbot::Key,			"aimbot" },
			{ Config::Triggerbot::Key,		"triggerbot" },
			{ Config::FakeLag::ToggleKey,	"toggle fakelag" },
			{ Config::LoadNextConfigKey,	"load next config" },
	#ifndef NCURL
			{ Config::InsultKey,			"send the insult to global chat" },
	#endif // !NCURL
			{ Config::BotMountKey,			"mount a bot" },
		};

		std::cout << "Hotkeys:\n";

		char keyName[24];
		for (UINT i = 0; i < _countof(hotkeys); ++i)
		{
			if (hotkeys[i].code)
			{
				if (GetVKeyName(hotkeys[i].code, keyName, sizeof(keyName)))
					std::cout << keyName << " - " << hotkeys[i].desc << '\n';
			}
			else
				std::cout << "Unbound - " << hotkeys[i].desc << '\n';
		}

		std::cout << "\n";
	}

	void ReadNext()
	{
		curConfig = (curConfig == 3) ? 1 : (curConfig + 1);
		Read(curConfig);
		Apply();

		std::cout << "Loading " << configNames[curConfig - 1] << " config\n\n";
		PrintHotkeys();

		for (UINT i = 0; i < curConfig; ++i)
			std::cout << '\a';
	}

	int GetWpnHitchance(int itemDefIndex, CSWeaponType weaponType)
	{
		if (itemDefIndex == WEAPON_SSG08)
			return Aimbot::Rage::HitChance::Percentages[6];
		else if (itemDefIndex == WEAPON_AWP)
			return Aimbot::Rage::HitChance::Percentages[7];
		else
			return Aimbot::Rage::HitChance::Percentages[weaponType - 1];
	}

	Aimbot::CWpnCfg* GetWeaponCfg(int itemDefIndex, CSWeaponType weaponType)
	{
		if (Aimbot::Rage::Enable)
			return &Aimbot::WpnCfgs[0];

		if (itemDefIndex == WEAPON_SSG08)
			return &Aimbot::WpnCfgs[6];
		else if (itemDefIndex == WEAPON_AWP)
			return &Aimbot::WpnCfgs[7];
		else
		{
			if (WEAPONTYPE_PISTOL <= weaponType && weaponType <= WEAPONTYPE_SNIPER_RIFLE)
				return &Aimbot::WpnCfgs[weaponType];
			else if (weaponType == WEAPONTYPE_MACHINEGUN)
				return &Aimbot::WpnCfgs[3];
			else
				return nullptr;
		}
	}
}