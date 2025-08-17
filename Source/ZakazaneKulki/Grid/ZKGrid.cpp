// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Grid/ZKGrid.h"

#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Components/BrushComponent.h"
#include "Components/BoxComponent.h"

AZKGrid::AZKGrid()
{
    PrimaryActorTick.bCanEverTick = true;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);

    SetRootComponent(Origin);

    GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
    check(GridMesh);

    GridMesh->SetupAttachment(Origin);
}

void AZKGrid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //DrawGrid();
}

void AZKGrid::SetSettings(const FIntPoint& GridDim, int32 InCellSize)
{
    GridDimension = GridDim;
    CellSize = InCellSize;
    WorldWidth = GridDimension.X * CellSize;
    WorldHeight = GridDimension.Y * CellSize;

    InitGrid();

    check(GridMesh->GetStaticMesh());
    const FBox Box = GridMesh->GetStaticMesh()->GetBoundingBox();
    const FVector Size = Box.GetSize();

    GridMesh->SetRelativeScale3D(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0));
    GridMesh->SetRelativeLocation(0.5 * FVector(WorldHeight, WorldWidth, 0.0));

    const FVector GridLoc = GetActorLocation();
    UE_LOG(LogTemp, Log, TEXT("NavMeshBoundsVolume spawned and NavMesh rebuilt for bounds: %s"), *GridLoc.ToString());

    InitNavMesh();
}

void AZKGrid::BeginPlay()
{
    Super::BeginPlay();
}

void AZKGrid::DrawGrid()
{
    // height
    for (int32 i = 0; i < GridDimension.Y + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorRightVector() * WorldWidth;
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
    }

    // width
    for (int32 i = 0; i < GridDimension.X + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorForwardVector() * WorldHeight;
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
    }
}

void AZKGrid::InitGrid()
{
    Cells.Init(ECellType::Empty, GridDimension.X * GridDimension.Y);
    InitWalls();
}

void AZKGrid::InitWalls()
{
    for (int32 y = 0; y < GridDimension.Y; ++y)
    {
        for (int32 x = 0; x < GridDimension.X; ++x)
        {
            const bool bIsWall = x == 0 || x == GridDimension.X - 1 || y == 0 || y == GridDimension.Y - 1;
            if (bIsWall)
            {
                const int32 Index = PositionToIndex(x, y);
                Cells[Index] = ECellType::Wall;
            }
        }
    }
}

void AZKGrid::InitNavMesh()
{
    //TODO
}

int32 AZKGrid::PositionToIndex(const int32 X, const int32 Y) const
{
    return X + Y + GridDimension.X;
}
