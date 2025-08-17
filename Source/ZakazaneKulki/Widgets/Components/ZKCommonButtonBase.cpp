// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "Widgets/Components/ZKCommonButtonBase.h"

#include "UI/ZKUISubsystem.h"

#include "CommonTextBlock.h"

void UZKCommonButtonBase::SetButtonText(FText InText) 
{
    if (CommonTextBlock_ButtonText && !InText.IsEmpty())
    {
        
        CommonTextBlock_ButtonText->SetText(bUserUpperCaseForButtonText ? InText.ToUpper() : InText);
    }
}

void UZKCommonButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetButtonText(ButtonDisplayText);
}

void UZKCommonButtonBase::NativeOnCurrentTextStyleChanged() 
{
    Super::NativeOnCurrentTextStyleChanged();

    if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
    {
        CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
    }
}


void UZKCommonButtonBase::NativeOnHovered() 
{
    Super::NativeOnHovered();

    if (!ButtonDescriptionText.IsEmpty())
    {
        UZKUISubsystem::Get(this)->OnButtonDescriptionTextUpdateDelegate.Broadcast(this, ButtonDescriptionText);
    }
}

void UZKCommonButtonBase::NativeOnUnhovered() 
{
    Super::NativeOnUnhovered();
    UZKUISubsystem::Get(this)->OnButtonDescriptionTextUpdateDelegate.Broadcast(this, FText::GetEmpty());
}

