// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ZKBasePawn.generated.h"

class UStaticMeshComponent;
class UZKAttributeComponent;
class UCapsuleComponent;

UCLASS(Abstract,BlueprintType)
class ZAKAZANEKULKI_API AZKBasePawn : public APawn
{
	GENERATED_BODY()

public:
    AZKBasePawn(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZK|Components")
    UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZK|Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZK|Components")
    TObjectPtr<UZKAttributeComponent> AttributeComponent;
};
