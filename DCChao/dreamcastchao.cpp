#include "pch.h"
#include "SADXModLoader.h"
#include "al_shape_basic.h"
#include <string>
#include <ModelInfo.h>
#include "chao.h"
#include "data/al_motion/alm_rappa_dc.h"
#include "data/al_motion//al_dc_motion.h"
#include "al_race.h"
const int CalcPosPtr = 0x00765110;
void AL_CalcShadowPos(ObjectMaster* a1)
{
	__asm
	{
		mov eax, a1
		call CalcPosPtr
	}
}

DataPointer(unsigned short, word_3CE2BF8, 0x3CE2BF8);
void CalculatePositions(ObjectMaster* a1, al_object* a2)
{
	chaowk* v1; // esi
	Angle v2; // eax
	al_object* ptr = a2;
	v1 = (chaowk*)a1->Data1;
	while (1)
	{
		njPushMatrixEx();
		AL_CalcMotionMartix(ptr);
		AL_CalcShadowPos(a1);
		word_3CE2BF8++;
		if (ptr->pChild)
			CalculatePositions(a1, ptr->pChild);
		njPopMatrixEx();
		if (!ptr->pSibling)
			break;
		ptr = ptr->pSibling;
	}
}

void __cdecl Chao_SetAnimVars(ObjectMaster* a1);

void __cdecl sub_7659A0(ObjectMaster* a1)
{
	chaowk* v1; // esi
	Angle v2; // eax

	v1 = (chaowk*)a1->Data1;
	word_3CE2BF8 = 0;
	Chao_SetAnimVars(a1);
	njPushMatrixEx();
	njUnitMatrix(0);
	njTranslateV(0, &v1->entity.Position);
	v2 = v1->entity.Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}
	CalculatePositions(a1, v1->Shape.pObject);
	njPopMatrixEx();

}

void __cdecl Chao_UpdateModel(ObjectMaster* a1)
{
	chaowk* v1; // esi
	char v2; // al
	AL_SHAPE* v3; // esi
	int v4; // et1
	double v6; // st7
	unsigned __int8 v7; // c2
	unsigned __int8 v8; // c3
	double v9; // st7
	double v10; // st7
	int v11; // et1
	double v13; // st7
	unsigned __int8 v14; // c2
	unsigned __int8 v15; // c3
	double v16; // st7
	double v17; // st7

	v1 = (chaowk*)a1->Data1;
	v3 = &v1->Shape;
	//if (v1->ModelData.modelFlags & 2)
	{
		sub_767790(a1);
	}
	//old shadow code from sa2dc?
	//if (ALOField_Find(a1, 1, 150))
	{
		//v3->Flag |= 8u;
	}
	//else
	{
		//v3->Flag &= ~8u;
	}
	if (v3->pLeftHandItemObject)
	{
		v4 = v3->LeftHandItemActiveFlag;
		v6 = v3->LeftHandItemScale;
		if (!v4)
		{
			v10 = v6 - 0.1;
			v3->LeftHandItemScale = v10;
			if (v10 < 0.0)
			{
				v3->LeftHandItemScale = 0.0;
				v3->pLeftHandItemObject = 0;
			}
		}
		else
		{
			v9 = v6 + 0.1;
			v3->LeftHandItemScale = v9;
			if (v9 > 1.0)
			{
				v3->LeftHandItemScale = 1.0;
			}
		}
	}
	if (v3->pRightHandItemObject)
	{
		v4 = v3->RightHandItemActiveFlag;
		v6 = v3->RightHandItemScale;
		if (!v4)
		{
			v10 = v6 - 0.1;
			v3->RightHandItemScale = v10;
			if (v10 < 0.0)
			{
				v3->RightHandItemScale = 0.0;
				v3->pRightHandItemObject = 0;
			}
		}
		else
		{
			v9 = v6 + 0.1;
			v3->RightHandItemScale = v9;
			if (v9 > 1.0)
			{
				v3->RightHandItemScale = 1.0;
			}
		}
	}


	sub_7659A0(a1);
}

