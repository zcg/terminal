// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "InteractionViewModel.g.h"
#include "ViewModelHelpers.h"
#include "Utils.h"

namespace winrt::Microsoft::Terminal::Settings::Editor::implementation
{
    struct InteractionViewModel : InteractionViewModelT<InteractionViewModel>, ViewModelHelper<InteractionViewModel>
    {
    public:
        InteractionViewModel(Model::GlobalAppSettings globalSettings, Model::WindowSettings windowSettings);

        // DON'T YOU DARE ADD A `WINRT_CALLBACK(PropertyChanged` TO A CLASS DERIVED FROM ViewModelHelper. Do this instead:
        using ViewModelHelper<InteractionViewModel>::PropertyChanged;

        GETSET_BINDABLE_ENUM_SETTING(TabSwitcherMode, Model::TabSwitcherMode, _WindowSettings.TabSwitcherMode);
        GETSET_BINDABLE_ENUM_SETTING(CopyFormat, winrt::Microsoft::Terminal::Control::CopyFormat, _WindowSettings.CopyFormatting);
        GETSET_BINDABLE_ENUM_SETTING(ConfirmOnClose, Model::ConfirmOnClose, _GlobalSettings.ConfirmOnClose);

        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, CopyOnSelect);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, TrimBlockSelection);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, TrimPaste);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, SnapToGridOnResize);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, FocusFollowMouse);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, ScrollToZoom);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, ScrollToChangeOpacity);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, DetectURLs);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, SearchWebDefaultQueryUrl);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, WordDelimiters);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, WarnAboutLargePaste);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, WarnAboutMultiLinePaste);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_GlobalSettings, EnableColorSelection);
        PERMANENT_OBSERVABLE_PROJECTED_SETTING(_WindowSettings, EnableTabDragDrop);

        // Grey out the toggle when the OS refuses drag/drop anyway (elevated or
        // running as a different user); used to disable the EnableTabDragDrop
        // control. See Utils::CanUwpDragDrop. GH#15689.
        bool CanEnableTabDragDrop() const noexcept;
        // Help text for the EnableTabDragDrop control that explains why it is
        // disabled when CanEnableTabDragDrop is false.
        winrt::hstring TabDragDropDescription() const;

    private:
        Model::GlobalAppSettings _GlobalSettings;
        Model::WindowSettings _WindowSettings;
    };
};

namespace winrt::Microsoft::Terminal::Settings::Editor::factory_implementation
{
    BASIC_FACTORY(InteractionViewModel);
}
