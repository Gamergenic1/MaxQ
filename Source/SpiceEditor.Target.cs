// Copyright 2021 Gamergenic.  See full copyright notice in MainModule.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// This is a sample application demonstrating usage of Module 'Spice',
// an implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


using UnrealBuildTool;
using EpicGames.Core;


public class SpiceEditorTarget : TargetRules
{
    public SpiceEditorTarget( TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "Spice", "SpiceEditor", "SpiceUncooked" } );
        
        bUseFastPDBLinking = false;
        bPublicSymbolsByDefault = true;  // <- Forced to true on Windows anyways
        WindowsPlatform.bStripUnreferencedSymbols = false;

        SpiceTarget.BuildCSpiceLib(this);
    }
}
