// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/ZKWidgetActivatableBase.h"
#include "Types.h"
#include "ZKWidgetConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;


UCLASS()
class ZAKAZANEKULKI_API UZKConfirmScreenObject : public UObject
{
    GENERATED_BODY()
public:

    static UZKConfirmScreenObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage);
    static UZKConfirmScreenObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage);
    static UZKConfirmScreenObject* CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage);

    UPROPERTY(Transient)
    FText ScreenTitle;

    UPROPERTY(Transient)
    FText ScreenMessage;

    UPROPERTY(Transient)
    TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};

/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class ZAKAZANEKULKI_API UZKWidgetConfirmScreen : public UZKWidgetActivatableBase
{
    GENERATED_BODY()

public:
    // Gets called outside of the class when this widget is constructed and before it's pushed to the modal stack
    void InitConfirmScreen(UZKConfirmScreenObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons;
};
