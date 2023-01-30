EXTERN_C_START

typedef struct _QUEUE_CONTEXT {

    ULONG PrivateDeviceData;  // just a placeholder

} QUEUE_CONTEXT, *PQUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(QUEUE_CONTEXT, QueueGetContext)

NTSTATUS VirtualHIDDriverQueueInitialize(_In_ WDFDEVICE Device);

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL VirtualHIDDriverEvtIoDeviceControl;
EVT_WDF_IO_QUEUE_IO_STOP VirtualHIDDriverEvtIoStop;

EXTERN_C_END
