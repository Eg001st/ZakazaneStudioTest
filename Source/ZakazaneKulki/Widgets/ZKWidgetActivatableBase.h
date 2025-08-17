// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ZKWidgetActivatableBase.generated.h"

 
class AZKUIPlayerController;

 /**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class ZAKAZANEKULKI_API UZKWidgetActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
    UFUNCTION(BlueprintPure)
    AZKUIPlayerController* GetOwningUIPlayerController();

private:

	TWeakObjectPtr<AZKUIPlayerController> CachedOwningPC;
};
