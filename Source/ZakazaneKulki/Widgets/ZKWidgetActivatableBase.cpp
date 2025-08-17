// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Widgets/ZKWidgetActivatableBase.h"

#include "UI/ZKUIPlayerController.h"


AZKUIPlayerController* UZKWidgetActivatableBase::GetOwningUIPlayerController()
{
    if (!CachedOwningPC.IsValid())
    {
        CachedOwningPC = GetOwningPlayer<AZKUIPlayerController>();
    }

    return CachedOwningPC.IsValid()? CachedOwningPC.Get() : nullptr;
}
