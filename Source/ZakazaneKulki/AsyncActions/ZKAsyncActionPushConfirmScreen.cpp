// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved


#include "AsyncActions/ZKAsyncActionPushConfirmScreen.h"

#include "UI/ZKUISubsystem.h"



UZKAsyncActionPushConfirmScreen* UZKAsyncActionPushConfirmScreen::PushConfirmScreen(
    const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
    if (auto World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull); GEngine)  //?
    {
       auto Node = NewObject<UZKAsyncActionPushConfirmScreen>();
        Node->CachedWorld = World;
        Node->CachedScreenType = ScreenType;
        Node->CachedScreenTitle = InScreenTitle;
        Node->CachedScreenMessage = InScreenMessage;

        Node->RegisterWithGameInstance(World);
        return Node;
    }

    return nullptr;
}

void UZKAsyncActionPushConfirmScreen::Activate() 
{
    UZKUISubsystem::Get(CachedWorld.Get())
        ->PushConfirmScreenToModalStackAsync(CachedScreenType, CachedScreenTitle, CachedScreenMessage,  //
            [this](EConfirmScreenButtonType ClickedButtonType) //
            { //
                OnButtonClicked.Broadcast(ClickedButtonType);
                SetReadyToDestroy();
            });
}
