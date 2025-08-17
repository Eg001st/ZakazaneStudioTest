// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "Types.h"
#include "ZKDeveloperSettings.generated.h"

class UZKWidgetActivatableBase;
class UMaterialInstanceDynamic;


/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "ZK Settings"))
class ZAKAZANEKULKI_API UZKDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(Config, EditAnywhere, Category = "ZK|UI|WidgetReference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UZKWidgetActivatableBase>> WidgetMap;

	UPROPERTY(Config, EditAnywhere, Category = "ZK|Maps")
    TMap<FName, TSoftObjectPtr<UWorld>> Maps;

	UPROPERTY(EditAnywhere, Category = "ZK")
    TMap<EEnemyType, TObjectPtr<UMaterialInstance>> MaterialMapping;
};
