#ifndef __COMPLEX_FUNCTIONS_HPP__
#define __COMPLEX_FUNCTIONS_HPP__

#include <cmath>
#include <string>

#include "Parameters.hpp"

namespace Fractal
{
    typedef void (*FunctionPointer)(double &a, double &b);

    const double Epsilon = std::numeric_limits<double>::epsilon();

    void Multiply(double x, double y, double a, double b, double &zx, double &zy)
    {
        zx = (x * a - y * b);

        zy = (x * b + y * a);
    }

    void Divide(double a, double b, double c, double d, double &zx, double &zy)
    {
        auto denom = c * c + d * d;

        zx = (a * c + b * d) / denom;

        zy = (b * c - a * d) / denom;
    }

    int Sign(double val)
    {
        return val >= 0.0 ? 1 : -1;
    }

    double Mag2(double zx, double zy)
    {
        return zx * zx + zy * zy;
    }

    double Abs(double zx, double zy)
    {
        return std::sqrt(Fractal::Mag2(zx, zy));
    }

    double Mag(double zx, double zy)
    {
        return Fractal::Abs(zx, zy);
    }

    void Reciprocal(double &zx, double &zy)
    {
        auto mag2 = Fractal::Mag2(zx, zy) + Fractal::Epsilon;

        zx = zx / mag2;

        zy = -zy / mag2;
    }

    void Sin(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::sin(oldx) * std::cosh(oldy);

        zy = std::cos(oldx) * std::sinh(oldy);
    }

    void Cos(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::cos(oldx) * std::cosh(oldy);

        zy = -std::sin(oldx) * std::sinh(oldy);
    }

    void Exp(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        auto expx = std::exp(oldx);

        zx = expx * std::cos(oldy);

        zy = expx * std::sin(oldy);
    }

    void Log(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::log(oldx * oldx + oldy * oldy) / 2.0;

        zy = std::atan2(oldy, oldx);
    }

    void Logistic(double &zx, double &zy)
    {
        auto oldx = 1.0 - zx;

        auto oldy = -zy;

        Fractal::Multiply(zx, zy, oldx, oldy, zx, zy);
    }

    void Tan(double &zx, double &zy)
    {
        auto denum = std::cos(2.0 * zx) + std::cosh(2.0 * zy);

        zx = std::sin(2.0 * zx) / denum;

        zy = std::sinh(2.0 * zy) / denum;
    }

    void Cot(double &zx, double &zy)
    {
        auto denum = std::cosh(2.0 * zy) - std::cos(2.0 * zx);

        zx = std::sin(2.0 * zx) / denum;

        zy = -std::sinh(2.0 * zy) / denum;
    }

    void Sec(double &zx, double &zy)
    {
        Fractal::Cos(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Csc(double &zx, double &zy)
    {
        Fractal::Sin(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Sinh(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::sinh(oldx) * std::cos(oldy);

        zy = std::cosh(oldx) * std::sin(oldy);
    }

    void Cosh(double &zx, double &zy)
    {
        auto oldx = zx;

        auto oldy = zy;

        zx = std::cosh(oldx) * std::cos(oldy);

        zy = std::sinh(oldy) * std::sin(oldy);
    }

    void Tanh(double &zx, double &zy)
    {
        auto denum = std::cosh(2.0 * zx) + std::cos(2.0 * zy);

        zx = std::sinh(2.0 * zx) / denum;

        zy = std::sin(2.0 * zy) / denum;
    }

    void Coth(double &zx, double &zy)
    {
        auto denum = std::cosh(2.0 * zx) - std::cos(2.0 * zy);

        zx = std::sinh(2.0 * zx) / denum;

        zy = -std::sin(2.0 * zy) / denum;
    }

    void Sech(double &zx, double &zy)
    {
        Fractal::Cosh(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Csch(double &zx, double &zy)
    {
        Fractal::Sinh(zx, zy);

        Fractal::Reciprocal(zx, zy);
    }

    void Conjugate(double &zx, double &zy)
    {
        zy = -zy;
    }

    void Sqr(double &zx, double &zy)
    {
        auto xtemp = zx * zx - zy * zy;

        zy = (zx + zx) * zy;

        zx = xtemp;
    }

    void Power(double &zx, double &zy, int exponent)
    {
        if (exponent == 0)
        {
            zx = 1.0;

            zy = 1.0;
        }
        else if (exponent == 2)
        {
            Fractal::Sqr(zx, zy);
        }
        else if (exponent > 2)
        {
            auto oldx = zx;

            auto oldy = zy;

            for (auto i = 0; i < exponent - 1; i++)
            {
                Fractal::Multiply(zx, zy, oldx, oldy, zx, zy);
            }
        }
        else if (exponent < 0)
        {
            Fractal::Reciprocal(zx, zy);

            Fractal::Power(zx, zy, -exponent);
        }
    }

    void Power(double ax, double ay, double bx, double by, double &zx, double &zy)
    {
        Fractal::Log(ax, ay);

        Fractal::Log(bx, by);

        Fractal::Multiply(ax, ay, bx, by, zx, zy);

        Fractal::Exp(zx, ay);
    }

    void Absolute(double &zx, double &zy)
    {
        zx = std::abs(zx);

        zy = std::abs(zy);
    }

    void Identity(double &zx, double &zy)
    {
        zx = zx;

        zy = zy;
    }

    Fractal::FunctionPointer MapFunction(std::string function)
    {
        if (function == "sin")
        {
            return Fractal::Sin;
        }
        else if (function == "cos")
        {
            return Fractal::Cos;
        }
        else if (function == "tan")
        {
            return Fractal::Tan;
        }
        else if (function == "cot")
        {
            return Fractal::Cot;
        }
        else if (function == "sec")
        {
            return Fractal::Sec;
        }
        else if (function == "csc")
        {
            return Fractal::Csc;
        }
        else if (function == "sinh")
        {
            return Fractal::Sinh;
        }
        else if (function == "cosh")
        {
            return Fractal::Cosh;
        }
        else if (function == "tanh")
        {
            return Fractal::Tanh;
        }
        else if (function == "coth")
        {
            return Fractal::Coth;
        }
        else if (function == "sech")
        {
            return Fractal::Sech;
        }
        else if (function == "csch")
        {
            return Fractal::Csch;
        }
        else if (function == "exp")
        {
            return Fractal::Exp;
        }
        else if (function == "log")
        {
            return Fractal::Log;
        }
        else if (function == "logistic")
        {
            return Fractal::Logistic;
        }
        else if (function == "conj")
        {
            return Fractal::Conjugate;
        }
        else if (function == "sqr")
        {
            return Fractal::Sqr;
        }
        else if (function == "reciprocal")
        {
            return Fractal::Reciprocal;
        }
        else if (function == "abs")
        {
            return Fractal::Absolute;
        }
        else
        {
            return Fractal::Identity;
        }
    }
}

#endif
