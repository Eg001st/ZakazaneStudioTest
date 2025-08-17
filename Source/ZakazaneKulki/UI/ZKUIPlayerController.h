// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZKUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZAKAZANEKULKI_API AZKUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void OnPossess(APawn* PawnToPossess) override;

protected:

	const FName DefaultCameraTag{"Default"};
};
