#pragma once

extern bool g_bDangerZone;

struct CEntInfo
{
	uintptr_t	m_pEntity;
	int			m_SerialNumber;
	CEntInfo*	m_pPrev;
	CEntInfo*	m_pNext;
};

enum MoveType_t : UCHAR
{
	MOVETYPE_NONE = 0,			// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
};

// Flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_ANIMDUCKING			(1<<2)	// Player flag -- Player is in the process of crouching or uncrouching but could be in transition
// examples:                                   Fully ducked:  FL_DUCKING &  FL_ANIMDUCKING
//           Previously fully ducked, unducking in progress:  FL_DUCKING & !FL_ANIMDUCKING
//                                           Fully unducked: !FL_DUCKING & !FL_ANIMDUCKING
//           Previously fully unducked, ducking in progress: !FL_DUCKING &  FL_ANIMDUCKING
#define	FL_WATERJUMP			(1<<3) // Player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5) // Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8) // Is a player
#define FL_FAKECLIENT			(1<<9) // Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<10) // In water

class CWeapon;

class CPlayer
{
public:
	int			index;
	uintptr_t	model;
	DWORD		m_clrRender;
	vec3		m_vecAbsVelocity;
	bool		m_bDormant;
	int			m_iTeamNum;
	int			m_iHealth;
	int			m_fFlags;
	vec3		m_vecViewOffset;
	vec3		m_vecVelocity;
	vec3		m_vecOrigin;
	char		m_lifeState;
	float		m_flSimulationTime;
	bool		m_bSpotted;
	uintptr_t	m_pBones;
	uintptr_t	m_pStudioHdr;
	DWORD		m_hActiveWeapon;
	vec3		m_aimPunchAngle;
	int			m_iDefaultFOV;
	int			m_nTickBase;
	bool		m_bIsScoped;
	bool		m_bIsWalking;
	bool		m_bGunGameImmunity;
	int			m_iShotsFired;
	int			m_nSurvivalTeam;
	float		m_flFlashAlpha;
	float		m_flFlashMaxAlpha;
	vec3		m_angEyeAngles;
	int			m_iIDEntIndex;
	CUtlVector	m_Hits;

	uintptr_t Address;

	inline void SetFromChunk(std::byte* chunk)
	{
		index = *reinterpret_cast<decltype(index)*>(reinterpret_cast<uintptr_t>(chunk) + 0x64);
		model = *reinterpret_cast<decltype(model)*>(reinterpret_cast<uintptr_t>(chunk) + 0x6C);
		CHUNKTONETVAR(chunk, m_clrRender);
		m_vecAbsVelocity = *reinterpret_cast<decltype(m_vecAbsVelocity)*>(reinterpret_cast<uintptr_t>(chunk) + 0x94);
		m_bDormant = *reinterpret_cast<decltype(m_bDormant)*>(reinterpret_cast<uintptr_t>(chunk) + 0xED);
		CHUNKTONETVAR(chunk, m_iTeamNum);
		CHUNKTONETVAR(chunk, m_iHealth);
		CHUNKTONETVAR(chunk, m_fFlags);
		CHUNKTONETVAR(chunk, m_vecViewOffset);
		CHUNKTONETVAR(chunk, m_vecVelocity);
		CHUNKTONETVAR(chunk, m_vecOrigin);
		CHUNKTONETVAR(chunk, m_lifeState);
		CHUNKTONETVAR(chunk, m_flSimulationTime);
		CHUNKTONETVAR(chunk, m_bSpotted);
		CHUNKTONETVAR(chunk, m_pBones);
		m_pStudioHdr = *reinterpret_cast<decltype(m_pStudioHdr)*>(reinterpret_cast<uintptr_t>(chunk) + Signatures::m_pStudioHdr);
		CHUNKTONETVAR(chunk, m_hActiveWeapon);
		CHUNKTONETVAR(chunk, m_aimPunchAngle);
		CHUNKTONETVAR(chunk, m_iDefaultFOV);
		CHUNKTONETVAR(chunk, m_nTickBase);
		CHUNKTONETVAR(chunk, m_bIsScoped);
		CHUNKTONETVAR(chunk, m_bIsWalking);
		CHUNKTONETVAR(chunk, m_bGunGameImmunity);
		CHUNKTONETVAR(chunk, m_iShotsFired);
		CHUNKTONETVAR(chunk, m_nSurvivalTeam);
		CHUNKTONETVAR(chunk, m_flFlashAlpha);
		CHUNKTONETVAR(chunk, m_flFlashMaxAlpha);
		CHUNKTONETVAR(chunk, m_angEyeAngles);
		CHUNKTONETVAR(chunk, m_iIDEntIndex);
		m_Hits = *reinterpret_cast<decltype(m_Hits)*>(reinterpret_cast<uintptr_t>(chunk) + Signatures::m_Hits);
	}

	inline void Update(uintptr_t pEntity)
	{
		std::byte* chunk = new std::byte[Signatures::m_Hits + sizeof(CUtlVector)];
		ReadProcessMemory(Mem::Process, reinterpret_cast<LPCVOID>(pEntity), chunk, Signatures::m_Hits + sizeof(CUtlVector), 0);
		SetFromChunk(chunk);
		delete[] chunk;
		Address = pEntity;
	}

	inline bool GetWeapon(CWeapon& out) const;

	inline bool IsEnemy(const CPlayer& pPlayer) const
	{
		return g_bDangerZone ? ((m_nSurvivalTeam == -1) || (m_nSurvivalTeam != pPlayer.m_nSurvivalTeam)) : (m_iTeamNum != pPlayer.m_iTeamNum);
	}

	inline bool IsGoodTarget() const
	{
		return !m_bDormant && !m_lifeState && !m_bGunGameImmunity;
	}
} g_LocalPlayer;

CPlayer g_Players[63];
unsigned int g_PlayersCount = 0;