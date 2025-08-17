// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/ZKWidgetActivatableBase.h"
#include "ZKPauseWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class ZAKAZANEKULKI_API UZKPauseWidget : public UZKWidgetActivatableBase
{
	GENERATED_BODY()
public:

    virtual bool Initialize() override;

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UButton> Button_Continue;

private:

	UFUNCTION()
    void OnClearPause();
};
