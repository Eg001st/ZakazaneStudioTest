// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "GameplayTagContainer.h"

#include "ZKAsyncActionPushSoftWidget.generated.h"

class UZKWidgetActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UZKWidgetActivatableBase*, PushedWidget);

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API UZKAsyncActionPushSoftWidget : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject",
                                     BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Widget Stack"))
    static UZKAsyncActionPushSoftWidget* PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPC,
        TSoftClassPtr<UZKWidgetActivatableBase> InSoftWidgetClass,
        UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget = true);

    virtual void Activate() override;

    UPROPERTY(BlueprintAssignable)
    FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

    UPROPERTY(BlueprintAssignable)
    FOnPushSoftWidgetDelegate AfterPush;

private:

    TWeakObjectPtr<UWorld> CachedOwningWorld;
    TWeakObjectPtr<APlayerController> CachedOwningPC;
    TSoftClassPtr<UZKWidgetActivatableBase> CachedSoftWidgetClass;
    FGameplayTag CachedWidgetStackTag;
    bool bCachedFocusOnNewlyPushedWidget = false;
};
