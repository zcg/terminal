// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

namespace Microsoft::Terminal::MaterialHelpers
{
    // AcrylicDark uses the normal DWM acrylic backdrop plus these XAML tints.
    inline constexpr winrt::Windows::UI::Color AcrylicDarkSolidTint{ 0xff, 0x28, 0x28, 0x28 };
    inline constexpr winrt::Windows::UI::Color AcrylicDarkOverlayTint{ 0xb8, 0x28, 0x28, 0x28 };
    inline constexpr float AcrylicDarkTintOpacity = 0.65f;
    inline constexpr float AcrylicDefaultTintOpacity = 0.5f;
}
