// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Shooting_Range : ModuleRules
{
	public Shooting_Range(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.Add("Shooting_Range");
		PrivateIncludePaths.Add("Shooting_Range/Bullet");
		PrivateIncludePaths.Add("Shooting_Range/GameMode");
		PrivateIncludePaths.Add("Shooting_Range/UI");
		PrivateIncludePaths.Add("Shooting_Range/Weapon");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
