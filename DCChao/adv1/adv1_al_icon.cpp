#include "../pch.h"
#include "SADXModLoader.h"
#include "../chao.h"
#include "../al_race.h"
#include <cstddef>
#include "adv1_al_icon.h"
#include <random>
void FUN_80518dc4(ADV1_AL_ICON* icon)

{
	float fVar1;
	short  uVar2;
	short  wVar3;
	uVar2 = icon->smode_u;
	if (uVar2 == 2) {
		fVar1 = icon->sclspd_u.x;
		icon->sclspd_u.x = fVar1 + (-fVar1 * 0.08 - (icon->scl_u.x - 3.0) * 0.32);
		icon->scl_u.x = icon->scl_u.x + icon->sclspd_u.x;
		fVar1 = icon->sclspd_u.y;
		icon->sclspd_u.y = fVar1 + (-fVar1 * 0.12 - (icon->scl_u.y - 3.0) * 0.32);
		icon->scl_u.y = icon->scl_u.y + icon->sclspd_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.16 - (icon->pos_u.y - 2.2) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		wVar3 = icon->timer;
		icon->timer = wVar3 - 1;
		if (wVar3 == 0) {
			icon->smode_u = icon->smode_u + 1;
		}
	}
	else {
		if (uVar2 < 2) {
			if (uVar2 == 0) {
				icon->icon_num_u = ICON_NUM_BIKKURI;
				icon->pos_u.x = 0.0;
				icon->pos_u.y = 0.0;
				icon->pos_u.z = 0.01;
				icon->velo_u.y = 0.0;
				icon->scl_u.x = 0.5;
				icon->scl_u.y = 0.2;
				icon->sclspd_u.x = 0.0;
				icon->sclspd_u.y = 0.0;
				icon->smode_u = icon->smode_u + 1;
			}
			else {
				if (10 < icon->timer_u) {
					icon->smode_u = uVar2 + 1;
				}
			}
		}
		else {
			if (uVar2 < 4) {
				icon->scl_u.x = icon->scl_u.x - 0.4;
				if (icon->scl_u.x < 0.0) {
					icon->scl_u.x = 0.0;
				}
				icon->scl_u.y = icon->scl_u.y - 0.4;
				if (icon->scl_u.y < 0.0) {
					icon->scl_u.y = 0.0;
				}
				icon->pos_u.y = icon->pos_u.y - 0.4;
				if (icon->pos_u.y < 0.0) {
					icon->pos_u.y = 0.0;
					icon->mode = 0;
					icon->smode_u = 0;
					icon->smode_d = 0;
					icon->timer = 0;
				}
			}
		}
	}
	uVar2 = icon->smode_d;
	if (uVar2 == 1) {
		icon->scl_d.x = icon->scl_d.x - 0.05;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		if (icon->scl_d.x < 0.5) {
			icon->smode_d = icon->smode_d + 1;
			return;
		}
		return;
	}
	if (uVar2 == 0) {
		icon->icon_num_d = ICON_NUM_MARU;
		icon->pos_d.x = 0.0;
		icon->pos_d.y = 0.0;
		icon->pos_d.z = 0.0;
		icon->scl_d.x = 1.0;
		icon->scl_d.y = 1.0;
		icon->smode_d = icon->smode_d + 1;
		return;
	}
	if (uVar2 < 3) {
		fVar1 = icon->sclspd_d.x;
		icon->sclspd_d.x = fVar1 + (-fVar1 * 0.03 - (icon->scl_d.x - 1.0) * 0.32);
		icon->scl_d.x = icon->scl_d.x + icon->sclspd_d.x;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		return;
	}
	return;
}

