#include "pch.h"
#include "SADXModLoader.h"
#include <memory>
#include "al_shape_basic.h"
#include "chao.h"
#include "al_race.h"
//#include "al_shape.h"
//#include "MemAccess.h"
//#include "Chao.h"
//#include "al_animation.h"


Uint16 Chao_ColorSetNodes[] =
{
  0x01, 0x03, 0x06, 0x08, 0x0A,
  0x0D, 0x10, 0x13, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1E, 0x1F,
  0xFFFF
};

NJS_BGRA Chao_DreamcastSA2Colors[7] =
{
  { 255u, 255u, 255u, 255u },
  { 63u, 63u, 63u, 255u },
  { 127u, 127u, 127u, 255u },
  { 255u, 255u, 255u, 255u },
  { 255u, 127u, 127u, 255u },
  { 127u, 255u, 127u, 255u },
  { 127u, 127u, 255u, 255u }
};

void __cdecl DeleteChunkObjectPointer(BasicObjectPointer* a1)
{
	BasicObjectPointerModel* v1; // esi

	if (a1)
	{
		if (a1->base.child)
		{
			DeleteChunkObjectPointer((BasicObjectPointer*)a1->base.child);
			a1->base.child = 0;
		}
		if (a1->base.sibling)
		{
			DeleteChunkObjectPointer((BasicObjectPointer*)a1->base.sibling);
			a1->base.sibling = 0;
		}
		v1 = (BasicObjectPointerModel*)a1->base.model;
		if (v1)
		{
			if (v1->model.points)
			{
				_HeapFree(v1->model.points);
				v1->model.points = 0;
			}
			if (v1->model.normals)
			{
				_HeapFree(v1->model.normals);
				v1->model.normals = 0;
			}
			if (v1->model.mats)
			{
				_HeapFree(v1->model.mats);
				v1->model.mats = 0;
			}
			_HeapFree(v1);
		}
		if (a1->Matrix)
		{
			_HeapFree(a1->Matrix);
		}
		_HeapFree(a1);
	}
}

void __cdecl Chao_SetVertexColor(BasicObjectPointer* a1, NJS_BGRA a2)
{
	NJS_MODEL_SADX* v2; // eax

	if (a1)
	{
		v2 = a1->base.basicdxmodel;
		if (v2)
		{
			for (int i = 0; i < v2->nbMat; i++)
				v2->mats[i].diffuse.argb = a2;
		}
	}
}
int al_shape_counter = 0;
int __cdecl GetList(NJS_OBJECT* a1, NJS_OBJECT** a2, int a3)
{
	NJS_OBJECT* v3; // ecx
	int result; // eax
	NJS_OBJECT* v5; // esi

	a2[a3] = a1;
	v3 = a1->child;
	result = a3 + 1;
	if (v3)
	{
		result = GetList(v3, a2, result);
	}
	v5 = a1->sibling;
	if (v5)
	{
		result = GetList(v5, a2, result);
	}
	return result;
}
void AL_GetObjectList(NJS_OBJECT* a1, NJS_OBJECT** a2)
{
	NJS_OBJECT* v2; // ecx
	signed int v3; // eax
	NJS_OBJECT* v4; // edx

	*a2 = a1;
	v2 = a1->child;
	v3 = 1;
	if (v2)
	{
		v3 = GetList(v2, a2, 1);
	}
	v4 = a1->sibling;
	if (v4)
	{
		GetList(v4, a2, v3);
	}
}

int dword_3CE04FC = 0;

