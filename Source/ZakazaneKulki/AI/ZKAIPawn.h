// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pawn/ZKBasePawn.h"
#include "Types.h"
#include "ZKAIPawn.generated.h"

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API AZKAIPawn : public AZKBasePawn
{
    GENERATED_BODY()

public:
    AZKAIPawn(const FObjectInitializer& ObjectInitializer);


    void SetColor();
    void InitAttributes(const FVector& SpawnCenter, const FVector& SpawnLocation, EEnemyType InEnemyType);

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZK|Settings")
    EEnemyType EnemyType{EEnemyType::Unknown};


};
