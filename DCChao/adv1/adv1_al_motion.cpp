#include "../pch.h"
#include "SADXModLoader.h"
#include "../chao.h"
#include "../data/al_motion//al_dc_motion.h"
#include "../al_race.h"
void ADV1_AL_MotionInit(chaowk* wk)
{
	ADV1_AL_MOTION_CTRL* ctrl = (ADV1_AL_MOTION_CTRL*)&wk->MotionCtrl;
	memset(ctrl, 0, sizeof(ADV1_AL_MOTION_CTRL));
	ctrl->curr_num = 0;
	ctrl->link_num = 0;
	ctrl->req_num = 0;
	ctrl->motion_table = exportedSA1;
	ctrl->mode = ctrl->motion_table[ctrl->curr_num].mode;
	ctrl->multi_spd = 1;
	ctrl->nframe = ctrl->motion_table[ctrl->curr_num].start_frame;
	ctrl->flag &= ~0x3F;
}

void MotionCtrl(ADV1_AL_MOTION_CTRL* motiontable)
{
	float fVar1;
	unsigned short wVar2;
	al_motion_table* paVar3;
	paVar3 = &motiontable->motion_table[(short)motiontable->curr_num];
	if ((motiontable->flag & 0x40) != 0) {
		motiontable->flag &= ~0x40;
	}
	if ((motiontable->flag & 8) != 0) {
		motiontable->timer = 0;
	}
	motiontable->timer = motiontable->timer + 1;
	if ((motiontable->flag & 0x10) != 0) {
		motiontable->flag &= ~0x12;
		motiontable->link_num = motiontable->req_num;
		motiontable->lframe = motiontable->motion_table[motiontable->req_num].start_frame;
		//motiontable->curr_num = motiontable->req_num;
		//motiontable->nframe = motiontable->motion_table[(short)motiontable->req_num].start_frame;
		motiontable->flag |= 1;
		//motiontable->flag = motiontable->flag & ~1;
		//motiontable->flag = motiontable->flag & ~2;
	}

	if ((motiontable->flag & 2) != 0) {
		return;
	}
	if ((motiontable->flag & 1) != 0) {

		return;
	}
	//not port, this is hacked in code to prevent a crash, this happens on the climbing bug for example
	float usedSpeed = motiontable->multi_spd;
	if (usedSpeed < 0)
		usedSpeed *= -1;
	motiontable->nframe = paVar3->frame_spd * usedSpeed + motiontable->nframe;
	if (paVar3->frame_spd <= 0.00000000) {
		if (0.00000000 <= paVar3->frame_spd) {
			return;
		}
		fVar1 = paVar3->end_frame;
		if (fVar1 < motiontable->nframe) {
			return;
		}
		//anim ends (currentframe >= endframe)
		wVar2 = paVar3->mode;
		if (wVar2 == 2) {
			motiontable->curr_num = paVar3->next;
			motiontable->flag |= 8;
			motiontable->multi_spd = 1.00000000f;
			motiontable->flag |= 0x40;
			motiontable->multi_spd = 1.00000000f;
			return;
		}
		if ((short)wVar2 < 2) {
			if (wVar2 == 0) {
				motiontable->nframe = motiontable->nframe - (fVar1 - paVar3->start_frame);
				motiontable->flag |= 0x40;
				motiontable->multi_spd = 1.00000000f;
				return;
			}
			//mode == 1
			if ((short)wVar2 < 0) {
				return;
			}
			motiontable->flag |= 1;
			motiontable->flag |= 8;
			motiontable->flag |= 0x40;
			motiontable->multi_spd = 1.00000000;
			motiontable->link_num = paVar3->next;
			motiontable->nframe = paVar3->end_frame;
			motiontable->lframe = motiontable->motion_table[(short)paVar3->next].start_frame;
			return;
		}
		if (3 < (short)wVar2) {
			return;
		}
		//mode == 3
		motiontable->nframe = fVar1;
		motiontable->flag |= 2;
		motiontable->flag |= 0x40;
		motiontable->multi_spd = 1.00000000;
		return;
	}
	fVar1 = paVar3->end_frame;
	if (motiontable->nframe < fVar1) {
		return;
	}
	wVar2 = paVar3->mode;
	if (wVar2 == 2) {
		motiontable->curr_num = paVar3->next;
		motiontable->flag |= 8;
		motiontable->flag |= 0x40;
		motiontable->multi_spd = 1.00000000;
		return;
	}
	if (1 < (short)wVar2) {
		if (3 < (short)wVar2) {
			return;
		}
		motiontable->nframe = fVar1 - 0.01000000;
		motiontable->flag |= 2;
		motiontable->flag |= 0x40;
		motiontable->multi_spd = 1.00000000;
		return;
	}
	if (wVar2 != 0) {
		if ((short)wVar2 < 0) {
			return;
		}
		motiontable->flag |= 1;
		motiontable->link_num = paVar3->next;
		motiontable->nframe = paVar3->end_frame - 0.01000000;
		motiontable->lframe = motiontable->motion_table[(short)paVar3->next].start_frame;
		motiontable->flag |= 0x40;
		motiontable->multi_spd = 1.00000000;
		return;
	}
	motiontable->nframe = motiontable->nframe - (fVar1 - paVar3->start_frame);
	motiontable->flag |= 0x40;
	motiontable->multi_spd = 1.00000000;

	return;
}

