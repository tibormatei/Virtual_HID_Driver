#include "driver.h"
#include "driver.tmh"


NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;
    WDF_OBJECT_ATTRIBUTES attributes;

#if UMDF_VERSION_MAJOR == 2 && UMDF_VERSION_MINOR == 0
    WPP_INIT_TRACING(MYDRIVER_TRACING_ID);
#else
    WPP_INIT_TRACING(DriverObject, RegistryPath);
#endif

    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = DriverContextCleanup;

    WDF_DRIVER_CONFIG_INIT(&config, DeviceAdd);

    status = WdfDriverCreate(DriverObject, RegistryPath, &attributes, &config, WDF_NO_HANDLE);

    if (!NT_SUCCESS(status))
    {
#if UMDF_VERSION_MAJOR == 2 && UMDF_VERSION_MINOR == 0
        WPP_CLEANUP();
#else
        WPP_CLEANUP(DriverObject);
#endif
        return status;
    }

    return status;
}

NTSTATUS DeviceAdd(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    UNREFERENCED_PARAMETER(Driver);

    NTSTATUS status = VirtualHIDDriverCreateDevice(DeviceInit);

    return status;
}

VOID DriverContextCleanup(_In_ WDFOBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

#if UMDF_VERSION_MAJOR == 2 && UMDF_VERSION_MINOR == 0
    WPP_CLEANUP();
#else
    WPP_CLEANUP(WdfDriverWdmGetDriverObject((WDFDRIVER)DriverObject));
#endif
}
