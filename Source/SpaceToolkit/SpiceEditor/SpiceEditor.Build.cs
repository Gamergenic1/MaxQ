// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


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