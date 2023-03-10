#pragma once

#include "public.h"


EXTERN_C_START

typedef struct _DEVICE_CONTEXT
{
    WDFSPINLOCK SpinLock;

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext)

NTSTATUS VirtualHIDDriverCreateDevice(_Inout_ PWDFDEVICE_INIT DeviceInit);
EVT_WDF_OBJECT_CONTEXT_CLEANUP VirtualHIDDriverCleanupDevice;

EXTERN_C_END
