// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "UI/ZKUISubsystem.h"

#include "UI/UITags.h"
#include "Utils/ZKFunctionLibrary.h"
#include "Widgets/ZKPrimaryLayoutWidget.h"
#include "Widgets/ZKWidgetActivatableBase.h"
#include "Widgets/ZKWidgetConfirmScreen.h"


#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UZKUISubsystem* UZKUISubsystem::Get(const UObject* WorldContextObject)
{
    if (IsValid(GEngine))
    {
        TObjectPtr<UWorld> World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

        return UGameInstance::GetSubsystem<UZKUISubsystem>(World->GetGameInstance());
    }
    return nullptr;
}

bool UZKUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> Classes;
        GetDerivedClasses(GetClass(), Classes);

        return Classes.IsEmpty();
    }

    return false;
}

void UZKUISubsystem::RegisterPrimaryLayoutWidget(UZKPrimaryLayoutWidget* InCreatedWidget)
{
    check(InCreatedWidget);
    PrimaryLayout = InCreatedWidget;
}

void UZKUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
    TSoftClassPtr<UZKWidgetActivatableBase> InSoftWidgetClass,
    TFunction<void(EAsyncPushWidgetState, UZKWidgetActivatableBase*)> AsyncPushStateCallback)
{
    check(!InSoftWidgetClass.IsNull());

    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(  //
        InSoftWidgetClass.ToSoftObjectPath(),                      //
        FStreamableDelegate::CreateLambda(                         //
            [InSoftWidgetClass, this, InWidgetStackTag, AsyncPushStateCallback]()
            {
                UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
                check(LoadedWidgetClass && PrimaryLayout);
                const auto FoundWidgetStack = PrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);

                auto CreatedWidget = FoundWidgetStack->AddWidget<UZKWidgetActivatableBase>(  //
                    LoadedWidgetClass,                                                       //
                    [AsyncPushStateCallback](UZKWidgetActivatableBase& CreatedWidgetInstance)
                    {
                        AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);  //
                    });
                AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
            }));
}

void UZKUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle,
    const FText& InScreenMessage, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
    TObjectPtr<UZKConfirmScreenObject> CreatedInfoObject{nullptr};
    switch (InScreenType)
    {
        case EConfirmScreenType::OK: 
           CreatedInfoObject = UZKConfirmScreenObject::CreateOKScreen(InScreenTitle, InScreenMessage);
            break;
        case EConfirmScreenType::YesNo: 
            CreatedInfoObject = UZKConfirmScreenObject::CreateYesNoScreen(InScreenTitle, InScreenMessage);
            break; 
        case EConfirmScreenType::OKCancel:
            CreatedInfoObject = UZKConfirmScreenObject::CreateOKCancelScreen(InScreenTitle, InScreenMessage);
            break;
        case EConfirmScreenType::Unknown: break;
        default: break;
    }

    check(CreatedInfoObject);
    
    PushSoftWidgetToStackAsync(UITags::UI_WidgetStack_Modal,
        UZKFunctionLibrary::GetFrontendSoftWidgetClassByTag(UITags::Frontend_Widget_ConfirmScreen),  //
        [CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UZKWidgetActivatableBase* PusheWidget)  //
        {
            if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
            {
               auto CreatedConfirmScreen = CastChecked<UZKWidgetConfirmScreen>(PusheWidget);
                CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
            }
        });
}
