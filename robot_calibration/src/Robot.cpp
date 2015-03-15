#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw;
	Joystick stick;
	Talon left_front;
	Talon left_back;
	Talon right_front;
	Talon right_back;
	CANTalon crab_arms;
	CANTalon left_arm;
	CANTalon right_arm;

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

	void TeleopPeriodic()
	{
		//crab_arms.Set(stick.GetY());
//		if(stick.GetRawButton(0x0001))
//		{
//			crab_arms.Set(1.0);
//			left_arm.Set(1.0);
//			right_arm.Set(1.0);
//
////			left_front.Set(1.0);
////			left_back.Set(1.0);
////			right_front.Set(1.0);
////			right_back.Set(1.0);
//		}
//		else if(stick.GetRawButton(0x0002))
//		{
//			crab_arms.Set(-1.0);
//			left_arm.Set(-1.0);
//			right_arm.Set(-1.0);
//
////			left_front.Set(-1.0);
////			left_back.Set(-1.0);
////			right_front.Set(-1.0);
////			right_back.Set(-1.0);
//		}
//		else
//		{
			right_back.Set(stick.GetY());
			crab_arms.Set(stick.GetY());
			left_arm.Set(stick.GetY());
			right_arm.Set(stick.GetY());

			SmartDashboard::PutNumber("Stick",stick.GetY());
			SmartDashboard::PutNumber("Current in crab arm", crab_arms.GetOutputCurrent());
			SmartDashboard::PutNumber("Current in left arm", left_arm.GetOutputCurrent());
			SmartDashboard::PutNumber("Current in right arm", right_arm.GetOutputCurrent());
			printf("stick = %f\n", stick.GetY());
//			left_front.Set(0.0);
//			left_back.Set(0.0);
//			right_front.Set(0.0);
//			right_back.Set(0.0);
		//}
	}

	void TestPeriodic()
	{
		lw->Run();
	}

public:
	   Robot() : stick(0), left_front(1), left_back(3), right_front(0), right_back(2), left_arm(0), right_arm(1), crab_arms(2)
	   {
		   SmartDashboard::init();
	   }

};

START_ROBOT_CLASS(Robot);
