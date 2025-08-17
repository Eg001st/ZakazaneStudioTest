// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZKAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZAKAZANEKULKI_API UZKAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    
    // It’s generally better to use getters and setters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float InitialStrength {10.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float MaxStrength {100.f};

    UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    float CurrentStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float InitialSpeed {10.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    float MaxSpeed {100.f};

    UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    float CurrentSpeed;

    void AddStrength(float Value);
    void AddSpeed(float Value);
    void RemoveStrength(float Value);
    void RemoveSpeed(float Value);

    bool IsAlive() const;
};