FunctionPointer(int, sub_737080, (ObjectMaster* a1), 0x737080);
FunctionPointer(int, ReturnBlinkValue, (ObjectMaster* a1), 0x00737060);
FunctionPointer(void, sub_765010, (NJS_OBJECT* a1), 0x765010);
DataPointer(char, ChaoNodeIndex, 0x03CE04E4);
DataPointer(NJS_MDATA2*, ChaoMotionData, 0x03CE1358);
DataPointer(float, ChaoCurrentFrame, 0x03CE135C);
DataPointer(int, ChaoFrameCount, 0x03CE1360);
DataPointer(NJS_MDATA2*, ChaoTransitionMotionData, 0x03CE1364);
DataPointer(float, ChaoTransitionStartFrame, 0x03CE1368);
DataPointer(int, ChaoTransitionFrameCount, 0x03CE136C);
DataPointer(float, ChaoLinkFrame, 0x03CE1370);

DataArray(NJS_BGRA, ChaoColors, 0x0389D828, 13);
void DrawChaoDC(ObjectMaster* a1, al_object* a2)
{
	chaowk* data1 = (chaowk*)a1->Data1;
	//lazy to write a new hook so im doing this

	njPushMatrixEx();
	if (ChaoNodeIndex == 0)
	{
		data1->Zone.Ratio = data1->Zone.Ratio + (-data1->Zone.Ratio * 0.15f - (a1->Data1->Scale.z - 1.00000000) * 0.28000000);
		a1->Data1->Scale.z += data1->Zone.Ratio;
		a1->Data1->Scale.y = 2 - a1->Data1->Scale.z;
		njScale(0, a1->Data1->Scale.y, a1->Data1->Scale.z, a1->Data1->Scale.y);
	}
	while (1)
	{
		njPushMatrixEx();
		AL_CalcMotionMartix(a2);



		int eyelidRotX = ((chaowk*)a1->Data1)->Face.EyeLidExpressionCurrCloseAng + ((chaowk*)a1->Data1)->Face.EyeLidBlinkAng - 0x4000;// ;
		int slope = ((chaowk*)a1->Data1)->Face.EyeLidExpressionCurrSlopeAng;
		if (a2->pItemObject)
		{
			njSetTexture(a2->pItemTexlist);
			//SetChunkMaterialFlags(SecondTextureEnvironmentMap);
			njPushMatrixEx();
			if (a2->ItemOffsetFlag)
			{
				njTranslateEx(&a2->ItemOffsetPos);
				njRotateXYZ(0, a2->ItemOffsetAng.x, a2->ItemOffsetAng.y, a2->ItemOffsetAng.z);
			}
			njScale(0, a2->ItemScale, a2->ItemScale, a2->ItemScale);
			njCnkDrawObject((NJS_CNK_OBJECT*)a2->pItemObject);
			njPopMatrixEx();
			//SetChunkMaterialFlags(0);
		}

		if (CurrentChaoStage != 1) {
			if (ChaoNodeIndex == 19)              // left eyelid
			{

				if (eyelidRotX)
				{
					njRotateX(0, eyelidRotX);
				}
				if (slope)
				{
					njRotateZ(0, slope);
				}
			}
			if (ChaoNodeIndex == 22)              // right eyelid
			{
				if (eyelidRotX)
				{
					njRotateX(0, eyelidRotX);
				}
				if (slope)
				{
					njRotateZ(0, -slope);
				}
			}
		}
		njSetTexture(&CHAO_TEXLIST);

		if (ChaoNodeIndex != 18 && ChaoNodeIndex != 21 && ChaoNodeIndex != 28)
			if (a2->pModel)
			{
				for (int i = 0; i < ((NJS_MODEL_SADX*)a2->pModel)->nbMat; i++)
				{
					if (data1->pParamGC->Color)
					{
						((NJS_MODEL_SADX*)a2->pModel)->mats[i].diffuse.argb = ChaoColors[data1->pParamGC->Color - 1];
					}
					if (!data1->pParamGC->Texture)
					{
						if (data1->pParamGC->MonotoneHighlights)
							((NJS_MODEL_SADX*)a2->pModel)->mats[i].attrflags &= ~NJD_FLAG_USE_TEXTURE;
						else ((NJS_MODEL_SADX*)a2->pModel)->mats[i].attrflags |= NJD_FLAG_USE_TEXTURE;
					}
					else
					{
						njSetTexture(&ChaoTexLists[0]);
						((NJS_MODEL_SADX*)a2->pModel)->mats[i].attrflags |= NJD_FLAG_USE_TEXTURE;
						((NJS_MODEL_SADX*)a2->pModel)->mats[i].attrflags |= NJD_FLAG_USE_ENV;
						((NJS_MODEL_SADX*)a2->pModel)->mats[i].attr_texId = data1->pParamGC->Texture + 17;
						((NJS_MODEL_SADX*)a2->pModel)->mats[i].diffuse.color = 0xFFFFFFFF;
					}
				}
			}

		//if (ChaoNodeIndex == 18 || ChaoNodeIndex == 21) njSetTexture(&ChaoTexLists[2]);
		//if(CurrentChaoStage != 1)
		/*
		if (ChaoNodeIndex == 28) {
			NJS_MODEL_SADX* sadx = (NJS_MODEL_SADX*)a2->pModel;
			if (sadx->mats[0].attr_texId < 100)
				njSetTexture(&ChaoTexLists[5]);
			else njSetTexture(&CHAO_TEXLIST);
		}
		*/
		if (ChaoNodeIndex == 18)
		{
			njTranslate(0, ((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosY, 0.0);
			//njScale(0, ((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosX);
		}
		else if (ChaoNodeIndex == 21)
		{
			//njScale(0, ((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosX);
			njTranslate(0, -((chaowk*)a1->Data1)->Face.EyePosX, ((chaowk*)a1->Data1)->Face.EyePosY, 0.0);
		}

		FunctionPointer(void, njSetZCompare, (int a1), 0x0077ED00);
		VoidFunc(npSetZCompare, 0x00401420);
		if (ChaoNodeIndex == 19 || ChaoNodeIndex == 22)
		{

			if (CurrentChaoStage == 1 || eyelidRotX != -0x4000)
			{
				njSetZCompare(3u);
				//DrawCnkModel((NJS_CNK_MODEL*)mdl1same2);
				sub_408530((NJS_OBJECT*)a2);
				npSetZCompare();
			}
		}
		else
		{
			if (data1->pParamGC->Type < ChaoType_Neutral_Chaos && data1->pParamGC->Type > ChaoType_Dark_Chaos && a2->pPartsObject) {
				njSetTexture((NJS_TEXLIST*)0x033A1340);
				DrawCnkModel((NJS_CNK_MODEL*)a2->pPartsObject->model);
			}
			else
				if ((NJS_MODEL_SADX*)a2->pModel)
					njDrawModel_SADX_Dynamic((NJS_MODEL_SADX*)a2->pModel);
		}


		ChaoNodeIndex++;
		if (a2->pChild)
			DrawChaoDC(a1, a2->pChild);
		njPopMatrixEx();
		if (!a2->pSibling)
			break;
		a2 = a2->pSibling;
	}
	njPopMatrixEx();

}

void __cdecl Chao_SetAnimVars(ObjectMaster* a1)
{
	MOTION_CTRL* v1; // eax
	chaowk* v2; // eax
	NJS_MOTION* v3; // ecx
	NJS_MOTION* v4; // ecx
	if (CurrentChaoStage == 1)
	{
		v2 = (chaowk*)a1->Data1;
		ADV1_AL_MOTION_CTRL* adv1 = (ADV1_AL_MOTION_CTRL*)& v2->MotionCtrl;
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
ObjectFunc(sub_737030, 0x737030);
void Chao_Display_(ObjectMaster* a1)
{
	Chao_SetAnimVars(a1);
	njPushMatrixEx();
	njTranslateEx(&a1->Data1->Position);
	njRotateY(0, a1->Data1->Rotation.y);
	njSetTexture(&ChaoTexLists[0]);
	//SetChaoTexturePalette(a1, 0); //modified because headers
	ChaoNodeIndex = 0;
	DrawChaoDC(a1, ((chaowk*)a1->Data1)->Shape.pObject);//a1->Data1.Chao->ModelData.PointerToStructWithCnkObject);
	//njCnkDrawObject(&a1->Data1.Chao->ModelData.PointerToStructWithCnkObject->base);
	njPopMatrixEx();
	njPushMatrixEx();
	njTranslate(0, 0, 2, 0);
	sub_737030(a1);
	njPopMatrixEx();
}


NJS_OBJECT* LoadChaoModel(const char* path, const char* name)
{
	std::string str = std::string(path);
	str += "\\DCChao\\";
	str += name;
	ModelInfo* modelInfo = new ModelInfo(str);
	return modelInfo->getmodel();
}

NJS_OBJECT* LoadEvoChaoModel(const char* path, const char* evo, const char* subevo)
{
	std::string str = std::string(path);
	str += "\\DCChao\\";
	str += evo;
	str += "_";
	str += subevo;
	str += ".sa1mdl";
	ModelInfo* modelInfo = new ModelInfo(str);
	return modelInfo->getmodel();
}

DataArray(NJS_OBJECT*, Al_RootObject, 0x034BD4A8, 100);

void SetTexID(NJS_OBJECT* a1, int a2)
{
	int eye = a2;

	//correct sa2 eye texID to sa1
	switch (eye)
	{
	case 2:
		eye = 4;
		break;
	case 3:
		eye = 5;
		break;
	case 4:
		eye = 2;
		break;
	case 5:
		eye = 6;
		break;
	case 6:
		eye = 3;
		break;
	case 7:
		eye = 4;
		break;
	case 10:
		eye = 7;
		break;
	default:
		eye = 0;
		break;
	}

	if (a1)
		a1->basicdxmodel->mats[0].attr_texId = 164 + eye;
}
DataArray(uint16_t, word_88733C, 0x88733C, 26);
DataArray(uint16_t, word_887320, 0x887320, 26);
DataArray(uint16_t, word_887370, 0x887370, 26);
FunctionPointer(void, AL_MatChangeObjectTexture, (al_object* pObject, __int16 TexId), 0x0075B360);
void __cdecl AL_FaceSetEye_(ObjectMaster* tp, int EyeNum, int timer)
{
	AL_FACE_CTRL* v3; // esi
	int v4; // eax
	ObjectMaster* v5; // edx
	int v6; // eax
	int v7; // eax
	ObjectMaster* v8; // edx
	int v9; // edi
	unsigned __int8 v10; // al

	chaowk* wk = (chaowk*)tp->Data1;
	v3 = (AL_FACE_CTRL*)& wk->Face;
	v3->EyeCurrNum = EyeNum;
	v3->EyeTimer = timer;
	v4 = v3->EyeCurrNum;//AL_FaceReturnDefaultEye(tp);
	if (!v4)
	{
		if (v3->EyeDefaultNum == 10)
		{
			v3->EyeLidExpressionAimCloseAng = 13653;
			v3->EyeLidExpressionAimSlopeAng = 3640;
			goto LABEL_10;
		}
		goto LABEL_8;
	}
	v6 = v4 - 9;
	if (!v6)
	{
		v3->EyeLidExpressionAimCloseAng = 16384;
	LABEL_9:
		v3->EyeLidExpressionAimSlopeAng = 0;
		goto LABEL_10;
	}
	if (v6 != 1)
	{
	LABEL_8:
		v3->EyeLidExpressionAimCloseAng = 0;
		goto LABEL_9;
	}
	v3->EyeLidExpressionAimCloseAng = 13653;
	v3->EyeLidExpressionAimSlopeAng = 3640;
LABEL_10:
	v7 = v3->EyeCurrNum;
	if (v7 && v7 != ChaoEyes_Mean)
	{
		v9 = word_887320[EyeNum];
	}
	else
	{
		v9 = word_887370[v3->EyeColorNum];
	}
	v10 = wk->pParamGC->Type;
	if (v10 >= ChaoType_Neutral_Chaos && v10 <= ChaoType_Dark_Chaos)
	{
		if (v3->EyeCurrNum == 7)
		{
			v9 = (unsigned __int16)word_887320[EyeNum];
		}
		else
		{
			v9 = word_887370[v3->EyeColorNum];
		}
	}
	AL_MatChangeObjectTexture(v3->pEyeObject[0], v9);
	AL_MatChangeObjectTexture(v3->pEyeObject[1], v9);
}
void __cdecl Chao_SetMouth_(ObjectMaster* a1, ChaoMouth a2, int timer)
{
	chaowk* data1 = (chaowk*)a1->Data1;
	data1->Face.MouthTimer = timer;

	uint16_t* a2a;
	if ((unsigned __int8)data1->pParamGC->Type < ChaoType_Neutral_Chaos || (unsigned __int8)data1->pParamGC->Type > ChaoType_Dark_Chaos)
		a2a = &word_88733C[2 * a2];
	else
		a2a = word_88733C;
	int copy[2];
	copy[0] = a2a[0];
	copy[1] = a2a[1];
	for (int i = 0; i < 2; i++)
		switch (copy[i])
		{
		case 1:
			copy[i] = 176;
			break;
		case 2:
			copy[i] = 177;
			break;
		case 3:
			copy[i] = 179;
			break;
		case 4:
			copy[i] = 175;
			break;
		case 5:
			copy[i] = 178;
			break;
		case 6:
			copy[i] = 175;
			break;
		case 7:
			copy[i] = 182;
			break;
		case 10:
			copy[i] = 180;
			break;
		case 11:
			copy[i] = 181;
			break;
		default:
			copy[i] = 174;
			break;
		}
	if (data1->Shape.CurrObjectList[28])
	{
		((NJS_MODEL_SADX*)data1->Shape.CurrObjectList[28]->pModel)->mats[0].attr_texId = copy[1];
		((NJS_MODEL_SADX*)data1->Shape.CurrObjectList[28]->pModel)->mats[1].attr_texId = copy[0];
	}
}

void LoadEvoChao(const char* path, const char* evo, int index)
{
	Al_RootObject[index] = LoadEvoChaoModel(path, evo, "Base");
	Al_RootObject[index + 1] = LoadEvoChaoModel(path, evo, "Normal");
	Al_RootObject[index + 2] = LoadEvoChaoModel(path, evo, "Swim");
	Al_RootObject[index + 3] = LoadEvoChaoModel(path, evo, "Fly");
	Al_RootObject[index + 4] = LoadEvoChaoModel(path, evo, "Run");
	Al_RootObject[index + 5] = LoadEvoChaoModel(path, evo, "Power");

	//for (int i = 0; i < 7; i++) //override hero slots
	//	Al_RootObject[index + 6 + i] = Al_RootObject[i];

	//for (int i = 0; i < 7; i++) //override dark slots
	//	Al_RootObject[index + 12 + i] = Al_RootObject[i];
}

void LoadTempHeroEvo(const char* path, const char* name, int index)
{

	Al_RootObject[index] = LoadChaoModel(path, name);
	Al_RootObject[index + 1] = Al_RootObject[index];
	Al_RootObject[index + 2] = Al_RootObject[index];
	Al_RootObject[index + 3] = Al_RootObject[index];
	Al_RootObject[index + 4] = Al_RootObject[index];
	Al_RootObject[index + 5] = Al_RootObject[index];
}

void LoadChaosEvo(const char* path, const char* name, int index)
{
	Al_RootObject[index] = LoadChaoModel(path, name);
	Al_RootObject[index + 1] = Al_RootObject[index];
	Al_RootObject[index + 2] = Al_RootObject[index];
	Al_RootObject[index + 3] = Al_RootObject[index];
	Al_RootObject[index + 4] = Al_RootObject[index];
	Al_RootObject[index + 5] = Al_RootObject[index];

	//for (int i = 0; i < 7; i++) //override hero slots
	//	Al_RootObject[index + 6 + i] = Al_RootObject[i];

	//for (int i = 0; i < 7; i++) //override dark slots
	//	Al_RootObject[index + 12 + i] = Al_RootObject[i];
}

void LoadChildChao(const char* path)
{
	Al_RootObject[0] = LoadChaoModel(path, "Base.sa1mdl");
	Al_RootObject[1] = LoadChaoModel(path, "Normal.sa1mdl");
	Al_RootObject[2] = LoadChaoModel(path, "Swim.sa1mdl");
	Al_RootObject[3] = LoadChaoModel(path, "Fly.sa1mdl");
	Al_RootObject[4] = LoadChaoModel(path, "Run.sa1mdl");
	Al_RootObject[5] = LoadChaoModel(path, "Power.sa1mdl");

	//for (int i = 0; i < 7; i++)
	//	Al_RootObject[6 + i] = Al_RootObject[i];

//	for (int i = 0; i < 7; i++)
	//	Al_RootObject[12 + i] = Al_RootObject[i];
}

void __cdecl FreeSomeChaoData_(ObjectMaster* a1)
{
	chaowk* v1; // esi
	AL_GROUP_OBJECT_LIST* v2; // eax
	AL_SHAPE* v3; // esi

	v1 = (chaowk*)a1->Data1;
	v2 = v1->Shape.pObjectList;
	v3 = &v1->Shape;
	if (v2)
	{
		_HeapFree(v2);
	}
	if (v3->pObjectListH)
	{
		_HeapFree(v3->pObjectListH);
	}
	if (v3->pObjectListD)
	{
		_HeapFree(v3->pObjectListD);
	}
	_HeapFree(v1->Shape.palette);
	DeleteChunkObjectPointer((BasicObjectPointer*)v3->pObject);
}
FunctionPointer(void, AL_FaceReturnDefaultEye, (ObjectMaster* tp), 0x007373F0);
FunctionPointer(void, AL_FaceReturnDefaultMouth, (ObjectMaster* tp), 0x00737410);
FunctionPointer(void, AL_SetMotionLink, (ObjectMaster* tp, int MtnNum), 0x00734F00);
void __cdecl ADV1toADV2_SetMotionLink(int a1, int a2)
{
	int temp = *(int*)((int)a1 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	chaowk* wk = (chaowk*)obj->Data1;
	ADV1_AL_MOTION_CTRL* adv1 = (ADV1_AL_MOTION_CTRL*)& wk->MotionCtrl;
	adv1->flag |= 0x10;
	adv1->req_num = a2;
	//adv1->mode = adv1->motion_table[adv1->req_num].mode;
	return;
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


			MotionCtrl((ADV1_AL_MOTION_CTRL*)& v1->MotionCtrl);
			MotionCtrl2((ADV1_AL_MOTION_CTRL*)& v1->MotionCtrl);


		}
		else
		{
			MotionControl(&v1->MotionCtrl);
		}
	}
}
FunctionPointer(void, MotionInit, (MOTION_CTRL* ctrl, MOTION_TABLE* table), 0x0073F7E0);
void __cdecl AL_MotionInit(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	if (CurrentChaoStage == 1)
	{
		//MotionInit(&wk->MotionCtrl, (MOTION_TABLE*)exportedSA1);
		ADV1_AL_MOTION_CTRL* ctrl = (ADV1_AL_MOTION_CTRL*)& wk->MotionCtrl;
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
	else
		MotionInit(&wk->MotionCtrl, (MOTION_TABLE*)0x036A94E8);
}
FunctionPointer(void, sub_757100, (EntityData1* a1, int a2), 0x757100);
void __cdecl sub_757100_Hook(EntityData1* a1, int a2)
{
	Alr* race = (Alr*)a1->LoopData;
	int temp = *(int*)((int)a2 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	chaowk* wk = (chaowk*)obj->Data1;

	ADV1_AL_MOTION_CTRL* ctrl = (ADV1_AL_MOTION_CTRL*)& wk->MotionCtrl;
	*(float*)(a2 + 0x134) = ((ADV1_AL_MOTION_CTRL*)& wk->MotionCtrl)->multi_spd;

	sub_757100(a1, a2);

	((ADV1_AL_MOTION_CTRL*)& wk->MotionCtrl)->multi_spd = *(float*)(a2 + 0x134);
}
static void __declspec(naked) ALR_DashHook()
{
	__asm
	{
		push esi // a2
		push edi // a1

		// Call your __cdecl function here:
		call ALR_Dash

		pop edi // a1
		pop esi // a2
		retn
	}
}
struct AlrRootAnswer
{
	void* tag;
	float minpath_pathpos;
	float main_pathpos;
};
FunctionPointer(signed int, GetStatusOnPath, (int a1, int a2), 0x0049C330);
FunctionPointer(float, sub_49C670, (int a1, NJS_VECTOR* a2, int a3, float* a4), 0x49C670);
DataArray(int*, off_3673640, 0x3673640, 3);
DataArray(char, usepath, 0x08890BC, 5);
void __cdecl AlrRoot_GetAnswer(EntityData1* a1, int a2, AlrRootAnswer* a3, int use_shortcut)
{
	EntityData1* v4; // edi
	int v5; // ebx
	int v6; // ST00_4
	Angle i; // ebx
	int v8; // eax
	int v9; // esi
	Loop* v10; // eax
	double v11; // st7
	double v12; // st6
	double v13; // st5
	float v14; // ST0C_4
	double v15; // st7
	float a4a; // [esp+14h] [ebp-Ch]
	int v17; // [esp+18h] [ebp-8h]
	int v18; // [esp+1Ch] [ebp-4h]
	float a1a; // [esp+24h] [ebp+4h]

	v4 = a1;
	v5 = (int)a1->LoopData;
	v6 = *(_DWORD*)(v5 + 4 * a1->Rotation.x);
	v18 = (int)a1->LoopData;
	a1a = sub_49C670(v6, (NJS_VECTOR*)a2, 0, &a3->main_pathpos);
	a3->minpath_pathpos = a3->main_pathpos;
	a3->tag = *(void**)(v5 + 4 * v4->Rotation.x);
	if (v4->Object)
	{
		v17 = *(unsigned char*)0x3CD370A;
		for (i = 0; i < v4->Rotation.x; ++i)
		{
			v8 = (unsigned __int8)usepath[v17];
			if (use_shortcut != 1)
			{
				v8 &= ~1u;
			}
			if ((1 << i) & v8)
			{
				v9 = *(_DWORD*)(v18 + 4 * i);
				a4a = 0.0f;
				if (*(float*)((int)v4->Object + 8 * i) < (double)a3->main_pathpos)
				{
					v15 = sub_49C670(v9, (NJS_VECTOR*)a2, 0, &a4a);
				}
				else
				{
					v10 = *(Loop * *)(v9 + 8);
					v11 = *(float*)a2 - v10->Position.x;
					v12 = *(float*)(a2 + 4) - v10->Position.y;
					v13 = *(float*)(a2 + 8) - v10->Position.z;
					v14 = v13 * v13 + v12 * v12 + v11 * v11;
					v15 = squareroot(v14);
				}
				if (*(float*)(v9 + 4) - 10.0 < a4a)
				{
					return;
				}
				if (v15 <= a1a)
				{
					a1a = v15;
					a3->minpath_pathpos = a4a;
					a3->tag = (void*)v9;
				}
			}
		}
	}
}

unsigned __int8 eye_tex_num[8] =
{ 164u, 165u, 166u, 167u, 168u, 169u, 170u, 171u };
FunctionPointer(void, AL_FaceSetEye, (ObjectMaster* tp, int EyeNum, int timer), 0x007370A0);
void __cdecl ADV1_AL_SetEyeNum(alifewk* a1, int a2, int a3)
{
	int temp = *(int*)((int)a1 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	//AL_FaceSetEye(obj, a2, a3);
	chaowk* wk = (chaowk*)obj->Data1;
	wk->Face.EyeCurrNum = a2;
	wk->Face.EyeTimer = a3;
	if (a3 == 2)
		wk->Face.EyeTimer = -1;
	if (wk->Shape.CurrObjectList[18])
		((NJS_OBJECT*)wk->Shape.CurrObjectList[18])->basicdxmodel->mats[0].attr_texId = eye_tex_num[a2];
	if (wk->Shape.CurrObjectList[21])
		((NJS_OBJECT*)wk->Shape.CurrObjectList[21])->basicdxmodel->mats[0].attr_texId = eye_tex_num[a2];
}
DataArray(char, byte_37C2160, 0x37C2160, 12);
void __cdecl sub_76DF50(alifewk* a1, int a2, int a3)
{
	int temp = *(int*)((int)a1 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	chaowk* wk = (chaowk*)obj->Data1;

	wk->Face.MouthCurrNum = a2;
	if (wk->Face.pMouthObject)
	{
		NJS_OBJECT* model = (NJS_OBJECT*)wk->Face.pMouthObject->pChild;
		(model->basicdxmodel)->mats[0].attr_texId = (unsigned __int8)byte_37C2160[2 * a2];
		(model->basicdxmodel)->mats[1].attr_texId = (unsigned __int8)byte_37C2160[2 * a2 + 1];
	}
	wk->Face.MouthTimer = a3;
	if (a3 == 2)
		wk->Face.MouthTimer = -1;
}
void __cdecl sub_76DFE0(alifewk* a1, int a2, int a3, int a4)
{
	int temp = *(int*)((int)a1 + 0x8D0);
	ObjectMaster* obj = (ObjectMaster*)temp;
	chaowk* wk = (chaowk*)obj->Data1;
	ADV1_AL_FACE_HACK* face = (ADV1_AL_FACE_HACK*)& wk->Face;
	face->eyelid_request_close_ang = a2 + 0x4000;
	face->eyelid_request_express_ang = a3;
	face->eyelid_keep_timer = a4;
}
FunctionPointer(void, AL_FaceEyeLidControl, (ObjectMaster* a1), 0x00737210);
FunctionPointer(int, AdjustAngle, (__int16 bams_a, unsigned __int16 bams_b, int dang), 0x0438350);
void __cdecl AL_FaceEyeLidControl_(ObjectMaster* a1)
{
	chaowk* wk = (chaowk*)a1->Data1;
	if (CurrentChaoStage == 1)
	{
		ADV1_AL_FACE_HACK* face = (ADV1_AL_FACE_HACK*)& wk->Face;
		//EyelidExpression part
		if (face->eyelid_keep_timer < 0)
		{
			AL_FaceEyeLidControl(a1);
		}
		else
		{
			face->eyelid_keep_timer--;
			face->EyeLidExpressionCurrSlopeAng = AdjustAngle(face->EyeLidExpressionCurrSlopeAng, face->eyelid_request_express_ang, 0x40);
			face->EyeLidExpressionCurrCloseAng = AdjustAngle(face->eyelid_request_close_ang, face->EyeLidExpressionCurrCloseAng, 0x100);
		}
		((NJS_OBJECT*)wk->Shape.CurrObjectList[19])->ang[0] = face->EyeLidExpressionCurrCloseAng - 0x4000;
		((NJS_OBJECT*)wk->Shape.CurrObjectList[19])->ang[1] = face->EyeLidExpressionCurrSlopeAng;
		((NJS_OBJECT*)wk->Shape.CurrObjectList[22])->ang[0] = face->EyeLidExpressionCurrCloseAng - 0x4000;
		((NJS_OBJECT*)wk->Shape.CurrObjectList[22])->ang[1] = -face->EyeLidExpressionCurrSlopeAng;
	}
	else
		AL_FaceEyeLidControl(a1);
}

void DreamcastChao_Init(const char* path)
{
	//threshold increase for magnitude and hpos/vpos sliders
	WriteData((float*)0x34BBA00, 1.5f);
	WriteData((float*)0x34BBA04, 1.5f);

	//model loading
	for (int i = 0; i < 100; i++) Al_RootObject[i] = nullptr;
	LoadChildChao(path);
	LoadEvoChao(path, "Normal", 18);
	LoadEvoChao(path, "Swim", 6 * (ChaoType_Neutral_Swim - 2));
	LoadEvoChao(path, "Fly", 6 * (ChaoType_Neutral_Fly - 2));
	LoadEvoChao(path, "Run", 6 * (ChaoType_Neutral_Run - 2));
	LoadEvoChao(path, "Power", 6 * (ChaoType_Neutral_Power - 2));
	LoadChaosEvo(path, "Light Chao.sa1mdl", 6 * (ChaoType_Neutral_Chaos - 2));

	//motion
	exportedSA1[0x24].frame_spd *= 0.8f; //drown slow down code thing
	WriteJump((void*)0x0076DAC0, ADV1toADV2_SetMotionLink); //race motion set animation
	WriteJump((void*)0x00734EC0, AL_MotionInit); //race motion init
	WriteJump((void*)0x00734EE0, AL_MotionControl);  //race motion controller
	WriteJump((void*)0x00764B10, Chao_SetAnimVars); //race motion setup
	WriteCall((void*)0x007574D2, sub_757100_Hook); //before-after race action controller 

	WriteJump((void*)0x00751F30, AlrRoot_GetAnswer);

	//face
	//WriteJump((void*)AL_FaceSetEye, AL_FaceSetEye_);
	WriteJump((void*)0x076DF10, ADV1_AL_SetEyeNum);
	//WriteJump((void*)0x76DF50, sub_76DF50);
	WriteData<2>((char*)0x737440, (char)0); //set eyesclX and eyesclY to 0 instead of 1.0f, since its unused anyways and i use it for the race eye timer
	WriteJump((void*)0x0075B360, SetTexID); //eye
	WriteJump((void*)0x00737190, Chao_SetMouth_); //mouth
	WriteJump((void*)0x76DFE0, sub_76DFE0); //race eyelid
	WriteCall((void*)0x00737660, AL_FaceEyeLidControl_); //race eyelid controller

	//race fixes
	WriteJump((void*)0x0754E20, ALR_DashHook); //fixes running speed

	//LoadTempHeroEvo(path, "60.sa1mdl", 6 * (ChaoType_Neutral_Normal - 2));

	//model rendering
	WriteJump((void*)0x00741F20, Chao_UpdateModel);
	WriteJump((void*)0x00741C80, Chao_LoadModels);
	WriteJump((void*)0x0074136A, DeleteChunkObjectPointer);
	WriteJump((void*)0x0075AF20, Chao_SetVertexColor);
	WriteJump((void*)0x0073E730, DrawChaoDC);
	WriteJump((void*)FreeSomeChaoData, FreeSomeChaoData_);

}