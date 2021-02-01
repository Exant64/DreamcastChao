#pragma once
//sa2 icon enum
enum
{
    MD_ICON_NORMAL = 0x0,
    MD_ICON_BIKKURI = 0x1,
    MD_ICON_HIRAMEKI = 0x2,
    MD_ICON_HATENA = 0x3,
    MD_ICON_HEART = 0x4,
    MD_ICON_MOJYA = 0x5,
};
//sa1dc tex ids
enum 
{
    ICON_NUM_NONE = 0x0,
    ICON_NUM_MARU = 0x1,
    ICON_NUM_BIKKURI = 0x2,
    ICON_NUM_HATENA = 0x3,
    ICON_NUM_ONPU = 0x4,
    ICON_NUM_HEART = 0x5,
    ICON_NUM_MOJYA = 0x6,
    ICON_NUM_HOSHI = 0x7,
    ICON_NUM_MOKU = 0x8,
    ICON_NUM_DROP = 0x9,
};
//sa1 emotion ball id
enum 
{
    ADV1_MD_ICON_NORMAL = 0x0,
    ADV1_MD_ICON_NOTICE = 0x1,
    ADV1_MD_ICON_BIKKURI = 0x2,
    ADV1_MD_ICON_HIRAMEKI = 0x3,
    ADV1_MD_ICON_HATENA = 0x4,
    ADV1_MD_ICON_HAPPY = 0x5,
    ADV1_MD_ICON_HEART = 0x6,
    ADV1_MD_ICON_MOJYA = 0x7,
    ADV1_MD_ICON_HOSHI = 0x8,
    ADV1_MD_ICON_DROP = 0x9,
};

void ADV1_AL_IconControl(ObjectMaster* a1); 
void ADV1_AL_IconDraw(ObjectMaster* a1);
void __cdecl ADV1_AL_InitIcon(ObjectMaster* a1);
void __cdecl AL_IconSet_DC(ObjectMaster* a1, char a2, int a3);
void __cdecl AL_IconReset(ObjectMaster* tp);