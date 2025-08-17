// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types.h"
#include "ZKGameMode.generated.h"

class AAIController;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPauseStateChangedDelegate, bool);

/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API AZKGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
 
    AZKGameMode();

    virtual void StartPlay() override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

 
    FOnPauseStateChangedDelegate OnPauseStateChanged;

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    void SpawnOneBot();

    FTimerHandle EnemySpawnTimer;
    TMap<EEnemyType, int32> EnemiesSpawnQueue;
};

