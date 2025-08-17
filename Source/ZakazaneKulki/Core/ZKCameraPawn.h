// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ZKCameraPawn.generated.h"

class UCameraComponent;

UCLASS() //Not used
class ZAKAZANEKULKI_API AZKCameraPawn : public APawn
{
    GENERATED_BODY()

public:
    AZKCameraPawn();

    void UpdateLocation(const FIntPoint& Dimension, int32 InCellSize, const FTransform& InGridTransform);

protected:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> Origin;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> CameraComponent;

private:
    FIntPoint Dim;
    int32 CellSize;
    FTransform GridTransform;
    FDelegateHandle ResizeHandle;

    void OnViewportResized(FViewport* Viewport, uint32 Val);

    double FOVTan(double FOVDegrees);
    double VerticalFOV(double HorFOVDegrees, double ViewportAspectHW);
};

namespace ZKCameraPawn
{
constexpr double GridMargin = 2.0;
}