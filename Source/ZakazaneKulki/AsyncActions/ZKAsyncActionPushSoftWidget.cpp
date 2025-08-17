// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "AsyncActions/ZKAsyncActionPushSoftWidget.h"

#include "UI/ZKUISubsystem.h"
#include "Widgets/ZKWidgetActivatableBase.h"

UZKAsyncActionPushSoftWidget* UZKAsyncActionPushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPC,
    TSoftClassPtr<UZKWidgetActivatableBase> InSoftWidgetClass, UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InWidgetStackTag,
    bool bFocusOnNewlyPushedWidget)
{
    checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
    if (auto World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); GEngine) //?
    {
        TObjectPtr<UZKAsyncActionPushSoftWidget> Node = NewObject<UZKAsyncActionPushSoftWidget>();
        Node->CachedOwningWorld = World;
        Node->CachedOwningPC = OwningPC;
        Node->CachedSoftWidgetClass = InSoftWidgetClass;
        Node->CachedWidgetStackTag = InWidgetStackTag;
        Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

        Node->RegisterWithGameInstance(World);
        return Node;
    }

    return nullptr;
}

void UZKAsyncActionPushSoftWidget::Activate()
{
    UZKUISubsystem* ZKUISubsystem = UZKUISubsystem::Get(CachedOwningWorld.Get());

    ZKUISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,  //
        [this](EAsyncPushWidgetState InPushState, UZKWidgetActivatableBase* PushedWidget)
        {
            switch (InPushState)
            {
                case EAsyncPushWidgetState::OnCreatedBeforePush:
                    PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
                    OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
                    break;
                case EAsyncPushWidgetState::AfterPush:
                    AfterPush.Broadcast(PushedWidget);
                    if (bCachedFocusOnNewlyPushedWidget)
                    {
                        if (auto WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
                        {
                            WidgetToFocus->SetFocus();
                        }
                    }
                    SetReadyToDestroy();
                    break;
                default: break;
            }
        });
}
