#include "driver.h"
#include "queue.tmh"
#include "loger.h"
#include "hidclass.h"
#include "hidsdi.h"


NTSTATUS VirtualHIDDriver_IoInitialize(_In_ WDFDEVICE Device)
{
    WDFQUEUE queue;
    NTSTATUS status;
    WDF_IO_QUEUE_CONFIG queueConfig;
    WDF_OBJECT_ATTRIBUTES queueAttributes;
    PQUEUE_CONTEXT queueContext;

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

    queueContext = GetQueueContext(queue);
    queueContext->deviceInputBufferSize = 0;

    return status;
}

VOID VirtualHIDDriver_IoDeviceControl(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    UNREFERENCED_PARAMETER(InputBufferLength);

    NTSTATUS status = STATUS_UNSUCCESSFUL;

    switch (IoControlCode)
    {
        case IOCTL_HID_GET_COLLECTION_DESCRIPTOR:
            write_log_message("VirtualHIDDriver_IoDeviceControl - IOCTL_HID_GET_COLLECTION_DESCRIPTOR");
            break;

        case IOCTL_HID_GET_COLLECTION_INFORMATION:
            status = GetCollectionInformation(Request, OutputBufferLength);
            break;

        case IOCTL_SET_NUM_DEVICE_INPUT_BUFFERS:
            status = SetNumDeviceInputBuffer(Queue, Request);
            break;

        default:
            write_log_message("VirtualHIDDriver_IoDeviceControl - default: ");
            status = STATUS_NOT_IMPLEMENTED;
            break;
    }

    WdfRequestComplete(Request, status);
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

NTSTATUS GetCollectionInformation(IN WDFREQUEST Request, IN size_t OutputBufferLength)
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    PHID_COLLECTION_INFORMATION hidInformation = NULL;
    ULONG_PTR information = 0;

    if (OutputBufferLength < sizeof(HID_COLLECTION_INFORMATION))
    {
        status = STATUS_BUFFER_TOO_SMALL;
        information = 0;
    }
    else
    {
        // Copy the HID_COLLECTION_INFORMATION to the output buffer.
        status = WdfRequestRetrieveOutputBuffer(Request, sizeof(HID_COLLECTION_INFORMATION), &hidInformation, NULL);
        if (!NT_SUCCESS(status))
        {
            return status;
        }

        hidInformation->DescriptorSize = sizeof(HID_COLLECTION_INFORMATION);
        hidInformation->VendorID = 0x0F3F;
        hidInformation->ProductID = 0x0101;
        hidInformation->VersionNumber = 0x0001;
        hidInformation->Polled = TRUE;

        information = sizeof(HID_COLLECTION_INFORMATION);
    }

    WdfRequestSetInformation(Request, information);

    return status;
}

NTSTATUS SetNumDeviceInputBuffer(IN WDFQUEUE Queue, IN WDFREQUEST Request)
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    PULONG pInputBuffer = NULL;
    PQUEUE_CONTEXT queueContext;

    status = WdfRequestRetrieveInputBuffer(Request, sizeof(ULONG), &pInputBuffer, NULL);
    if (!NT_SUCCESS(status))
    {
        return status;
    }

    queueContext = GetQueueContext(Queue);
    queueContext->deviceInputBufferSize = *pInputBuffer;

    return status;
}
