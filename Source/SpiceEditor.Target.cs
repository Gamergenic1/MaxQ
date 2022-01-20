// Copyright 2021 Gamergenic.  See full copyright notice in MainModule.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


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
