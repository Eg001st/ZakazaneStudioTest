// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ZakazaneKulkiEditorTarget : TargetRules
{
	public ZakazaneKulkiEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ZakazaneKulki" } );
	}
}
