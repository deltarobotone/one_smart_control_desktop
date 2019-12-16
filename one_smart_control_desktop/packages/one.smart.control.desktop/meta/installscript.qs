function Component()
{
}

Component.prototype.createOperations = function()
{
    installer.gainAdminRights()
    component.createOperations();

    if (systemInfo.productType === "windows") {

        component.addOperation("CreateShortcut", "@TargetDir@/one_smart_control_desktop.exe", "@StartMenuDir@/One Smart Control Desktop.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/oneicon.ico",
            "description=Open One Smart Control");

        component.addOperation("CreateShortcut", "@TargetDir@/uninstall.bat", "@StartMenuDir@/Uninstall.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll","iconId=2",
            "description=Open One Smart Control");
    }
}