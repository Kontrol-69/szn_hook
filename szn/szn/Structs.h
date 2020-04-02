extern void load_structs(void);

struct client_t
{
	int currentValid;					//0x0000
	int nextValid;						//0x0004
	int ClientNumber;					//0x0008
	char Name[16];						//0x000C
	int Team;							//0x001C
	int oldTeam;						//0x0020
	int Rank;							//0x0024
	int Prestige;						//0x0028
	int Perk;							//0x002C
	char _0x002C[0x4];
	int Score;							//0x0034
	char _0x0038[0x8];
	char Model[4][64];					//0x0040
	char _0x0140[0x100];
	char backModel[2][64];				//0x0240
	char _0x02C0[0x138];
	int lerpMoveDir;					//0x03F8
	char _0x03FC[0x4];
	D3DXVECTOR3 viewAngle;				//0x0400
	char _0x040C[0x78];
	int Stance;							//0x0484
	char _0x0488[0xC];
	int isShooting;						//0x0494
	char _0x0498[0x4];
	int isAds;							//0x049C
	char _0x04A0[0x60];
	int WeaponID;						//0x0500
	char _0x0504[0x10];
	int isAkimbo;						//0x0514
	char _0x0518[0x4];
	int riotShieldNext;					//0x051C
	int cardtitleInfo[3];				//0x0520
};

struct cg_s
{
	int ServerTime;					//0x0000
	int isAlive;					//0x0004
	int JumpDelay;					//0x0008
	int WeaponActionState;			//0x000C
	int IsIngame;					//0x0010
	char pad_0014[8];				//0x0014
	D3DXVECTOR3 Origin;				//0x001C
	char pad_0028[12];				//0x0028
	int LethalTimer;				//0x0034
	int MaxEntites;					//0x0038
	char pad_003C[200];				//0x003C
	int ClientID;					//0x0104
	char pad_0108[8];				//0x0108
	D3DXVECTOR3 viewAngle;			//0x0110
	char pad_011C[52];				//0x011C
	int Health;						//0x0150
	char pad_0154[4];				//0x0154
	int MaxHealth;					//0x0158
	char pad_015C[356];				//0x015C
	float adsSpread;				//0x02C0
	float hipfireSpread;			//0x02C4
	char pad_02C8[984];				//0x02C8
	int EntityCount;				//0x06A0
	char pad_06A4[0xF636C];			//0x06A4
	client_t client[18];		//0xF6A10
};

struct entity_t
{
	short currentValid;				//0x0000
	short nextValid;				//0x0002
	char pad_0004[20];				//0x0004
	D3DXVECTOR3 CurrentOrigin;		//0x0018
	D3DXVECTOR3 Angles;				//0x0024
	char pad_0024[60];				//0x0024
	int eFlags;						//0x006C
	char pad_0070[24];				//0x0070
	D3DXVECTOR3 NextOrigin;			//0x0088
	char pad_0094[72];				//0x0094
	int ClientID;					//0x00DC
	int eType;						//0x00E0
	char pad_00E4[4];				//0x00E4
	int Stance;						//0x00E8
	char pad_00EC[24];				//0x00EC
	D3DXVECTOR3 PredictedOrigin;	//0x0104
	char pad_0110[92];				//0x0110
	int ItemID;						//0x016C
	char pad_0170[44];				//0x0170
	int nextClientID;				//0x019C
	char pad_01A0[8];				//0x01A0
	short WeaponID;					//0x01A8
	char pad_01AA[2];				//0x01AA
	short WeaponID2;				//0x01AC
	char pad_01AC[0x2E];			//0x01AE
	int isAlive;					//0x01DC
	char pad_01E0[36];				//0x01E0
};

struct usercmd_s
{
	int serverTime; //0x0000
	int buttons; //0x0004
	int viewAngles[3]; //0x0008
	char _0x0014[0x6]; //0x0014
	byte fDir; //0x001A
	byte rDir; //0x001B
	char _0x001C[0xC]; //0x001C
};

struct clientactive_t
{
	char _0x0000[0x60];
	D3DXVECTOR3 spawnAngle;		//0x60
	char _0x006C[0x31C4];
	D3DXVECTOR3 viewAngle;		//0x3230
	usercmd_s Cmd[128];			//0x323C
	int CurrentCmd;