BasicObjectPointer* __cdecl al_shape_load(NJS_OBJECT* a1, NJS_OBJECT* a2, BasicObjectPointer* a3)
{
	BasicObjectPointer* chunkObject = (BasicObjectPointer*)_HeapAlloc(1, sizeof(BasicObjectPointer));
	memcpy(&chunkObject->base, a1, 0x34);
	chunkObject->Matrix = (NJS_MATRIX_PTR)_HeapAlloc(1, sizeof(NJS_MATRIX));
	chunkObject->originalPosition.x = a1->pos[0];
	chunkObject->originalPosition.y = a1->pos[1];
	chunkObject->originalPosition.z = a1->pos[2];
	NJS_VECTOR* diffTest = (NJS_VECTOR*)((int)chunkObject + 0x38);
//	*diffTest = { 0,0,0 };
	diffTest->x = a1->pos[0] - a2->pos[0];
	diffTest->y = a1->pos[1] - a2->pos[1];
	diffTest->z = a1->pos[2] - a2->pos[2];
	//diffTest->y *= 100;
	//PrintDebug("diff %f %f %f \n", chunkObject->differenceOrigOther.x, chunkObject->differenceOrigOther.y, chunkObject->differenceOrigOther.z);
	//diffTest->y = 100;
	chunkObject->parent = a3;
	chunkObject->toy.model = 0;
	chunkObject->animalPart = 0;
	//model setup here
	if (a1->chunkmodel)
	{
		BasicObjectPointerModel* v7 = (BasicObjectPointerModel*)_HeapAlloc(1, sizeof(BasicObjectPointerModel));
		if (!v7)
		{
			DeleteChunkObjectPointer(chunkObject);
			return 0;
		}
		memcpy(v7, a1->model, sizeof(NJS_MODEL_SADX));
		chunkObject->base.model = v7;

		NJS_MODEL_SADX* sadx = a1->basicdxmodel;
		if (a1->basicdxmodel->nbPoint)
		{
			if (a1->basicdxmodel->points)
			{

				NJS_POINT3* resultVList = (NJS_POINT3*)_HeapAlloc(1, sizeof(NJS_POINT3) * a1->basicdxmodel->nbPoint);
				if (!resultVList)
				{
					DeleteChunkObjectPointer(chunkObject);
					return 0;
				}
				memcpy(resultVList, a1->basicdxmodel->points, sizeof(NJS_POINT3) * a1->basicdxmodel->nbPoint);
				chunkObject->base.basicdxmodel->points = resultVList;
				dword_3CE04FC++;
			}

			if (a1->basicdxmodel->normals)
			{

				NJS_POINT3* resultVList = (NJS_POINT3*)_HeapAlloc(1, sizeof(NJS_POINT3) * a1->basicdxmodel->nbPoint);
				if (!resultVList)
				{
					DeleteChunkObjectPointer(chunkObject);
					return 0;
				}
				memcpy(resultVList, a1->basicdxmodel->normals, sizeof(NJS_POINT3) * a1->basicdxmodel->nbPoint);
				chunkObject->base.basicdxmodel->normals = resultVList;
				//dword_3CE04FC++;
			}
		}
		if (a1->basicdxmodel->nbMat)
			if (a1->basicdxmodel->mats)
			{
				NJS_MATERIAL* resultVList = (NJS_MATERIAL*)_HeapAlloc(1, sizeof(NJS_MATERIAL) * a1->basicdxmodel->nbMat);
				if (!resultVList)
				{
					DeleteChunkObjectPointer(chunkObject);
					return 0;
				}
				memcpy(resultVList, a1->basicdxmodel->mats, sizeof(NJS_MATERIAL) * a1->basicdxmodel->nbMat);
				chunkObject->base.basicdxmodel->mats = resultVList;
			}

	}
	
	//al_shape_counter++;
	chunkObject->parent = a3;
	if (a1->child)
	{
		chunkObject->base.child = (NJS_OBJECT*)al_shape_load(a1->child, a2->child, chunkObject);
	}
	if (a1->sibling)
	{
		chunkObject->base.sibling = (NJS_OBJECT*)al_shape_load(a1->sibling, a2->sibling, a3);
	}
	return chunkObject;

}

void sub_734C90(BasicObjectPointer* a1)
{
	BasicObjectPointer* i;

	for (i = a1; i; i = (BasicObjectPointer*)i->base.sibling)
	{
		i->toy.exists = 0;
		if (i->base.child)
		{
			sub_734C90((BasicObjectPointer*)i->base.child);
		}
	}
}

void SetAllToyExistsNull(ObjectMaster* a1)
{
	sub_734C90((BasicObjectPointer*)((chaowk*)a1->Data1)->Shape.pObject);
	((chaowk*)a1->Data1)->Shape.LeftHandItemActiveFlag = 0;
	((chaowk*)a1->Data1)->Shape.RightHandItemActiveFlag = 0;
}

int word_3CE2BF8 = 0;

bool isChild;
float PowerRun;
float FlySwim;
float Magnitude;
float flt_3CE2C64;
float flt_3CE2C4C;
float flt_3CE2C04;
float ModifiedPowerRun;
float ModifiedFlySwim;
float dword_3CE2C14;
float dword_3CE2C3C;
float dword_3CE2C30;
float flt_3CE2C74;
float flt_3CE2C48;
float flt_3CE2C54;
float flt_3CE2C10;
float flt_3CE2C0C;

NJS_OBJECT** OriginalModel;
NJS_OBJECT** NormalChildM;
NJS_OBJECT** NormalNormalM;
NJS_OBJECT** HeroChildM;
NJS_OBJECT** HeroNormalM;
NJS_OBJECT** DarkChildM;
NJS_OBJECT** DarkNormalM;

NJS_OBJECT** NormalRunPowerM;
NJS_OBJECT** HeroRunPowerM;
NJS_OBJECT** DarkRPM;

NJS_OBJECT** NeutralSFM;
NJS_OBJECT** HeroSFM;
NJS_OBJECT** DarkSFM;

bool IsDark;

