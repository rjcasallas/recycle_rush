#include "WPILib.h"
#include "WheelVector.h"

//Competition Script

//
// Max and Ethan's Script ()
//

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
    Robot() :
            right_front(0), left_front(1), right_back(2), left_back(3), crab_arms(0), right_spinner(4), left_spinner(5), right_arm(1), left_arm(2), stick(0), stick2(1), arm_low_limit(0), arm_high_limit(
                    1), sonar(0)
    {

    }

    void RobotInit() override
    {
        CameraServer::GetInstance()->SetQuality(50);
        //the camera name (ex "cam0") can be found through the roborio web interface
        CameraServer::GetInstance()->StartAutomaticCapture("cam2");
    }

    /**
     * Drive left & right motors for 2 seconds then stop
     */

    void Autonomous()
    {

        // TODO

        // (front = x )(sideways = Y)(rotation = Z)

        SetWheels(-0.2, 0, 0);

        Wait(1.5);  //    for 2 seconds

        SetWheels(0, 0, 0);

        Wait(1);

        /*


         RiseArm(0.31, 0, false);

         Wait(2);

         RiseArm(0, 0, false);

         Wait(1.0);

         SetWheels(0.3, 0, 0);

         Wait(1.5);  //    for 2 seconds

         SetWheels(0, 0, 0);

         Wait(3);

         RiseArm(-0.2, 0, false);

         Wait(1);



         /******


         // Wait(0.5);

         crab_arms.Set(-0.3);



         Wait(2.5);




         right_spinner.Set(0.6);
         left_spinner.Set(-0.6);

         Wait(1.5);


         right_spinner.Set(0);
         left_spinner.Set(0);


         Wait(0.5);

         crab_arms.Set(0.2);

         Wait(1.9);


         crab_arms.Set(0);

         Wait(0.5);
         //bars for lifting
         // right_arm.Set(0.2);
         // left_arm.Set(-0.2);
         Wait(1);

         right_arm.Set(0);
         left_arm.Set(0);
         Wait(0.5);


         *****/

    }

    /**
     * Runs the motors with arcade steering.
     */

    void SetWheels(float backforward_speed, float sideways_speed, float rotate_speed)
    {

        wheels_out = WheelVector::calc(-sideways_speed, -backforward_speed, -rotate_speed);
        wheels_out.zero(0.02);

        left_front.Set(wheels_out.getLeftFront());
        left_back.Set(wheels_out.getLeftBack());
        right_front.Set(wheels_out.getRightFront());
        right_back.Set(wheels_out.getRightBack());

    }

    void RiseArm(float arm_up, float arm_down, bool override)

    {
        if (arm_up > FULL_SPEED)
        {
            arm_up = FULL_SPEED;
        }

        if (arm_up < 0)
        {
            arm_up = 0;
        }

        if (arm_down > FULL_SPEED)
        {
            arm_down = FULL_SPEED;
        }

        if (arm_down < 0)
        {
            arm_down = 0;
        }

        float arm_up_down = arm_down - arm_up;

        if (((arm_low_limit.Get() && arm_down > 0) || (arm_high_limit.Get() && arm_up > 0)) && !override)
        {
            left_arm.Set(0);
            right_arm.Set(0);
        }

        else

        {
            left_arm.Set(arm_up_down);
            right_arm.Set(arm_up_down);

        }

    }

    void ExtendArms(float back_forward)
    {
        if (back_forward > FULL_SPEED)
        {
            back_forward = FULL_SPEED;
        }

        if (back_forward < -FULL_SPEED)
        {
            back_forward = -FULL_SPEED;
        }

        crab_arms.Set(back_forward);

    }

    void SetSpinner(float crab_rotate, float crab_in_out)

    {
        if (crab_rotate > FULL_SPEED)
        {
            crab_rotate = FULL_SPEED;
        }

        if (crab_rotate < -FULL_SPEED)
        {
            crab_rotate = -FULL_SPEED;
        }

        if (crab_in_out > FULL_SPEED)
        {
            crab_in_out = FULL_SPEED;
        }

        if (crab_in_out < -FULL_SPEED)
        {
            crab_in_out = -FULL_SPEED;
        }

        right_spinner.Set(crab_rotate + crab_in_out);
        left_spinner.Set(crab_rotate - crab_in_out);

    }

    //void CrabArmSpinner

    void OperatorControl()
    {
        float wheels_sideways, wheels_back_forward, wheels_rotate;
        float crab_back_forward;
        float crab_in_out;
        float crab_rotate;
        float arm_up;
        float arm_down;
        float wheel_speed = MEDIUM_SPEED;
        float arm_speed = MEDIUM_SPEED;
        bool override = false;

        while (IsOperatorControl() && IsEnabled())
        {
            // Wheel Driver's Buttons
            if (stick.GetRawButton(3))

            {
                wheel_speed = SLOW_SPEED;
            }

            else if (stick.GetRawButton(1))

            {
                wheel_speed = MEDIUM_SPEED;
            }

            else if (stick.GetRawButton(2))

            {

                wheel_speed = FULL_SPEED;
            }

            // Arm Driver's Buttons
            if (stick2.GetRawButton(3))

            {

                arm_speed = SLOW_SPEED;
            }

            else if (stick2.GetRawButton(1))

            {
                arm_speed = MEDIUM_SPEED;
            } else if (stick2.GetRawButton(2))

            {
                arm_speed = FULL_SPEED;
            }
            // EMERGENCY OVERRIDE!!
            if (stick2.GetRawButton(7))
            {
                override = false;
            }
            if (stick2.GetRawButton(8))
            {
                override = true;
            }

            // Movements
            wheels_sideways = stick.GetX(stick.kLeftHand) * wheel_speed;
            wheels_back_forward = stick.GetY(stick.kLeftHand) * wheel_speed;
            wheels_rotate = stick.GetRawAxis(4) * wheel_speed;

            crab_back_forward = stick2.GetY(stick2.kLeftHand) * arm_speed;
            crab_in_out = stick2.GetRawAxis(5) * arm_speed;   // spinner in out
            crab_rotate = stick2.GetRawAxis(4) * arm_speed;  // spinner

            arm_up = stick2.GetRawAxis(3) * arm_speed;
            arm_down = stick2.GetRawAxis(2) * arm_speed;

            //
            // Mecanum section
            //

            SetWheels(wheels_back_forward, wheels_sideways, wheels_rotate);

            //
            // Picking arm section
            //

            // WARNING: LEFT HAS TO BE NEGATED FOR BOTH ARMS MOVE IN THE SAME DIRECTION
            //          OTHERWISE, THE ROBOT WILL BREAK!!!!!

            RiseArm(arm_up, arm_down, override);

            //
            //  Crab_Arms
            //

            ExtendArms(crab_back_forward);

            // spinners

            SetSpinner(crab_rotate, crab_in_out);

            // Debug Outputs
            SmartDashboard::PutNumber("sonar value", sonar.GetValue());
            SmartDashboard::PutNumber("arm_low_limit", arm_low_limit.Get());
            SmartDashboard::PutNumber("arm_high_limit", arm_high_limit.Get());
            SmartDashboard::PutNumber("arm_up", arm_up);
            SmartDashboard::PutNumber("arm_down", arm_down);
            SmartDashboard::PutNumber("arm_speed", arm_speed);
            SmartDashboard::PutNumber("override", override);

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

