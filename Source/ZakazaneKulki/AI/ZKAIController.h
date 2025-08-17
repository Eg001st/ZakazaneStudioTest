// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZKAIController.generated.h"


class UZKAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class ZAKAZANEKULKI_API AZKAIController : public AAIController
{
	GENERATED_BODY()

public:
    AZKAIController();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UZKAIPerceptionComponent> ZKAIPerceptionComponent;
};
