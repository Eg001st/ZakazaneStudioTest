// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZKGameHUD.generated.h"

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API AZKGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ZK|UI")
    TSubclassOf<UUserWidget> PlayerPawnHUDWidgetClass;

    UFUNCTION(BlueprintImplementableEvent)
    void OnPause(bool IsPauseSet);

private:

    void OnPauseStateChanged(bool IsPauseSet);
};
