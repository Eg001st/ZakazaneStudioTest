// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Components/ZKAttributeComponent.h"


void UZKAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentStrength = InitialStrength;
    CurrentSpeed = InitialSpeed;
}

void UZKAttributeComponent::AddStrength(float Value)
{
    CurrentStrength = FMath::Clamp(CurrentStrength + Value, 0.f, MaxStrength);
}

void UZKAttributeComponent::AddSpeed(float Value)
{
    CurrentSpeed = FMath::Clamp(CurrentSpeed + Value, 0.f, MaxSpeed);
}

void UZKAttributeComponent::RemoveStrength(float Value)
{
    AddStrength(-Value);
}

void UZKAttributeComponent::RemoveSpeed(float Value)
{
    AddSpeed(-Value);
}

bool UZKAttributeComponent::IsAlive() const
{
    return CurrentStrength > 0.f && CurrentSpeed > 0.f;
}