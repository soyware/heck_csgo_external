#pragma once

#define BONE_USED_BY_HITBOX	0x00000100	// bone (or child) is used by a hit box

// Credits: ReactiioN
enum EHitbox
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_CHEST,
	HITBOX_LOWER_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_LOWER_ARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_LOWER_ARM,
	HITBOX_LAST
};

struct mstudiobbox_t
{
	int					bone;
	int					group;				// intersection group
	vec3				bbmin;				// bounding box
	vec3				bbmax;
	int					szHitboxNameIndex;	// offset to the name of the hitbox.
	int					unused[3];
	float				radius;
	int					unused2[4];
};

struct mstudiohitboxset_t
{
	int					szNameIndex;
	int					numhitboxes;
	int					hitboxindex;
};

struct mstudiobone_t
{
	int					szNameIndex;
	int		 			parent;				// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

	// default values
	vec3				pos;
	float				quat[4];
	vec3				rot;

	// compression scale
	vec3				posscale;
	vec3				rotscale;

	matrix3x4_t			poseToBone;
	float				qAlignment[4];
	int					flags;
	int					proctype;
	int					procindex;			// procedural rule
	mutable int			physicsbone;		// index into physically simulated bone
	int					surfacepropidx;		// index into string tablefor property name

	int					contents;			// See BSPFlags.h for the contents flags
	int					SurfacePropLookup;	// this index must be cached by the loader, not saved in the file
	int					unused[7];
};

namespace Studio
{
	std::unordered_map<uint32_t, int[HITBOX_LAST]> mapHitboxBones;

	void InitHitboxBones(uint32_t fnHandle, uintptr_t pStudioHdr)
	{
		uintptr_t studiohdr;
		Mem::Read<uintptr_t>(pStudioHdr, studiohdr);

		int hitboxsetindex;
		Mem::Read<int>(studiohdr + 0xB0, hitboxsetindex);

		uintptr_t pHitboxSet = studiohdr + hitboxsetindex;
		mstudiohitboxset_t hitboxset; // player have just 1 set
		Mem::Read<mstudiohitboxset_t>(pHitboxSet, hitboxset);

		if (hitboxset.numhitboxes != HITBOX_LAST)
			ErrorExit("Error: Hitboxes enum requires an update");

		for (UINT i = 0; i < HITBOX_LAST; ++i)
			mapHitboxBones[fnHandle][i] = Mem::Read<mstudiobbox_t>(pHitboxSet + hitboxset.hitboxindex + i * sizeof(mstudiobbox_t)).bone;
	}

	const int* const GetHitboxBones(const CPlayer& Player)
	{
		uint32_t fnHandle;
		Mem::Read<uint32_t>(Player.model, fnHandle);

		auto s = mapHitboxBones.find(fnHandle);
		if (s == mapHitboxBones.end())
		{
			InitHitboxBones(fnHandle, Player.m_pStudioHdr);
			return mapHitboxBones.find(fnHandle)->second;
		}
		else
			return s->second;
	}

	//void GetBones(const CPlayer& Player)
	//{
	//	uintptr_t studiohdr;
	//	Mem::Read<uintptr_t>(Mem::Read<uintptr_t>(Player.pStudioHdr), studiohdr);

	//	struct studiohdr_part
	//	{
	//		int					numbones;
	//		int					boneindex;
	//	};
	//	studiohdr_part bonePart;
	//	Mem::Read<studiohdr_part>(studiohdr + 0x9C, bonePart);

	//	for (UINT i = 0; i < bonePart.numbones; ++i)
	//	{
	//		mstudiobone_t bone;
	//		Mem::Read<mstudiobone_t>(studiohdr + bonePart.boneindex + i * sizeof(mstudiobone_t), bone);
	//		if (bone.flags & BONE_USED_BY_HITBOX)
	//			return; // do shit
	//	}
	//}
}