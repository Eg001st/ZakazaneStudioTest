// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Pawn/ZKPlayerPawn.h"

#include "AI/ZKAIPawn.h"
#include "Pawn/ZKPlayerController.h"
#include "Components/ZKAttributeComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AZKPlayerPawn::AZKPlayerPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    check(SpringArmComponent);

    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 1000.f;
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->SetRelativeRotation(FRotator(-90.0, 0.0, 0.0));
    SpringArmComponent->bUsePawnControlRotation = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    check(CameraComponent);

    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->OrthoWidth = 1024.f;
}

void AZKPlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    check(InputMappingMovement);

    if (const auto ZKPlayerController = Cast<AZKPlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ZKPlayerController->GetLocalPlayer()))
        {
            if (InputMappingMovement != nullptr)
            {
                InputSystem->AddMappingContext(InputMappingMovement, 0);
            }
        }
    }

    if (!CapsuleComponent->OnComponentBeginOverlap.IsAlreadyBound(this, &AZKPlayerPawn::OnOverlapBegin))
    {
        CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AZKPlayerPawn::OnOverlapBegin);
    }
}

void AZKPlayerPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UpdateCursorLocation();
    if (bWantsToMove)
    {
        HandleMovement(DeltaSeconds);
    }
}

void AZKPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(MoveAction);
    if (UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AZKPlayerPawn::MovePressed);
        EIComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &AZKPlayerPawn::MoveReleased);
    }
}

void AZKPlayerPawn::MovePressed()
{
    bWantsToMove = true;
}

void AZKPlayerPawn::MoveReleased()
{
    bWantsToMove = false;
}

void AZKPlayerPawn::UpdateCursorLocation()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        FHitResult Hit;
        PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
        TargetWorldPos = Hit.Location;
    }
}

void AZKPlayerPawn::HandleMovement(float DeltaTime)
{
    if (!AttributeComponent) return;

    FVector Dir = (TargetWorldPos - GetActorLocation()).GetSafeNormal2D();
    float Force = AttributeComponent->CurrentSpeed * 100.f;  // multiplier
    MeshComponent->AddForce(Dir * Force);
}

void AZKPlayerPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        AZKAIPawn* AIPawn = Cast<AZKAIPawn>(OtherActor);
        if (AIPawn)
        {
            FVector MyScale = GetActorScale3D();
            FVector EnemyScale = AIPawn->GetActorScale3D();

            
            if (MyScale.Size() > EnemyScale.Size())
            {
                SetActorScale3D(MyScale + FVector(0.2f));  
                AIPawn->Destroy();
                UE_LOG(LogTemp, Warning, TEXT("Player ate AI!"));
            }
            else
            {
                
                Destroy();
                UE_LOG(LogTemp, Warning, TEXT("Player was eaten!"));
            }
        }
    }
}

