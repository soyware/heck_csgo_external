#pragma once

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#include <SDKDDKVer.h>

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
using namespace std::chrono_literals;
#include <TlHelp32.h>
#include <Psapi.h>
#include <conio.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <vector>
#include <unordered_map>