// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "TutorialUtilities.h"

#if WITH_EDITOR
#include "Interfaces/IPluginManager.h"
#endif


DEFINE_LOG_CATEGORY(LogMaxQTutorials);

namespace MaxQTutorial
{
    FString MaxQPluginInfo()
    {
        FString PluginName = TEXT("MaxQ");
        FString Info = PluginName;

    #if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetBaseDir(), TEXT("Documentation"));
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        FString AbsolutePluginFilePath = PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);

        Info = FString::Printf(TEXT("%s (Documentation:%s)"), *IPluginManager::Get().FindPlugin(*PluginName)->GetFriendlyName(), *AbsolutePluginFilePath);
    #endif

        return Info;
    }

    void Log(const FString& LogString, const FColor& Color)
    {
        UE_LOG(LogMaxQTutorials, Log, TEXT("%s"), *LogString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, Color, LogString);
        }
    }

    void Log(const FString& LogString, ES_ResultCode ResultCode)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            UE_LOG(LogMaxQTutorials, Log, TEXT("%s"), *LogString);
        }
        else
        {
            UE_LOG(LogMaxQTutorials, Error, TEXT("%s"), *LogString);
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, LogString);
        }
    }
}


void UTutorialUtilities::GetMaxQPluginInfo(FString& Info)
{
    Info = MaxQTutorial::MaxQPluginInfo();
}
