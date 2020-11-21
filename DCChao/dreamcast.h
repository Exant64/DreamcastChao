#pragma once
#include "SADXModLoader.h"
ObjectMaster* __cdecl Flower_Load(ObjectMaster* a1, NJS_VECTOR* a2);
void BreedingFlower2(NJS_CNK_OBJECT* a1);
void BreedingFlower1(NJS_CNK_OBJECT* a1);
void DrawDCToys(NJS_CNK_OBJECT* a1);
void DrawDCToys2(NJS_CNK_OBJECT* a1);
void Dreamcast_Init();
void DreamcastChao_Init(const char* path);
void __cdecl ADV1toADV2_SetMotionLink(int a1, int a2);