#pragma once

enum
{
	LUMP_ENTITIES					= 0,	// *
	LUMP_PLANES						= 1,	// *
	LUMP_TEXDATA					= 2,	// *
	LUMP_VERTEXES					= 3,	// *
	LUMP_VISIBILITY					= 4,	// *
	LUMP_NODES						= 5,	// *
	LUMP_TEXINFO					= 6,	// *
	LUMP_FACES						= 7,	// *
	LUMP_LIGHTING					= 8,	// *
	LUMP_OCCLUSION					= 9,
	LUMP_LEAFS						= 10,	// *
	LUMP_FACEIDS					= 11,
	LUMP_EDGES						= 12,	// *
	LUMP_SURFEDGES					= 13,	// *
	LUMP_MODELS						= 14,	// *
	LUMP_WORLDLIGHTS				= 15,	// 
	LUMP_LEAFFACES					= 16,	// *
	LUMP_LEAFBRUSHES				= 17,	// *
	LUMP_BRUSHES					= 18,	// *
	LUMP_BRUSHSIDES					= 19,	// *
	LUMP_AREAS						= 20,	// *
	LUMP_AREAPORTALS				= 21,	// *
	LUMP_PROPCOLLISION				= 22,	// static props convex hull lists
	LUMP_PROPHULLS					= 23,	// static prop convex hulls
	LUMP_PROPHULLVERTS				= 24,	// static prop collision verts
	LUMP_PROPTRIS					= 25,	// static prop per hull triangle index start/count

	LUMP_DISPINFO					= 26,
	LUMP_ORIGINALFACES				= 27,
	LUMP_PHYSDISP					= 28,
	LUMP_PHYSCOLLIDE				= 29,
	LUMP_VERTNORMALS				= 30,
	LUMP_VERTNORMALINDICES			= 31,
	LUMP_DISP_LIGHTMAP_ALPHAS		= 32,
	LUMP_DISP_VERTS					= 33,		// CDispVerts
	LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS = 34,	// For each displacement
												//     For each lightmap sample
												//         byte for index
												//         if 255, then index = next byte + 255
												//         3 bytes for barycentric coordinates
	// The game lump is a method of adding game-specific lumps
	// FIXME: Eventually, all lumps could use the game lump system
	LUMP_GAME_LUMP					= 35,
	LUMP_LEAFWATERDATA				= 36,
	LUMP_PRIMITIVES					= 37,
	LUMP_PRIMVERTS					= 38,
	LUMP_PRIMINDICES				= 39,
	// A pak file can be embedded in a .bsp now, and the file system will search the pak
	//  file first for any referenced names, before deferring to the game directory 
	//  file system/pak files and finally the base directory file system/pak files.
	LUMP_PAKFILE					= 40,
	LUMP_CLIPPORTALVERTS			= 41,
	// A map can have a number of cubemap entities in it which cause cubemap renders
	// to be taken after running vrad.
	LUMP_CUBEMAPS					= 42,
	LUMP_TEXDATA_STRING_DATA		= 43,
	LUMP_TEXDATA_STRING_TABLE		= 44,
	LUMP_OVERLAYS					= 45,
	LUMP_LEAFMINDISTTOWATER			= 46,
	LUMP_FACE_MACRO_TEXTURE_INFO	= 47,
	LUMP_DISP_TRIS					= 48,
	LUMP_PROP_BLOB					= 49,	// static prop triangle & string data
	LUMP_WATEROVERLAYS              = 50,
	LUMP_LEAF_AMBIENT_INDEX_HDR		= 51,	// index of LUMP_LEAF_AMBIENT_LIGHTING_HDR
	LUMP_LEAF_AMBIENT_INDEX         = 52,	// index of LUMP_LEAF_AMBIENT_LIGHTING

	// optional lumps for HDR
	LUMP_LIGHTING_HDR				= 53,
	LUMP_WORLDLIGHTS_HDR			= 54,
	LUMP_LEAF_AMBIENT_LIGHTING_HDR	= 55,	// NOTE: this data overrides part of the data stored in LUMP_LEAFS.
	LUMP_LEAF_AMBIENT_LIGHTING		= 56,	// NOTE: this data overrides part of the data stored in LUMP_LEAFS.

	LUMP_XZIPPAKFILE				= 57,   // deprecated. xbox 1: xzip version of pak file
	LUMP_FACES_HDR					= 58,	// HDR maps may have different face data.
	LUMP_MAP_FLAGS                  = 59,   // extended level-wide flags. not present in all levels
	LUMP_OVERLAY_FADES				= 60,	// Fade distances for overlays
	LUMP_OVERLAY_SYSTEM_LEVELS		= 61,	// System level settings (min/max CPU & GPU to render this overlay) 
	LUMP_PHYSLEVEL                  = 62,
	LUMP_DISP_MULTIBLEND			= 63,	// Displacement multiblend info
};
namespace BSP
{
	struct lump_t
	{
		int		fileOfs;		// offset into file (bytes)
		int		fileLen;		// length of lump (bytes)
		int		version;		// lump format version
		char	fourCC[4];		// lump ident code
	};

	struct dheader_t
	{
		int		ident;			// BSP file identifier
		int		version;		// BSP file version
		lump_t	lumps[64];		// lump directory array HEADER_LUMPS
		int		mapRevision;	// the map's revision (iteration, version) number
	};

