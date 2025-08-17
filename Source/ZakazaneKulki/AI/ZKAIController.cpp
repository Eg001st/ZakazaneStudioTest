// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "AI/ZKAIController.h"

#include "AI/ZKAIPerceptionComponent.h"

AZKAIController::AZKAIController() 
{
    ZKAIPerceptionComponent = CreateDefaultSubobject<UZKAIPerceptionComponent>("ZKAIPerceptionComponent");
    SetPerceptionComponent(*ZKAIPerceptionComponent);
}
