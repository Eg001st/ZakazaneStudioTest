// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Core/ZKCameraPawn.h"

#include "Camera/CameraComponent.h"

AZKCameraPawn::AZKCameraPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);

    SetRootComponent(Origin);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    check(CameraComponent);

    CameraComponent->SetupAttachment(Origin);

    CameraComponent->SetRelativeRotation(FQuat(FRotator(-90,0,0)));
}

void AZKCameraPawn::UpdateLocation(const FIntPoint& Dimension, int32 InCellSize, const FTransform& InGridTransform)
{
    Dim = Dimension;
    CellSize = InCellSize;
    GridTransform = InGridTransform;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto* Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.Remove(ResizeHandle);
    ResizeHandle = Viewport->ViewportResizedEvent.AddUObject(this, &AZKCameraPawn::OnViewportResized);

    OnViewportResized(Viewport, 0);
}

void AZKCameraPawn::OnViewportResized(FViewport* Viewport, uint32 Val)
{
    if (!Viewport || Viewport->GetSizeXY().Y == 0 || Dim.Y == 0) return;

    const double WorldWidth = Dim.X * CellSize;
    const double WorldHeight = Dim.Y * CellSize;

    double LocationZ = 0.0;
    const double ViewportAspect = StaticCast<double>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const double GridAspect = StaticCast<double>(Dim.X) / Dim.Y;

    if (ViewportAspect <= GridAspect)
    {
        const double MarginWidth = (Dim.X + ZKCameraPawn::GridMargin) * CellSize;
        LocationZ = MarginWidth / FOVTan(CameraComponent->FieldOfView);
    }
    else
    {
        check(ViewportAspect);
        const double VFOV = VerticalFOV(CameraComponent->FieldOfView, 1.0 / ViewportAspect);
        const double MarginHeight = (Dim.Y + ZKCameraPawn::GridMargin) * CellSize;
        LocationZ = MarginHeight / FOVTan(VFOV);
    }

    const FVector NewPawnLocation = GridTransform.GetLocation() + 0.5 * FVector(WorldHeight, WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}

double AZKCameraPawn::FOVTan(double FOVDegrees)
{
    return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5));
}

double AZKCameraPawn::VerticalFOV(double HorFOVDegrees, double ViewportAspectHW)
{
    return FMath::RadiansToDegrees(2.0 * FMath::Atan(FMath::Tan(FMath::DegreesToRadians(HorFOVDegrees) * 0.5) * ViewportAspectHW));
}