	usercmd_s* get_cmd(int i)
	{
		return &Cmd[i & 0x7F];
	}
};

struct cursor_info
{
	float x;
	float y;
	int lastMoveTime;
};

struct uicontext_t
{
	int localClientNum;
	float bias;
	int realTime;
	int frameTime;
	cursor_info cursor;
	int isCursorVisible;
	int paintFull;
	int screenWidth;
	int screenHeight;
	float screenAspect;
	float FPS;
	float blurRadiusOut;
};

struct refdef_t
{
	int x;							// 0x0
	int y;							// 0x4
	int width;						// 0x8
	int height;						// 0xC
	D3DXVECTOR2 Fov;				// 0x10
	D3DXVECTOR3 Origin;				// 0x18
	D3DXVECTOR3 Axis[3];			// 0x24
	char padding00[0x1C];
};

enum weapType_t
{
	WEAPTYPE_BULLET = 0x0,
	WEAPTYPE_GRENADE = 0x1,
	WEAPTYPE_PROJECTILE = 0x2,
	WEAPTYPE_RIOTSHIELD = 0x3,
	WEAPTYPE_NUM = 0x4,
};

enum weapClass_t
{
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_SNIPER = 0x1,
	WEAPCLASS_MG = 0x2,
	WEAPCLASS_SMG = 0x3,
	WEAPCLASS_SPREAD = 0x4,
	WEAPCLASS_PISTOL = 0x5,
	WEAPCLASS_GRENADE = 0x6,
	WEAPCLASS_ROCKETLAUNCHER = 0x7,
	WEAPCLASS_TURRET = 0x8,
	WEAPCLASS_THROWINGKNIFE = 0x9,
	WEAPCLASS_NON_PLAYER = 0xA,
	WEAPCLASS_ITEM = 0xB,
	WEAPCLASS_NUM = 0xC,
};

enum PenetrateType
{
	PENETRATE_TYPE_NONE = 0x0,
	PENETRATE_TYPE_SMALL = 0x1,
	PENETRATE_TYPE_MEDIUM = 0x2,
	PENETRATE_TYPE_LARGE = 0x3,
	PENETRATE_TYPE_COUNT = 0x4,
};

enum weapInventoryType_t
{
	WEAPINVENTORY_PRIMARY = 0x0,
	WEAPINVENTORY_OFFHAND = 0x1,
	WEAPINVENTORY_ITEM = 0x2,
	WEAPINVENTORY_ALTMODE = 0x3,
	WEAPINVENTORY_EXCLUSIVE = 0x4,
	WEAPINVENTORY_SCAVENGER = 0x5,
	WEAPINVENTORYCOUNT = 0x6,
};

enum weapFireType_t
{
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
	WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
	WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
	WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
	WEAPON_FIRETYPECOUNT = 0x6,
	WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
	WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
};

enum OffhandClass
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_THROWINGKNIFE = 0x4,
	OFFHAND_CLASS_OTHER = 0x5,
	OFFHAND_CLASS_COUNT = 0x6,
};

enum weapStance_t
{
	WEAPSTANCE_STAND = 0x0,
	WEAPSTANCE_DUCK = 0x1,
	WEAPSTANCE_PRONE = 0x2,
	WEAPSTANCE_NUM = 0x3,
};

enum activeReticleType_t
{
	VEH_ACTIVE_RETICLE_NONE = 0x0,
	VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
	VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
	VEH_ACTIVE_RETICLE_COUNT = 0x3,
};

enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum ammoCounterClipType_t
{
	AMMO_COUNTER_CLIP_NONE = 0x0,
	AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
	AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
	AMMO_COUNTER_CLIP_ROCKET = 0x4,
	AMMO_COUNTER_CLIP_BELTFED = 0x5,
	AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
	AMMO_COUNTER_CLIP_COUNT = 0x7,
};

enum weapOverlayReticle_t
{
	WEAPOVERLAYRETICLE_NONE = 0x0,
	WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
	WEAPOVERLAYRETICLE_NUM = 0x2,
};

enum WeapOverlayInteface_t
{
	WEAPOVERLAYINTERFACE_NONE = 0x0,
	WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
	WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
	WEAPOVERLAYINTERFACECOUNT = 0x3,
};

