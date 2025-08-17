// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ZakazaneKulkiTarget : TargetRules
{
	public ZakazaneKulkiTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ZakazaneKulki" } );
	}
}
