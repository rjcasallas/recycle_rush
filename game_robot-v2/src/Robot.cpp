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
class Robot: public SampleRobot {

    const float SLOW_SPEED = 0.2;
    const float MEDIUM_SPEED = 0.5;
    const float FULL_SPEED = 0.8;


    Talon left_front;
    Talon right_front;
    Talon left_back;
    Talon right_back;
    Joystick stick; // only joystick
    Joystick stick2;
    WheelVector wheels_out;
    CANTalon crab_arms;
    Victor right_spinner;
    Victor left_spinner;
    CANTalon left_arm;
    CANTalon right_arm;
    AnalogInput sonar;
    DigitalInput main_arm_limit;


    //DigitalInput       ;






    /**

     float wheels_sideways, wheels_back_forward, wheels_rotate;
     float crab_forward, crab_backward;
     float crab_in_out;
     float crab_rotate;

     **/

public:
    Robot() :
            left_front(1), right_front(0), left_back(3), right_back(2),
            stick(0), stick2(1),
            crab_arms(0), right_spinner(4), left_spinner(5), left_arm(2), right_arm(1),
            sonar(0), main_arm_limit(0)
    {

    }

    /**
     * Drive left & right motors for 2 seconds then stop
     */
    void Autonomous() {

    }

    /**
     * Runs the motors with arcade steering.
     */
    void OperatorControl() {

        float wheels_sideways, wheels_back_forward, wheels_rotate;
        float crab_forward;
        float crab_backward;
        float crab_in_out;
        float crab_rotate;
        float arm_up_down;
        float arm_speed = MEDIUM_SPEED;  // medium speed



        while (IsOperatorControl() && IsEnabled())
        {

            if(stick2.GetRawButton(3))
            {
                arm_speed = SLOW_SPEED;
            }

            if(stick2.GetRawButton(1))
            {
               arm_speed = MEDIUM_SPEED;
            }
            if(stick2.GetRawButton(2))
            {
                arm_speed = FULL_SPEED;
            }

            wheels_sideways = stick.GetX(stick.kLeftHand);
            wheels_back_forward = stick.GetY(stick.kLeftHand);
            wheels_rotate = stick.GetRawAxis(4);
            crab_forward = stick2.GetRawAxis(3);
            crab_backward = stick2.GetRawAxis(2);
            crab_in_out = stick2.GetY(stick2.kLeftHand); // spinner in out
            crab_rotate = stick2.GetX(stick2.kLeftHand);  // spinner
            arm_up_down = stick2.GetRawAxis(5) * arm_speed;

            //
            // Mecanum section
            //

            wheels_out = WheelVector::calc(wheels_sideways,
                    -wheels_back_forward, wheels_rotate);
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

            if(main_arm_limit.Get() && arm_up_down > 0)
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


            crab_arms.Set(crab_forward - crab_backward);

            // spinners
            right_spinner.Set(crab_in_out - crab_rotate);
            left_spinner.Set(crab_rotate + crab_in_out);

            SmartDashboard::PutNumber("sonar value", sonar.GetValue());
            SmartDashboard::PutNumber("main_arm_limit", main_arm_limit.Get());
            SmartDashboard::PutNumber("arm_speed", arm_speed);
            Wait(.05);

        }

        /*while (IsOperatorControl() && IsEnabled())
         {
         Wait(0.005);				// wait for a motor update time
         }*/
    }

    /**
     * Runs during test mode
     */
    void Test() {
    }
};

START_ROBOT_CLASS(Robot);

