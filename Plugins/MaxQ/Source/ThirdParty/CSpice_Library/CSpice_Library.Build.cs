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
    // Spice and SpiceEditor BuiltTargetRules need access, so these must be constant or static.
    public const string RelativePathToCSpiceModule = "Plugins/MaxQ/Source/ThirdParty/CSpice_Library/";
    public const string RelativePathToCSpiceToolkit = RelativePathToCSpiceModule + "cspice/";
    public const string RelativePathToCSpiceLibraries = RelativePathToCSpiceModule + "lib/";

    public CSpice_Library(ReadOnlyTargetRules Target) : base(Target)
	{
        bAddDefaultIncludePaths = false;

        string cspiceDir = Path.Combine(ModuleDirectory, "cspice/");
        string includeDir = Path.Combine(cspiceDir, "include/");
        string libFile = CSpiceLibPath(Target);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("MSDOS=1");
            PublicDefinitions.Add("OMIT_BLANK_CC=1");
            PublicDefinitions.Add("NON_ANSI_STDIO=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDefinitions.Add("CSPICE_MAC_OSX_INTEL_64BIT_GCC=1");
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


    // Spice and SpiceEditor BuiltTargetRules need access, so this must be static.
    static public string CSpiceLibPath(ReadOnlyTargetRules targetRules)
    {
        string libName = "/cspice.lib";
        
        if (targetRules.Platform == UnrealTargetPlatform.Mac)
        {
            libName = "/cspice.a";
        }
        
        string relativePathToCSpiceLib = RelativePathToCSpiceLibraries + targetRules.Platform.ToString() + libName;

        return Path.Combine(targetRules.ProjectFile.Directory.FullName, relativePathToCSpiceLib);
    }


    // Spice and SpiceEditor BuiltTargetRules need access, so this must be static.
    static public string CSpiceLibBuildStep(ReadOnlyTargetRules targetRules)
    {
        if (targetRules.Platform == UnrealTargetPlatform.Win64)
        {
            return RelativePathToCSpiceToolkit + "makeall_ue.bat";
        }
        else if (targetRules.Platform == UnrealTargetPlatform.Mac)
        {
            return RelativePathToCSpiceToolkit + "makeall_ue.csh";
        }
        else
        {
            string Err = string.Format("cspice SDK not found for platform {0}", targetRules.Platform.ToString());

            return Err;

            /*  
            throw new BuildException(Err);
            */
            
        }
    }
}
