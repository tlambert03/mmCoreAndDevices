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

#include "CoreDevice.h"
#include "../MMCore.h"
#include "../CoreProperty.h"
#include "../../MMDevice/DeviceUtils.h"
#include "../../MMDevice/MMDeviceConstants.h"
#include <cstring>

CoreDevice::CoreDevice(CMMCore* core) :
   core_(core),
   label_(MM::g_Keyword_CoreDevice),
   description_("Core device"),
   callback_(nullptr)
{
}

CoreDevice::~CoreDevice()
{
}

unsigned CoreDevice::GetNumberOfProperties() const
{
   CorePropertyCollection* props = getProperties();
   if (props)
   {
      std::vector<std::string> names = props->GetNames();
      return static_cast<unsigned>(names.size());
   }
   return 0;
}

int CoreDevice::GetProperty(const char* name, char* value) const
{
   if (!name || !value)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   std::string val = props->Get(name);
   CDeviceUtils::CopyLimitedString(value, val.c_str());
   return DEVICE_OK;
}

int CoreDevice::SetProperty(const char* name, const char* value)
{
   if (!name || !value)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   if (props->IsReadOnly(name))
      return DEVICE_INVALID_PROPERTY_VALUE;
   
   try
   {
      // Use Execute instead of Set to trigger property-specific logic
      props->Execute(name, value);
      return DEVICE_OK;
   }
   catch (...)
   {
      return DEVICE_INVALID_PROPERTY_VALUE;
   }
}

bool CoreDevice::HasProperty(const char* name) const
{
   if (!name)
      return false;
   
   CorePropertyCollection* props = getProperties();
   return props && props->Has(name);
}

bool CoreDevice::GetPropertyName(unsigned idx, char* name) const
{
   if (!name)
      return false;
   
   CorePropertyCollection* props = getProperties();
   if (!props)
      return false;
   
   std::vector<std::string> names = props->GetNames();
   if (idx >= names.size())
      return false;
   
   CDeviceUtils::CopyLimitedString(name, names[idx].c_str());
   return true;
}

int CoreDevice::GetPropertyReadOnly(const char* name, bool& readOnly) const
{
   if (!name)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   readOnly = props->IsReadOnly(name);
   return DEVICE_OK;
}

int CoreDevice::GetPropertyInitStatus(const char* name, bool& preInit) const
{
   if (!name)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   // Core properties are not pre-init properties
   preInit = false;
   return DEVICE_OK;
}

int CoreDevice::HasPropertyLimits(const char* name, bool& hasLimits) const
{
   if (!name)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   // Core properties don't have numeric limits (they use allowed values instead)
   hasLimits = false;
   return DEVICE_OK;
}

int CoreDevice::GetPropertyLowerLimit(const char* name, double& lowLimit) const
{
   // Core properties don't have numeric limits
   return DEVICE_INVALID_PROPERTY;
}

int CoreDevice::GetPropertyUpperLimit(const char* name, double& hiLimit) const
{
   // Core properties don't have numeric limits
   return DEVICE_INVALID_PROPERTY;
}

int CoreDevice::GetPropertyType(const char* name, MM::PropertyType& pt) const
{
   if (!name)
      return DEVICE_INVALID_PROPERTY;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(name))
      return DEVICE_INVALID_PROPERTY;
   
   // All core properties are strings
   pt = MM::String;
   return DEVICE_OK;
}

unsigned CoreDevice::GetNumberOfPropertyValues(const char* propertyName) const
{
   if (!propertyName)
      return 0;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(propertyName))
      return 0;
   
   std::vector<std::string> values = props->GetAllowedValues(propertyName);
   return static_cast<unsigned>(values.size());
}

bool CoreDevice::GetPropertyValueAt(const char* propertyName, unsigned index, char* value) const
{
   if (!propertyName || !value)
      return false;
   
   CorePropertyCollection* props = getProperties();
   if (!props || !props->Has(propertyName))
      return false;
   
   std::vector<std::string> values = props->GetAllowedValues(propertyName);
   if (index >= values.size())
      return false;
   
   CDeviceUtils::CopyLimitedString(value, values[index].c_str());
   return true;
}

