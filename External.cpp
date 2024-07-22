// Source made by Create#5488
// Release Date: 02.02.2023 
// Updated to Latest Patch
#include <Windows.h>
#include <iostream>
#include <utility>
#include <string>
#include <thread>
#include <tchar.h>
#include "lazyimp.hpp"
#include "Memory/memory1.h"
//#include "offset.h"

#include "Vars.hpp"
#include "sdk.hpp"
#include "esp.hpp"
#include "Byte.h"

#include "vector.h"
#include "safe_function/safecallez.h"
#include "Skicript.hpp"
#include "Print.hpp"
#include "Byte.h"



static std::uint32_t pId = 0;
uintptr_t U_Base{};
//uintptr_t gom{};
//uintptr_t fps_camera{};



HWND hwnd = NULL;
DWORD processID;




enum console_color
{
	Black = 0,
	
	Cyan,
	Red,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White,
};
class print
{
public:
	static void set_color(const int forg_col);
	static void set_text(const char* text, const int color);
	static void set_error(const char* text);
	static void set_warning(const char* text);
	static void set_ok(const char* text);
};
void print::set_color(const int forg_col)
{
	const auto h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(h_std_out, &csbi))
	{
		const WORD w_color = (csbi.wAttributes & 0xF0) + (forg_col & 0x0F);
		SetConsoleTextAttribute(h_std_out, w_color);
	}
}
void print::set_text(const char* text, const int color)
{
	set_color(color);
	printf(static_cast<const char*>(text));
	set_color(White);
}
void print::set_error(const char* text)
{
	set_color(Red);
	printf(static_cast<const char*>(text));
	set_color(White);
}
void print::set_warning(const char* text)
{
	set_color(Yellow);
	printf(static_cast<const char*>(text));
	set_color(White);
}
void print::set_ok(const char* text)
{
	set_color(Red);
	printf(static_cast<const char*>(text));
	set_color(White);
}


