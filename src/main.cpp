#include "DeviceSelect.h"
#include "applications/taskmanager/TaskManager.h"

using namespace Applications;

TaskManager *taskManager;

void setup()
{
  taskManager = new TaskManager();
  taskManager->begin();
}

void loop()
{
  taskManager->loop();
}
