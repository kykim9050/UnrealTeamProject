// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal5_Portfolio : ModuleRules
{
	public Unreal5_Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, ""));
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule" , "EnhancedInput", "Paper2D", "MotionWarping", "Slate", "SlateCore", "MovieScene", "LevelSequence", "UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