void FUN_80518a74(ADV1_AL_ICON* icon)
{
	float fVar1;
	short uVar2;
	short wVar3;
	;

	uVar2 = icon->smode_u;
	if (uVar2 == 2) {
		fVar1 = icon->sclspd_u.x;
		icon->sclspd_u.x = fVar1 + (-fVar1 * 0.06 - (icon->scl_u.x - 3.5) * 0.12);
		icon->scl_u.x = icon->scl_u.x + icon->sclspd_u.x;
		fVar1 = icon->sclspd_u.y;
		icon->sclspd_u.y = fVar1 + (-fVar1 * 0.12 - (icon->scl_u.y - 3.5) * 0.32);
		icon->scl_u.y = icon->scl_u.y + icon->sclspd_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.16 - (icon->pos_u.y - 2.5) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		wVar3 = icon->timer;
		icon->timer = wVar3 - 1;
		if (wVar3 == 0) {
			icon->smode_u = icon->smode_u + 1;
		}
	}
	else {
		if (uVar2 < 2) {
			if (uVar2 == 0) {
				icon->icon_num_u = ICON_NUM_HATENA;
				icon->pos_u.x = 0.0;
				icon->pos_u.y = 0.0;
				icon->pos_u.z = 0.01;
				icon->velo_u.y = 0.0;
				icon->scl_u.x = 0.5;
				icon->scl_u.y = 0.2;
				icon->sclspd_u.x = 0.0;
				icon->sclspd_u.y = 0.0;
				icon->smode_u = icon->smode_u + 1;
			}
			else {
				if (10 < icon->timer_u) {
					icon->smode_u = uVar2 + 1;
				}
			}
		}
		else {
			if (uVar2 < 4) {
				icon->scl_u.x = icon->scl_u.x - 0.7;
				if (icon->scl_u.x < 0.0) {
					icon->scl_u.x = 0.0;
				}
				icon->scl_u.y = icon->scl_u.y - 0.4;
				if (icon->scl_u.y < 0.0) {
					icon->scl_u.y = 0.0;
				}
				icon->pos_u.y = icon->pos_u.y - 0.4;
				if (icon->pos_u.y < 0.0) {
					icon->pos_u.y = 0.0;
					icon->mode = 0;
					icon->smode_u = 0;
					icon->smode_d = 0;
					icon->timer = 0;
				}
			}
		}
	}
	uVar2 = icon->smode_d;
	if (uVar2 == 1) {
		icon->scl_d.x = icon->scl_d.x - 0.05;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		if (icon->scl_d.x < 0.5) {
			icon->smode_d = icon->smode_d + 1;
			return;
		}
		return;
	}
	if (uVar2 == 0) {
		icon->icon_num_d = ICON_NUM_MARU;
		icon->pos_d.x = 0.0;
		icon->pos_d.y = 0.0;
		icon->pos_d.z = 0.0;
		icon->scl_d.x = 1.0;
		icon->scl_d.y = 1.0;
		icon->smode_d = icon->smode_d + 1;
		return;
	}
	if (uVar2 < 3) {
		fVar1 = icon->sclspd_d.x;
		icon->sclspd_d.x = fVar1 + (-fVar1 * 0.03 - (icon->scl_d.x - 1.0) * 0.32);
		icon->scl_d.x = icon->scl_d.x + icon->sclspd_d.x;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		return;
	}
	return;
}

void FUN_80518718(ADV1_AL_ICON* icon)

