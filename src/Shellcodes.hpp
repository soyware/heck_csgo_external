#pragma once

//void SetTag(const char* newTag)
//{
//	if (!Mem::GetAlloc()) return;
//	static uintptr_t Alloc = reinterpret_cast<uintptr_t>(Mem::GetAlloc());
//
//	static bool bInjected = false;
//	if (!bInjected)
//	{
//		BYTE Shellcode[15 + 16] = { 0xBA, 0x00, 0x00, 0x00, 0x00,	// mov	edx, (tag address)
//									0x8B, 0xCA,						// mov	ecx, edx
//									0xB8, 0x00, 0x00, 0x00, 0x00,	// mov	eax, (SendClanTag address)
//									0xFF, 0xD0,						// call	eax
//									0xC3 };							// ret
//																	// (tag)
//
//		*reinterpret_cast<uintptr_t*>(&Shellcode[1]) = Alloc + 15;
//		*reinterpret_cast<uintptr_t*>(&Shellcode[8]) = Offsets::SendClanTag;
//		strcpy_s(reinterpret_cast<char*>(&Shellcode[15]), 16, newTag);
//		Mem::Write<BYTE[15 + 16]>(Alloc, Shellcode);
//		bInjected = true;
//	}
//	else
//		WriteProcessMemory(Mem::Process, reinterpret_cast<LPVOID>(Alloc + 15), newTag, strlen(newTag) + 1, 0);
//
//	Mem::CreateThread(Alloc);
//}
#define SIZE_SETTAG (15 + 16)

//void SetName(const char* newName)
//{
//	if (!Mem::GetAlloc()) return;
//	static uintptr_t Alloc = reinterpret_cast<uintptr_t>(Mem::GetAlloc()) + SIZE_SETTAG;
//
//	static bool bInjected = false;
//	if (!bInjected)
//	{
//		BYTE Shellcode[37 + 128] = { 0x55,							// push	ebp
//									0x8B, 0xEC,						// mov	ebp, esp
//									0x83, 0xE4, 0xF8,				// and	esp, 0FFFFFFF8h
//									0x8B, 0x45, 0x08,				// mov	eax, [ebp+args]
//									0x83, 0xEC, 0x44,				// sub	esp, 44h
//									0x53,							// push	ebx
//									0x56,							// push	esi
//									0x57,							// push	edi
//									0xBE, 0x00, 0x00, 0x00, 0x00,	// mov	esi, (pointer to value to set)
//									0xBF, 0x00, 0x00, 0x00, 0x00,	// mov	edi, (pointer to convar name)
//									0xB8, 0x00, 0x00, 0x00, 0x00,	// mov	eax, (SetInfo part)
//									0xFF, 0xE0,						// jmp	eax
//									'n', 'a', 'm', 'e', '\0' };
//
//		*reinterpret_cast<uintptr_t*>(&Shellcode[16]) = Alloc + 37;
//		*reinterpret_cast<uintptr_t*>(&Shellcode[21]) = Alloc + 32;
//		*reinterpret_cast<uintptr_t*>(&Shellcode[26]) = Offsets::SetInfo_part;
//		strcpy_s(reinterpret_cast<char*>(&Shellcode[37]), 128, newName);
//		Mem::Write<BYTE[37 + 128]>(Alloc, Shellcode);
//		bInjected = true;
//	}
//	else
//		WriteProcessMemory(Mem::Process, reinterpret_cast<LPVOID>(Alloc + 37), newName, strlen(newName) + 1, 0);
//
//	Mem::CreateThread(Alloc);
//}
#define SIZE_SETNAME (37 + 128)

void RankReveal()
{
	if (!Mem::GetAlloc()) return;
	static LPVOID Alloc = reinterpret_cast<char*>(Mem::GetAlloc()) + SIZE_SETTAG + SIZE_SETNAME;
	Mem::CreateThread(Signatures::ServerRankRevealAll, Alloc);
}
#define SIZE_RANKREVEAL 12

