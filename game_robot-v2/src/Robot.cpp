#include "WPILib.h"
#include "WheelVector.h"

//
// Max + Ethan (No Homo)

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
    const float SLOW_SPEED = 0.2;
    const float MEDIUM_SPEED = 0.5;
    const float FULL_SPEED = 0.8;

    // Wheels
    Talon right_front;
    Talon left_front;
    Talon right_back;
    Talon left_back;
    WheelVector wheels_out;
    // Crab arms
    CANTalon crab_arms;
    Victor right_spinner;
    Victor left_spinner;
    // Raising arms
    CANTalon right_arm;
    CANTalon left_arm;
    // Joysticks
    Joystick stick;
    Joystick stick2;
    // Sensors and switches
    DigitalInput arm_low_limit;
    DigitalInput arm_high_limit;
    AnalogInput sonar;

public:
    Robot() :   right_front(0), left_front(1), right_back(2), left_back(3),
                crab_arms(0), right_spinner(4), left_spinner(5),
                left_arm(2), right_arm(1),
                stick(0), stick2(1),
                arm_low_limit(0), arm_high_limit(1), sonar(0)
    {

    }

    /**
     * Drive left & right motors for 2 seconds then stop
     */
    void Autonomous()
    {
        // TODO
    }

    /**
     * Runs the motors with arcade steering.
     */
    void OperatorControl()
    {
        float wheels_sideways, wheels_back_forward, wheels_rotate;
        float crab_back_forward;
        float crab_in_out;
        float crab_rotate;
        float arm_up;
        float arm_down;
        float arm_speed = MEDIUM_SPEED;

        while (IsOperatorControl() && IsEnabled())
        {
            // Buttons
            if(stick2.GetRawButton(3))
            {
                arm_speed = SLOW_SPEED;
            }
            else if(stick2.GetRawButton(1))
            {
               arm_speed = MEDIUM_SPEED;
            }
            else if(stick2.GetRawButton(2))
            {
                arm_speed = FULL_SPEED;
            }

            // Movements
            wheels_sideways = stick.GetX(stick.kLeftHand);
            wheels_back_forward = stick.GetY(stick.kLeftHand);
            wheels_rotate = stick.GetRawAxis(4);
            
            crab_back_forward = stick2.GetY(stick2.kLeftHand);
            crab_in_out = stick2.GetY(stick2.kRightHand);   // spinner in out
            crab_rotate = stick2.GetX(stick2.kRightHand);   // spinner

            arm_up = stick2.GetRawAxis(3) * arm_speed;
            arm_down = stick2.GetRawAxis(2) * arm_speed;
            
            //
            // Mecanum section
            //

            wheels_out = WheelVector::calc(wheels_sideways, -wheels_back_forward, wheels_rotate);
            wheels_out.zero(0.05);

            left_front.Set(wheels_out.getLeftFront());
            left_back.Set(wheels_out.getLeftBack());
            right_front.Set(wheels_out.getRightFront());
            right_back.Set(wheels_out.getRightBack());

            //
            // Picking arm section
            //

            // WARNING: LEFT HAS TO BE NEGATED FOR BOTH ARMS MOVE IN THE SAME DIRECTION
            //          OTHERWISE, THE ROBOT WILL BREAK!!!!!

            if( (arm_low_limit.Get() && arm_up_down > 0) || (arm_high_limit.Get() && arm_up_down < 0) )
            {
                left_arm.Set(0);
                right_arm.Set(0);
            }
            else
            {
                left_arm.Set(-arm_up_down);
                right_arm.Set(arm_up_down);
            }

            //
            //  Crab_Arms
            //

            crab_arms.Set(crab_back_forward);

            // spinners
            right_spinner.Set(crab_in_out - crab_rotate);
            left_spinner.Set(crab_rotate + crab_in_out);

            // Debug Outputs
            SmartDashboard::PutNumber("sonar value", sonar.GetValue());
            SmartDashboard::PutNumber("main_arm_limit", main_arm_limit.Get());
            SmartDashboard::PutNumber("arm_speed", arm_speed);

            Wait(.05);
        }
    }

    /**
     * Runs during test mode
     */
    void Test()
    {
        // TODO
    }
};

START_ROBOT_CLASS(Robot);

