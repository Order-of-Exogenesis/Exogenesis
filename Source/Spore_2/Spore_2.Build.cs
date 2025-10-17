// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Spore_2 : ModuleRules
{
	public Spore_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "ProceduralMeshComponent" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