	struct dnode_t
	{
		int				planeNum;		// index into plane array
		int				children[2];	// negative numbers are -(leafs + 1), not nodes
		short			mins[3];		// for frustum culling
		short			maxs[3];
		unsigned short	firstFace;		// index into face array
		unsigned short	numFaces;		// counting both sides
		short			area;			// If all leaves below this node are in the same area, then this is the area index. If not, this is -1.
		short			paddding;		// pad to 32 bytes length
	};

	struct dplane_t
	{
		vec3	normal;		// normal vector
		float	dist;		// distance from origin
		int		type;		// plane axis identifier
	};

	struct dleaf_t
	{
		int				contents;			// OR of all brushes (not needed?)
		short			cluster;			// cluster this leaf is in
		short			area : 9;			// area this leaf is in
		short			flags : 7;			// flags
		short			mins[3];			// for frustum culling
		short			maxs[3];
		unsigned short	firstLeafFace;		// index into leaffaces
		unsigned short	numLeafFaces;
		unsigned short	firstLeafBrush;		// index into leafbrushes
		unsigned short	numLeafBrushes;
		short			leafWaterDataID;	// -1 for not in water
	};


	char*		m_mapData = nullptr;
	dplane_t*	m_lumpPlane = nullptr;
	dnode_t*	m_lumpNode = nullptr;
	dleaf_t*	m_lumpLeaf = nullptr;

	void Load(const char Map[])
	{
		char Path[MAX_PATH];
		strcpy_s(Path, sizeof(Path), Mem::GetDir());
		strcat_s(Path, sizeof(Path), "csgo\\");
		strcat_s(Path, sizeof(Path), Map);
		char* scrim = strstr(Path, "_scrim");
		if (scrim)
		{
			scrim[0] = '.';
			scrim[1] = 'b';
			scrim[2] = 's';
			scrim[3] = 'p';
			scrim[4] = '\0';
		}

		std::ifstream File(Path, std::ios::binary | std::ios::ate);
		if (File.fail())
			ErrorExit("Failed to open a map");

		const int length = File.tellg();
		File.seekg(0, File.beg);

		delete[] m_mapData;
		m_mapData = new char[length];
		File.read(m_mapData, length);
		File.close();

		const dheader_t* header = reinterpret_cast<dheader_t*>(m_mapData);
		m_lumpPlane = reinterpret_cast<dplane_t*>(m_mapData + header->lumps[LUMP_PLANES].fileOfs);
		m_lumpNode = reinterpret_cast<dnode_t*>(m_mapData + header->lumps[LUMP_NODES].fileOfs);
		m_lumpLeaf = reinterpret_cast<dleaf_t*>(m_mapData + header->lumps[LUMP_LEAFS].fileOfs);
	}

	dleaf_t* GetLeafForPoint(const vec3& point)
	{
		int iNode = 0;
		while (iNode >= 0)
		{
			const dnode_t* pNode = &m_lumpNode[iNode];
			const dplane_t* pPlane = &m_lumpPlane[pNode->planeNum];
			iNode = (((point.x * pPlane->normal.x + point.y * pPlane->normal.y + point.z * pPlane->normal.z) - pPlane->dist) > 0.f) ? pNode->children[0] : pNode->children[1];
		}
		return &m_lumpLeaf[-1 - iNode];
	}

	bool isVisible(const vec3& start, const vec3& end)
	{
		vec3 direction(end - start);
		int stepCount = direction.Length();
		direction /= stepCount;

		vec3 point(start);
		while (stepCount)
		{
			point += direction;
			const dleaf_t* leaf = GetLeafForPoint(point);
			if (leaf && (leaf->contents & 1))
				return false;

			--stepCount;
		}
		return true;
	}

	bool canWallbang(const vec3& start, const vec3& end, int WeaponIndex)
	{
		int leftWallbangable;
		switch (WeaponIndex)
		{
		case WEAPON_DEAGLE:

		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_FAMAS:
		case WEAPON_GALILAR:
		case WEAPON_M4A1:
		case WEAPON_SG556:
		case WEAPON_M4A1_SILENCER:

		case WEAPON_M249:
		case WEAPON_NEGEV:
			leftWallbangable = 12;
			break;
		case WEAPON_AWP:
			leftWallbangable = 26;
			break;
		case WEAPON_G3SG1:
		case WEAPON_SCAR20:
			leftWallbangable = 18;
			break;
		case WEAPON_REVOLVER:
		case WEAPON_SSG08:
			leftWallbangable = 16;
			break;
		case WEAPON_TASER:
			leftWallbangable = 0;
			break;
		default:
			leftWallbangable = 3;
			break;
		}

		vec3 direction(end - start);
		int stepCount = direction.Length();
		direction /= stepCount;

		vec3 point(start);
		while (stepCount)
		{
			point += direction;
			const dleaf_t* leaf = GetLeafForPoint(point);
			if (leaf && (leaf->contents & 1))
			{
				if (leftWallbangable <= 0)
					return false;

				--leftWallbangable;
			}
			--stepCount;
		}
		return true;
	}

	bool CanHit(const vec3& start, const vec3& end, int WeaponIndex)
	{
		return (!Config::Aimbot::PseudoAwall) ? isVisible(start, end) : canWallbang(start, end, WeaponIndex);
	}
}