#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#include <vsg/vk/DeviceMemory.h>

namespace vsg
{
    class VSG_DECLSPEC Buffer : public Inherit<Object, Buffer>
    {
    public:
        Buffer(VkBuffer Buffer, VkBufferUsageFlags usage, VkSharingMode sharingMode, Device* device, AllocationCallbacks* allocator=nullptr);

        using Result = vsg::Result<Buffer, VkResult, VK_SUCCESS>;
        static Result create(Device* device, VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode, AllocationCallbacks* allocator=nullptr);

        VkBufferUsageFlags usage() const { return _usage; }
        VkSharingMode shaderMode() const { return _sharingMode; }
        VkBuffer buffer() const { return _buffer; }

        Device* getDevice() { return _device; }
        const Device* getDevice() const { return _device; }

        DeviceMemory* getDeviceMemory() { return _deviceMemory; }
        const DeviceMemory* getDeviceMemory() const { return _deviceMemory; }

        VkResult bind(DeviceMemory* deviceMemory, VkDeviceSize memoryOffset)
        {
            VkResult result = vkBindBufferMemory(*_device, _buffer, *deviceMemory, memoryOffset);
            if (result == VK_SUCCESS)
            {
                _deviceMemory = deviceMemory;
                _memoryOffset = memoryOffset;
            }
            return result;
        }

        operator VkBuffer () const { return _buffer; }

    protected:
        virtual ~Buffer();

        VkBuffer                        _buffer;
        VkBufferUsageFlags              _usage;
        VkSharingMode                   _sharingMode;


        ref_ptr<Device>                 _device;
        ref_ptr<AllocationCallbacks>    _allocator;

        ref_ptr<DeviceMemory>           _deviceMemory;
        VkDeviceSize                    _memoryOffset;
    };
}
