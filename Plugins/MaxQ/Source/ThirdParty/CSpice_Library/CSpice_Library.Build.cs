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
    public CSpice_Library(ReadOnlyTargetRules Target) : base(Target)
    {
        bAddDefaultIncludePaths = false;

        string cspiceDir = Path.Combine(ModuleDirectory, "cspice/");
        string includeDir = Path.Combine(cspiceDir, "include/");
        string libDir = Path.Combine(ModuleDirectory, "lib", Target.Platform.ToString());
        if(Target.Platform == UnrealTargetPlatform.Win64)
        {

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
        }

        string libName;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            libName = "cspice.lib";
            PublicDefinitions.Add("MSDOS=1");
            PublicDefinitions.Add("OMIT_BLANK_CC=1");
            PublicDefinitions.Add("NON_ANSI_STDIO=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            libName = "cspice.lib";
            PublicDefinitions.Add("CSPICE_MAC_OSX_INTEL_64BIT_GCC=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            libName = "libcspice.lib";
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
            throw new BuildException(Err);
        }
        string libFile = Path.Combine(libDir, libName);

        Type = ModuleRules.ModuleType.External;
        PrecompileForTargets = PrecompileTargetsType.Any;
        PublicPreBuildLibraries.Add(libFile);

        if (!Directory.Exists(includeDir))
        {
            string Err = string.Format("cspice headers not found at {0}.  A copy of cspice/include must be present", includeDir);
            throw new BuildException(Err);
        }

        PublicIncludePaths.Add(includeDir);
    }
}
