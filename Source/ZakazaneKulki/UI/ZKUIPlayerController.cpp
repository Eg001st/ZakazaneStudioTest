// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "UI/ZKUIPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"


void AZKUIPlayerController::OnPossess(APawn* PawnToPossess)
{
    Super::OnPossess(PawnToPossess);

    TArray<AActor*> Cameras;
    UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), DefaultCameraTag, Cameras);

    if (!Cameras.IsEmpty())
    {
        SetViewTarget(Cameras[0]);
    }

}
