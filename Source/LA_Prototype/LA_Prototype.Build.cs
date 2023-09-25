// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LA_Prototype : ModuleRules
{
	public LA_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
