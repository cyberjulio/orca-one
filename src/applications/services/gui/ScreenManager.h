#pragma once

#include <WString.h>
#include <TFT_eSPI.h>

#include "AbstractGuiModule.h"
#include "Screen.h"
#include "TopBar.h"

namespace Applications::Services::GUI
{
    class ScreenManager : public AbstractGuiModule
    {
    private:
        static ScreenManager *_instance;
        static bool _initialized;
        std::shared_ptr<TFT_eSPI> _tft;
        Screen *_currentScreen = nullptr;
        TopBar *_topBar;

    public:
        ScreenManager(std::shared_ptr<TFT_eSPI> tft);

        static ScreenManager *getInstance();
        static void setCurrentScreen(Screen *newScreen, bool setPrevious = true);
        static void setToPreviousScreen();

        template <typename T>
        static void setCurrentScreen(bool setPrevious = true)
        {
            auto tft = ScreenManager::getInstance()->_tft;
            auto screen = new T(tft);
            ScreenManager::setCurrentScreen(screen, setPrevious);
        }

        static Screen *getCurrentScreen();

        static void render();

        virtual void render(std::shared_ptr<TFT_eSPI> tft);
    };
}