{
	float fVar1;
	short uVar2;
	short wVar3;
	;

	uVar2 = icon->smode_u;
	if (uVar2 == 2) {
		fVar1 = icon->sclspd_u.x;
		icon->sclspd_u.x = fVar1 + (-fVar1 * 0.3 - (icon->scl_u.x - 3.5) * 0.32);
		icon->scl_u.x = icon->scl_u.x + icon->sclspd_u.x;
		fVar1 = icon->sclspd_u.y;
		icon->sclspd_u.y = fVar1 + (-fVar1 * 0.3 - (icon->scl_u.y - 3.5) * 0.32);
		icon->scl_u.y = icon->scl_u.y + icon->sclspd_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.5 - (icon->pos_u.y - 1.8) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		wVar3 = icon->timer;
		icon->timer = wVar3 - 1;
		if (wVar3 == 0) {
			icon->smode_u = icon->smode_u + 1;
		}
	}
	else {
		if (uVar2 < 2) {
			if (uVar2 == 0) {
				icon->icon_num_u = ICON_NUM_ONPU;
				icon->pos_u.x = -0.2;
				icon->pos_u.y = 0.0;
				icon->pos_u.z = 0.01;
				icon->velo_u.y = 0.0;
				icon->scl_u.x = 0.5;
				icon->scl_u.y = 0.2;
				icon->sclspd_u.x = 0.0;
				icon->sclspd_u.y = 0.0;
				icon->smode_u = icon->smode_u + 1;
			}
			else {
				if (10 < icon->timer_u) {
					icon->smode_u = uVar2 + 1;
				}
			}
		}
		else {
			if (uVar2 < 4) {
				icon->scl_u.x = icon->scl_u.x - 0.4;
				if (icon->scl_u.x < 0.0) {
					icon->scl_u.x = 0.0;
				}
				icon->scl_u.y = icon->scl_u.y - 0.4;
				if (icon->scl_u.y < 0.0) {
					icon->scl_u.y = 0.0;
				}
				icon->pos_u.y = icon->pos_u.y - 0.25;
				if (icon->pos_u.y < 0.0) {
					icon->pos_u.y = 0.0;
					icon->mode = 0;
					icon->smode_u = 0;
					icon->smode_d = 0;
					icon->timer = 0;
				}
			}
		}
	}
	uVar2 = icon->smode_d;
	if (uVar2 == 1) {
		icon->scl_d.x = icon->scl_d.x - 0.05;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		if (icon->scl_d.x < 0.5) {
			icon->smode_d = icon->smode_d + 1;
			return;
		}
		return;
	}
	if (uVar2 == 0) {
		icon->icon_num_d = ICON_NUM_MARU;
		icon->pos_d.x = 0.0;
		icon->pos_d.y = 0.0;
		icon->pos_d.z = 0.0;
		icon->scl_d.x = 1.0;
		icon->scl_d.y = 1.0;
		icon->smode_d = icon->smode_d + 1;
		return;
	}
	if (uVar2 < 3) {
		fVar1 = icon->sclspd_d.x;
		icon->sclspd_d.x = fVar1 + (-fVar1 * 0.3 - (icon->scl_d.x - 1.5) * 0.32);
		icon->scl_d.x = icon->scl_d.x + icon->sclspd_d.x;
		icon->scl_d.y = (3.0 - icon->scl_d.x) * 0.7;
		return;
	}
	return;
}

void FUN_805183f4(ADV1_AL_ICON* icon)

{
	float fVar1;
	short uVar2;
	short wVar3;
	;

	uVar2 = icon->smode_u;
	if (uVar2 == 2) {
		fVar1 = icon->sclspd_u.x;
		icon->sclspd_u.x = fVar1 + (-fVar1 * 0.08 - (icon->scl_u.x - 3.3) * 0.15);
		icon->scl_u.x = icon->scl_u.x + icon->sclspd_u.x;
		fVar1 = icon->sclspd_u.y;
		icon->sclspd_u.y = fVar1 + (-fVar1 * 0.12 - (icon->scl_u.y - 3.1) * 0.32);
		icon->scl_u.y = icon->scl_u.y + icon->sclspd_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.16 - (icon->pos_u.y - 1.0) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		wVar3 = icon->timer;
		icon->timer = wVar3 - 1;
		if (wVar3 == 0) {
			icon->smode_u = icon->smode_u + 1;
		}
	}
	else {
		if (uVar2 < 2) {
			if (uVar2 == 0) {
				icon->icon_num_u = ICON_NUM_HEART;
				icon->pos_u.x = 0.0;
				icon->pos_u.y = 0.0;
				icon->pos_u.z = -0.01;
				icon->velo_u.y = 0.0;
				icon->scl_u.x = 0.0;
				icon->scl_u.y = 0.0;
				icon->sclspd_u.x = 0.0;
				icon->sclspd_u.y = 0.0;
				icon->smode_u = icon->smode_u + 1;
			}
			else {
				if (10 < icon->timer_u) {
					icon->smode_u = uVar2 + 1;
				}
			}
		}
		else {
			if (uVar2 < 4) {
				icon->scl_u.x = icon->scl_u.x - 0.4;
				if (icon->scl_u.x < 0.0) {
					icon->scl_u.x = 0.0;
				}
				icon->scl_u.y = icon->scl_u.y - 0.4;
				if (icon->scl_u.y < 0.0) {
					icon->scl_u.y = 0.0;
					icon->mode = 0;
					icon->smode_u = 0;
					icon->smode_d = 0;
					icon->timer = 0;
				}
			}
		}
	}
	uVar2 = icon->smode_d;
	if (uVar2 == 1) {
		icon->scl_d.x = icon->scl_d.x - 0.05;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		if (icon->scl_d.x < 0.5) {
			icon->smode_d = icon->smode_d + 1;
			return;
		}
		return;
	}
	if (uVar2 == 0) {
		icon->icon_num_d = ICON_NUM_MARU;
		icon->pos_d.x = 0.0;
		icon->pos_d.y = 0.0;
		icon->pos_d.z = 0.0;
		icon->scl_d.x = 1.0;
		icon->scl_d.y = 1.0;
		icon->smode_d = icon->smode_d + 1;
		return;
	}
	if (uVar2 < 3) {
		fVar1 = icon->sclspd_d.x;
		icon->sclspd_d.x = fVar1 + (-fVar1 * 0.03 - (icon->scl_d.x - 1.0) * 0.32);
		icon->scl_d.x = icon->scl_d.x + icon->sclspd_d.x;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		return;
	}
	return;
}

