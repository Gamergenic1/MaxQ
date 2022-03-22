// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once


#define UE_BUILD_DEBUG 1
#define WITH_EDITOR 0
#define WITH_ENGINE 0
#define WITH_UNREAL_DEVELOPER_TOOLS 0
#define WITH_PLUGIN_SUPPORT 0
#define IS_MONOLITHIC 1
#define IS_PROGRAM 1
#define WITH_SERVER_CODE 0

#define UBT_COMPILED_PLATFORM Windows
#define PLATFORM_WINDOWS 1

#define ENGINE_API __declspec( dllimport )
#define CORE_API __declspec( dllimport )
#define COREUOBJECT_API __declspec( dllimport )

#define _AMD64_

// UE5 EA declares a local variable named "X64" in two header files, which collides on the X64 def.
#if defined(X64)
#undef X64
#define X64_UNDEFINED
#endif

#include "CoreMinimal.h"

#if defined(X64_UNDEFINED)
#undef X64_UNDEFINED
#define X64
#endif

#include "Modules/ModuleInterface.h"

// C:\Program Files\Epic Games\UE_5.0EA\Engine\Source\Runtime\CoreUObject\Public
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "UObject/Class.h"
#include "Kismet/BlueprintFunctionLibrary.h"