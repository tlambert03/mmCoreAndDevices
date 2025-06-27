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

#include "../../MMDevice/MMDevice.h"
#include "../../MMDevice/MMDeviceConstants.h"
#include <string>
#include <map>

class CMMCore;
class CorePropertyCollection;

/**
 * CoreDevice implements the MM::Device interface for the virtual "Core" device.
 * This device exposes Core properties (like Camera, Shutter, Focus, etc.) as
 * device properties, eliminating the need for special-case handling throughout
 * the Core.
 */
class CoreDevice : public MM::Device
{
public:
   CoreDevice(CMMCore* core);
   virtual ~CoreDevice();

   // MM::Device interface implementation
   virtual unsigned GetNumberOfProperties() const override;
   virtual int GetProperty(const char* name, char* value) const override;
   virtual int SetProperty(const char* name, const char* value) override;
   virtual bool HasProperty(const char* name) const override;
   virtual bool GetPropertyName(unsigned idx, char* name) const override;
   virtual int GetPropertyReadOnly(const char* name, bool& readOnly) const override;
   virtual int GetPropertyInitStatus(const char* name, bool& preInit) const override;
   virtual int HasPropertyLimits(const char* name, bool& hasLimits) const override;
   virtual int GetPropertyLowerLimit(const char* name, double& lowLimit) const override;
   virtual int GetPropertyUpperLimit(const char* name, double& hiLimit) const override;
   virtual int GetPropertyType(const char* name, MM::PropertyType& pt) const override;
   virtual unsigned GetNumberOfPropertyValues(const char* propertyName) const override;
   virtual bool GetPropertyValueAt(const char* propertyName, unsigned index, char* value) const override;

   // Sequence-related methods (not supported by Core device)
   virtual int IsPropertySequenceable(const char* name, bool& isSequenceable) const override;
   virtual int GetPropertySequenceMaxLength(const char* propertyName, long& nrEvents) const override;
   virtual int StartPropertySequence(const char* propertyName) override;
   virtual int StopPropertySequence(const char* propertyName) override;
   virtual int ClearPropertySequence(const char* propertyName) override;
   virtual int AddToPropertySequence(const char* propertyName, const char* value) override;
   virtual int SendPropertySequence(const char* propertyName) override;

   virtual bool GetErrorText(int errorCode, char* errMessage) const override;
   virtual bool Busy() override;
   virtual double GetDelayMs() const override;
   virtual void SetDelayMs(double delay) override;
   virtual bool UsesDelay() override;

   // Deprecated module handle methods
   virtual HDEVMODULE GetModuleHandle() const override;
   virtual void SetModuleHandle(HDEVMODULE hLibraryHandle) override;

   virtual void SetLabel(const char* label) override;
   virtual void GetLabel(char* name) const override;
   virtual void SetModuleName(const char* moduleName) override;
   virtual void GetModuleName(char* moduleName) const override;
   virtual void SetDescription(const char* description) override;
   virtual void GetDescription(char* description) const override;

   virtual int Initialize() override;
   virtual int Shutdown() override;

   virtual MM::DeviceType GetType() const override;
   virtual void GetName(char* name) const override;
   virtual void SetCallback(MM::Core* callback) override;

   // Device discovery API (not applicable to Core device)
   virtual bool SupportsDeviceDetection(void) override;
   virtual MM::DeviceDetectionStatus DetectDevice(void) override;

   // Hub-peripheral relationship (not applicable to Core device)
   virtual void SetParentID(const char* parentId) override;
   virtual void GetParentID(char* parentID) const override;

private:
   CMMCore* core_;                    // Reference to the Core (not owned)
   std::string label_;
   std::string description_;
   MM::Core* callback_;               // Core callback interface (not owned)
   
   // Helper methods
   CorePropertyCollection* getProperties() const;
};