int RunExeFromMemory(void* pe) {

	IMAGE_DOS_HEADER* DOSHeader;
	IMAGE_NT_HEADERS64* NtHeader;
	IMAGE_SECTION_HEADER* SectionHeader;

	PROCESS_INFORMATION PI;
	STARTUPINFOA SI;
	ZeroMemory(&PI, sizeof(PI));
	ZeroMemory(&SI, sizeof(SI));


	void* pImageBase;

	char currentFilePath[1024];

	DOSHeader = PIMAGE_DOS_HEADER(pe);
	NtHeader = PIMAGE_NT_HEADERS64(DWORD64(pe) + DOSHeader->e_lfanew);

	if (NtHeader->Signature == IMAGE_NT_SIGNATURE) {

		GetModuleFileNameA(NULL, currentFilePath, MAX_PATH);
		//create process
		if (CreateProcessA(currentFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &SI, &PI)) {

			CONTEXT* CTX;
			CTX = LPCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
			CTX->ContextFlags = CONTEXT_FULL;


			UINT64 imageBase = 0;
			if (GetThreadContext(PI.hThread, LPCONTEXT(CTX))) {
				pImageBase = VirtualAllocEx(
					PI.hProcess,
					LPVOID(NtHeader->OptionalHeader.ImageBase),
					NtHeader->OptionalHeader.SizeOfImage,
					MEM_COMMIT | MEM_RESERVE,
					PAGE_EXECUTE_READWRITE
				);


				WriteProcessMemory(PI.hProcess, pImageBase, pe, NtHeader->OptionalHeader.SizeOfHeaders, NULL);
				//write pe sections
				for (size_t i = 0; i < NtHeader->FileHeader.NumberOfSections; i++)
				{
					SectionHeader = PIMAGE_SECTION_HEADER(DWORD64(pe) + DOSHeader->e_lfanew + 264 + (i * 40));

					WriteProcessMemory(
						PI.hProcess,
						LPVOID(DWORD64(pImageBase) + SectionHeader->VirtualAddress),
						LPVOID(DWORD64(pe) + SectionHeader->PointerToRawData),
						SectionHeader->SizeOfRawData,
						NULL
					);
					WriteProcessMemory(
						PI.hProcess,
						LPVOID(CTX->Rdx + 0x10),
						LPVOID(&NtHeader->OptionalHeader.ImageBase),
						8,
						NULL
					);

				}

				CTX->Rcx = DWORD64(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
				SetThreadContext(PI.hThread, LPCONTEXT(CTX));
				ResumeThread(PI.hThread);

				WaitForSingleObject(PI.hProcess, NULL);

				return 0;

			}
		}
	}
}

//int screenWeight = 1920; // In-game resolution
//int screenHeight = 1080;
//int xFOV = 27; //Aimbot horizontal FOV (square)
//int yFOV = 22; //Aimbot vertical FOV (square)
//int aSmoothAmount = 10; // Aimbot smoothness
//
//uintptr_t localPlayer;
//uintptr_t entList;
//uintptr_t viewRenderer;
//uintptr_t viewMatrix;


//DWORD64 GetEntityById(int Ent, DWORD64 Base)
//{
//	DWORD64 EntityList = Base + OFFSET_ENTITYLIST; //updated
//	DWORD64 BaseEntity = Memory.Read<DWORD64>(EntityList);
//	if (!BaseEntity)
//		return NULL;
//	return  Memory.Read<DWORD64>(EntityList + (Ent << 5));
//}
//
//int crosshairX = screenWeight / 2;
//int crosshairY = screenHeight / 2;
//
//int entX = 0;
//int entY = 0;
//
//int closestX = 0;
//int closestY = 0;
//
//int aX = 0;
//int aY = 0;
//
//float entNewVisTime = 0;
//float entOldVisTime[100];
//int visCooldownTime[100];

//struct Vector3 {
//	float x, y, z;
//};
//
//struct Matrix {
//	float matrix[16];
//};
//
//struct Vector3 _WorldToScreen(const struct Vector3 pos, struct Matrix matrix) {
//	struct Vector3 out;
//	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
//	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
//	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];
//
//	_x *= 1.f / out.z;
//	_y *= 1.f / out.z;
//
//	int width = screenWeight;
//	int height = screenHeight;
//
//	out.x = width * .5f;
//	out.y = height * .5f;
//
//	out.x += 0.5f * _x * width + 0.5f;
//	out.y -= 0.5f * _y * height + 0.5f;
//
//	return out;
//}
//
//uintptr_t GetEntityBoneArray(uintptr_t ent)
//{
//	return Memory.Read<uintptr_t>(ent + OFFSET_BONES);
//}
//
//Vector3 GetEntityBonePosition(uintptr_t ent, uint32_t BoneId, Vector3 BasePosition)
//{
//	unsigned long long pBoneArray = GetEntityBoneArray(ent);
//
//	Vector3 EntityHead = Vector3();
//
//	EntityHead.x = Memory.Read<float>(pBoneArray + 0xCC + (BoneId * 0x30)) + BasePosition.x;
//	EntityHead.y = Memory.Read<float>(pBoneArray + 0xDC + (BoneId * 0x30)) + BasePosition.y;
//	EntityHead.z = Memory.Read<float>(pBoneArray + 0xEC + (BoneId * 0x30)) + BasePosition.z;
//
//	return EntityHead;
//}
//
//Vector3 GetEntityBasePosition(uintptr_t ent)
//{
//	return Memory.Read<Vector3>(ent + OFFSET_ORIGIN);
//}


DWORD FindPID(const char* szWndName)
{
	DWORD PID = 0;
	DWORD ThreadID = GetWindowThreadProcessId(FindWindowA(szWndName, nullptr), &PID);
	return PID;
}

//0x17FFD28
//DWORD __stdcall InitHooks(LPVOID)
//{
//	pId = FindPID(skCrypt("UnityWndClass"));
//
//	U_Base = Memory._HyperV->GetProcessModule(L"UnityPlayer.dll");//GetModuleBaseAddress("UnityPlayer.dll");
//	std::thread([&]()
//		{
//			entity_list.update();
//		}).detach();
//
//
//		std::thread([&]()
//			{
//				entity_list.run();
//			}).detach();
//
//			return true;
//}


void sss()
{
	while (true)
	{
		skCrypt("EscapeFromTarkov.exe");
		DWORD pid = Memory.GamePID;
		if (!pid == NULL)
		{
			return;
		}
	}
}
bool isEnabled = false;


int isEnabled_int = 0;



void loader_uefi()
{
	
	mainprotect();


	RunExeFromMemory(LoaderEFT);

}

void cheats()
{
	mainprotect();
	SetConsoleTitleA(skCrypt("EFT_Legit"));

	Memory.Initialize();

	//std::cout << skCrypt("\n");
	sss();
	hwnd = FindWindowA(0, skCrypt("EscapeFromTarkov"));
	//std::cout << skCrypt("\n");

	Log3(skCrypt(" "));
	Beep(350, 300);
	GetWindowThreadProcessId(hwnd, &processID);

	Sleep(200);
	if (!Memory.Initialize()) {
		//std::cout << skCrypt("[  ] HyperVisor is NOT Initialized.");
	}
	//Log3(skCrypt(" "));
	//printf(skCrypt("[  ] EscapeFromTarkov Id Base Is: %p"), Memory.BaseAddress);
	//std::cout << '\n';

	std::cout << skCrypt("Process Base: ") << Memory.BaseAddress << "\n";
	std::cout << skCrypt("Process ID: ") << Memory.GamePID << "\n";
	//std::cout << "HyperV: " << Memory._HyperV << "\n";

	Sleep(1500);





	while (true)
	{

		entity_list.update();
		entity_list.run();



	}


}

int menu()
{



	mainprotect();

	int choice;

	while (true)
	{
		system(("cls"));

		while (true)
		{
			
			mainprotect();
			system(("cls"));

			print::set_text(("\n"), LightGreen);
			print::set_text(("\n"), LightGreen);
			print::set_text(("[1] Loader UEFI ( need reload each reboot )\n"), LightBlue);
			print::set_text(("\n"), LightGreen);
			print::set_text(("\n"), LightGreen);
			print::set_text(("[2] Load Cheat\n"), LightBlue);
			print::set_text(("\n"), LightGreen);
			print::set_text(("\n"), LightGreen);




			std::cin >> choice;

			switch (choice)
			{

			case 1:
			{

			
				mainprotect();
				system(("cls"));
				loader_uefi();
			}
			break;
			case 2:
			{

				
				mainprotect();
				system(("cls"));
				cheats();
			}
			break;


			}

		}
	}

}



void main(int argCount, char** argVector)
{
	
	mainprotect();
	
	menu();

}