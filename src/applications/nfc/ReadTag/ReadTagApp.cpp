#include "ReadTagApp.h"
#include "ReadTagMenuScreen.h"

using namespace Applications::Nfc::ReadTag;

void ReadTagApp::app_main(std::shared_ptr<AppContext> appContext)
{
    appContext->getScreeManager()->setCurrentScreen<ReadTagMenuScreen>();
}
