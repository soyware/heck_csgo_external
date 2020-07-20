#pragma once

#define M_PI_F			( static_cast<float>(3.1415926535897932384626433832795) )
#define RAD2DEG(rad)	( static_cast<float>(rad) * static_cast<float>(180.f / M_PI_F) )
#define DEG2RAD(deg)	( static_cast<float>(deg) * static_cast<float>(M_PI_F / 180.f) )

//inline void clrHexToFloat(const uint32_t dw, float fl[])
//{
//	fl[0] = ((dw & 0xFF000000) >> 24) / 255.f;
//	fl[1] = ((dw & 0x00FF0000) >> 16) / 255.f;
//	fl[2] = ((dw & 0x0000FF00) >> 8) / 255.f;
//	fl[3] = (dw & 0x000000FF) / 255.f;
//}

extern void ErrorExit(const char* szErr);

inline void GetKeyValue(const char* in, const char* key, int& value)
{
	const char* subs = strstr(in, key) + strlen(key);
	if (subs)
		sscanf_s(subs, "%*[^0-9]%d", &value);
	else
	{
		char err[64] = "Failed to get a key-value ";
		strcat_s(err, sizeof(err), key);
		ErrorExit(err);
	}
}

inline void GetKeyValue(const char* in, const char* key, float& value)
{
	const char* subs = strstr(in, key) + strlen(key);
	if (subs)
		sscanf_s(subs, "%*[^0-9]%f", &value);
	else
	{
		char err[64] = "Failed to get a key-value ";
		strcat_s(err, sizeof(err), key);
		ErrorExit(err);
	}
}

inline float HexToFloat(uint32_t hex)
{
	return *reinterpret_cast<float*>(&hex);
}

inline uint32_t FloatToHex(float fl)
{
	return *reinterpret_cast<uint32_t*>(&fl);
}

struct CUtlVector
{
	uintptr_t m_pMemory; //0x0000 
	int m_nAllocationCount; //0x0004 
	int m_nGrowSize; //0x0008 
	int m_Size; //0x000C 
	uintptr_t m_pElements; //0x0010 
}; //Size=0x0014

BOOL ChangeVolume(float flVolume)
{
	HRESULT hr = NULL;
	IMMDeviceEnumerator* deviceEnumerator = nullptr;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	if (FAILED(hr))
		return FALSE;

	IMMDevice* defaultDevice = nullptr;
	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &defaultDevice);
	deviceEnumerator->Release();
	if (FAILED(hr))
		return FALSE;

	IAudioClient* audioClient = nullptr;
	hr = defaultDevice->Activate(__uuidof(IAudioClient),
		CLSCTX_INPROC_SERVER, NULL, (void**)&audioClient);
	defaultDevice->Release();
	if (FAILED(hr))
		return FALSE;

	WAVEFORMATEX* pwfx = nullptr;
	hr = audioClient->GetMixFormat(&pwfx);
	if (FAILED(hr))
		return FALSE;

	hr = audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 0, 0, pwfx, NULL);
	if (FAILED(hr))
		return FALSE;

	ISimpleAudioVolume* audioVolume = nullptr;
	hr = audioClient->GetService(__uuidof(ISimpleAudioVolume), (void**)&audioVolume);
	audioClient->Release();
	if (FAILED(hr))
		return FALSE;

	hr = audioVolume->SetMasterVolume(flVolume, NULL);
	audioVolume->Release();

	return SUCCEEDED(hr);
}

inline bool GetVKeyName(int vkey, char* buffer, int buffersize)
{
	switch (vkey)
	{
	case VK_LBUTTON:
		strcpy_s(buffer, buffersize, "Left mouse button");
		return true;
	case VK_RBUTTON:
		strcpy_s(buffer, buffersize, "Right mouse button");
		return true;
	case VK_MBUTTON:
		strcpy_s(buffer, buffersize, "Middle mouse button");
		return true;
	case VK_XBUTTON1:
		strcpy_s(buffer, buffersize, "Forth mouse button");
		return true;
	case VK_XBUTTON2:
		strcpy_s(buffer, buffersize, "Fifth mouse button");
		return true;
	}

	UINT vsc = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	if (!vsc)
	{
		std::cout << "Warning: MapVirtualKey returned 0\n";
		return false;
	}

	int res = GetKeyNameText((vsc << 16), buffer, buffersize);
	if (!res)
	{
		std::cout << "Warning: GetKeyNameText returned 0\n";
		return false;
	}

	return true;
}

#define CHUNKTONETVAR(chunk, var) var = *reinterpret_cast<decltype(var)*>(reinterpret_cast<uintptr_t>(chunk) + NetVars::var)