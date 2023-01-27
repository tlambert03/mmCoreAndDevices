#include <iostream>
#include <MMCore.h>

#define PROJECT_NAME "AcqEngC"

auto main() -> int
{

    CMMCore *mmc = new CMMCore();
    std::cout << "Core version: " << mmc->getAPIVersionInfo() << std::endl;
    std::string mdir = "/Users/talley/Library/Application Support/pymmcore-plus/mm/Micro-Manager-2.0.1-20230118";
    mmc->setDeviceAdapterSearchPaths({mdir});
    std::cout << "adapter paths: " << mmc->getDeviceAdapterSearchPaths()[0] << std::endl;
    mmc->loadSystemConfiguration("/Users/talley/Desktop/MMConfig_demo.cfg");
    std::cout << "Loaded config" << std::endl;
    for (std::string i : mmc->getLoadedDevices())
        std::cout << i << ' ';

    return 0;
}