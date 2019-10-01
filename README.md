<Img src="https://github.com/deltarobotone/image_database/blob/master/logos/logos%20(8).PNG" width=500>

# [**>>>Download here<<<**](https://github.com/deltarobotone/one_smart_control_desktop/archive/v0.1-install.zip)
# One Smart Control Desktop Software  

We recommend to download the official offline installer. Unzip the package and run the **OneSmartControlDesktopInstaller.exe** to install the application on your Windows 10 system (64 bit). A few steps later you can find a new entry in your start-menu. Launch the One Smart Control Desktop Application and have some fun with Delta-Robot One. We recommend a screen with a minimum of 1600x900 pixels to display the application in full size. 

For more information about One Smart Control have look on the wiki page of this repository.

[**>>>One Smart Control Wiki<<<**](https://github.com/deltarobotone/one_smart_control_desktop/wiki)

The One Smart Control Application is written in C++ using the Qt-Creator IDE and Qt-Framework. Check out the development branch of this repository and have a look at the sourcecode.

[**>>>Development Branch (Master)<<<**](https://github.com/deltarobotone/one_smart_control_desktop/tree/master)

If you want to use the raw build files you can get these at the build branch.

[**>>>Pre-Build (Windows 10)<<<**](https://github.com/deltarobotone/one_smart_control_desktop/tree/prebuild-win10)

# Overview and short introduction

One Smart Control Desktop provides control functions on the left side (if a robot is connected the commands run directly!). The center of this application contains a visualisation of the robot workingspace. Below th Workingspace are some buttons to etablish a connection to your Delta-Robot One. On the right side a flowchart represents a robot program (here prefilled). The toolbar below the chart provides add, change and delete functions. You can run, save or load a program using this toolbar.

[<img src="https://raw.githubusercontent.com/deltarobotone/image_database/master/smart_control/smart_control%20(1).png" width="1000">](https://raw.githubusercontent.com/deltarobotone/image_database/master/smart_control/smart_control%20(1).png)



At this image the robots tool center point (TCP) is moved to the right side means positive y-axis. The Gripper is closed (blue TCP) and the green light of the robot is enabled with full intensity. The TCP is near the workingspace limit. The reachable position (x,y) depends on the z-axis. The workingspace is splitted in some levels which are displayed on the vectical scale near the working area. The outside area (filled with pattern) is not reachable at the actual workingspace level.

[<img src="https://raw.githubusercontent.com/deltarobotone/image_database/master/smart_control/smart_control%20(2).png" width="1000">](https://raw.githubusercontent.com/deltarobotone/image_database/master/smart_control/smart_control%20(2).png)
