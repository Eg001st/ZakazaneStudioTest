// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Widgets/ZKPauseWidget.h"

#include "Components/Button.h"
#include "Gameframework/GameModeBase.h"

bool UZKPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (Button_Continue)
    {
        Button_Continue->OnClicked.AddDynamic(this, &UZKPauseWidget::OnClearPause);
    }

    return InitStatus;
}

TOptional<FUIInputConfig> UZKPauseWidget::GetDesiredInputConfig() const
{
    Super::GetDesiredInputConfig();

 
    return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
}

void UZKPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
    DeactivateWidget();
}
