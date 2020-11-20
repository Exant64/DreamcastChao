#include "SADXModLoader.h"
#include "dreamcast.h"
#include "chao.h"

#include "al_shape_basic.h"
#define ReplaceTextures(a,b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
extern "C"
{
	int tree_counter = 0;
	int jointva = 0;
	void AL_MyCode(ObjectMaster* a1, al_object* a2, NJS_VECTOR* out)
	{
		al_object* v2 = a2;
		do
		{
			njPushMatrixEx();
			AL_CalcMotionMartix(v2);
			if (tree_counter == jointva) //store vec if node found
			{
				//njGetTranslation(0, out);
				njCalcPoint(0, (NJS_VECTOR*)0x08894FC, out);
			}
			al_object* v29 = v2->pChild;
			++tree_counter;
			if (v29)
			{
				AL_MyCode(a1, v29,out );
			}
			njPopMatrixEx();
			v2 = v2->pSibling;
		} while (v2);
	}
	FunctionPointer(void, AL_InitCalcMotionMatrix, (ObjectMaster* a1),0x00764B10);
	int __cdecl ALR_GetBodyPosition(NJS_VECTOR* vec, int task, void* a3, int joint)
	{
		int temp = *(int*)((int)a3 + 0x8D0);
		ObjectMaster* a1 = (ObjectMaster*)temp;
		tree_counter = 0;
		jointva = joint;
		if (jointva == 7)
			jointva = 11;
		njPushMatrixEx();
		njUnitMatrix(0);
		njRotateY(0, a1->Data1->Rotation.y);
		AL_InitCalcMotionMatrix(a1);
		AL_MyCode(a1, ((chaowk*)a1->Data1)->Shape.pObject, vec);
		njPopMatrixEx();
		return 1;
	}
	
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		ReplaceTextures("CHAO", "CHAO_DCCWE");

		//test
		//PrintDebug("DCCHAO TEST %d %d %d \n", LookUpMorphFlag[0x12], LookUpMorphFlag[0x15], LookUpMorphFlag[0x1B]);

		DreamcastChao_Init(path);
		Dreamcast_Init();

		
		//fixes restored race toy crash (it was trying to get the sa1 chao model node hierarchy, had to port it to use the sa2 one
		WriteJump((void*)0x00754D00, ALR_GetBodyPosition);

	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}