// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "AI/ZKAIPawn.h"

#include "AI/ZKAIController.h"
#include "Components/ZKAttributeComponent.h"
#include "Utils/ZKFunctionLibrary.h"

AZKAIPawn::AZKAIPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AZKAIController::StaticClass();
}

void AZKAIPawn::SetColor()
{
    if (!MeshComponent) return;

    const auto MaterialInstance = UZKFunctionLibrary::GeMaterialInstanceByEnemyType(EnemyType);
    MeshComponent->SetMaterial(0, MaterialInstance);
}

void AZKAIPawn::InitAttributes(const FVector& SpawnCenter, const FVector& SpawnLocation, EEnemyType InEnemyType)
{
    if (!AttributeComponent || !MeshComponent) return;

    EnemyType = InEnemyType;

    const float Distance = FVector::Dist2D(SpawnCenter, SpawnLocation);  
    
    const float MaxDistance = 2000.f;

    const float StrengthMultiplier = FMath::Lerp(0.5f, 1.5f, Distance / MaxDistance);
    const float SpeedMultiplier = FMath::Lerp(0.5f, 1.5f, Distance / MaxDistance);

    AttributeComponent->CurrentStrength = AttributeComponent->InitialStrength * StrengthMultiplier;
    AttributeComponent->MaxStrength = AttributeComponent->CurrentStrength;

    AttributeComponent->CurrentSpeed = AttributeComponent->InitialSpeed * SpeedMultiplier;
    AttributeComponent->MaxSpeed = AttributeComponent->CurrentSpeed;

    const FVector NewScale = FVector(StrengthMultiplier);  
    MeshComponent->SetWorldScale3D(NewScale);
}
