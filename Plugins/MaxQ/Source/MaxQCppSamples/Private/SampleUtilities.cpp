// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SampleUtilities.h"
#include "Spice.h"

#if WITH_EDITOR
#include "Interfaces/IPluginManager.h"
#endif


DEFINE_LOG_CATEGORY(LogMaxQSamples);

namespace MaxQSamples
{
    const FString PluginName = TEXT("MaxQ");

    FString MaxQPluginInfo()
    {
        FString Info = PluginName;

    #if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetBaseDir(), TEXT("Documentation"));
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        FString AbsolutePluginFilePath = PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);

        Info = FString::Printf(TEXT("%s (Documentation:%s)"), *IPluginManager::Get().FindPlugin(*PluginName)->GetFriendlyName(), *AbsolutePluginFilePath);
    #endif

        return Info;
    }

    void AbsolutifyMaxQPath(FString& path)
    {
#if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetContentDir(), path);
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        FString PluginFilePath = PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);

        if (FPaths::FileExists(PluginFilePath) || FPaths::DirectoryExists(PluginFilePath))
        {
            path = PluginFilePath;
        }
#endif
    }

    FString MaxQPathAbsolutified(const FString& path)
    {
        FString AbsolutePath = path;
        AbsolutifyMaxQPath(AbsolutePath);
        return AbsolutePath;
    }

    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths)
    {
        TArray<FString> AbsolutePaths;

        for (auto path : paths)
        {
            AbsolutePaths.Add(MaxQPathAbsolutified(path));
        }

        return AbsolutePaths;
    }

    void Log(const FString& LogString, const FColor& Color)
    {
        UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, Color, LogString);
        }
    }

    void Log(const FString& LogString, ES_ResultCode ResultCode)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        }
        else
        {
            UE_LOG(LogMaxQSamples, Error, TEXT("%s"), *LogString);
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, LogString);
        }
    }
}


void USampleUtilities::GetMaxQPluginInfo(FString& Info)
{
    Info = MaxQSamples::MaxQPluginInfo();
}

void USampleUtilities::GetMaxQPathAbsolutified(const FString& path, FString& AbsolutePath)
{
    AbsolutePath = MaxQSamples::MaxQPathAbsolutified(path);
}

void USampleUtilities::GetMaxQPathsAbsolutified(const TArray<FString>& paths, TArray<FString>& AbsolutePaths)
{
    AbsolutePaths = MaxQSamples::MaxQPathsAbsolutified(paths);
}

bool USampleUtilities::LoadKernelList(const FString& ListName, const TArray<FString>& KernelFiles)
{
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    USpice::furnsh_list(ResultCode, ErrorMessage, MaxQSamples::MaxQPathsAbsolutified(KernelFiles));

    MaxQSamples::Log(FString::Printf(TEXT("Loaded %s Kernel files"), *ListName), ResultCode);
    if (ResultCode != ES_ResultCode::Success)
    {
        MaxQSamples::Log(FString::Printf(TEXT("Error: %s"), *ErrorMessage), FColor::Red);
    }

    return ResultCode == ES_ResultCode::Success;
}

void USampleUtilities::GetDefaultBasicKernels(TArray<FString>& BasicKernels)
{
    BasicKernels.Empty();

    // This is a "Leap Seconds" kernel
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));

    // This is a PCK kernel... Which contains data about planet orientations, etc
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/pck00010.tpc"));

    // This mass kernel matches what was used to generate de431, not de440...
    // ...which we load below...  But that's okay here
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/gm_de431.tpc"));

    // SPK Kernel, which is a trimmed down subset of de440 (32mb, instead of 114m)
    // (GitHub balks at anything over 100mb).
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/SPK/planets/de440s.bsp"));
}

void USampleUtilities::GetDefaultItrf93Kernels(TArray<FString>& Itrf93Kernels)
{
    Itrf93Kernels.Empty();

    // A "binary earth" PCK is a high precision measurement or prediction of the Earth's orientation
    // This kernel is predictive and a "low precision" version (it's still 14mb, so...)
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_200101_990628_predict.bpc"));

    // We need this FK kernel to establish the "ITRF" reference frame, which is affixed to earth.
    // The data in the PCK file above is relative to ITRF, so we need it.
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_fixed.tf"));

    // This text file FK kernel establishes earth-fixed topocentric ROTATION offsets for 
    // Deep Space Space stations (antennas for communicating with deep space).
    // It defines reference frames only (rotation orientation), as rotation offsets, which are "class 4" FK frames.
    // More into: https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
    // It also established the Naif Id codes for the stations, like so:
    // NAIF_BODY_NAME += 'DSS-14'
    // NAIF_BODY_CODE += 399014
    // More info: https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/FK/stations/earth_topo_201023.tf"));

    // This binary SPK kernel is where the fixed POSITION offsets for the DSN stations come from.
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/SPK/stations/earthstns_itrf93_201023.bsp"));
}

void USampleUtilities::GetDefaultInsightMissionKernels(TArray<FString>& InsightMissionKernels)
{
    InsightMissionKernels.Empty();

    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/FK/insight_v05.tf"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_ls_ops181206_iau2000_v1.bsp"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/mar097s.bsp"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_struct_v01.bsp"));
}
