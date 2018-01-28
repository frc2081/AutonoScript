#include "AutonoScriptManager.h"

using namespace AutonoScript;

int main(int argc, char** argv)
{
  int ret;
  AutonoScriptManager* manager = new AutonoScriptManager();

  ret = manager->Run(argc, argv);

  delete manager;
  return ret;
}