void MotionCtrl2(ADV1_AL_MOTION_CTRL* motiontable)
{
	if (motiontable->flag & 1)
	{
		al_motion_table* motion = &motiontable->motion_table[motiontable->link_num];

		motiontable->link_ratio = motiontable->link_ratio + motion->link_spd;
		if (1.00000000 < motiontable->link_ratio) {
			motiontable->link_ratio = 0.00000000;
			motiontable->nframe = motiontable->lframe;
			motiontable->curr_num = motiontable->link_num;
			motiontable->mode = motion->mode;
			motiontable->flag = motiontable->flag & 0xfffe;
			motiontable->flag = motiontable->flag | 8;
			motiontable->multi_spd = 1.00000000;
		}
	}
}

FunctionPointer(void, MotionControl, (MOTION_CTRL* a1), 0x0073F830);
void __cdecl AL_MotionControl(ObjectMaster* a1)
{
	chaowk* v1; // eax
	v1 = (chaowk*)a1->Data1;
	if (v1->ChaoFlag & 4)
	{
		if (CurrentChaoStage == 1)
		{
			MotionCtrl((ADV1_AL_MOTION_CTRL*)&v1->MotionCtrl);
			MotionCtrl2((ADV1_AL_MOTION_CTRL*)&v1->MotionCtrl);
		}
		else
			MotionControl(&v1->MotionCtrl);
	}
}

FunctionPointer(void, MotionInit, (MOTION_CTRL* ctrl, MOTION_TABLE* table), 0x0073F7E0);
void __cdecl AL_MotionInit(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	if (CurrentChaoStage == 1)
		ADV1_AL_MotionInit(wk);
	else
		MotionInit(&wk->MotionCtrl, (MOTION_TABLE*)0x036A94E8);
}

void __cdecl ADV1toADV2_SetMotionLink(int a1, int a2)
{
	int temp = *(int*)((int)a1 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	chaowk* wk = (chaowk*)obj->Data1;
	ADV1_AL_MOTION_CTRL* adv1 = (ADV1_AL_MOTION_CTRL*)&wk->MotionCtrl;
	adv1->flag |= 0x10;
	adv1->req_num = a2;	
	return;
}

DataPointer(NJS_MDATA2*, ChaoMotionData, 0x03CE1358);
DataPointer(float, ChaoCurrentFrame, 0x03CE135C);
DataPointer(int, ChaoFrameCount, 0x03CE1360);
DataPointer(NJS_MDATA2*, ChaoTransitionMotionData, 0x03CE1364);
DataPointer(float, ChaoTransitionStartFrame, 0x03CE1368);
DataPointer(int, ChaoTransitionFrameCount, 0x03CE136C);
DataPointer(float, ChaoLinkFrame, 0x03CE1370);
void __cdecl Chao_SetAnimVars(ObjectMaster* a1)
{
	MOTION_CTRL* v1; // eax
	chaowk* v2; // eax
	NJS_MOTION* v3; // ecx
	NJS_MOTION* v4; // ecx
	if (CurrentChaoStage == 1)
	{
		v2 = (chaowk*)a1->Data1;
		ADV1_AL_MOTION_CTRL* adv1 = (ADV1_AL_MOTION_CTRL*)&v2->MotionCtrl;
		al_motion_table* table = adv1->motion_table;
		ChaoMotionData = (NJS_MDATA2*)table[adv1->curr_num].motion->mdata;
		ChaoFrameCount = table[adv1->curr_num].motion->nbFrame;
		ChaoCurrentFrame = adv1->nframe;
		if (adv1->flag & 1)
		{
			ChaoTransitionMotionData = (NJS_MDATA2*)table[adv1->link_num].motion->mdata;
			ChaoTransitionFrameCount = table[adv1->link_num].motion->nbFrame;
			ChaoTransitionStartFrame = adv1->lframe;
			ChaoLinkFrame = adv1->link_ratio;
		}
		else
		{
			ChaoTransitionMotionData = 0;
		}
	}
	else
	{
		v2 = (chaowk*)a1->Data1;
		v3 = v2->MotionCtrl.minfo[0].pMotion;
		v1 = &v2->MotionCtrl;
		ChaoMotionData = (NJS_MDATA2*)v3->mdata;
		ChaoFrameCount = v3->nbFrame;
		ChaoCurrentFrame = v1->minfo[0].frame;
		if (v1->flag & 2)
		{
			v4 = v1->minfo[1].pMotion;
			ChaoTransitionMotionData = (NJS_MDATA2*)v4->mdata;
			ChaoTransitionFrameCount = v4->nbFrame;
			ChaoTransitionStartFrame = v1->minfo[1].frame;
			ChaoLinkFrame = v1->ratio;
		}
		else
		{
			ChaoTransitionMotionData = 0;
		}
	}
}

void DCChao_Motion_Init()
{
	exportedSA1[0x24].frame_spd *= 0.8f; //drown slow down code thing
	WriteJump((void*)0x0076DAC0, ADV1toADV2_SetMotionLink); //race motion set animation
	WriteJump((void*)0x00734EC0, AL_MotionInit); //race motion init
	WriteJump((void*)0x00734EE0, AL_MotionControl);  //race motion controller
	WriteJump((void*)0x00764B10, Chao_SetAnimVars); //race motion setup
}