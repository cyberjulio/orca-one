#include "MainMenuScreen.h"
#include "../../AppUtils.h"
#include "../../settings/about/AboutApp.h"
#include "../../settings/webui/WebUIApp.h"
#include "../../infrared/tvbgone/TVBGoneApp.h"
#include "../../Translate.h"
#include "../../../domain/entities/Color.h"
#include "../../nfc/ReadTag/ReadTagApp.h"

using namespace Applications::Services::GUI;
using namespace Applications;

MainMenuScreen::MainMenuScreen(std::shared_ptr<TFT_eSPI> tft) : MenuScreen(tft, false)
{
    // this->addItem(newAppsMainMenuItem());
    // this->addItem(newWifiMainMenuItem());
    // this->addItem(newBluetoothMainMenuItem());
    // this->addItem(newSubGhzMainMenuItem());
    this->addItem(newNfcMainMenuItem());
    this->addItem(newInfraredMainMenuItem());
    // this->addItem(newBadUsbMainMenuItem());
    this->addItem(newSettingsMainMenuItem());
}

MenuItem MainMenuScreen::newAppsMainMenuItem()
{
    MenuItem appsMenuItem("appsMenuItem", this->translate("MainMenu_Apps"));
    return appsMenuItem;
}

MenuItem MainMenuScreen::newWifiMainMenuItem()
{
    MenuItem wifiMenuItem("wifiMenuItem", this->translate("MainMenu_Wifi"));
    return wifiMenuItem;
}

MenuItem MainMenuScreen::newBluetoothMainMenuItem()
{
    MenuItem bluetoothMenuItem("bluetoothMenuItem", this->translate("MainMenu_Bluetooth"));
    return bluetoothMenuItem;
}

MenuItem MainMenuScreen::newSubGhzMainMenuItem()
{
    MenuItem subGhzMenuItem("subGhzMenuItem", this->translate("MainMenu_SubGhz"));
    return subGhzMenuItem;
}

MenuItem MainMenuScreen::newNfcMainMenuItem()
{
    MenuItem nfcMenuItem("nfcMenuItem", this->translate("MainMenu_Nfc"));
	MenuItem nfcReadTagSubMenuItem("nfcReadTagSubMenuItem", "Read Tag");

    nfcReadTagSubMenuItem.setOnClick([]() { AppUtils::runApplication<Applications::Nfc::ReadTag::ReadTagApp>(); });

    nfcMenuItem.addItem(nfcReadTagSubMenuItem);
    return nfcMenuItem;
}

MenuItem MainMenuScreen::newInfraredMainMenuItem()
{
    MenuItem infraredMenuItem("infraredMenuItem", this->translate("MainMenu_Infrared"));

    //  TV-B-Gone
    MenuItem infraredTVBGoneSubMenuItem("infraredTVBGoneSubMenuItem", "TV-B-Gone");
    infraredTVBGoneSubMenuItem.setOnClick([]()
                                          { AppUtils::runApplication<Applications::Infrared::TVBGone::TVBGoneApp>(); });
    infraredMenuItem.addItem(infraredTVBGoneSubMenuItem);

    return infraredMenuItem;
}

MenuItem MainMenuScreen::newBadUsbMainMenuItem()
{
    MenuItem badUsbMenuItem("badUsbMenuItem", this->translate("MainMenu_BadUSB"));
    return badUsbMenuItem;
}

MenuItem MainMenuScreen::newSettingsColorSubMenuItem()
{
    MenuItem settingsColorSubMenuItem("settingsColorSubMenuItem", this->translate("MainMenu_Settings_Color"));
    auto currentSettings = DeviceBase::getInstance()->getSettings();

    for (int currColorIdx = Default; currColorIdx <= LATEST_COLOR_SCHEME_INDEX; currColorIdx++)
    {
        ColorScheme scheme = static_cast<ColorScheme>(currColorIdx);
        String schemeName = colorSchemeToString(scheme);
        MenuItem colorSubmenu("Color_" + schemeName, schemeName);
        colorSubmenu.setOnClick([=]()
        {

            auto colorSchemeData = colorSchemeToData(scheme);
            auto currentSettings = DeviceBase::getInstance()->getSettings();
            currentSettings->setPrimaryColor(colorSchemeData.primaryColor);
            currentSettings->setBackgroundColor(colorSchemeData.backgroundColor);
            DeviceBase::getInstance()->saveSettings();
        });
        settingsColorSubMenuItem.addItem(colorSubmenu);
    }

    return settingsColorSubMenuItem;
}

MenuItem MainMenuScreen::newSettingsMainMenuItem()
{
    MenuItem settingsMenuItem("settingsMenuItem", this->translate("MainMenu_Settings"));

    // Web UI
    MenuItem settingsWebUISubMenuItem("settingsWebUISubMenuItem", "Web UI");
    settingsWebUISubMenuItem.setOnClick([]()
                                        { AppUtils::runApplication<Applications::Settings::WebUI::WebUIApp>(); });
    settingsMenuItem.addItem(settingsWebUISubMenuItem);

    // Color
    settingsMenuItem.addItem(MainMenuScreen::newSettingsColorSubMenuItem());

    // Language
    MenuItem settingsLanguageSubMenuItem("settingsLanguageSubMenuItem", this->translate("MainMenu_Settings_Language"));
    MenuItem settingsLanguageEnglishSubMenuItem("settingsLanguageEnglishSubMenuItem", "English");
    MenuItem settingsLanguagePortuguesBrasilSubMenuItem("settingsLanguagePortuguesBrasilSubMenuItem", "Portugues (BR)");

    // Language - English
    settingsLanguageEnglishSubMenuItem.setOnClick([]()
                                                  {
    auto currentSettings = DeviceBase::getInstance()->getSettings();

    currentSettings->setLanguage(Domain::Entities::Language::English);

    DeviceBase::getInstance()->saveSettings(); });

    settingsLanguageSubMenuItem.addItem(settingsLanguageEnglishSubMenuItem);

    // Language - PortuguesBrazil

    settingsLanguagePortuguesBrasilSubMenuItem.setOnClick([]()
                                                          {
    auto currentSettings = DeviceBase::getInstance()->getSettings();

    currentSettings->setLanguage(Domain::Entities::Language::PortuguesBrazil);

    DeviceBase::getInstance()->saveSettings(); });

    settingsLanguageSubMenuItem.addItem(settingsLanguagePortuguesBrasilSubMenuItem);

    settingsMenuItem.addItem(settingsLanguageSubMenuItem);

    // Reboot
    MenuItem settingsRebootSubMenuItem("settingsRebootSubMenuItem", this->translate("MainMenu_Settings_Reboot"));
    settingsRebootSubMenuItem.setOnClick([]()
                                         { ESP.restart(); });
    settingsMenuItem.addItem(settingsRebootSubMenuItem);

    // About
    MenuItem settingsAboutSubMenuItem("settingsAboutSubMenuItem", this->translate("MainMenu_Settings_About"));
    settingsAboutSubMenuItem.setOnClick([]()
                                        { AppUtils::runApplication<Applications::Settings::About::AboutApp>(); });
    settingsMenuItem.addItem(settingsAboutSubMenuItem);

    return settingsMenuItem;
}
