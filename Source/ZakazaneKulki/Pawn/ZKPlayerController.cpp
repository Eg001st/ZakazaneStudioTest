// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Pawn/ZKPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameModeBase.h"

AZKPlayerController::AZKPlayerController()
{
    bShouldPerformFullTickWhenPaused = true;
}

void AZKPlayerController::BeginPlay()
{
    Super::BeginPlay();

     bShowMouseCursor = true;  

    if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (InputMappingUI != nullptr)
        {
            InputSystem->AddMappingContext(InputMappingUI, 1);
        }
    }
}

void AZKPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        InputComponent->bBlockInput = false;
        if (PauseGameAction != nullptr)
        {
            Input->BindAction(PauseGameAction, ETriggerEvent::Started, this, &AZKPlayerController::OnPauseGame);
        }
    }
}

void AZKPlayerController::OnPauseGame(const FInputActionValue& Value)
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    const auto GameMode = GetWorld()->GetAuthGameMode();
    const bool IsPaused = GameMode->IsPaused();
    if (!IsPaused)
    {
        GameMode->SetPause(this);
    }
    else
    {
        GameMode->ClearPause();
    }
}
