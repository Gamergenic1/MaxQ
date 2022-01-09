// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


using UnrealBuildTool;

public class SpiceUncooked : ModuleRules
{
    public SpiceUncooked(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                    "BlueprintGraph",
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "EnhancedInput",
                    "GraphEditor",
                    "InputCore",
                    "KismetCompiler",
                    "PropertyEditor",
                    "Slate",
                    "SlateCore",
                    "UnrealEd"
            });

            PrivateDependencyModuleNames.AddRange(new string[] { "CSpice_Library", "Spice" });
    }
}