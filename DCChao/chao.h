#pragma once
#include "SADXModLoader.h"

struct al_motion_table
{
	NJS_MOTION* motion;
	__int16 mode;
	__int16 next;
	float start_frame;
	float end_frame;
	float frame_spd;
	float link_spd;
};
struct ADV1_AL_MOTION_CTRL
{
	unsigned __int16 mode;
	unsigned __int16 flag;
	unsigned __int16 timer;
	__int16 curr_num;
	__int16 link_num;
	__int16 req_num;
	float nframe;
	float pframe;
	float lframe;
	float link_ratio;
	float* multi_spd;//float multi_spd;
	al_motion_table* motion_table;
	
};

struct NJS_MKEY_SA
{
	Sint16 keyframe;
	Sint16 ang[3];
};
struct MOTION_TABLE
{
	NJS_MOTION* pMotion;
	__int16 mode;
	__int16 posture;
	int next;
	int link_step;
	float start;
	float end;
	float spd;
};
struct MOTION_INFO
{
	int mode;
	float frame;
	float start;
	float end;
	float spd;
	NJS_MOTION* pMotion;
};
struct MOTION_CTRL
{
	unsigned __int16 flag;
	unsigned __int16 posture;
	int curr_num;
	int next_num;
	float multi_spd;
	float link_spd;
	float ratio;
	MOTION_INFO minfo[2];
	MOTION_TABLE* table;
};

enum eKW_BHV_KIND : int32_t
{
	KW_BHV_ART = 0x0,
	KW_BHV_DANCE = 0x1,
	KW_BHV_SING = 0x2,
	KW_BHV_MUSIC = 0x3,
	KW_BHV_MINI1 = 0x4,
	KW_BHV_MINI2 = 0x5,
	KW_BHV_MINI3 = 0x6,
	KW_BHV_MINI4 = 0x7,
	KW_BHV_MINI5 = 0x8,
	KW_BHV_MINI6 = 0x9,
	KW_BHV_MINI7 = 0xA,
	KW_BHV_MINI8 = 0xB,
	KW_BHV_MINI9 = 0xC,
	KW_BHV_MINI10 = 0xD,
	KW_BHV_MINI11 = 0xE,
	KW_BHV_MINI12 = 0xF,
	KW_BHV_MINI13 = 0x10,
	KW_BHV_MINI14 = 0x11,
	KW_BHV_MINI15 = 0x12,
	KW_BHV_MINI16 = 0x13,
	KW_BHV_MINI17 = 0x14,
	KW_BHV_MINI18 = 0x15,
	KW_BHV_TOY1 = 0x16,
	KW_BHV_TOY2 = 0x17,
	KW_BHV_TOY3 = 0x18,
	KW_BHV_TOY4 = 0x19,
	KW_BHV_TOY5 = 0x1A,
	KW_BHV_TOY6 = 0x1B,
	KW_BHV_TOY7 = 0x1C,
	KW_BHV_TOY8 = 0x1D,
	KW_BHV_TOY9 = 0x1E,
	KW_BHV_TOY10 = 0x1F,
	KW_BHV_TOY11 = 0x20,
	KW_BHV_FLY = 0x21,
	KW_BHV_SWIM = 0x22,
	KW_BHV_CLIMB_TREE = 0x23,
	KW_BHV_CLIMB_WALL = 0x24,
	KW_BHV_WATER = 0x25,
	KW_BHV_SWING = 0x26,
	KW_BHV_SIT = 0x27,
	KW_BHV_DENGURI = 0x28,
	KW_BHV_TOILET = 0x29,
	KW_BHV_PYON = 0x2A,
	KW_BHV_BOWLING = 0x2B,
	KW_BHV_FUKKIN = 0x2C,
	KW_BHV_SHIRIFURI = 0x2D,
	KW_BHV_OJIGI = 0x2E,
	KW_BHV_CHIWA = 0x2F,
	KW_BHV_NADERU = 0x30,
	KW_BHV_AGERU = 0x31,
	KW_BHV_TALK = 0x32,
	KW_BHV_PUNCH = 0x33,
	KW_BHV_OKOSU = 0x34,
	KW_BHV_TEFURI = 0x35,
	KW_BHV_HAKUSYU = 0x36,
	KW_BHV_SURIYORU = 0x37,
	KW_BHV_AKANBE = 0x38,
	KW_BHV_WA = 0x39,
	KW_BHV_NAGERU = 0x3A,
	KW_BHV_FIGHT = 0x3B,
	KW_BHV_IGAMI = 0x3C,
	KW_BHV_LISTEN = 0x3D,
	KW_BHV_WATCH = 0x3E,
};

