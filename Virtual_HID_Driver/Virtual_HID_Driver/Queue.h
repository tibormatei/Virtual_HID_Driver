#pragma once

EXTERN_C_START

typedef struct _QUEUE_CONTEXT {

    ULONG PrivateDeviceData;  // just a placeholder

} QUEUE_CONTEXT, *PQUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(QUEUE_CONTEXT, QueueGetContext)

NTSTATUS VirtualHIDDriverQueueInitialize(_In_ WDFDEVICE Device);

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL VirtualHIDDriver_IoDeviceControl;
EVT_WDF_IO_QUEUE_IO_READ VirtualHIDDriver_IoRead;
EVT_WDF_IO_QUEUE_IO_WRITE VirtualHIDDriver_IoWrite;
EVT_WDF_IO_QUEUE_IO_CANCELED_ON_QUEUE VirtualHIDDriver_IoCancel;
EVT_WDF_IO_QUEUE_IO_STOP VirtualHIDDriver_IoStop;

EXTERN_C_END
