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
        // Initialize Spinlocks
        deviceContext = GetDeviceContext(device);
        WdfSpinLockCreate(&deviceAttributes, &deviceContext->SpinLock);

        status = WdfDeviceCreateDeviceInterface(device, &GUID_DEVINTERFACE_VirtualHIDDriver, NULL);
        if (NT_SUCCESS(status))
        {
            status = VirtualHIDDriver_IoInitialize(device);
        }
    }

    return status;
}

VOID VirtualHIDDriverCleanupDevice(_In_ WDFOBJECT Device)
{
    PDEVICE_CONTEXT deviceContext;
    PQUEUE_CONTEXT queueContext;

    deviceContext = GetDeviceContext(Device);
    WdfSpinLockRelease(deviceContext->SpinLock);

    queueContext = GetQueueContext(Device);
    destroyCircularQueue(queueContext->circularQueue);
}
