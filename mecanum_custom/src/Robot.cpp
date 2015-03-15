#include "WPILib.h"
#include "WheelVector.h"

class Robot: public SampleRobot
{
private:
   //double RAD_TO_NORMAL = 1.0 / 850;
   //double K = 0.8;
   double SpinnerMaxSpeed = 0.2;

   Joystick stick; // only joystick
   Joystick stick2;
   Talon left_front;
   Talon left_back;
   Talon right_front;
   Talon right_back;
   Victor RightSpinner;
   Victor LeftSpinner;
   CANTalon crab_arms;
   CANTalon left_arm;
   CANTalon right_arm;
   WheelVector input;
   WheelVector desired_out;
   DigitalInput Sensor1;
   DigitalInput Sensor2;
   LiveWindow *lw;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			desired_out = WheelVector::calc(stick.GetX(stick.kLeftHand), -stick.GetY(stick.kLeftHand), stick.GetRawAxis(4));
			desired_out.zero(0.2);

			//WheelVector actual_out(left_front_encoder.GetRate(), left_back_encoder.GetRate(), right_front_encoder.GetRate(), right_back_encoder.GetRate());
			//WheelVector actual_out;

			//actual_out = actual_out * RAD_TO_NORMAL;
			//input = input + (desired_out - actual_out) * K;
			input = desired_out;
			//input.limit(1.0);

			printf("gamepad: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", desired_out.getLeftFront(), desired_out.getLeftBack(), desired_out.getRightFront(), desired_out.getRightBack());
			//printf("sensors: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", actual_out.getLeftFront(), actual_out.getLeftBack(), actual_out.getRightFront(), actual_out.getRightBack());
			printf("output:  left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n\n", input.getLeftFront(), input.getLeftBack(), input.getRightFront(), input.getRightBack());
			//printf("encoder: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", 0.0, 0.0, encoder, 0.0);

			left_front.Set(input.getLeftFront());
			left_back.Set(input.getLeftBack());
			right_front.Set(input.getRightFront());
			right_back.Set(input.getRightBack());

			right_arm.Set(stick2.GetY());
			if (stick2.GetX() > 0)
			{
				if (not Sensor1.Get())
				{
					crab_arms.Set(stick2.GetX());
				}
				else
				{
					crab_arms.Set(0);
				}
			}
			else if (stick2.GetX() < 0)
			{
				if (not Sensor2.Get())
				{
					crab_arms.Set(stick2.GetX());
				}
				else
				{
					crab_arms.Set(0);
				}
			}

			left_arm.Set(-stick2.GetY());

			if (stick.GetRawButton(3))
			{
				LeftSpinner.Set(SpinnerMaxSpeed);
				RightSpinner.Set(SpinnerMaxSpeed);
			}
			else if (stick.GetRawButton(2))
			{
				LeftSpinner.Set(-SpinnerMaxSpeed);
				RightSpinner.Set(-SpinnerMaxSpeed);
			}
			else
			{
				LeftSpinner.Set(0);
				RightSpinner.Set(0);
			}

			//SmartDashboard::PutNumber("Stick",stick.GetY());
			SmartDashboard::PutNumber("Left Front", input.getLeftFront());
			SmartDashboard::PutNumber("Left Back", input.getLeftBack());
			SmartDashboard::PutNumber("Right Front", input.getRightFront());
			SmartDashboard::PutNumber("Right Back", input.getRightBack());
			//SmartDashboard::PutNumber("X left", stick.GetX(stick.kLeftHand));
			SmartDashboard::PutNumber("0", stick.GetRawAxis(0));
			SmartDashboard::PutNumber("1", stick.GetRawAxis(1));
			SmartDashboard::PutNumber("2", stick.GetRawAxis(2));
			SmartDashboard::PutNumber("3", stick.GetRawAxis(3));
			SmartDashboard::PutNumber("4", stick.GetRawAxis(4));
			SmartDashboard::PutNumber("5", stick.GetRawAxis(5));
			SmartDashboard::PutNumber("6", stick.GetRawAxis(6));
			SmartDashboard::PutNumber("Sensor 1", Sensor1.Get());
			SmartDashboard::PutNumber("Sensor 2", Sensor2.Get());
			printf("stick = %f\n", stick.GetY());

			Wait(0.005); // wait for a motor update time
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}

public:
   Robot() :
      stick(0), stick2(1), left_front(1), left_back(3), right_front(0), right_back(2),left_arm(2), right_arm(1), crab_arms(0),
	  RightSpinner(4),LeftSpinner(5),Sensor1(0),Sensor2(1)/*,
      left_front_encoder(1, 2), left_back_encoder(3, 4), right_front_encoder(5, 6), right_back_encoder(7, 8)*/
   {
      //this->SetPeriod(0); //Set update period to sync with robot control packets (20ms nominal)
      //left_front_encoder.SetDistancePerPulse(1.0);
      //left_back_encoder.SetDistancePerPulse(1.0);
      //right_front_encoder.SetDistancePerPulse(1.0);
      //right_back_encoder.SetDistancePerPulse(1.0);
      // left_front_encoder.Start();
      // left_back_encoder.Start();
      // right_front_encoder.Start();
      // right_back_encoder.Start();
   }
};

START_ROBOT_CLASS(Robot);
