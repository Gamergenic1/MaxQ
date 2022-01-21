// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


using System.IO;
using UnrealBuildTool;

public class CSpice_Library : ModuleRules
{
    public const string RelativePathToCSpiceToolkit = "Source\\MaxQ\\CSpice_Library\\cspice\\";
    public const string RelativePathToCSpiceLib = "Source\\MaxQ\\CSpice_Library\\lib\\Win64\\cspice.lib";

    public CSpice_Library(ReadOnlyTargetRules Target) : base(Target)
	{
        bAddDefaultIncludePaths = false;

        string cspiceDir = Path.Combine(ModuleDirectory, "cspice/");
        string includeDir = Path.Combine(cspiceDir, "include/");
        string libFile = CSpiceLibPath(Target);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("MSDOS");
            PublicDefinitions.Add("OMIT_BLANK_CC");
            PublicDefinitions.Add("NON_ANSI_STDIO");
        }
        /*
        Add conditionals for any other platforms you want to support via recompilation here:
        else if (Target.Platform == UnrealTargetPlatform.XXXX)
        {
            // either include a naif pre-build lib, or allow it to recompile
            // (for C spice platforms, see: https://naif.jpl.nasa.gov/naif/toolkit_C.html)
        }
        */
        else
        { 
            string Err = string.Format("cspice SDK not found for platform {0}", Target.Platform.ToString());
            System.Console.WriteLine(Err);
            throw new BuildException(Err);
        }

        Type = ModuleRules.ModuleType.External;
        PrecompileForTargets = PrecompileTargetsType.Any;
        PublicPreBuildLibraries.Add(libFile);
        
        if (!Directory.Exists(includeDir))
        {
            string Err = string.Format("cspice headers not found at {0}.  A copy of cspice/include must be present", includeDir);
            System.Console.WriteLine(Err);
            throw new BuildException(Err);
        }

        PublicIncludePaths.Add(includeDir);
    }

    static public string CSpiceLibPath(ReadOnlyTargetRules targetRules)
    {
        string relativePathToCSpiceLib = "Source\\MaxQ\\CSpice_Library\\lib\\" + targetRules.Platform.ToString() + "\\cspice.lib";

        return Path.Combine(targetRules.ProjectFile.Directory.FullName, relativePathToCSpiceLib);
    }
}