void FUN_8051809c(ADV1_AL_ICON* icon)

{
	float fVar1;
	short uVar2;
	short wVar3;


	uVar2 = icon->smode_u;
	if (uVar2 == 2) {
		fVar1 = icon->sclspd_u.x;
		icon->sclspd_u.x = fVar1 + (-fVar1 * 0.08 - (icon->scl_u.x - 3.8) * 0.15);
		icon->scl_u.x = icon->scl_u.x + icon->sclspd_u.x;
		fVar1 = icon->sclspd_u.y;
		icon->sclspd_u.y = fVar1 + (-fVar1 * 0.12 - (icon->scl_u.y - 3.8) * 0.32);
		icon->scl_u.y = icon->scl_u.y + icon->sclspd_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.16 - (icon->pos_u.y - 2.2) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		fVar1 = icon->velo_u.y;
		icon->velo_u.y = fVar1 + (-fVar1 * 0.16 - (icon->pos_u.x - 0.5) * 0.4);
		icon->pos_u.y = icon->pos_u.y + icon->velo_u.y;
		wVar3 = icon->timer;
		icon->timer = wVar3 - 1;
		if (wVar3 == 0) {
			icon->smode_u = icon->smode_u + 1;
		}
	}
	else {
		if (uVar2 < 2) {
			if (uVar2 == 0) {
				icon->icon_num_u = ICON_NUM_MOJYA;
				icon->pos_u.x = 0.0;
				icon->pos_u.y = 0.0;
				icon->pos_u.z = -0.01;
				icon->velo_u.y = 0.0;
				icon->scl_u.x = 0.0;
				icon->scl_u.y = 0.0;
				icon->sclspd_u.x = 0.0;
				icon->sclspd_u.y = 0.0;
				icon->smode_u = icon->smode_u + 1;
			}
			else {
				if (10 < icon->timer_u) {
					icon->smode_u = uVar2 + 1;
				}
			}
		}
		else {
			if (uVar2 < 4) {
				icon->scl_u.x = icon->scl_u.x - 0.4;
				if (icon->scl_u.x < 0.0) {
					icon->scl_u.x = 0.0;
				}
				icon->scl_u.y = icon->scl_u.y - 0.4;
				if (icon->scl_u.y < 0.0) {
					icon->scl_u.y = 0.0;
					icon->mode = 0;
					icon->smode_u = 0;
					icon->smode_d = 0;
					icon->timer = 0;
				}
			}
		}
	}
	uVar2 = icon->smode_d;
	if (uVar2 == 1) {
		icon->scl_d.x = icon->scl_d.x - 0.05;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		if (icon->scl_d.x < 0.5) {
			icon->smode_d = icon->smode_d + 1;
			return;
		}
		return;
	}
	if (uVar2 == 0) {
		icon->icon_num_d = ICON_NUM_MARU;
		icon->pos_d.x = 0.0;
		icon->pos_d.y = 0.0;
		icon->pos_d.z = 0.0;
		icon->scl_d.x = 1.0;
		icon->scl_d.y = 1.0;
		icon->smode_d = icon->smode_d + 1;
		return;
	}
	if (uVar2 < 3) {
		fVar1 = icon->sclspd_d.x;
		icon->sclspd_d.x = fVar1 + (-fVar1 * 0.03 - (icon->scl_d.x - 1.0) * 0.32);
		icon->scl_d.x = icon->scl_d.x + icon->sclspd_d.x;
		icon->scl_d.y = 2.0 - icon->scl_d.x;
		return;
	}
	return;
}

