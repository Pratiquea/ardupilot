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

//     if (plane.quadplane.guided_mode_enabled()) {
//         /*
//           if using Q_GUIDED_MODE then project forward by the stopping distance
//         */
//         plane.guided_WP_loc.offset_bearing(degrees(plane.ahrs.groundspeed_vector().angle()),
//                                            plane.quadplane.stopping_distance());
//     }
//     plane.set_guided_WP();
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
// Initializing controller here

bool ModeGuided::_enter()
{
    // start in velocity control mode (maintaining similar behaviour to copter)    
    plane.quadplane.vel_control_start();
    gcs().send_text(MAV_SEVERITY_INFO,"Entered guided mode and initiated 
        position control");
    
    //if guided mode doesn't start, perform the following checks:
    //  check plane.auto_state.vtol_loiter
    //  check plane.quadplane.available()

    return true;
}

void ModeGuided::update()
{
    if (plane.auto_state.vtol_loiter && plane.quadplane.available()) 
    {
        // To Do: Perform a check for initialization of vel_control_run()
        plane.quadplane.vel_control_run();
    }
}

void ModeGuided::navigate()
{
    gcs().send_text(MAV_SEVERITY_INFO,"In ModeGuided::navigate()");
    // Zero indicates to use WP_LOITER_RAD
    plane.update_loiter(0);
}

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
//Customization//

// guided_set_velocity - sets guided mode's target velocity
//void ModeGuided::set_velocity(const Vector3f& velocity, bool use_yaw, float yaw_cd, bool use_yaw_rate, float yaw_rate_cds, bool relative_yaw)
//{
    /* 
    //Prateek has modified this part..

    // check we are in velocity control mode
    if (guided_mode != SubMode::Velocity) {
        vel_control_start();
    }

    // set yaw state
    set_yaw_state(use_yaw, yaw_cd, use_yaw_rate, yaw_rate_cds, relative_yaw);

    // record velocity target
    guided_vel_target_cms = velocity;*/
//    vel_update_time_ms = millis();


//}

//Customization//
