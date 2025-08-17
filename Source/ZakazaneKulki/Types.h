#pragma once

#include "Types.generated.h"

enum class ECellType
{
    Empty = 0,
    Wall
};

enum class EAsyncPushWidgetState : uint8
{
    OnCreatedBeforePush = 0,
    AfterPush
};

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
    OK = 0,
    YesNo,
    OKCancel,
    Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
    Confirmed = 0,
    Cancelled,
    Closed,
    Unknown UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextToDisplay;
};

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
    Red = 0,
    Yellow,
    Purple,
    Unknown UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TMap<EEnemyType, int32> EnemiesMapping;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "5.0", ClampMax = "100.0"))
    float EnemySpawnRate{5.f};

    UPROPERTY(EditAnywhere, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditAnywhere, Category = "Game")
    float SpawnRadius{2000.f};
};