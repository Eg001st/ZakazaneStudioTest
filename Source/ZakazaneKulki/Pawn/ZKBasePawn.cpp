// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Pawn/ZKBasePawn.h"

#include "Components/ZKAttributeComponent.h"
#include "Components/CapsuleComponent.h"

AZKBasePawn::AZKBasePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    check(MeshComponent);

    SetRootComponent(MeshComponent);

    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetEnableGravity(false);

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
    MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    MeshComponent->SetMobility(EComponentMobility::Movable);

    MeshComponent->BodyInstance.bLockZTranslation = true;  
    MeshComponent->BodyInstance.bLockXRotation = true;     
    MeshComponent->BodyInstance.bLockYRotation = true;
    MeshComponent->BodyInstance.bLockZRotation = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    check(CapsuleComponent);

    CapsuleComponent->InitCapsuleSize(50.f, 50.f);
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CapsuleComponent->SetCollisionObjectType(ECC_Pawn);
    CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    CapsuleComponent->SetGenerateOverlapEvents(true);

    AttributeComponent = CreateDefaultSubobject<UZKAttributeComponent>(TEXT("AttributeComp"));
}
