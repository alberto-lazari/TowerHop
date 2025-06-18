using UnrealBuildTool;

public class TowerHop : ModuleRules
{
	public TowerHop(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"EnhancedInput",
			"InputCore",
			"UMG",
			"Slate",
			"SlateCore",
		});
	}
}
