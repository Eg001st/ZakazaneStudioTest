// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types.h"
#include "ZKAsyncActionPushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EConfirmScreenButtonType, ClickedButtonType);


/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API UZKAsyncActionPushConfirmScreen : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject",
                                     BlueprintInternalUseOnly = "true", DisplayName = "ShowConfirmationScreen"))
    static UZKAsyncActionPushConfirmScreen* PushConfirmScreen(
        const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage);

    virtual void Activate() override;

    UPROPERTY(BlueprintAssignable)
    FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:
    TWeakObjectPtr<UWorld> CachedWorld;
    EConfirmScreenType CachedScreenType;
    FText CachedScreenTitle;
    FText CachedScreenMessage;
};