short LookUpMorphFlag[] = { 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 4, 5, 2, 4, 5, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 0 ,2, 2, 2, 3, 2, 3 };

void MorphChao(unsigned int *a1)
{
	NJS_VECTOR* originalVertices;
	NJS_VECTOR* SwimFlyVertices;
	NJS_VECTOR* NormalVertices;
	NJS_VECTOR* RunPowerVertices;
	NJS_VECTOR* ChildVertices;

	NJS_MATERIAL* originalMats;
	NJS_MATERIAL* SwimFlyMats;
	NJS_MATERIAL* NormalMats;
	NJS_MATERIAL* RunPowerMats;
	NJS_MATERIAL* ChildMats;

	int firstObj = 1;

	for (int i = 0; i < 40; i++)
	{
		NJS_OBJECT* model = (NJS_OBJECT*)OriginalModel[i];
		NJS_OBJECT* childm = (NJS_OBJECT*)NormalChildM[i];
		NJS_OBJECT* normalm = (NJS_OBJECT*)NormalNormalM[i];
		NJS_OBJECT* runpowerm = (NJS_OBJECT*)NormalRunPowerM[i];
		NJS_OBJECT* swimflym = (NJS_OBJECT*)NeutralSFM[i];

		if (LookUpMorphFlag[i] & 1)
			if (model->basicdxmodel)
			{
				bool dontLerp = (isChild && (i == 37 || i == 39));
				if (dontLerp == false)
					for (int j = 0; j < model->basicdxmodel->nbPoint; j++)
					{
						originalVertices = &model->basicdxmodel->points[j];
						SwimFlyVertices = &swimflym->basicdxmodel->points[j];
						NormalVertices = &normalm->basicdxmodel->points[j];
						RunPowerVertices = &runpowerm->basicdxmodel->points[j];
						ChildVertices = &childm->basicdxmodel->points[j];

						originalVertices->x =
							ModifiedPowerRun * (NormalVertices->x * flt_3CE2C64 + RunPowerVertices->x * PowerRun) +
							ModifiedFlySwim * (NormalVertices->x * flt_3CE2C4C + SwimFlyVertices->x * FlySwim);
						originalVertices->x = originalVertices->x * Magnitude + ChildVertices->x * flt_3CE2C04;
						originalVertices->y =
							ModifiedPowerRun * (NormalVertices->y * flt_3CE2C64 + RunPowerVertices->y * PowerRun) +
							ModifiedFlySwim * (NormalVertices->y * flt_3CE2C4C + SwimFlyVertices->y * FlySwim);
						originalVertices->y = originalVertices->y * Magnitude + ChildVertices->y * flt_3CE2C04;
						originalVertices->z =
							ModifiedPowerRun * (NormalVertices->z * flt_3CE2C64 + RunPowerVertices->z * PowerRun) +
							ModifiedFlySwim * (NormalVertices->z * flt_3CE2C4C + SwimFlyVertices->z * FlySwim);
						originalVertices->z = originalVertices->z * Magnitude + ChildVertices->z * flt_3CE2C04;
						/*
						originalVertices->x = (((SwimFlyVertices->x - NormalVertices->x) * FlySwim + NormalVertices->x)
							* ModifiedFlySwim
							+ ((RunPowerVertices->x - NormalVertices->x) * PowerRun + NormalVertices->x)
							* ModifiedPowerRun
							- ChildVertices->x)
							* Magnitude
							+ ChildVertices->x;
						
						originalVertices->y = (((SwimFlyVertices->y - NormalVertices->y) * FlySwim + NormalVertices->y)
							* ModifiedFlySwim
							+ ((RunPowerVertices->y - NormalVertices->y) * PowerRun + NormalVertices->y)
							* ModifiedPowerRun
							- ChildVertices->y)
							* Magnitude
							+ ChildVertices->y;
						originalVertices->z = (((SwimFlyVertices->z - NormalVertices->z) * FlySwim + NormalVertices->z)
							* ModifiedFlySwim
							+ ((RunPowerVertices->z - NormalVertices->z) * PowerRun + NormalVertices->z)
							* ModifiedPowerRun
							- ChildVertices->z)
							* Magnitude
							+ ChildVertices->z;
*/
						originalVertices = &model->basicdxmodel->normals[j];
						SwimFlyVertices = &swimflym->basicdxmodel->normals[j];
						NormalVertices = &normalm->basicdxmodel->normals[j];
						RunPowerVertices = &runpowerm->basicdxmodel->normals[j];
						ChildVertices = &childm->basicdxmodel->normals[j];

						originalVertices->x = (((SwimFlyVertices->x - NormalVertices->x) * FlySwim + NormalVertices->x)
							* ModifiedFlySwim
							+ ((RunPowerVertices->x - NormalVertices->x) * PowerRun + NormalVertices->x)
							* ModifiedPowerRun
							- ChildVertices->x)
							* Magnitude
							+ ChildVertices->x;
						originalVertices->y = (((SwimFlyVertices->y - NormalVertices->y) * FlySwim + NormalVertices->y)
							* ModifiedFlySwim
							+ ((RunPowerVertices->y - NormalVertices->y) * PowerRun + NormalVertices->y)
							* ModifiedPowerRun
							- ChildVertices->y)
							* Magnitude
							+ ChildVertices->y;
						originalVertices->z = (((SwimFlyVertices->z - NormalVertices->z) * FlySwim + NormalVertices->z)
							* ModifiedFlySwim
							+ ((RunPowerVertices->z - NormalVertices->z) * PowerRun + NormalVertices->z)
							* ModifiedPowerRun
							- ChildVertices->z)
							* Magnitude
							+ ChildVertices->z;
					}

				if (dontLerp == false)
				for (int j = 0; j < model->basicdxmodel->nbMat; j++)
				{
					originalMats = &model->basicdxmodel->mats[j];
					SwimFlyMats = &swimflym->basicdxmodel->mats[j];
					NormalMats = &normalm->basicdxmodel->mats[j];
					RunPowerMats = &runpowerm->basicdxmodel->mats[j];
					ChildMats = &childm->basicdxmodel->mats[j];
					
					float fVar5 = Magnitude;
					if (fVar5 > 1) fVar5 = 1.0f;
					float fVar19 = 1.0 - fVar5;

					float weirdMagicFloat = 1;
					float fVar8 = ModifiedPowerRun *
						(NormalMats->diffuse.argb.r * weirdMagicFloat *
							flt_3CE2C64 +
						RunPowerMats->diffuse.argb.r * weirdMagicFloat
							* PowerRun) +
						ModifiedFlySwim *
						(NormalMats->diffuse.argb.r * weirdMagicFloat *
							flt_3CE2C4C +
							SwimFlyMats->diffuse.argb.r * weirdMagicFloat * FlySwim);
					
					if (fVar8 < 0) fVar8 = 0;
					if (fVar8 > 255) fVar8 = 255;
					fVar8 = ChildMats->diffuse.argb.r * fVar19 + fVar8 * fVar5;
					originalMats->diffuse.argb.r = fVar8;
					
					fVar8 = ModifiedPowerRun *
						(NormalMats->diffuse.argb.g * weirdMagicFloat *
							flt_3CE2C64 +
							RunPowerMats->diffuse.argb.g * weirdMagicFloat
							* PowerRun) +
						ModifiedFlySwim *
						(NormalMats->diffuse.argb.g * weirdMagicFloat *
							flt_3CE2C4C +
							SwimFlyMats->diffuse.argb.g * weirdMagicFloat * FlySwim);
					
					if (fVar8 < 0) fVar8 = 0;
					if (fVar8 > 255) fVar8 = 255;
					fVar8 = ChildMats->diffuse.argb.g * fVar19 + fVar8 * fVar5;
					originalMats->diffuse.argb.g = fVar8;
					fVar8 = ModifiedPowerRun *
						(NormalMats->diffuse.argb.b * weirdMagicFloat *
							flt_3CE2C64 +
							RunPowerMats->diffuse.argb.b * weirdMagicFloat
							* PowerRun) +
						ModifiedFlySwim *
						(NormalMats->diffuse.argb.b * weirdMagicFloat *
							flt_3CE2C4C +
							SwimFlyMats->diffuse.argb.b * weirdMagicFloat * FlySwim);
					if (fVar8 < 0) fVar8 = 0;
					if (fVar8 > 255) fVar8 = 255;
					fVar8 = ChildMats->diffuse.argb.b * fVar19 + fVar8 * fVar5;
					originalMats->diffuse.argb.b = fVar8;
					
					/*
					float v23 = ((((double)SwimFlyMats->diffuse.argb.b - (double)NormalMats->diffuse.argb.b) * dword_3CE2C3C + (double)NormalMats->diffuse.argb.b) * flt_3CE2C0C
						+ (((double)RunPowerMats->diffuse.argb.b - (double)NormalMats->diffuse.argb.b) * dword_3CE2C14 + (double)NormalMats->diffuse.argb.b) * flt_3CE2C10);
					originalMats->diffuse.argb.b = (((double)(unsigned __int8)v23 - (double)ChildMats->diffuse.argb.b) * dword_3CE2C30
						+ (double)ChildMats->diffuse.argb.b);

					v23 = ((((double)SwimFlyMats->diffuse.argb.r - (double)NormalMats->diffuse.argb.r) * dword_3CE2C3C + (double)NormalMats->diffuse.argb.r) * flt_3CE2C0C
						+ (((double)RunPowerMats->diffuse.argb.r - (double)NormalMats->diffuse.argb.r) * dword_3CE2C14 + (double)NormalMats->diffuse.argb.r) * flt_3CE2C10);
					originalMats->diffuse.argb.r = (((double)(unsigned __int8)v23 - (double)ChildMats->diffuse.argb.r) * dword_3CE2C30
						+ (double)ChildMats->diffuse.argb.r);

					v23 = ((((double)SwimFlyMats->diffuse.argb.g - (double)NormalMats->diffuse.argb.g) * dword_3CE2C3C + (double)NormalMats->diffuse.argb.g) * flt_3CE2C0C
						+ (((double)RunPowerMats->diffuse.argb.g - (double)NormalMats->diffuse.argb.g) * dword_3CE2C14 + (double)NormalMats->diffuse.argb.g) * flt_3CE2C10);
					originalMats->diffuse.argb.g = (((double)(unsigned __int8)v23 - (double)ChildMats->diffuse.argb.g) * dword_3CE2C30
						+ (double)ChildMats->diffuse.argb.g);
						*/
					if(firstObj)
						*a1 = originalMats->diffuse.color;
				}
				firstObj = 0;
			}
		//if (false && (isChild && ) ||
			//LookUpMorphFlag[i] & 4)
		if(LookUpMorphFlag[i] & 2)
		{
			model->pos[0] = ((((swimflym)->pos[0] - normalm->pos[0]) * FlySwim + normalm->pos[0]) * ModifiedFlySwim
				+ (((runpowerm)->pos[0] - normalm->pos[0]) * PowerRun + normalm->pos[0]) * ModifiedPowerRun
				- childm->pos[0])
				* Magnitude
				+ childm->pos[0];

			model->pos[1] = ((((swimflym)->pos[1] - normalm->pos[1]) * FlySwim + normalm->pos[1]) * ModifiedFlySwim
				+ (((runpowerm)->pos[1] - normalm->pos[1]) * PowerRun + normalm->pos[1]) * ModifiedPowerRun
				- childm->pos[1])
				* Magnitude
				+ childm->pos[1];

			model->pos[2] = ((((swimflym)->pos[2] - normalm->pos[2]) * FlySwim + normalm->pos[2]) * ModifiedFlySwim
				+ (((runpowerm)->pos[2] - normalm->pos[2]) * PowerRun + normalm->pos[2]) * ModifiedPowerRun
				- childm->pos[2])
				* Magnitude
				+ childm->pos[2];

			model->ang[0] = (((((double)(swimflym)->ang[0] - normalm->ang[0]) * FlySwim
				+ normalm->ang[0])
				* ModifiedFlySwim
				+ (((double)(runpowerm)->ang[0] - normalm->ang[0]) * PowerRun
					+ normalm->ang[0])
				* ModifiedPowerRun
				- (double)childm->ang[0])
				* Magnitude
				+ (double)childm->ang[0]);

			model->ang[1] = (((((double)(swimflym)->ang[1] - normalm->ang[1]) * FlySwim
				+ normalm->ang[1])
				* ModifiedFlySwim
				+ (((double)(runpowerm)->ang[1] - normalm->ang[1]) * PowerRun
					+ normalm->ang[1])
				* ModifiedPowerRun
				- (double)childm->ang[1])
				* Magnitude
				+ (double)childm->ang[1]);

			model->ang[2] = (((((double)(swimflym)->ang[2] - normalm->ang[2]) * FlySwim
				+ normalm->ang[2])
				* ModifiedFlySwim
				+ (((double)(runpowerm)->ang[2] - normalm->ang[2]) * PowerRun
					+ normalm->ang[2])
				* ModifiedPowerRun
				- (double)childm->ang[2])
				* Magnitude
				+ (double)childm->ang[2]);
		}
		
	}
}

