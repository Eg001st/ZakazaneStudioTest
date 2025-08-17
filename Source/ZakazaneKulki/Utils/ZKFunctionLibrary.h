// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types.h"
#include "GameplayTagContainer.h"

#include "ZKFunctionLibrary.generated.h"

class UZKWidgetActivatableBase;

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API UZKFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "ZK")
    static TSoftClassPtr<UZKWidgetActivatableBase> GetFrontendSoftWidgetClassByTag(
        UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InTag);

    UFUNCTION(BlueprintPure, Category = "ZK")
    static TSoftObjectPtr<UWorld> GetLevelByName(FName InName);

    UFUNCTION(BlueprintPure, Category = "ZK")
    static UMaterialInstance* GeMaterialInstanceByEnemyType(EEnemyType InType);
};
