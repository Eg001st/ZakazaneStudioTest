// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "ZKGrid.generated.h"

class UStaticMeshComponent;

UCLASS() //Not used 
class ZAKAZANEKULKI_API AZKGrid : public AActor
{
    GENERATED_BODY()

public:
    AZKGrid();

    virtual void Tick(float DeltaTime) override;

    void SetSettings(const FIntPoint& GridDim, int32 InCellSize);

    UStaticMeshComponent* GetMesh() const { return GridMesh; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> Origin;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> GridMesh;

private:
    FIntPoint GridDimension{};
    int32 CellSize;
    int32 WorldWidth;
    int32 WorldHeight;

    TArray<ECellType> Cells;

    void DrawGrid();
    void InitGrid();
    void InitWalls();
    void InitNavMesh();

    int32 PositionToIndex(const int32 X, const int32 Y) const;
    
};
