// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Widgets/ZKPrimaryLayoutWidget.h"

TObjectPtr<UCommonActivatableWidgetContainerBase> UZKPrimaryLayoutWidget::FindWidgetStackByTag(const FGameplayTag& InTag)
{
    checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find the widget stack by the tag %s"), *InTag.ToString());
    return RegisteredWidgetStackMap.FindRef(InTag);
}

void UZKPrimaryLayoutWidget::RegisterWidgetStack(
    UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
    if (!IsDesignTime())
    {
        if (!RegisteredWidgetStackMap.Contains(InStackTag))
        {
            RegisteredWidgetStackMap.Add(InStackTag, InStack);
        }
    }
}
