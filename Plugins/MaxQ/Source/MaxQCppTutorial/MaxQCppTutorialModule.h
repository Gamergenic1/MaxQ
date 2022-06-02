// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class MAXQCPPTUTORIAL_API FMaxQCppTutorialModule : public IModuleInterface
{
public:
	static inline FMaxQCppTutorialModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FMaxQCppTutorialModule>("MaxQCppTutorial");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("MaxQCppTutorial");
	}
};