// aka, the shiny jewel colors.
void __cdecl Chao_SetDreamcastSA2Colors_(ObjectMaster* chao, __int16 color)
{
	chaowk* data1; // eax
	NJS_BGRA* v3; // ebx
	al_object** v4; // esi
	Uint16* v5; // edi
	signed int v6; // edx

	data1 = (chaowk*)chao->Data1;
	v3 = (NJS_BGRA*)& Chao_DreamcastSA2Colors[color];
	v4 = data1->Shape.CurrObjectList;
	v5 = Chao_ColorSetNodes;
	data1->pParamGC->Color = color;
	v6 = 0;
	do
	{
		if (*v5 == -1)
		{
			break;
		}
		if (*v5 == v6)
		{
			Chao_SetVertexColor((BasicObjectPointer*)* v4, *v3);
			++v5;
		}
		++v4;
		++v6;
	} while (v6 < 40);
}

void __cdecl Chao_SetDreamcastSA2Colors(ObjectMaster* a1)
{
	unsigned __int8 v1; // al

	v1 = ((chaowk*)a1->Data1)->pParamGC->Color;
	if (v1)
	{
		Chao_SetDreamcastSA2Colors_(a1, v1);
	}
}
ObjectFunc(EmotionBallColoring, 0x00735060);
void __cdecl sub_767790(ObjectMaster* a1)
{
	chaowk* v1; // esi
	ChaoDataBase* v2; // ecx
	float v3; // edx
	int ChaoType; // eax
	bool IsChild; // zf
	AL_GROUP_OBJECT_LIST* v6; // eax
	double v8; // st7
	int v9; // [esp-4h] [ebp-Ch]

	v1 = (chaowk*)a1->Data1;
	v2 = v1->pParamGC;
	PowerRun = v2->PowerRun;
	v3 = v2->FlySwim;
	OriginalModel = (NJS_OBJECT * *)v1->Shape.CurrObjectList;
	FlySwim = v3;
	ChaoType = (unsigned __int8)v2->Type;
	NormalChildM = v1->Shape.pObjectList->Zero;
	IsChild = ChaoType == 2;
	v6 = v1->Shape.pObjectList;
	isChild = IsChild;
	if (IsChild)
	{
		NormalNormalM = v6->Normal;
		HeroChildM = v1->Shape.pObjectListH->Zero;
		HeroNormalM = v1->Shape.pObjectListH->Normal;
		DarkChildM = v1->Shape.pObjectListD->Zero;
		DarkNormalM = v1->Shape.pObjectListD->Normal;
		if (PowerRun < 0.0)
		{
			NormalRunPowerM = v1->Shape.pObjectList->Run;
			HeroRunPowerM = v1->Shape.pObjectListH->Run;
			DarkRPM = v1->Shape.pObjectListD->Run;
			PowerRun = PowerRun * -1.0f;
		}
		else
		{
			NormalRunPowerM = v1->Shape.pObjectList->Power;
			HeroRunPowerM = v1->Shape.pObjectListH->Power;
			DarkRPM = v1->Shape.pObjectListD->Power;
		}
		if (FlySwim >= 0.0)
		{
			NeutralSFM = v1->Shape.pObjectList->Fly;
			HeroSFM = v1->Shape.pObjectListH->Fly;
			DarkSFM = v1->Shape.pObjectListD->Fly;
			goto LABEL_15;
		}
		NeutralSFM = v1->Shape.pObjectList->Swim;
		HeroSFM = v1->Shape.pObjectListH->Swim;
		DarkSFM = v1->Shape.pObjectListD->Swim;
	}
	else
	{
		NormalNormalM = v6->Normal;
		if (PowerRun < 0.0f)
		{
			NormalRunPowerM = v1->Shape.pObjectList->Run;
			PowerRun = PowerRun * -1.0f;
		}
		else
		{
			NormalRunPowerM = v1->Shape.pObjectList->Power;
		}
		if (FlySwim >= 0.0f)
		{
			NeutralSFM = v1->Shape.pObjectList->Fly;
			goto LABEL_15;
		}
		NeutralSFM = v1->Shape.pObjectList->Swim;
	}
	FlySwim = FlySwim * -1.0f;
LABEL_15:
	Magnitude = v2->EvolutionProgress;
	if (PowerRun == 0.0f)
	{
		PowerRun = 0.000001f;
	}
	if (FlySwim == 0.0f)
	{
		FlySwim = 0.000001f;
	}

	flt_3CE2C64 = 1.0f - PowerRun;
	flt_3CE2C4C = 1.0f - FlySwim;
	flt_3CE2C04 = 1.0f - Magnitude;
	v8 = 1.0f / (FlySwim + PowerRun);
	ModifiedPowerRun = PowerRun * v8;
	ModifiedFlySwim = v8 * FlySwim;
	if (PowerRun <= 1.0f)
	{
		if (PowerRun >= -1.0f)
		{
			dword_3CE2C14 = PowerRun;
		}
		else
		{
			dword_3CE2C14 = -1.0f;
		}
	}
	else
	{
		dword_3CE2C14 = 1.0f;
	}
	if (FlySwim <= 1.0f)
	{
		if (FlySwim >= -1.0f)
		{
			dword_3CE2C3C = FlySwim;
		}
		else
		{
			dword_3CE2C3C = -1.0f;
		}
	}
	else
	{
		dword_3CE2C3C = 1.0f;
	}
	if (Magnitude <= 1.0f)
	{
		if (Magnitude >= -1.0f)
		{
			dword_3CE2C30 = Magnitude;
		}
		else
		{
			dword_3CE2C30 = -1.0f;
		}
	}
	else
	{
		dword_3CE2C30 = 1.0f;
	}
	flt_3CE2C74 = 1.0f - dword_3CE2C14;
	flt_3CE2C48 = 1.0f - dword_3CE2C3C;
	flt_3CE2C54 = 1.0f - dword_3CE2C30;
	flt_3CE2C10 = dword_3CE2C14 * v8;
	flt_3CE2C0C = v8 * dword_3CE2C3C;
	v9 = (unsigned __int8)a1->Data1->Index;
	chaowk* wk = (chaowk*)a1->Data1;
	ADV1_AL_ICON* icon = (ADV1_AL_ICON*)&wk->Icon;
	//EmotionBallColoring(a1);
	//MorphChao(&wk->Icon.Color);
	MorphChao(&icon->col.color);

	//icon->col.color = 0xFFFFFFFF;
	//iconColor->a *= otherColors->a;
	//iconColor->a *= otherColors[DCType].a;
	//wk->Icon.Color = IconColors[DCType];
	Chao_SetDreamcastSA2Colors(a1);
	v1->Shape.Flag &= ~2u;
}

