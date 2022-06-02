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
        ExtraModuleNames.AddRange( new string[] { "Spice", "MaxQMain" } );

        BuildCSpiceLib(this);
    }

    static public void BuildCSpiceLib(TargetRules targetRules)
    {
        Log.TraceInformation("Setting PreBuildSteps");

        // Q: Can the libraries pre-built and released by naif be used?
        //    Q: On Mac?
        //    A: Yes
        //    Q: On Windows?
        //    A: No, due to a C-Runtime incompatibility. For more info, see:
        //        https://gamedevtricks.com/post/third-party-libs-2#the-problem-with-this-solution
        // Q: Can the CSPICE library be updated?
        //    Yes, delete windows (to trigger a rebuild) and update other platform libraries (from naif) in CSpice_Library/lib 

        ReadOnlyTargetRules readOnlyTargetRules = new ReadOnlyTargetRules(targetRules);
        
        string BuildStep = CSpice_Library.CSpiceLibBuildStep(readOnlyTargetRules);
        string PreBuildStep = "$(ProjectDir)\\" + BuildStep + " \"$(ProjectDir)\\" + CSpice_Library.RelativePathToCSpiceToolkit + "\"";

        PreBuildStep = PreBuildStep.Replace('/', Path.DirectorySeparatorChar).Replace('\\', Path.DirectorySeparatorChar);
        
        targetRules.PreBuildSteps.Add(PreBuildStep);
    }
}