// Copyright 2021 Gamergenic.  See full copyright notice in MainModule.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


using UnrealBuildTool;
using EpicGames.Core;
using System.Collections.Generic;
using System.IO;

public class SpiceTarget : TargetRules
{
    public SpiceTarget(TargetInfo Target) : base(Target)
    {
        Log.TraceInformation("Instantiating SpiceTarget");

        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;

        // Assumes CSpice_Library has already been built.

        ExtraModuleNames.Add("Spice");
        ExtraModuleNames.Add("MaxQMain");
        CppStandard = CppStandardVersion.Cpp17;
    }
}
