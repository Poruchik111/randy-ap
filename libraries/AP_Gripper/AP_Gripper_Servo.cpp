#include <AP_Gripper/AP_Gripper_Servo.h>

#if AP_GRIPPER_SERVO_ENABLED

#include <GCS_MAVLink/GCS.h>
#include <AP_Logger/AP_Logger.h>
#include <SRV_Channel/SRV_Channel.h>

#if CONFIG_HAL_BOARD == HAL_BOARD_SITL
  #include <SITL/SITL.h>
#endif

extern const AP_HAL::HAL& hal;

void AP_Gripper_Servo::init_gripper()
{
    // move the servo to the neutral position
    SRV_Channels::set_output_pwm(SRV_Channel::k_gripper, config.neutral_pwm);
}

void AP_Gripper_Servo::grab()
{
    // check if we are already grabbing
    if (config.state == AP_Gripper::STATE_GRABBING) {
        // do nothing
        return;
    }

    // check if we are already grabbed
    if (config.state == AP_Gripper::STATE_GRABBED) {
        // inform user that we are already grabbed
        GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Gripper load grabbed");
        return;
    }

    // flag we are active and grabbing cargo
    config.state = AP_Gripper::STATE_GRABBING;

    // move the servo to the grab position
    SRV_Channels::set_output_pwm(SRV_Channel::k_gripper, config.grab_pwm);
    _last_grab_or_release = AP_HAL::millis();
    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Gripper load grabbing");
    LOGGER_WRITE_EVENT(LogEvent::GRIPPER_GRAB);
}


void AP_Gripper_Servo::release()
{
    // check if we are already releasing
    if (config.state == AP_Gripper::STATE_RELEASING) {
        // do nothing
        return;
    }
    
    // flag we are releasing cargo
    config.state = AP_Gripper::STATE_RELEASING;

    // move the servo to the release position
    SRV_Channels::set_output_pwm(SRV_Channel::k_gripper, config.release_pwm);
    _last_grab_or_release = AP_HAL::millis();
    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Gripper load releasing");
}

bool AP_Gripper_Servo::has_state_pwm(const uint16_t pwm) const
{
    // return true if servo is in position represented by pwm
    uint16_t current_pwm;
    if (!SRV_Channels::get_output_pwm(SRV_Channel::k_gripper, current_pwm)) {
        // function not assigned to a channel, perhaps?
        return false;
    }
    if (current_pwm != pwm) {
        // last action did not set pwm to the current value
        // (e.g. last action was a grab not a release)
        return false;
    }
    if (AP_HAL::millis() - _last_grab_or_release < SERVO_ACTUATION_TIME) {
        // servo still moving....
        return false;
    }
        //set PWM 0 after servo released
    SRV_Channels::set_output_pwm(SRV_Channel::k_gripper, config.neutral_pwm);

    return true;
}

bool AP_Gripper_Servo::released() const
{
    return (config.state == AP_Gripper::STATE_RELEASED);
}

// type-specific periodic updates:
void AP_Gripper_Servo::update_gripper()
{
    // Check for successful  released
   
    if (config.state == AP_Gripper::STATE_RELEASING && has_state_pwm(config.release_pwm)) {
        config.state = AP_Gripper::STATE_RELEASED;
        GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Gripper load released 82");
    }
}

bool AP_Gripper_Servo::valid() const
{
    if (!AP_Gripper_Backend::valid()) {
        return false;
    }
    if (!SRV_Channels::function_assigned(SRV_Channel::k_gripper)) {
        return false;
    }
    return true;
}

#endif  // AP_GRIPPER_SERVO_ENABLED
