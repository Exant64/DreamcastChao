#pragma once
struct Alr;
struct AlrEffUnit
{
	NJS_POINT3 trans;
	NJS_POINT3 velocity;
	char frame;
	char frame_inc_time;
	char mode;
	char flag;
	unsigned __int16 timer;
	unsigned __int16 tmp;
};
struct AlrEffData
{
	NJS_TEXLIST* texlist;
	NJS_TEXANIM* anim;
	float scale;
	char frame_inc_time_max;
	char anim_num;
	char unit_num;
	char tmp;
};
struct AlrEff
{
	AlrEffUnit unit[5];
	NJS_TEXLIST* texlist;
	NJS_TEXANIM* anim;
	float scale;
	void(__cdecl* exec)(AlrEffUnit*, NJS_POINT3*, NJS_POINT3*);
	unsigned __int16 frame_inc_time_max;
	char anim_num;
	char unit_num;
};
struct AlrEvent
{
	char level;
	char cnt;
	unsigned __int16 timer;
	void(__cdecl* event)(Alr*);
};
struct __declspec(align(2)) TaskCommunication
{
	ObjectMaster* obj_tp;
	char obj_kind;
	char command;
	char status;
};

struct __declspec(align(4)) Alr
{
	AlrEff eff;
	AlrEvent event;
	TaskCommunication communication;
	char id;
	char area;
	unsigned __int16 flag;
	char rank;
	char mode;
	char command;
	char smode;
	float sloop;
	float pathpos;
	char use_path;
	char ex_mode;
	unsigned __int16 ex_cnt;
	int amplitude;
	char now;
	char motion;
	char chao_flag;
	char voice;
	char zone;
	char padding;
	unsigned __int16 para_timer;
	float monooto;
	char sleep;
	char tire;
	char stress;
	char tmp;
	void* awp;
	void* twp;
};
struct ADV1_AL_IMPLESSION
{
	char like;
	char meet;
};
struct __declspec(align(4)) ADV1_AL_IMPLESSION2
{
	unsigned int id;
	char like;
	char meet;
};

struct ADV1_AL_MEMORY
{
	ADV1_AL_IMPLESSION player[6];
	ADV1_AL_IMPLESSION2 chao[32];
};

struct __declspec(align(4)) al_status
{
	char type;
	char garden_num;
	char like;
	char key1;
	char name[8];
	unsigned __int16 swim;
	unsigned __int16 fly;
	unsigned __int16 run;
	unsigned __int16 power;
	unsigned __int16 health;
	unsigned __int16 health_max;
	char fruit_kind[8];
	float h_pos;
	float v_pos;
	float growth;
	unsigned __int16 intimate;
	unsigned __int16 life;
	unsigned __int16 old;
	unsigned __int16 get_minimal;
	char win;
	char key2;
	unsigned __int16 flag;
	NJS_POINT3 pos;
	unsigned int age;
	unsigned int id;
	char animal_part_num[7];
	char key3;
	unsigned __int16 pt_swim;
	unsigned __int16 pt_fly;
	unsigned __int16 pt_run;
	unsigned __int16 pt_power;
	char kindness;
	char aggressive;
	char curiosity;
	char charm;
	char breed;
	char sleep;
	char hunger;
	char tedious;
	char tire;
	char stress;
	char narrow;
	char pleasure;
	char anger;
	char sorrow;
	char fear;
	char lonely;
	ADV1_AL_MEMORY memory;
	char nbSucceed;
	char lane;
	char IsCPU;
	char key4;
	char exist;
	unsigned __int16 mayu_timer;
	char race_time[20];
	char extra_num;
};
struct ADV1_AL_TMP_STATUS
{
	float aim_h_pos;
	float aim_v_pos;
	float aim_grouth;
	NJS_ARGB aim_argb;
};
struct al_action_ctrl
{
	unsigned __int16 old_mode;
	unsigned __int16 curr_mode;
	unsigned __int16 req_mode;
	unsigned __int16 flag;
	unsigned __int16 timer;
};
struct ADV1_AL_SHADOW
{
	unsigned __int16 flag;
	NJS_POINT3 colli_center;
	float colli_top;
	float colli_radius;
	float colli_bottom;
	float cliff_height;
	float bound_side;
	float bound_floor;
	float bound_friction;
	float bound_ceiling;
	int bound_add_angle;
	float shadow_scl;
	float shadow_scl_ratio;
	float water_pos;
	char si[204];
};
struct ADV1_AL_BODY
{
	obj* object;
	obj* my_parts[50];
	obj* zero[50];
	obj* standard[50];
	obj* fly[50];
	obj* run[50];
	obj* power[50];
	obj* swim[50];
	NJS_TEXLIST* tex;
};

struct alifewk
{
	int work;
	NJS_POINT3 velo;
	NJS_POINT3 acc;
	Rotation3 ang_aim;
	Rotation3 ang_spd;
	float rad;
	float height;
	float weight;
	ObjectMaster* lock_tp;
	void(__cdecl* dest_org)(ObjectMaster*);
	unsigned __int16 action_timer;
	unsigned __int16 stimer;
	unsigned __int16 voice_timer;
	unsigned __int16 rhythm_timer;
	__int16 old_mode;
	__int16 old_smode;
	__int16 curr_mode;
	__int16 curr_smode;
	__int16 req_mode;
	__int16 req_smode;
	__int16 hold_mode;
	unsigned int flag;
	unsigned __int16 action_mode;
	NJS_BGRA mat_col;
	float mayu_scl;
	float mayu_alpha;
	int name_alpha;
	unsigned __int16 name_timer;
	unsigned __int16 damage_timer;
	int pitch;
	int yaw;
	int roll;
	__int16 aim_num;
	NJS_POINT3 home;
	NJS_POINT3 aim;
	NJS_POINT3 pre;
	NJS_POINT3 offset;
	Rotation3 aim_ang;
	int view_angle;
	float view_range2;
	float hear_range2;
	float buyo_scale;
	float chao_scl;
	float aim_hpos;
	float aim_vpos;
	float aim_growth;
	unsigned __int16 sekkachi_timer;
	al_status* status;
	ADV1_AL_TMP_STATUS tmp_status;
	al_action_ctrl action_ctrl;
	ADV1_AL_MOTION_CTRL motion_ctrl;
	ADV1_AL_SHADOW shadow;
	ADV1_AL_BODY body;
};
struct ADV1_AL_FACE
{

	
};
struct ADV1_AL_FACE_HACK
{
	int EyeTimer;
	__int16 EyeColorNum;
	__int16 EyeCurrNum;
	__int16 EyeDefaultNum;
	__int16 padding;
	int MouthTimer;
	__int16 MouthCurrNum;
	__int16 MouthDefaultNum;
	float EyePosX;
	float EyePosY;
	int eyelid_keep_timer;
	int eyelid_request_close_ang;
	int eyelid_request_express_ang;
	al_object* pEyeObject[2];
	al_object* pMouthObject;
	int EyeLidBlinkMode;
	int EyeLidBlinkTimer;
	int EyeLidBlinkAng;
	int EyeLidExpressionMode;
	int EyeLidExpressionTimer;
	int EyeLidExpressionDefaultCloseAng;
	int EyeLidExpressionCurrCloseAng;
	int EyeLidExpressionAimCloseAng;
	int EyeLidExpressionDefaultSlopeAng;
	int EyeLidExpressionCurrSlopeAng;
	int EyeLidExpressionAimSlopeAng;
};
void __cdecl ALR_Dash(EntityData1* a1, alifewk* a2);