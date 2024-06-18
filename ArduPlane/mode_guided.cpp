#include "mode.h"
#include "Plane.h"

// bool ModeGuided::_enter()
// {
//     plane.guided_throttle_passthru = false;
//     /*
//       when entering guided mode we set the target as the current
//       location. This matches the behaviour of the copter code
//     */
//     plane.guided_WP_loc = plane.current_loc;

// #if HAL_QUADPLANE_ENABLED
//     if (plane.quadplane.guided_mode_enabled()) {
//         /*
//           if using Q_GUIDED_MODE then project forward by the stopping distance
//         */
//         plane.guided_WP_loc.offset_bearing(degrees(plane.ahrs.groundspeed_vector().angle()),
//                                            plane.quadplane.stopping_distance());
//     }
// #endif

//     plane.set_guided_WP();
//     return true;
// }

bool ModeGuided::_enter()
{
    plane.guided_throttle_passthru = false;
    /*
    when entering guided mode we set the target as the current
    location. This matches the behaviour of the copter code
    */
    plane.guided_WP_loc = plane.current_loc;

#if HAL_QUADPLANE_ENABLED
    // If plane is in guided mode and loitering in VTOL configuration
    if(plane.quadplane.guided_mode_enabled())
    {
        // Sets target position based on plane.next_WP_loc and initializes the poscontrol 
        // STATE of the vehicle (fixed wing or VTOL or transition phase)
        plane.quadplane.guided_start();
        // // Put in VTOL mode if not already in VTOL. This might be redundant.
        // if(!plane.quadplane.in_vtol_mode())
        // {
        //     plane.quadplane.set_vtol_loiter();
        // }

        // clear pause state when entering guided mode for quadplane configuration
        // this allows for various submodes: angle control, position control
        // velocity control, etc.
        plane.quadplane.resume_qguided();
        // start in velocity control mode 
        plane.quadplane.vel_control_start();
        plane.quadplane.set_vel_guided_target_zero();
        gcs().send_text(MAV_SEVERITY_INFO,"Entered guided mode");
    }
#endif
    
    plane.set_guided_WP();
    return true;
}

void ModeGuided::update()
{
    // Check if we are in VTOL mode
    if (plane.quadplane.in_vtol_mode() && plane.quadplane.available()) 
    {
        // run the velocity controller loop
        plane.quadplane.guided_update();
    }
}

// void ModeGuided::update()
// {
// #if HAL_QUADPLANE_ENABLED
//     if (plane.auto_state.vtol_loiter && plane.quadplane.available()) {
//         plane.quadplane.guided_update();
//         return;
//     }
// #endif
//     plane.calc_nav_roll();
//     plane.calc_nav_pitch();
//     plane.calc_throttle();
// }

// void ModeGuided::navigate()
// {
//     // Zero indicates to use WP_LOITER_RAD
//     plane.update_loiter(0);
// }

bool ModeGuided::handle_guided_request(Location target_loc)
{
    plane.guided_WP_loc = target_loc;

    // add home alt if needed
    if (plane.guided_WP_loc.relative_alt) {
        plane.guided_WP_loc.alt += plane.home.alt;
        plane.guided_WP_loc.relative_alt = 0;
    }

    plane.set_guided_WP();

    return true;
}