void __cdecl sub_765070(BasicObjectPointer* a1)
{
	BasicObjectPointer* v1; // esi

	v1 = a1;
	do
	{
		njPushMatrixEx();
		njTranslateV(0, (NJS_VECTOR*)v1->base.pos);
		njRotateXYZ(0, v1->base.ang[0], v1->base.ang[1], v1->base.ang[2]);
		njGetMatrix(v1->Matrix);
		if (v1->base.child)
		{
			sub_765070((BasicObjectPointer*)v1->base.child);
		}
		njPopMatrixEx();
		v1 = (BasicObjectPointer*)v1->base.sibling;
	} while (v1);
}
void __cdecl sub_7650C0(ObjectMaster* a1)
{
	njPushMatrixEx();
	njUnitMatrix(0);
	njTranslateV(0, &a1->Data1->Position);
	if (a1->Data1->Rotation.y)
	{
		njRotateY(0, a1->Data1->Rotation.y);
	}
	sub_765070((BasicObjectPointer*)((chaowk*)a1->Data1)->Shape.pObject);
	njPopMatrixEx();
}
short word_3CE04F8 = 0;
void __cdecl AllocateChaoPalette(ObjectMaster* a1)
{
	((chaowk*)a1->Data1)->Shape.palette = (unsigned short*)_HeapAlloc(1, 0x60u);
}