void ClientCmd_Unrestricted(const char* command)
{
	if (!Mem::GetAlloc()) return;
	static uintptr_t Alloc = reinterpret_cast<uintptr_t>(Mem::GetAlloc()) + SIZE_SETTAG + SIZE_SETNAME + SIZE_RANKREVEAL;

	static bool bInjected = false;
	if (!bInjected)
	{
		BYTE Shellcode[15 + 128] = { 0x6A, 0x00,					// push   0x0
									0x68, 0x00, 0x00, 0x00, 0x00,	// push   (pointer to command)
									0xB8, 0x00, 0x00, 0x00, 0x00,	// mov    eax,(ClientCmd_Un)
									0xFF, 0xD0,						// call   eax 
									0xC3 };							// ret
																	// (command)

		*reinterpret_cast<uintptr_t*>(&Shellcode[3]) = Alloc + 15;
		*reinterpret_cast<uintptr_t*>(&Shellcode[8]) = Signatures::ClientCmd_Unrestricted;
		strcpy_s(reinterpret_cast<char*>(&Shellcode[15]), 128, command);
		Mem::Write<BYTE[15 + 128]>(Alloc, Shellcode);
		bInjected = true;
	}
	else
		WriteProcessMemory(Mem::Process, reinterpret_cast<LPVOID>(Alloc + 15), command, strlen(command) + 1, 0);

	Mem::CreateThread(Alloc);
}
#define SIZE_CLIENTCMD (15 + 128)

int GetModelIndex(const char* path)
{
	if (!Mem::GetAlloc()) return -1;
	static uintptr_t Alloc = reinterpret_cast<uintptr_t>(Mem::GetAlloc()) + SIZE_SETTAG + SIZE_SETNAME + SIZE_RANKREVEAL + SIZE_CLIENTCMD;

	static bool bInjected = false;
	if (!bInjected)
	{
		BYTE Shellcode[19 + 64] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00,	// mov	ecx,DWORD PTR ds:(modelInfoClient)
									0x68, 0x00, 0x00, 0x00, 0x00,		// push	(pointer to name)
									0x8B, 0x01,							// mov	eax,DWORD PTR [ecx]
									0x8B, 0x40, 0x08,					// mov	eax,DWORD PTR [eax+0x8]
									0xFF, 0xD0,							// call	eax
									0xC3 };								// ret
																		// (name)

		*reinterpret_cast<uintptr_t*>(&Shellcode[2]) = Signatures::ModelInfoClient;
		*reinterpret_cast<uintptr_t*>(&Shellcode[7]) = Alloc + 19;
		strcpy_s(reinterpret_cast<char*>(&Shellcode[19]), 64, path);
		Mem::Write<BYTE[19 + 64]>(Alloc, Shellcode);
		bInjected = true;
	}
	else
		WriteProcessMemory(Mem::Process, reinterpret_cast<LPVOID>(Alloc + 19), path, strlen(path) + 1, 0);

	return Mem::CreateThreadReturn(Alloc);
}
#define SIZE_GETMODELINDEX (19 + 64)

void R_LoadNamedSkys(const char* skyname)
{
	if (!Mem::GetAlloc()) return;
	static uintptr_t Alloc = reinterpret_cast<uintptr_t>(Mem::GetAlloc()) + SIZE_SETTAG + SIZE_SETNAME + SIZE_RANKREVEAL + SIZE_CLIENTCMD + SIZE_GETMODELINDEX;

	static bool bInjected = false;
	if (!bInjected)
	{
		BYTE Shellcode[13 + 48] = { 0xB9, 0x00, 0x00, 0x00, 0x00,	// mov	ecx, (skyname address)
									0xB8, 0x00, 0x00, 0x00, 0x00,	// mov	eax, (R_LoadNamedSkys address)
									0xFF, 0xD0,						// call	eax
									0xC3 };							// ret
																	// (skyname)

		*reinterpret_cast<uintptr_t*>(&Shellcode[1]) = Alloc + 13;
		*reinterpret_cast<uintptr_t*>(&Shellcode[6]) = Signatures::LoadNamedSkys;
		strcpy_s(reinterpret_cast<char*>(&Shellcode[13]), 48, skyname);
		Mem::Write<BYTE[13 + 48]>(Alloc, Shellcode);
		bInjected = true;
	}
	else
		WriteProcessMemory(Mem::Process, reinterpret_cast<LPVOID>(Alloc + 13), skyname, strlen(skyname) + 1, 0);

	Mem::CreateThread(Alloc);
}
#define SIZE_LOADNAMEDSKYS (13 + 48)

const size_t g_AllocSize = SIZE_SETTAG + SIZE_SETNAME + SIZE_RANKREVEAL + SIZE_CLIENTCMD + SIZE_GETMODELINDEX + SIZE_LOADNAMEDSKYS;