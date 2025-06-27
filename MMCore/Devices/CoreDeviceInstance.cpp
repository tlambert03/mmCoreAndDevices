// PROJECT:       Micro-Manager
// SUBSYSTEM:     MMCore
//
// COPYRIGHT:     University of California, San Francisco, 2025,
//                All Rights reserved
//
// LICENSE:       This file is distributed under the "Lesser GPL" (LGPL) license.
//                License text is included with the source distribution.
//
//                This file is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty
//                of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//                IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//                INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES.

#include "CoreDeviceInstance.h"
#include "../MMCore.h"

CoreDeviceInstance::CoreDeviceInstance(CMMCore* core,
      mm::logging::Logger deviceLogger,
      mm::logging::Logger coreLogger) :
   DeviceInstance(core, nullptr, "Core", new CoreDevice(core), 
                  [](MM::Device* d) { delete d; }, MM::g_Keyword_CoreDevice, 
                  deviceLogger, coreLogger)
{
}

CoreDeviceInstance::~CoreDeviceInstance()
{
   // The base class destructor will call the delete function,
   // which will delete our CoreDevice
}

MM::DeviceType CoreDeviceInstance::GetType() const
{
   return MM::CoreDevice;
}

std::string CoreDeviceInstance::GetName() const
{
   return "Core";
}
