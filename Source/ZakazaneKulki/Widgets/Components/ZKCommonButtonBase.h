// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ZKCommonButtonBase.generated.h"

class UCommonTextBlock;
/**
 *
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class ZAKAZANEKULKI_API UZKCommonButtonBase : public UCommonButtonBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetButtonText(FText InText);

private:
    virtual void NativePreConstruct() override;
    virtual void NativeOnCurrentTextStyleChanged() override;
    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZKButton", meta = (AllowPrivateAccess = "true"))
    FText ButtonDisplayText;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZKButton", meta = (AllowPrivateAccess = "true"))
    bool bUserUpperCaseForButtonText{false};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZKButton", meta = (AllowPrivateAccess = "true"))
    FText ButtonDescriptionText;
};