enum weapProjExposion_t
{
	WEAPPROJEXP_GRENADE = 0x0,
	WEAPPROJEXP_ROCKET = 0x1,
	WEAPPROJEXP_FLASHBANG = 0x2,
	WEAPPROJEXP_NONE = 0x3,
	WEAPPROJEXP_DUD = 0x4,
	WEAPPROJEXP_SMOKE = 0x5,
	WEAPPROJEXP_HEAVY = 0x6,
	WEAPPROJEXP_NUM = 0x7,
};

enum WeapStickinessType
{
	WEAPSTICKINESS_NONE = 0x0,
	WEAPSTICKINESS_ALL = 0x1,
	WEAPSTICKINESS_ALL_ORIENT = 0x2,
	WEAPSTICKINESS_GROUND = 0x3,
	WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
	WEAPSTICKINESS_KNIFE = 0x5,
	WEAPSTICKINESS_COUNT = 0x6,
};

enum guidedMissileType_t
{
	MISSILE_GUIDANCE_NONE = 0x0,
	MISSILE_GUIDANCE_SIDEWINDER = 0x1,
	MISSILE_GUIDANCE_HELLFIRE = 0x2,
	MISSILE_GUIDANCE_JAVELIN = 0x3,
	MISSILE_GUIDANCE_COUNT = 0x4,
};

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};

struct trace_t
{
	float fraction;					//0x0000
	D3DXVECTOR3 surfaceDirection;	//0x0004
	int surfaceFlags;				//0x0010
	int contents;					//0x0014
	const char* material;			//0x0018
	int hitType;					//0x001c
	unsigned short entityNum;		//0x0020
	unsigned short modelIndex;		//0x0022
	unsigned short partName;		//0x0024
	unsigned short partGroup;		//0x0026
	bool allsolid;					//0x0028
	bool startsolid;				//0x0029
	bool walkable;					//0x002A
	char _0x002B[0x5];
	D3DXVECTOR3 endpos;				//0x0030 
	BYTE didHitEntity;				//0x003C 
	char pad_0x003D[0x3];			//0x003D	
	__int32 materialType;			//0x0040	
};

typedef struct
{
	char _0x0000[64];		//0x0000
	char ModelName[32];		//0x0040  
} weapon_info_t;

typedef struct
{
	char _0x0000[4];					//0x0000
	weapon_info_t* weapon_info;			//0x0004  
	char _0x0008[44];					//0x0008
	DWORD typePenetration;				//0x0034  
	char _0x0038[488];					//0x0038
	__int32 shots;						//0x0220  
	char _0x0224[0x380];				//0x0224
	float distance;						//0x05A4  
	char _0x05A8[4152];					//0x05A8
} complete_weapon_def_t;

typedef struct
{
	int	WorldEntNum;
	int	ignoreEntIndex;
	float damageMultiplier;
	int	methodOfDeath;
	D3DXVECTOR3	Origin, Start, End,	Dir;
} bullet_fire_params;

typedef struct
{
	char* name; 
	char _0x0004[0x4];
	int flags; 
	__int32 value; 
	char _0x0010[0x3C];

	bool isBool()
	{
		return (flags & 0xFF) == 0x0;
	}

	bool isFloat()
	{
		return (flags & 0xFF) == 0x1;
	}

	bool isInt()
	{
		return (flags & 0xFF) == 0x5;
	}

	bool isString()
	{
		return (flags & 0xFF) == 0x7;
	}

	bool hasBeenModified()
	{
		return ((flags >> 8) & 0xFF) != 0x0;
	}

	int getIntValue()
	{
		return *(int*)&value;
	}

	float getFloatValue()
	{
		return *(float*)&value;
	}

	bool getBoolValue()
	{
		if (value & 0xFF)
			return true;
		return false;
	}

	char* getStringValue()
	{
		return (char*)value;
	}

	void setBool(bool val)
	{
		*(bool*)&value = val;
	}

	void setInt(int val)
	{
		*(int*)&value = val;
	}

	void setFloat(float val)
	{
		*(float*)&value = val;
	}

	void setString(char* val)
	{
		int len = strlen(val) + 1;
		char* tmp = (char*)malloc(len);
		memcpy(tmp, val, len);
		value = (int)tmp;
	}
} dvar_t;

extern cg_s* cg;
extern entity_t* entity;
extern clientactive_t* clientactive;
extern uicontext_t uicontext;
extern refdef_t* refdef;
extern trace_t trace;