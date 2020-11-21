#include "pch.h"
#include "SADXModLoader.h"
#include "al_shape_basic.h"
#include <string>

#include "chao.h"
#include "al_race.h"
#include "dreamcast.h"
//FunctionPointer(double, sub_7547A0, (float a2, float a3, float a4), 0x7547A0);
FunctionPointer(int, sub_74F980, (int a1), 0x74F980);
const int sub_7547A0Ptr = 0x7547A0;
double sub_7547A0(int* alr, float a1, float a2, float a3)
{
	double result;
	__asm
	{
		push a3
		push a2
		push a1
		mov ecx, alr
		call sub_7547A0Ptr
		add esp, 12
		fstp result
	}
	return result;
}
void __cdecl ALR_Dash(EntityData1* a1, alifewk* a2)
{
	Alr* v2; // ebp
	al_status* v3; // eax
	Angle v4; // ebx
	double v5; // st7
	int v6; // ebx
	al_status* v7; // eax
	char v8; // al
	double v9; // st7
	double v10; // st7
	double v11; // st7
	float v12; // ST18_4
	float v13; // ST00_4
	float v14; // [esp+14h] [ebp-Ch]
	float v15; // [esp+14h] [ebp-Ch]
	float v16; // [esp+18h] [ebp-8h]

	v2 = (Alr*)a1->LoopData;
	if (a1->NextAction)
	{
		if (a1->NextAction != 1)
		{
			return;
		}
	}
	else
	{
		v3 = a2->status;
		if (v3->run <= 3500u)
		{
			if (v3->kindness <= 0)
			{
				ADV1toADV2_SetMotionLink((int)a2, 0);
				v2->motion = 0;
			}
			else
			{
				ADV1toADV2_SetMotionLink((int)a2, 48);
				v2->motion = 48;
			}
		}
		else if (v3->fly <= 3500u)
		{
			ADV1toADV2_SetMotionLink((int)a2, 49);
			v2->motion = 49;
		}
		else
		{
			ADV1toADV2_SetMotionLink((int)a2, 10);
			v2->motion = 10;
		}
		a2->shadow.colli_center.y = 7.0;
		++a1->NextAction;
		a1->InvulnerableTime = 0;
		a1->Index = 0;
	}
	v4 = a1->Rotation.y;
	v14 = njSin(a1->Rotation.y);
	v5 = njCos(v4);
	v16 = v5;
	a2->acc.x = v5 * 0.023 - fabs(v14) * a2->velo.x * 0.023 + a2->acc.x;
	a2->acc.z = a2->acc.z - (fabs(v16) * a2->velo.z + v14) * 0.023;
	if (a1->InvulnerableTime > 90.0)
	{
		a2->acc.x = njSin(v2->amplitude) * v14 * 0.01 + a2->acc.x;
		a2->acc.z = njSin(v2->amplitude) * v16 * 0.01 + a2->acc.z;
	}
	v6 = ((double)rand() * 0.000030517578 * 1000.0);
	if (a1->InvulnerableTime > 0x12Cu && v6 < 15 - 2 * sub_74F980((int)v2))
	{
		a1->Action = 4;
		a1->NextAction = 0;
		a1->InvulnerableTime = 0;
		return;
	}
	if (a1->InvulnerableTime <= 0x3Cu)
	{
		goto LABEL_47;
	}
	v7 = a2->status;
	if (v7->sleep > 199u)
	{
		v7->sleep = 0;
		a1->Action = 5;
		a1->NextAction = 0;
		a1->InvulnerableTime = 0;
		return;
	}
	if (v7->stress <= 199u)
	{
	LABEL_47:
		if (v2->sleep < 1)
		{
			v2->sleep = 1;
		}
		if (v2->tire < 1)
		{
			v2->tire = 1;
		}
		v9 = v2->sloop * 10.0;
		if (v9 > 0.5)
		{
			v9 = 0.5;
		}
		v10 = v9 - (double)a2->status->power * 0.000024999999;
		if (v10 > 0.0)
		{
			v11 = 1.0 - v10;
			a2->acc.x = v11 * a2->acc.x;
			a2->acc.z = v11 * a2->acc.z;
			if (v2->tire < 2)
			{
				v2->tire = 2;
			}
			rand();
		}
		if ((double)(unsigned __int8)a1->Index > 120.0)
		{
			if (v2->sloop <= 0.0)
			{
				v2->voice = 1;
			}
			else
			{
				v2->voice = 5;
			}
			a1->Index = ((double)rand() * 0.000030517578 * 10.0);
		}
		v12 = njScalor(&a2->velo);
		v13 = (double)a2->status->run;
		v15 = sub_7547A0((int*)v2, v13, 0.25, 0.5);
		if (v12 > (double)v15)
		{
			njUnitVector(&a2->velo);
			a2->velo.x = v15 * a2->velo.x;
			a2->velo.y = v15 * a2->velo.y;
			a2->velo.z = v15 * a2->velo.z;
		}
		float dVar15 = 0.0f;
		int bVar3 = v2->motion;
		if (bVar3 == 10) {
			dVar15 = 2.00000000;
		}
		else {
			if (bVar3 < 10) {
				if (bVar3 == 0) {
					dVar15 = 0.50000000;
				}
				else {
				LAB_8050895c:
					dVar15 = 1.00000000;
				}
			}
			else {
				if (bVar3 == 0x31) {
					dVar15 = 2.00000000;
				}
				else {
					if ((0x30 < bVar3) || (bVar3 < 0x30)) goto LAB_8050895c;
					dVar15 = 2.70000005;
				}
			}
		}
		*(float*)&a2->motion_ctrl.multi_spd = (dVar15 * v15);
		if (a1->InvulnerableTime > 0x3Cu)
		{
			((char*)&a1->Status)[1] |= 0x10u;
		}
		((char*)& a1->Status)[1] |= 0x20u;
	}
	else
	{
		v7->stress = 0;
		v8 = a2->status->aggressive;
		a1->InvulnerableTime = 0;
		a1->NextAction = 0;
		if (v8 <= 0)
		{
			a1->Action = 7;
		}
		else
		{
			a1->Action = 6;
		}
	}
}
