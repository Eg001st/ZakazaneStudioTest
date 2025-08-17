// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pawn/ZKBasePawn.h"
#include "ZKPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

struct FInputActionValue;
/**
 *
 */
UCLASS()
class ZAKAZANEKULKI_API AZKPlayerPawn : public AZKBasePawn
{
    GENERATED_BODY()

public:
    AZKPlayerPawn(const FObjectInitializer& ObjectInitializer);

    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ZK|Movement")
    float MoveForce {2000.f};

private:
    UPROPERTY(EditDefaultsOnly, Category = "ZK|Input")
    TObjectPtr<UInputMappingContext> InputMappingMovement;

    UPROPERTY(EditDefaultsOnly, Category = "ZK|Input")
    TObjectPtr<UInputAction> MoveAction;


    bool bWantsToMove{false};
    FVector TargetWorldPos;

    void MovePressed();
    void MoveReleased();
    void UpdateCursorLocation();
    void HandleMovement(float DeltaTime);


    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

protected:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> CameraComponent;
};
