#include "driver.h"
#include "device.tmh"


NTSTATUS VirtualHIDDriverCreateDevice(_Inout_ PWDFDEVICE_INIT DeviceInit)
{
    WDF_OBJECT_ATTRIBUTES deviceAttributes;
    PDEVICE_CONTEXT deviceContext;
    WDFDEVICE device;
    NTSTATUS status;

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);

    status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);

    if (NT_SUCCESS(status))
    {
        deviceContext = DeviceGetContext(device);

        deviceContext->PrivateDeviceData = 0;

        status = WdfDeviceCreateDeviceInterface(device, &GUID_DEVINTERFACE_VirtualHIDDriver, NULL);

        if (NT_SUCCESS(status))
        {
            status = VirtualHIDDriverQueueInitialize(device);
        }
    }

    return status;
}
