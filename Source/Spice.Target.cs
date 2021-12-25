// Copyright 2021 Gamergenic.  See full copyright notice in MainModule.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// This is a sample application demonstrating usage of Module 'Spice',
// an implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/


using UnrealBuildTool;
using System.Collections.Generic;

public class SpiceTarget : TargetRules
{
	public SpiceTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Spice" } );

		SpiceEditorTarget.BuildCSpiceLib(this);
	}
}
