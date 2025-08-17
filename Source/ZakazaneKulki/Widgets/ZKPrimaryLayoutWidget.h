// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "ZKPrimaryLayoutWidget.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class ZAKAZANEKULKI_API UZKPrimaryLayoutWidget : public UCommonUserWidget
{
    GENERATED_BODY()

public:
    TObjectPtr<UCommonActivatableWidgetContainerBase> FindWidgetStackByTag(const FGameplayTag& InTag);

protected:
    UFUNCTION(BlueprintCallable)
    void RegisterWidgetStack(UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);

private:
    UPROPERTY(Transient) 
    TMap <FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
