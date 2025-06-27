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

#pragma once

#include "DeviceInstance.h"
#include "CoreDevice.h"

/**
 * CoreDeviceInstance wraps the CoreDevice to implement the DeviceInstance interface.
 * This allows the Core device to be managed like any other device in the system.
 */
class CoreDeviceInstance : public DeviceInstance
{
public:
   CoreDeviceInstance(CMMCore* core,
         mm::logging::Logger deviceLogger,
         mm::logging::Logger coreLogger);
   virtual ~CoreDeviceInstance();

   // DeviceInstance interface is inherited and implemented by base class
   MM::DeviceType GetType() const;
   std::string GetName() const;

   // Access the core device (for any specific operations)
   CoreDevice* GetCoreDevice() const { return static_cast<CoreDevice*>(pImpl_); }
};
