devcon /r remove "HID\VID_0F3F&PID_0101"
pnputil.exe /delete-driver oem16.inf /force
devcon install Virtual_HID_Driver.inf "HID\VID_0F3F&PID_0101"
devcon enable "HID\VID_0F3F&PID_0101"