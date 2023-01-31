#include "driver.h"
#include "device.tmh"
#include "loger.h"


NTSTATUS VirtualHIDDriverCreateDevice(_Inout_ PWDFDEVICE_INIT DeviceInit)
{
    WDF_OBJECT_ATTRIBUTES deviceAttributes;
    PDEVICE_CONTEXT deviceContext;
    WDFDEVICE device;
    NTSTATUS status;

    write_log_message("VirtualHIDDriverCreateDevice");

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);
    deviceAttributes.EvtCleanupCallback = VirtualHIDDriverCleanupDevice;

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

VOID VirtualHIDDriverCleanupDevice(_In_ WDFOBJECT Device)
{
    write_log_message("VirtualHIDDriverCleanupDevice");

    UNREFERENCED_PARAMETER(Device);
}
