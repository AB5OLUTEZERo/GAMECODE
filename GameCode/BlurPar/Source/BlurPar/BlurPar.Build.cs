// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlurPar : ModuleRules
{
	public BlurPar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Networking", "Sockets" ,"GameplayAbilities","GameplayTags","GameplayTasks"});
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore",
            "Paper2D",
            "AIModule",
            "NavigationSystem",
            "UMG"
        });
    }
}
