// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#include "UI/UITags.h"

namespace UITags
{
	// UI Widget stacks

	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Modal, "UI.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameMenu, "UI.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameHud, "UI.WidgetStack.GameHud");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Frontend, "UI.WidgetStack.Frontend");

	// Frontend widgets
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenuScreen, "Frontend.Widget.MainMenuScreen")
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_ConfirmScreen, "Frontend.Widget.ConfirmScreen")
    UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PauseScreen, "Frontend.Widget.PauseScreen")

}  // namespace UITags