// Sequence-related methods (not supported by Core device)
int CoreDevice::IsPropertySequenceable(const char* name, bool& isSequenceable) const
{
   isSequenceable = false;
   return DEVICE_OK;
}

int CoreDevice::GetPropertySequenceMaxLength(const char* propertyName, long& nrEvents) const
{
   nrEvents = 0;
   return DEVICE_UNSUPPORTED_COMMAND;
}

int CoreDevice::StartPropertySequence(const char* propertyName)
{
   return DEVICE_UNSUPPORTED_COMMAND;
}

int CoreDevice::StopPropertySequence(const char* propertyName)
{
   return DEVICE_UNSUPPORTED_COMMAND;
}

int CoreDevice::ClearPropertySequence(const char* propertyName)
{
   return DEVICE_UNSUPPORTED_COMMAND;
}

int CoreDevice::AddToPropertySequence(const char* propertyName, const char* value)
{
   return DEVICE_UNSUPPORTED_COMMAND;
}

int CoreDevice::SendPropertySequence(const char* propertyName)
{
   return DEVICE_UNSUPPORTED_COMMAND;
}

bool CoreDevice::GetErrorText(int errorCode, char* errMessage) const
{
   if (!errMessage)
      return false;
   
   // Use default device error messages
   CDeviceUtils::CopyLimitedString(errMessage, "Core device error");
   return true;
}

bool CoreDevice::Busy()
{
   // Core device is never busy
   return false;
}

double CoreDevice::GetDelayMs() const
{
   // Core device has no delay
   return 0.0;
}

void CoreDevice::SetDelayMs(double delay)
{
   // Core device ignores delay setting
}

bool CoreDevice::UsesDelay()
{
   // Core device doesn't use delay
   return false;
}

// Deprecated module handle methods
HDEVMODULE CoreDevice::GetModuleHandle() const
{
   return nullptr;
}

void CoreDevice::SetModuleHandle(HDEVMODULE hLibraryHandle)
{
   // Not applicable for Core device
}

void CoreDevice::SetLabel(const char* label)
{
   if (label)
      label_ = label;
}

void CoreDevice::GetLabel(char* name) const
{
   if (name)
      CDeviceUtils::CopyLimitedString(name, label_.c_str());
}

void CoreDevice::SetModuleName(const char* moduleName)
{
   // Not applicable for Core device
}

void CoreDevice::GetModuleName(char* moduleName) const
{
   if (moduleName)
      CDeviceUtils::CopyLimitedString(moduleName, "Core");
}

void CoreDevice::SetDescription(const char* description)
{
   if (description)
      description_ = description;
}

void CoreDevice::GetDescription(char* description) const
{
   if (description)
      CDeviceUtils::CopyLimitedString(description, description_.c_str());
}

int CoreDevice::Initialize()
{
   // Core device is always successfully initialized
   return DEVICE_OK;
}

int CoreDevice::Shutdown()
{
   // Nothing to shutdown for Core device
   return DEVICE_OK;
}

MM::DeviceType CoreDevice::GetType() const
{
   return MM::CoreDevice;
}

void CoreDevice::GetName(char* name) const
{
   if (name)
      CDeviceUtils::CopyLimitedString(name, "Core");
}

void CoreDevice::SetCallback(MM::Core* callback)
{
   callback_ = callback;
}

// Device discovery API (not applicable to Core device)
bool CoreDevice::SupportsDeviceDetection(void)
{
   return false;
}

MM::DeviceDetectionStatus CoreDevice::DetectDevice(void)
{
   return MM::Unimplemented;
}

// Hub-peripheral relationship (not applicable to Core device)
void CoreDevice::SetParentID(const char* parentId)
{
   // Core device has no parent
}

void CoreDevice::GetParentID(char* parentID) const
{
   if (parentID)
      CDeviceUtils::CopyLimitedString(parentID, "");
}

// Helper methods
CorePropertyCollection* CoreDevice::getProperties() const
{
   return core_ ? core_->getProperties() : nullptr;
}
