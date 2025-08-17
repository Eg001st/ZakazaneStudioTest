// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Utils/ZKFunctionLibrary.h"

#include "DevSettings/ZKDeveloperSettings.h"

TSoftClassPtr<UZKWidgetActivatableBase> UZKFunctionLibrary::GetFrontendSoftWidgetClassByTag(
    UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InTag)
{
    const auto ZKDeveloperSettings = GetDefault<UZKDeveloperSettings>();

    checkf(ZKDeveloperSettings->WidgetMap.Contains(InTag), TEXT("Could not find the widget with the tag %s"), *InTag.ToString());

    return ZKDeveloperSettings->WidgetMap.FindRef(InTag);
}

TSoftObjectPtr<UWorld> UZKFunctionLibrary::GetLevelByName(FName InName)
{
    const auto ZKDeveloperSettings = GetDefault<UZKDeveloperSettings>();

    checkf(ZKDeveloperSettings->Maps.Contains(InName), TEXT("Could not find the map under the name %s"), *InName.ToString());

    return ZKDeveloperSettings->Maps.FindRef(InName);
}

UMaterialInstance* UZKFunctionLibrary::GeMaterialInstanceByEnemyType(EEnemyType InType)
{
    const auto ZKDeveloperSettings = GetDefault<UZKDeveloperSettings>();
    check(ZKDeveloperSettings->MaterialMapping.Contains(InType));

    return ZKDeveloperSettings->MaterialMapping.FindRef(InType);
}
