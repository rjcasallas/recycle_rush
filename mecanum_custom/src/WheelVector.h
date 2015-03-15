#ifndef __WHEEL_VECTOR_H__
#define __WHEEL_VECTOR_H__

#include <algorithm>    // xmax


class WheelVector
{

public:

   WheelVector()
   {
      leftFront = 0;
      leftBack = 0;
      rightFront = 0;
      rightBack = 0;
   }

   WheelVector(double lf, double lb, double rf, double rb)
   {
      leftFront = lf;
      leftBack = lb;
      rightFront = rf;
      rightBack = rb;
   }

   WheelVector operator+(const WheelVector& w) const
   {
      return WheelVector(leftFront + w.leftFront, leftBack + w.leftBack, rightFront + w.rightFront, rightBack + w.rightBack);
   }

   WheelVector operator-(const WheelVector& w) const
   {
      return WheelVector(leftFront - w.leftFront, leftBack - w.leftBack, rightFront - w.rightFront, rightBack - w.rightBack);
   }

   WheelVector operator*(const double value) const
   {
      return WheelVector(leftFront * value, leftBack * value, rightFront * value, rightBack * value);
   }

   void normalize()
   {
      double lmax = xmax(xabs(leftFront), xabs(leftBack));
      double rmax = xmax(xabs(rightFront), xabs(rightBack));
      double max = xmax(lmax, rmax);
      if (max > 1.0)
      {
         leftFront /= max;
         leftBack /= max;
         rightFront /= max;
         rightBack /= max;
      }
   }

   void limit(double max)
   {
      leftFront = limit(leftFront, max);
      leftBack = limit(leftBack, max);
      rightFront = limit(rightFront, max);
      rightBack = limit(rightBack, max);
   }

   static WheelVector calc(double x, double y, double r)
   {
      WheelVector mv = calcMedial(x, y, r);
      WheelVector rv = calcRotational(x, y, r);
      WheelVector lv = calcLateral(x, y, r);

      WheelVector v = mv + rv + lv;
      v.normalize();
      return v;
   }

   static double limit(double value, double max)
   {
      double abs = xabs(value);
      return abs > 1.0 ? value / abs : value;
   }

   void zero(double value)
   {
      leftFront = xabs(leftFront) < value ? 0 : leftFront;
      leftBack = xabs(leftBack) < value ? 0 : leftBack;
      rightFront = xabs(rightFront) < value ? 0 : rightFront;
      rightBack = xabs(rightBack) < value ? 0 : rightBack;
   }

   double getLeftFront()
   {
      return leftFront;
   }

   double getLeftBack()
   {
      return leftBack;
   }

   double getRightFront()
   {
      return rightFront;
   }

   double getRightBack()
   {
      return rightBack;
   }

private:
   double leftFront;
   double leftBack;
   double rightFront;
   double rightBack;

   static WheelVector calcMedial(double x, double y, double r)
   {
      return WheelVector(-y, -y, y, y);
   }

   static WheelVector calcRotational(double x, double y, double r)
   {
      return WheelVector(r, r, r, r);
   }

   static WheelVector calcLateral(double x, double y, double r)
   {
      return WheelVector(x, -x, x, -x);
   }

   static double xabs(double value)
   {
      return value < 0 ? -value : value;
   }

   static double xmax(double a, double b)
   {
      return a > b ? a : b;
   }
};

#endif // __WHEEL_VECTOR_H__
