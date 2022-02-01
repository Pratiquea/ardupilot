#include "mode.h"
#include "Plane.h"

// bool ModeGuided::_enter()
// {
//     plane.guided_throttle_passthru = false;
//     /*
//       when entering guided mode we set the target as the current
//       location. This matches the behaviour of the copter code
//    */
//     plane.guided_WP_loc = plane.current_loc;

//     if (plane.quadplane.guided_mode_enabled()) {
//         /*
//           if using Q_GUIDED_MODE then project forward by the stopping distance
//         */
//         plane.guided_WP_loc.offset_bearing(degrees(plane.ahrs.groundspeed_vector().angle()),
//                                            plane.quadplane.stopping_distance());
//     }
//    plane.set_guided_WP();
//     return true;
// }

// void ModeGuided::update()
// {
//     if (plane.auto_state.vtol_loiter && plane.quadplane.available()) {
//         plane.quadplane.guided_update();
//     } else {
//         plane.calc_nav_roll();
//         plane.calc_nav_pitch();
//         plane.calc_throttle();
//     }
// }

// void ModeGuided::navigate()
// {
//     // Zero indicates to use WP_LOITER_RAD
//     plane.update_loiter(0);
// }

// Guided mode to work with external_navigation such as a VIO system (eg intel 
// realsense T265)
// Initializing controller in _enter() method

bool ModeGuided::_enter()
{
    // If plane is in guided mode and loitering in VTOL configuration
    if(plane.quadplane.guided_mode_enabled())
    {
        // Sets target position based on plane.next_WP_loc and initializes the poscontrol 
        // STATE of the vehicle (fixed wing or VTOL or transition phase)
        plane.quadplane.guided_start();
        // Put in VTOL mode if not already in VTOL. This might be redundant.
        if(!plane.auto_state.vtol_loiter)
        {
            plane.quadplane.set_vtol_loiter();
        }
        // start in velocity control mode (maintaining similar behaviour to copter)
        plane.quadplane.vel_control_start();
        gcs().send_text(MAV_SEVERITY_INFO,"initiated velocity control in guided mode");
    }
    return true;
}

void ModeGuided::update()
{
    // Check if we are in VTOL mode
    if (plane.auto_state.vtol_loiter && plane.quadplane.available()) 
    {
        // run the velocity controller loop
        plane.quadplane.guided_update();
    }
}

// removing navigate mehtod since we don't need waypoint navigation for
// auto docking.
// void ModeGuided::navigate()
// {
// }

bool ModeGuided::handle_guided_request(Location target_loc)
{
    // add home alt if needed
    if (target_loc.relative_alt) {
        target_loc.alt += plane.home.alt;
        target_loc.relative_alt = 0;
    }

    plane.set_guided_WP(target_loc);

    return true;
}