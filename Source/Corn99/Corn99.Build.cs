// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Corn99 : ModuleRules
{
	public Corn99(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
