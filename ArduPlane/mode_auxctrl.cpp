#include "mode.h"
#include "Plane.h"
//add changes here

bool ModeAuxctrl::_enter()
{
    // Boilerplate from guided mode



    
    /*
    when entering guided mode we set the target as the current
    location. This matches the behaviour of the copter code
    */
    //plane.guided_WP_loc = plane.current_loc;Location loc{plane.current_loc};
    // Location loc{plane.current_loc};    
    // plane.set_guided_WP(loc);
    
    // // If plane is in guided mode and loitering in VTOL configuration
    // if(plane.quadplane.guided_mode_enabled())
    // {
    //     // Sets target position based on plane.next_WP_loc and initializes the poscontrol 
    //     // STATE of the vehicle (fixed wing or VTOL or transition phase)
    //     plane.quadplane.guided_start();
    //     // Put in VTOL mode if not already in VTOL. This might be redundant.
    //     if(!plane.auto_state.vtol_loiter)
    //     {
    //         plane.quadplane.set_vtol_loiter();
    //     }

    //     // clear pause state when entering guided mode for quadplane configuration
    //     // this allows for various submodes: angle control, position control
    //     // velocity control, etc.
    //     plane.quadplane.resume_qguided();
    //     // start in velocity control mode 
    //     plane.quadplane.vel_control_start();
    //     plane.quadplane.set_vel_guided_target_zero();
    //     gcs().send_text(MAV_SEVERITY_INFO,"Entered guided mode");
    // }

    return true;
}

void ModeAuxctrl::update()
{
    // Check if we are in VTOL mode
    if (plane.quadplane.in_vtol_mode() && plane.quadplane.available()) 
    {
        // run the velocity controller loop
        
    }
}
