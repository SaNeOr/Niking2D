#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Niking2D/Core/Log.h"

#include "Niking2D/Debug/Instrumentor.h"

#ifdef N2_PLATFORM_WINDOWS
	#include <Windows.h>
#endif