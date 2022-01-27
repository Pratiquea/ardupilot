# Building ArduPlane - arduplane firmware #
This document is to simplify the main ArduPilot project BUILD.md file for ArduPlane firmware update.  

More details at Main project [BUILD.md](https://github.com/robowork/ardupilot/edit/feature/set_position_target_local_ned/BUILD.md)

Clone the project from GitHub:
```sh
git clone https://github.com/robowork/ardupilot.git
cd ardupilot
git submodule update --init --recursive
```

## Dependencies ##
- Windows environment
    - Cygwin Terminal (https://ardupilot.org/dev/docs/building-setup-windows-cygwin.html)  
(Note: ArduPlane.exe is generated in Windows environment)
## Basic usage ##

* **Build ArduPlane**  
    Run Cygwin Terminal from desktop as an Administrator

    ```sh
    cd <directory to Ardupilot repo>
    ./waf configure --board=sitl --toolchain i686-pc-cygwin
    ./waf -j8 plane
    ```  
    After compilation is done, `ArduPlane.exe` file which is generated in `~/ardupilot/build/sitl/bin/arduplane.exe` can be copy & paste to MissionPlanner sitl directory which is in `~/Documents/Mission Planner/sitl`.  