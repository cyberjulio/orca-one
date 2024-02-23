#include "MenuScreen.h"
#include "ComingSoonScreen.h"
#include "../../Translate.h"

using namespace Applications::Services::GUI;

MenuItem *MenuScreen::getCurrentItem()
{
    return &this->_items.at(this->_currentItemIndex);
}

MenuItem MenuScreen::newBackItem()
{
    auto currentScreen = ScreenManager::getCurrentScreen();
    auto action = [currentScreen]()
    {
        ScreenManager::setCurrentScreen(currentScreen);
    };

    auto item = MenuItem("backMenuItem", TRANSLATE("Back"));

    item.setOnClick(action);

    return item;
}

MenuScreen::MenuScreen(std::shared_ptr<TFT_eSPI> tft, bool hasParent) : Screen(tft)
{
    if (hasParent)
        this->addItem(this->newBackItem());
}

MenuScreen::~MenuScreen()
{
    this->_items.clear();
}

void MenuScreen::render(std::shared_ptr<TFT_eSPI> tft)
{
    auto device = DeviceBase::getInstance();
    auto backgroundColor = colorToUInt16(device->getSettings()->getBackgroundColor());
    tft->fillScreen(backgroundColor);

    auto displayInterface = DeviceBase::getInstance()->getInterfaces().displayInterface;
    auto displaySettings = displayInterface->getSettings();

    // tft->fillScreen(THEME_BACKGROUND_COLOR);

    int totalItems = this->_items.size();

    if (totalItems == 0)
        return;

    std::vector<MenuItem> itemsToShow = std::vector<MenuItem>();

    if (totalItems > displaySettings.menuItemsToShow)
    {
        auto firstItem = this->_currentItemIndex == 0
                             ? this->_items.at(totalItems - 1)
                             : this->_items.at(this->_currentItemIndex - 1);

        itemsToShow.push_back(firstItem);

        for (int i = this->_currentItemIndex; i < totalItems && itemsToShow.size() < displaySettings.menuItemsToShow; i++)
        {
            itemsToShow.push_back(this->_items.at(i));
        }

        if (itemsToShow.size() < displaySettings.menuItemsToShow)
        {
            for (int i = 0; i < totalItems && itemsToShow.size() < displaySettings.menuItemsToShow; i++)
            {
                itemsToShow.push_back(this->_items.at(i));
            }
        }
    }
    else
    {
        for (int i = 0; i < totalItems; i++)
        {
            itemsToShow.push_back(this->_items.at(i));
        }
    }

    auto marginStart = 0; // 10

    for (int i = 0; i < itemsToShow.size(); i++)
    {
        itemsToShow.at(i).setPosition(5, this->_topBarHeight + marginStart + (i * 28));
        itemsToShow.at(i).render(this->_tft);
    }

    this->_scrollbar.setCurrentItem(this->_currentItemIndex);
    this->_scrollbar.render(tft);
}

void MenuScreen::addItem(MenuItem item)
{
    this->_items.push_back(item);

    if (this->_currentItemIndex < 0)
    {
        this->_currentItemIndex = 0;
        this->_items.at(0).setSelected(true);
    }

    this->_scrollbar.setTotalItems(this->_items.size());
}

void MenuScreen::addItems(std::vector<MenuItem> items)
{
    for (auto item : items)
        this->addItem(item);
}

void MenuScreen::removeItem(String id)
{
    // todo
    this->_scrollbar.setTotalItems(this->_items.size());
}

void MenuScreen::buttonNextPressed()
{
    if (this->_items.size() <= 1)
        return;

    this->getCurrentItem()->setSelected(false);

    if (this->_currentItemIndex == (this->_items.size() - 1)) // last item
    {
        this->_currentItemIndex = 0;
    }
    else
    {
        this->_currentItemIndex++;
    }

    this->getCurrentItem()->setSelected(true);

    ScreenManager::render();
}

void MenuScreen::buttonPreviousPressed()
{
    if (this->_items.size() <= 1)
        return;

    this->getCurrentItem()->setSelected(false);

    if (this->_currentItemIndex == 0) // first item
    {
        this->_currentItemIndex = this->_items.size() - 1;
    }
    else
    {
        this->_currentItemIndex--;
    }

    this->getCurrentItem()->setSelected(true);

    ScreenManager::render();
}

void MenuScreen::buttonSelectPressed()
{
    auto currentItem = this->getCurrentItem();
    auto subItems = currentItem->getItems();

    if (subItems.size() > 0)
    {
        auto subMenuScreen = new MenuScreen(this->_tft);

        subMenuScreen->addItems(subItems);

        ScreenManager::setCurrentScreen(subMenuScreen);
    }
    else if (currentItem->isDefinedOnClick())
    {
        currentItem->click();
    }
    else
    {
        ScreenManager::setCurrentScreen(new ComingSoonScreen(this->_tft));
    }
}
