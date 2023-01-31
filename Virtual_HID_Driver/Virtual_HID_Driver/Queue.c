#include "driver.h"
#include "queue.tmh"
#include "loger.h"


NTSTATUS VirtualHIDDriverQueueInitialize(_In_ WDFDEVICE Device)
{
    WDFQUEUE queue;
    NTSTATUS status;
    WDF_IO_QUEUE_CONFIG queueConfig;
    WDF_OBJECT_ATTRIBUTES queueAttributes;

    write_log_message("VirtualHIDDriverQueueInitialize");

    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&queueConfig, WdfIoQueueDispatchParallel);

    queueConfig.EvtIoDeviceControl = VirtualHIDDriver_IoDeviceControl;
    queueConfig.EvtIoRead = VirtualHIDDriver_IoRead;
    queueConfig.EvtIoWrite = VirtualHIDDriver_IoWrite;
    queueConfig.EvtIoCanceledOnQueue = VirtualHIDDriver_IoCancel;
    queueConfig.EvtIoStop = VirtualHIDDriver_IoStop;

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&queueAttributes, QUEUE_CONTEXT);

    status = WdfIoQueueCreate(Device, &queueConfig, &queueAttributes, &queue);

    if(!NT_SUCCESS(status))
    {
        return status;
    }

    return status;
}

VOID VirtualHIDDriver_IoDeviceControl(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    write_log_message("VirtualHIDDriver_IoDeviceControl");

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);
    UNREFERENCED_PARAMETER(IoControlCode);

    WdfRequestComplete(Request, STATUS_SUCCESS);

    return;
}

VOID VirtualHIDDriver_IoRead(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t InputBufferLength)
{
    write_log_message("VirtualHIDDriver_IoRead");

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Request);
    UNREFERENCED_PARAMETER(InputBufferLength);
}

VOID VirtualHIDDriver_IoWrite(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t InputBufferLength)
{
    write_log_message("VirtualHIDDriver_IoWrite");

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Request);
    UNREFERENCED_PARAMETER(InputBufferLength);
}

VOID VirtualHIDDriver_IoCancel(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request)
{
    write_log_message("VirtualHIDDriver_IoCancel");

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Request);
}

VOID VirtualHIDDriver_IoStop(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ ULONG ActionFlags)
{
    write_log_message("VirtualHIDDriver_IoStop");

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Request);
    UNREFERENCED_PARAMETER(ActionFlags);

    return;
}
