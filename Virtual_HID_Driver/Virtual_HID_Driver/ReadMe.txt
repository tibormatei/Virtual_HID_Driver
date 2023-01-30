========================================================================
    Virtual_HID_Driver Project Overview
========================================================================

Ff you don't have windows signed driver license, you have to set unsigned driver settings

Step1: press Shift + click Restart
Step2: Troubleshoot > Advanced options > Startup Settings > Restart
Step3: To install driver without digital signature, press F7 to choose the Disable driver signature enforcement option.

---------------

cmd commands:

Install Driver:
devcon install Virtual_HID_Driver.inf Root\UMDF_Driver_Test1   // example: "USB\VID_0F3F&PID_0101"

Enable Device:
devcon enable Root\UMDF_Driver_Test1

Remove Device:
devcon /r remove "Root\UMDF_Driver_Test1"

Delete Driver:
pnputil.exe /delete-driver oem16.inf /force

Find Device:
devcon find *Test1*

Enumerate Drivers:
pnputil /enum-drivers > driver_List.txt

---------------
