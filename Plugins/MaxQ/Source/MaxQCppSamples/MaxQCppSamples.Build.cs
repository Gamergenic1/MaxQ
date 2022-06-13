// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


using UnrealBuildTool;

public class MaxQCppSamples : ModuleRules
{
	public MaxQCppSamples(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Spice" });

        PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "Json", "JsonUtilities", "UMG" });

        if (Target.bBuildEditor)
        {
            // Add stuff that's only needed when building the editor
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    // For the plugin manager, which is only used to get paths to plugin test content (kernels, etc)
                    "Projects"
                }
            );
        }
    }
}