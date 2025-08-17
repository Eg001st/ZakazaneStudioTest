// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Core/ZKGameMode.h"

#include "AI/ZKAIPawn.h"
#include "Core/ZKGameHUD.h"
#include "Pawn/ZKPlayerController.h"
#include "Pawn/ZKPlayerPawn.h"

#include "Kismet/GameplayStatics.h"

AZKGameMode::AZKGameMode()
{
    PlayerControllerClass = AZKPlayerController::StaticClass();
    DefaultPawnClass = AZKPlayerPawn::StaticClass();
    HUDClass = AZKGameHUD::StaticClass();
}

void AZKGameMode::StartPlay()
{
    Super::StartPlay();
    EnemiesSpawnQueue = GameData.EnemiesMapping;
    GetWorldTimerManager().SetTimer(EnemySpawnTimer, this, &AZKGameMode::SpawnOneBot, GameData.EnemySpawnRate, true);
}

bool AZKGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        OnPauseStateChanged.Broadcast(PauseSet);
    }

    return PauseSet;
}

bool AZKGameMode::ClearPause()
{
    const bool PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        OnPauseStateChanged.Broadcast(false);
    }

    return PauseCleared;
}

void AZKGameMode::SpawnOneBot()
{
    if (!GetWorld()) return;

    const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn) return;

    TArray<EEnemyType> AvailableKeys;
    for (const auto& Elem : EnemiesSpawnQueue)
    {
        if (Elem.Value > 0)
        {
            AvailableKeys.Add(Elem.Key);
        }
    }

    const EEnemyType RandomKey = AvailableKeys[FMath::RandRange(0, AvailableKeys.Num() - 1)];
    --EnemiesSpawnQueue[RandomKey];

    const FVector RandOffset = FVector(FMath::FRandRange(-GameData.SpawnRadius, GameData.SpawnRadius),
        FMath::FRandRange(-GameData.SpawnRadius, GameData.SpawnRadius), 50.0);

    const FVector SpawnLocation = PlayerPawn->GetActorLocation() + RandOffset;
    FTransform SpawnTransform;
    SpawnTransform.SetLocation(SpawnLocation);

    const auto NewAIPawn = GetWorld()->SpawnActorDeferred<AZKAIPawn>(
        GameData.AIPawnClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

    if (NewAIPawn)
    {

        NewAIPawn->InitAttributes(PlayerPawn->GetActorLocation(), SpawnLocation, RandomKey);
        NewAIPawn->SetColor();
        NewAIPawn->FinishSpawning(SpawnTransform);
        return;
    }

    GetWorldTimerManager().ClearTimer(EnemySpawnTimer);
}
