// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Core/ZKGameHUD.h"

#include "Core/ZKGameMode.h"
#include "AsyncActions/ZKAsyncActionPushSoftWidget.h"

#include "Blueprint/UserWidget.h"


void AZKGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    if (!GetWorld()) return;
    const auto PlayerPawnWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerPawnHUDWidgetClass);
    if (PlayerPawnWidget)
    {
        PlayerPawnWidget->AddToViewport();
    }

    const auto GameMode = Cast<AZKGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->OnPauseStateChanged.AddUObject(this, &AZKGameHUD::OnPauseStateChanged);
    }
}

void AZKGameHUD::OnPauseStateChanged(bool IsPauseSet) 
{
    OnPause(IsPauseSet);
}
