// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <dwmapi.h>

namespace Microsoft::Terminal::MaterialHelpers
{
    using BackgroundMaterial = winrt::Microsoft::Terminal::Settings::Model::BackgroundMaterial;
    using TerminalBackgroundMaterial = winrt::Microsoft::Terminal::Settings::Model::TerminalBackgroundMaterial;

    inline constexpr winrt::Windows::UI::Color AcrylicDarkSolidTint{ 0xff, 0x28, 0x28, 0x28 };
    inline constexpr winrt::Windows::UI::Color AcrylicDarkOverlayTint{ 0xb8, 0x28, 0x28, 0x28 };
    inline constexpr float AcrylicDarkTintOpacity = 0.65f;
    inline constexpr float AcrylicDefaultTintOpacity = 0.5f;

    template<typename ThemeT>
    [[nodiscard]] inline BackgroundMaterial ResolveApplicationBackgroundMaterial(
        const ThemeT& currentTheme,
        const BackgroundMaterial configuredMaterial)
    {
        if (configuredMaterial != BackgroundMaterial::Default)
        {
            return configuredMaterial;
        }

        const auto windowTheme = currentTheme.Window();
        return windowTheme && windowTheme.UseMica() ? BackgroundMaterial::Mica : BackgroundMaterial::Solid;
    }

    [[nodiscard]] constexpr bool IsWindowBackedApplicationMaterial(const BackgroundMaterial material) noexcept
    {
        return material == BackgroundMaterial::Mica ||
               material == BackgroundMaterial::MicaAlt ||
               material == BackgroundMaterial::Acrylic ||
               material == BackgroundMaterial::AcrylicDark;
    }

    [[nodiscard]] constexpr bool IsAcrylicApplicationMaterial(const BackgroundMaterial material) noexcept
    {
        return material == BackgroundMaterial::Acrylic || material == BackgroundMaterial::AcrylicDark;
    }

    [[nodiscard]] constexpr bool IsAcrylicDark(const BackgroundMaterial material) noexcept
    {
        return material == BackgroundMaterial::AcrylicDark;
    }

    [[nodiscard]] constexpr int SystemBackdropForMaterial(const BackgroundMaterial material) noexcept
    {
        switch (material)
        {
        case BackgroundMaterial::Mica:
            return DWMSBT_MAINWINDOW;
        case BackgroundMaterial::MicaAlt:
            return DWMSBT_TABBEDWINDOW;
        case BackgroundMaterial::Acrylic:
        case BackgroundMaterial::AcrylicDark:
            return DWMSBT_TRANSIENTWINDOW;
        default:
            return DWMSBT_NONE;
        }
    }

    template<typename AppearanceT>
    [[nodiscard]] TerminalBackgroundMaterial ResolveTerminalBackgroundMaterial(const AppearanceT& appearance)
    {
        const auto material = appearance.TerminalBackgroundMaterial();
        if (material != TerminalBackgroundMaterial::Default)
        {
            return material;
        }

        if (appearance.UseAcrylicOverrideSource())
        {
            return appearance.UseAcrylic() ? TerminalBackgroundMaterial::Acrylic : TerminalBackgroundMaterial::Solid;
        }

        return TerminalBackgroundMaterial::Default;
    }

    [[nodiscard]] constexpr bool ShouldUseWindowMaterialInTabRow(
        const BackgroundMaterial material,
        const bool windowMaterialAvailable) noexcept
    {
        return windowMaterialAvailable && IsWindowBackedApplicationMaterial(material);
    }

    [[nodiscard]] constexpr bool ShouldUseXamlAcrylicInTabRow(
        const BackgroundMaterial material,
        const bool useAcrylicInTabRow,
        const bool windowMaterialAvailable,
        const bool acrylicAllowedForWindowState) noexcept
    {
        if (!acrylicAllowedForWindowState || ShouldUseWindowMaterialInTabRow(material, windowMaterialAvailable))
        {
            return false;
        }

        return IsAcrylicApplicationMaterial(material) || useAcrylicInTabRow;
    }

}