/*
 originalVertices->x = (((SwimFlyVertices->x - NormalVertices->x) * FlySwim + NormalVertices->x)
								 * ModifiedFlySwim
								 + ((RunPowerVertices->x - NormalVertices->x) * PowerRun + NormalVertices->x)
								 * ModifiedPowerRun
								 - ChildVertices->x)
								* Magnitude
								+ ChildVertices->x;
*/

DataArray(NJS_OBJECT*, Al_RootObject, 0x034BD4A8, 100);
void Chao_LoadModels(ObjectMaster* a1)
{
	NJS_OBJECT** chaoObjects = Al_RootObject;//(NJS_OBJECT * *)GetProcAddress(GetModuleHandle(L"Data_dll_orig"), "AL_RootObject");
	//((chaowk*)a1->Data1)->pParamGC->Type = ChaoType_Neutral_Fly;
	//((chaowk*)a1->Data1)->pParamGC->PowerRun = 1.5f;
	//((chaowk*)a1->Data1)->pParamGC->EvolutionProgress = 1.5f;
	int type = ((chaowk*)a1->Data1)->pParamGC->Type;
	if (type >= 6u && !((type - 6) % 3))
		type--;
	else if (type >= ChaoType_Dark_Normal && type < ChaoType_Tails && !((type - ChaoType_Dark_Normal) % 3))
		type -= 2;
	((chaowk*)a1->Data1)->pParamGC->Type = (ChaoType)type;
	int v2 = 6 * ((unsigned __int8)type - 2);

	dword_3CE04FC = 0;
	word_3CE04F8 = 0;



	((chaowk*)a1->Data1)->Shape.pObject = (al_object*)al_shape_load(chaoObjects[v2], (NJS_OBJECT*)0x36CCF68, 0);

	((chaowk*)a1->Data1)->Shape.pObjectList = (AL_GROUP_OBJECT_LIST*)_HeapAlloc(1, sizeof(AL_GROUP_OBJECT_LIST));
	((chaowk*)a1->Data1)->Shape.pObjectListH = (AL_GROUP_OBJECT_LIST*)_HeapAlloc(1, sizeof(AL_GROUP_OBJECT_LIST));
	((chaowk*)a1->Data1)->Shape.pObjectListD = (AL_GROUP_OBJECT_LIST*)_HeapAlloc(1, sizeof(AL_GROUP_OBJECT_LIST));

	AL_GetObjectList((NJS_OBJECT*)((chaowk*)a1->Data1)->Shape.pObject, (NJS_OBJECT * *)((chaowk*)a1->Data1)->Shape.CurrObjectList);

	if (((chaowk*)a1->Data1)->Shape.pObjectList)
	{
		AL_GetObjectList(chaoObjects[v2], ((chaowk*)a1->Data1)->Shape.pObjectList->Zero);
		AL_GetObjectList(chaoObjects[v2 + 1], ((chaowk*)a1->Data1)->Shape.pObjectList->Normal);
		AL_GetObjectList(chaoObjects[v2 + 2], ((chaowk*)a1->Data1)->Shape.pObjectList->Swim);
		AL_GetObjectList(chaoObjects[v2 + 3], ((chaowk*)a1->Data1)->Shape.pObjectList->Fly);
		AL_GetObjectList(chaoObjects[v2 + 4], ((chaowk*)a1->Data1)->Shape.pObjectList->Run);
		AL_GetObjectList(chaoObjects[v2 + 5], ((chaowk*)a1->Data1)->Shape.pObjectList->Power);
	}

	if (((chaowk*)a1->Data1)->Shape.pObjectListH)
	{
		AL_GetObjectList(chaoObjects[v2], ((chaowk*)a1->Data1)->Shape.pObjectListH->Zero);
		AL_GetObjectList(chaoObjects[v2 + 1], ((chaowk*)a1->Data1)->Shape.pObjectListH->Normal);
		AL_GetObjectList(chaoObjects[v2 + 2], ((chaowk*)a1->Data1)->Shape.pObjectListH->Swim);
		AL_GetObjectList(chaoObjects[v2 + 3], ((chaowk*)a1->Data1)->Shape.pObjectListH->Fly);
		AL_GetObjectList(chaoObjects[v2 + 4], ((chaowk*)a1->Data1)->Shape.pObjectListH->Run);
		AL_GetObjectList(chaoObjects[v2 + 5], ((chaowk*)a1->Data1)->Shape.pObjectListH->Power);
	}

	if (((chaowk*)a1->Data1)->Shape.pObjectListD)
	{
		AL_GetObjectList(chaoObjects[v2], ((chaowk*)a1->Data1)->Shape.pObjectListD->Zero);
		AL_GetObjectList(chaoObjects[v2 + 1], ((chaowk*)a1->Data1)->Shape.pObjectListD->Normal);
		AL_GetObjectList(chaoObjects[v2 + 2], ((chaowk*)a1->Data1)->Shape.pObjectListD->Swim);
		AL_GetObjectList(chaoObjects[v2 + 3], ((chaowk*)a1->Data1)->Shape.pObjectListD->Fly);
		AL_GetObjectList(chaoObjects[v2 + 4], ((chaowk*)a1->Data1)->Shape.pObjectListD->Run);
		AL_GetObjectList(chaoObjects[v2 + 5], ((chaowk*)a1->Data1)->Shape.pObjectListD->Power);
	}

	/*
	if (((chaowk*)a1->Data1)->ModelData.HeroModels)
	{
		al_shape_CopyNodes(chaoObjects[6], ((chaowk*)a1->Data1)->ModelData.HeroModels->child);
		al_shape_CopyNodes(chaoObjects[7], ((chaowk*)a1->Data1)->ModelData.HeroModels->normal);
		al_shape_CopyNodes(chaoObjects[8], ((chaowk*)a1->Data1)->ModelData.HeroModels->swim);
		al_shape_CopyNodes(chaoObjects[9], ((chaowk*)a1->Data1)->ModelData.HeroModels->fly);
		al_shape_CopyNodes(chaoObjects[10], ((chaowk*)a1->Data1)->ModelData.HeroModels->run);
		al_shape_CopyNodes(chaoObjects[11], ((chaowk*)a1->Data1)->ModelData.HeroModels->power);
	}

	if (((chaowk*)a1->Data1)->ModelData.DarkModels)
	{
		al_shape_CopyNodes(chaoObjects[12], ((chaowk*)a1->Data1)->ModelData.DarkModels->child);
		al_shape_CopyNodes(chaoObjects[13], ((chaowk*)a1->Data1)->ModelData.DarkModels->normal);
		al_shape_CopyNodes(chaoObjects[14], ((chaowk*)a1->Data1)->ModelData.DarkModels->swim);
		al_shape_CopyNodes(chaoObjects[15], ((chaowk*)a1->Data1)->ModelData.DarkModels->fly);
		al_shape_CopyNodes(chaoObjects[16], ((chaowk*)a1->Data1)->ModelData.DarkModels->run);
		al_shape_CopyNodes(chaoObjects[17], ((chaowk*)a1->Data1)->ModelData.DarkModels->power);
	}
	*/

	//sub_741B20((BasicObjectPointer*)((chaowk*)a1->Data1)->ModelData.PointerToStructWithCnkObject);

	AllocateChaoPalette(a1);
	sub_7650C0(a1);
}