// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


using UnrealBuildTool;

public class SpiceEditor : ModuleRules
{
    public SpiceEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
                    "Core", "CoreUObject", "Engine",
                    "InputBlueprintNodes",
                    "InputCore",
                    "KismetCompiler",
                    "PropertyEditor",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "CSpice_Library"});
    }
}