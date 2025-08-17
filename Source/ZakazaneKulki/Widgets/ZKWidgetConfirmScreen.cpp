// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "Widgets/ZKWidgetConfirmScreen.h"

#include "Widgets/Components/ZKCommonButtonBase.h"

#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "ICommonInputModule.h"

UZKConfirmScreenObject* UZKConfirmScreenObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    auto InfoObject = NewObject<UZKConfirmScreenObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo OKButtonInfo;
    OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
    OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

    InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

    return InfoObject;
}

UZKConfirmScreenObject* UZKConfirmScreenObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    auto InfoObject = NewObject<UZKConfirmScreenObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo YesButtonInfo;
    YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
    YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

    InfoObject->AvailableScreenButtons.Add(YesButtonInfo);

    FConfirmScreenButtonInfo NoButtonInfo;
    NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
    NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

    InfoObject->AvailableScreenButtons.Add(NoButtonInfo);

    return InfoObject;
}

UZKConfirmScreenObject* UZKConfirmScreenObject::CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    auto InfoObject = NewObject<UZKConfirmScreenObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo OKButtonInfo;
    OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
    OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("OK"));

    InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

    FConfirmScreenButtonInfo CancelButtonInfo;
    CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
    CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

    InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

    return InfoObject;
}

void UZKWidgetConfirmScreen::InitConfirmScreen(
    UZKConfirmScreenObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
    check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

    CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
    CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

    // Checking if the entry box has old buttons created previously
    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->Reset<UZKCommonButtonBase>(  //
            [](UZKCommonButtonBase& ExistingButtons)          //
            {                                                 //
                ExistingButtons.OnClicked().Clear();
            });
    }

    check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());
    for (const auto& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
    {
        FDataTableRowHandle InputActionRowHandle;
        switch (AvailableButtonInfo.ConfirmScreenButtonType)
        {
            case EConfirmScreenButtonType::Cancelled:                                             
                InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();  
                break;                                                                           
            case EConfirmScreenButtonType::Closed:                                               
                InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();  
                break;                                                                            
            default: break;
        }

        auto AddedButton = DynamicEntryBox_Buttons->CreateEntry<UZKCommonButtonBase>();
        AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
        AddedButton->SetTriggeringInputAction(InputActionRowHandle);
        AddedButton->OnClicked().AddLambda(                       //
            [ClickedButtonCallback, AvailableButtonInfo, this]()  //
            {                                                     //
                ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
                DeactivateWidget();
            });
    }

    if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
    }
}
