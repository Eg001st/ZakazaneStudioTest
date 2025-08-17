// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZKPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API AZKPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    AZKPlayerController();

protected:
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "ZK|Input")
    TObjectPtr<UInputMappingContext> InputMappingUI;

    UPROPERTY(EditDefaultsOnly, Category = "ZK|Input")
    TObjectPtr<UInputAction> PauseGameAction;

    void OnPauseGame(const FInputActionValue& InputActionValue);
};
