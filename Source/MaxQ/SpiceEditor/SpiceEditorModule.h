// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class SPICEEDITOR_API FSpiceEditorModule : public IModuleInterface
{
public:
	static inline FSpiceEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FSpiceEditorModule>("SpiceEditor");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("SpiceEditor");
	}
};

