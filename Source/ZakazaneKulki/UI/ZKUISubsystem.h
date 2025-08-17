// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types.h"
#include "ZKUISubsystem.generated.h"

class UZKCommonButtonBase;
class UZKPrimaryLayoutWidget;
class UZKWidgetActivatableBase;

struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnButtonDescriptionTextUpdateDelegate, UZKCommonButtonBase*, BroadcastingButton, const FText&, DescriptionText);

UCLASS()
class ZAKAZANEKULKI_API UZKUISubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UZKUISubsystem* Get(const UObject* WorldContextObject);

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintCallable)
    void RegisterPrimaryLayoutWidget(UZKPrimaryLayoutWidget* InCreatedWidget);


    void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UZKWidgetActivatableBase> InSoftWidgetClass,
        TFunction<void(EAsyncPushWidgetState, UZKWidgetActivatableBase*)> AsyncPushStateCallback);

    void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMessage,
        TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

    UPROPERTY(BlueprintAssignable)
    FOnButtonDescriptionTextUpdateDelegate OnButtonDescriptionTextUpdateDelegate;

private:
    UPROPERTY(Transient)
    TObjectPtr<UZKPrimaryLayoutWidget> PrimaryLayout;
};
