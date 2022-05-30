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
    public const string RelativePathToCSpiceToolkit = "Source\\MaxQ\\CSpice_Library\\cspice\\";
    public const string RelativePathToCSpiceLib = "Source\\MaxQ\\CSpice_Library\\lib\\Win64\\cspice.lib";

    public SpiceTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "Spice" } );

        BuildCSpiceLib(this);
    }

    static public void BuildCSpiceLib(TargetRules targetRules)
    {
        string pathToCSpiceLib = CSpice_Library.CSpiceLibPath(new ReadOnlyTargetRules(targetRules));

        if (!File.Exists(pathToCSpiceLib))
        {
            // Note :  If the step fails, since it's a prebuild step, these rules will not be rebuilt.
            // So, don't cause a failure here, if you're iterating on these rules.
            // Also, changes to the invocation won't be seen until the following build!
            System.Console.WriteLine("Rebuilding cspice toolkit lib: {0}", pathToCSpiceLib);
            targetRules.PreBuildSteps.Add("$(ProjectDir)\\" + RelativePathToCSpiceToolkit + "makeall_ue.bat \"$(ProjectDir)\\" + RelativePathToCSpiceToolkit + "\"");
        }
        else
        {
            System.Console.WriteLine("cspice toolkit lib is up to date");
        }
    }
}