alifewk wkTest = { 0 };
FunctionPointer(void, njDrawTexture3DEx, (NJS_TEXTURE_VTX* a1, signed int count, int a3), 0x0077E940);
FunctionPointer(void, DrawTri, (NJS_POINT3COL* a1, int a2, int a3), 0x403C10);
void ADV1_AL_IconControl(ObjectMaster* a1)
{
	short tex[8];
	int uStack196[4];
	int puStack180[4];
	float pos[8];
	int wVar1;
	float dVar2;
	//undefined auStack8[8];
	chaowk* wk = (chaowk*)a1->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;

	switch (icon->mode)
	{
	case ADV1_MD_ICON_NORMAL:
		wVar1 = icon->smode_d;
		if (wVar1 == 1) {
			dVar2 = njSin(icon->phase);
			icon->scl_d.x = dVar2 * 0.15 + 1.0;
			icon->scl_d.y = 2.0 - icon->scl_d.x;
		}
		else {
			if (wVar1 == 0) {
				icon->icon_num_u = 0;
				icon->pos_u.x = 0.0;
				icon->pos_u.y = 2.5;
				icon->pos_u.z = 0.0;
				icon->scl_u.x = 3.5;
				icon->scl_u.y = 3.5;
				icon->icon_num_d = 1;
				icon->pos_d.x = 0.0;
				icon->pos_d.y = 0.0;
				icon->pos_d.z = 0.0;
				icon->scl_d.x = 1.0;
				icon->scl_d.y = 1.0;
				icon->phase = 0;
				icon->smode_d = icon->smode_d + 1;
			}
		}
		icon->phase = icon->phase + 0xc00;
		break;
	case ADV1_MD_ICON_NOTICE:
		FUN_80518dc4(icon);
		break;
	case ADV1_MD_ICON_BIKKURI:
		FUN_80518dc4(icon);
		break;
	case ADV1_MD_ICON_HIRAMEKI:
		FUN_80518dc4(icon);
		break;
	case ADV1_MD_ICON_HATENA:
		FUN_80518a74(icon);
		break;
	case ADV1_MD_ICON_HAPPY:
		FUN_80518718(icon);
		break;
	case ADV1_MD_ICON_HEART:
		FUN_805183f4(icon);
		break;
	case ADV1_MD_ICON_MOJYA:
		FUN_8051809c(icon);
		break;
	}
}
void ADV1_AL_IconDrawLight(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;

	NJS_POINT3COL col;
	NJS_POINT3 p[4];
	p[0] = { -0.5f, 0.5f, -0.399f };
	p[1] = { -0.5f, -0.5f, -0.399f };
	p[2] = { 0.5f, -0.5f, -0.399f };
	p[3] = { 0.5f, 0.5f, -0.399f };
	NJS_COLOR color[4];
	color[0].color = 0xCCFFFFFF;
	color[1].color = 0xCCFFFFFF;
	color[2].color = 0xCCFFFFFF;
	color[3].color = 0xCCFFFFFF;

	NJS_TEX uvs[4];
	uvs[0].u = 0;
	uvs[0].v = 0;

	uvs[1].u = 0;
	uvs[1].v = 0xFF;

	uvs[2].u = 0xFF;
	uvs[2].v = 0xFF;

	uvs[3].u = 0xFF;
	uvs[3].v = 0;
	col.p = p;
	col.col = color;
	col.tex = uvs;
	col.num = 4;

	NJS_VECTOR out;
	NJS_VECTOR in = icon->pos;
	njCalcPoint(0, &in, &out);

	njSetTexture(&AL_ICON_TEXLIST);
	njPushMatrix(_nj_unit_matrix_);
	{
		njTranslateV(0, &out);
		njScale(0, a1->Data1->Scale.y, -a1->Data1->Scale.z, a1->Data1->Scale.y);

		njPushMatrix(0);
		njRotateZ(0, (rand() * 2));
		njTranslateV(0, &icon->pos_d);
		njSetTextureNum(0xB);
		njColorBlendingMode(0, 8);
		njColorBlendingMode(1, 10);
		DrawTri(&col, 4, (NJD_DRAW)0x80000060);
		njColorBlendingMode(0, 8);
		njColorBlendingMode(1, 6);
		njPopMatrix(1);
	}
	njPopMatrix(1);
}
void ADV1_AL_IconDraw(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	if (wk->pParamGC->Type == ChaoType_Neutral_Chaos)
	{
		ADV1_AL_IconDrawLight(a1);
		return;
	}
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;

	NJS_POINT3COL col;
	NJS_POINT3 p[4];
	p[0] = { -0.5f, 0.5f, -0.399f };
	p[1] = { -0.5f, -0.5f, -0.399f };
	p[2] = { 0.5f, -0.5f, -0.399f };
	p[3] = { 0.5f, 0.5f, -0.399f };
	NJS_COLOR color[4];
	color[0] = icon->col;
	color[1] = icon->col;
	color[2] = icon->col;
	color[3] = icon->col;

	NJS_TEX uvs[4];
	uvs[0].u = 0;
	uvs[0].v = 0;

	uvs[1].u = 0;
	uvs[1].v = 0xFF;

	uvs[2].u = 0xFF;
	uvs[2].v = 0xFF;

	uvs[3].u = 0xFF;
	uvs[3].v = 0;
	col.p = p;
	col.col = color;
	col.tex = uvs;
	col.num = 4;


	//original code does this outside of this function in the 
	//chao draw function where they calcpoint it with the node position
	NJS_VECTOR out;
	NJS_VECTOR in = icon->pos;
	njCalcPoint(0, &in, &out);

	njSetTexture(&AL_ICON_TEXLIST);
	njPushMatrix(_nj_unit_matrix_);
	{
		njTranslateV(0, &out);
		njScale(0, a1->Data1->Scale.y, -a1->Data1->Scale.z, a1->Data1->Scale.y);

		njPushMatrix(0);
		njTranslateV(0, &icon->pos_d);
		njSetTextureNum(icon->icon_num_d);
		njScale(0, icon->scl_d.x, icon->scl_d.y, 1.0);
		DrawTri(&col, 4, (NJD_DRAW)0x80000060);
		njPopMatrix(1);

		njPushMatrix(0);
		njTranslateV(0, &icon->pos_u);
		njSetTextureNum(icon->icon_num_u);
		njScale(0, icon->scl_u.x, icon->scl_u.y, 1.0);
		DrawTri(&col, 4, (NJD_DRAW)0x80000060);
		njPopMatrix(1);
	}
	njPopMatrix(1);
	icon->timer_u = icon->timer_u + 1;
	icon->timer_d = icon->timer_d + 1;
}
void __cdecl ADV1_AL_InitIcon(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;
	memset(icon, 0, sizeof(ADV1_AL_ICON));
	icon->mode = 0;
	icon->next_mode = -1;
}
void __cdecl AL_IconReset(ObjectMaster* tp)
{
	chaowk* wk = (chaowk*)tp->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;
	icon->mode = 0;
	icon->next_mode = -1;
	icon->timer = 0;
	icon->smode_d = 0;
	icon->smode_u = 0;
	//maybe?
	//icon->timer_d = 0;
	//icon->timer_u = 0;
}

void __cdecl AL_IconSet_DC(ObjectMaster* a1, char a2, int a3)
{
	chaowk* wk = (chaowk*)a1->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;
	switch (a2)
	{
	case MD_ICON_BIKKURI:
		icon->mode = ADV1_MD_ICON_BIKKURI;
		break;
	case MD_ICON_HEART:
		icon->mode = ADV1_MD_ICON_HEART;
		break;
	case MD_ICON_MOJYA:
		icon->mode = ADV1_MD_ICON_MOJYA;
		break;
	case MD_ICON_HATENA:
		icon->mode = ADV1_MD_ICON_HATENA;
		break;
	default:
		icon->mode = a2;
		break;
	}
	//icon->timer_u = 0;
	//icon->timer_d = 0;
	icon->smode_d = 0;
	icon->smode_u = 0;
	icon->timer = a3;
}