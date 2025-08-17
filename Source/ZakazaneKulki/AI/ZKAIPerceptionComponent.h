// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ZKAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class ZAKAZANEKULKI_API UZKAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

	AActor* GetClosestActor() const;
	
};
