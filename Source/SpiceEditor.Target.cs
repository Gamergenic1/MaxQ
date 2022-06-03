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

// Note:
// On MacOS, Xcode project generation may fail if you do not have an ios sdk installed.
// The xcode project can be generated to exclude ios (macos only) like so:
// sh "/Users/Shared/Epic Games/UE_5.0/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" -project="/Users/username/Documents/GitHub/MaxQ/Spice.uproject" -game -Platforms="Mac"
// (of course, change the username and check the install path...)

public class SpiceEditorTarget : TargetRules
{
    public SpiceEditorTarget(TargetInfo Target) : base(Target)
    {
        Log.TraceInformation("Instantiating SpiceEditorTarget");

        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        bUseFastPDBLinking = false;
        bPublicSymbolsByDefault = true;  // <- Forced to true on Windows anyways
        WindowsPlatform.bStripUnreferencedSymbols = false;

        ExtraModuleNames.Add("Spice");
        ExtraModuleNames.Add("MaxQMain");

        UpdateDocs(Target);
        BuildCSpiceLib(this);
    }

    public void UpdateDocs(TargetInfo Target)
    {
        Log.TraceInformation("Setting PostBuildSteps");

        // Only invoke the windows batch file on windows...
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PostBuildSteps.Add("\"$(ProjectDir)\\updateplugindocs.bat\" \"$(ProjectDir)\"");
        }
    }

    // Note that if you change this method, other TargetRules that call it will not get the changes unless they change as well.
    // If you're working on the editor (SpiceEditorTarget) and change this method, your changes won't be effective until
    // SpiceEditorChanges as well.
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

        string BuildStep = CSpiceLibBuildStep(readOnlyTargetRules);
        string PreBuildStep = "";

        if (targetRules.Platform == UnrealTargetPlatform.Mac)
        {
            PreBuildStep += "csh ";
        }

        PreBuildStep += "$(ProjectDir)\\" + BuildStep + " \"$(ProjectDir)\\" + RelativePathToCSpiceToolkit + "\"";

        // Alternative to Path.Combine, but ensures the path inside $(ProjectDir) is corrected
        PreBuildStep = PreBuildStep.Replace('/', Path.DirectorySeparatorChar).Replace('\\', Path.DirectorySeparatorChar);

        targetRules.PreBuildSteps.Add(PreBuildStep);
    }

    // ------------------------------------------------------------------------
    // Duplication from CSpice_Library.Build.cs
    // Packaged builds disallow a dependency...
    // TODO: Solve this without code duplication

    // Spice and SpiceEditor BuiltTargetRules need access, so these must be constant or static.
    public const string RelativePathToCSpiceModule = "Plugins/MaxQ/Source/ThirdParty/CSpice_Library/";
    public const string RelativePathToCSpiceToolkit = RelativePathToCSpiceModule + "cspice/";
    public const string RelativePathToCSpiceLibraries = RelativePathToCSpiceModule + "lib/";

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
            throw new BuildException(Err);
        }
    }
}
