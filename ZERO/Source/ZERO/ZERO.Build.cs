// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZERO : ModuleRules
{
	public ZERO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "Paper2D",
            "AIModule",
            "NavigationSystem",
            "UMG"
        });
    }
}