struct KW_BHV_ENTRY
{
	eKW_BHV_KIND bhv;
};
struct AL_BEHAVIOR
{
	unsigned __int16 Flag;
	unsigned __int16 Mode;
	unsigned __int16 SubMode;
	unsigned __int16 MoveMode;
	int InterruptFlag;
	int Timer;
	int SubTimer;
	int LimitTimer;
	int BehaviorTimer;
	unsigned __int16 Intention;
	unsigned __int16 IntentionMode;
	int IntentionSubMode;
	unsigned int IntentionTimer[18];
	unsigned int IntervalTimer[128];
	int FreeWork;
	float MoveRadius;
	NJS_POINT3 BasePos;
	int(__cdecl* PrevFunc)(task*);
	int nbBhvFuncEntry;
	int CurrBhvFuncNum;
	int(__cdecl* BhvFuncList[16])(task*);
	int ReserveTimerList[16];
	int CurrKwBhvNum;
	int KwBhvList[4];
	unsigned int dummy[16];
};
struct AL_GROUP_OBJECT_LIST
{
	NJS_CNK_OBJECT* Zero[40];
	NJS_CNK_OBJECT* Normal[40];
	NJS_CNK_OBJECT* Swim[40];
	NJS_CNK_OBJECT* Fly[40];
	NJS_CNK_OBJECT* Run[40];
	NJS_CNK_OBJECT* Power[40];
};

struct AL_ITEM_INFO
{
	NJS_CNK_OBJECT* pObject;
	NJS_TEXLIST* pTexlist;
	NJS_POINT3 OffsetPos;
	Rotation3 OffsetAng;
};

struct AL_SHAPE
{
	al_object* pObject;
	al_object* CurrObjectList[40];
	AL_GROUP_OBJECT_LIST* pObjectList;
	AL_GROUP_OBJECT_LIST* pObjectListH;
	AL_GROUP_OBJECT_LIST* pObjectListD;
	NJS_POINT3 BodyPos;
	NJS_POINT3 HeadPos;
	NJS_POINT3 LeftHandPos;
	NJS_POINT3 RightHandPos;
	NJS_POINT3 LeftFootPos;
	NJS_POINT3 RightFootPos;
	NJS_POINT3 MouthPos;
	NJS_POINT3 MouthVec;
	NJS_POINT3 LeftEyePos;
	NJS_POINT3 LeftEyeVec;
	NJS_POINT3 RightEyePos;
	NJS_POINT3 RightEyeVec;
	NJS_CNK_OBJECT* pLeftHandItemObject;
	NJS_TEXLIST* pLeftHandItemTexlist;
	float LeftHandItemScale;
	float LeftHandItemActiveFlag;
	NJS_CNK_OBJECT* pRightHandItemObject;
	NJS_TEXLIST* pRightHandItemTexlist;
	float RightHandItemScale;
	float RightHandItemActiveFlag;
	unsigned __int16* palette;
	unsigned __int16 Flag;
	__int16 ColorNum;
	int EnvNum;
	unsigned int IconColor;
	float SclH;
	float SclV;
	float CamDist;
};

struct AL_ICON_INFO
{
	unsigned __int16 Mode;
	unsigned __int16 TexNum;
	int Timer;
	NJS_POINT3 Offset;
	NJS_POINT3 Pos;
	NJS_POINT3 Velo;
	NJS_POINT3 Scl;
	NJS_POINT3 SclSpd;
};

struct AL_ICON
{
	__int16 CurrType;
	__int16 NextType;
	int Timer;
	int NextTimer;
	int PuniPhase;
	int PosPhase;
	unsigned int Color;
	unsigned __int16 TexAnimNum;
	unsigned __int16 TexAnimTimer;
	int ang;
	NJS_POINT3 Up;
	NJS_POINT3 Pos;
	AL_ICON_INFO Upper;
	AL_ICON_INFO Lower;
};
struct AL_ZONE
{
	unsigned __int16 Flag;
	unsigned __int16 CurrNum;
	float Ratio;
	NJS_LINE Plane;
};
FunctionPointer(void, sub_408530, (NJS_OBJECT* a1), 0x408530);
FunctionPointer(void, AL_CalcMotionMartix, (al_object* a1), 0x00765010);
#pragma pack(push, 8)
struct __declspec(align(8)) chaowk
{
	EntityData1 entity;
	int Timer;
	int pMayu;
	ObjectMaster* pBookTask;
	int NestFlag;
	ObjectMaster* pAnyTask;
	int pAimTask;
	int AimNum;
	int RememberNum;
	int pitch;
	int ClimbFirstPos;
	int IsParamCopy;
	ChaoDataBase* pParamGC;
	TMP_PARAM tmpParam;
	int Stamina;
	int AimStamina;
	int tp;
	int pre_ang[3];
	int ChaoFlag;
	int ColliFormat;
	float CurrZone;
	MOTION_CTRL MotionCtrl;
	MOTION_CTRL MiniMotionCtrl;
	MOTION_TABLE MiniMotionTable[4];
	AL_BEHAVIOR Behavior;
	AL_SHAPE Shape;
	AL_FACE_CTRL Face;
	AL_ICON Icon;
	AL_ZONE Zone;
	AL_PERCEPTION Perception;
	void* pWork;
};
#pragma pack(pop)

