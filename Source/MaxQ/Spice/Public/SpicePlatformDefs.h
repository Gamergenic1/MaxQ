// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

// Set the working directory locally inside furnsh?
// This allows meta-kernels to load files in the same directory.
#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#define SET_WORKING_DIRECTORY_IN_FURNSH 1
#define StackAlloc _alloca
#define SpiceStringCopy(a,b) strcpy_s(a,b)
#define SpiceStringCopy3(a,b,c) strcpy_s(a,b,c)
#define SpiceStringCopyN strncpy_s
#define SpiceStringConcat strcat_s
#define SpiceStringCompare _stricmp
#define SpiceStringLengthN strnlen_s
#define SPICE_MAX_PATH WINDOWS_MAX_PATH
#define SpiceStaticPartialTemplate static
#elif PLATFORM_MAC
#include <string.h>
#define StackAlloc alloca
#define SpiceStringCopy(a,b) strlcpy(a,b, sizeof(a))
#define SpiceStringCopy3(a,b,c) strlcpy(a,c,b)
#define SpiceStringCopyN strncpy
#define SpiceStringConcat strcat
#define SpiceStringCompare strcmp
#define SpiceStringLengthN strnlen
#define SPICE_MAX_PATH 255
#define PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
#define PRAGMA_POP_PLATFORM_DEFAULT_PACKING
#define SpiceStaticPartialTemplate 
#endif
