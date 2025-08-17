// Yehor Kolohoida for Zakazane Studio. Copyright Yehor Kolohoida. All Right Reserved

#pragma once

#include "NativeGameplayTags.h"

/**
 *
 */
namespace UITags
{
	//UI Widget stacks
	ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_WidgetStack_Modal);
	ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_WidgetStack_GameMenu);
	ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_WidgetStack_GameHud);
	ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_WidgetStack_Frontend);

	// Frontend widgets
    ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenuScreen)
    ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_ConfirmScreen)
    ZAKAZANEKULKI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PauseScreen)

}  // namespace UITags
