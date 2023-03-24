using angle;
using System;

namespace TPP.Laboratory.ObjectOrientation.Lab01
{

    /// <summary>
    /// Class that computes the power of a number
    /// </summary>
    class Power {

        static void Main() {
            uint theBase = 2;
            uint exponent = 32;

            ulong result = 1;

            if (theBase == 0) {
                Console.WriteLine("Power: 0.");
                return;
            }

            while (exponent > 0) {
                result *= theBase;
                exponent--;
            }

            Console.WriteLine("Power: {0}.", result);

            Angle a = new Angle(Math.PI / 2);
            //Console.WriteLine("Ángulo. Radianes {0}, Grados {1}", a.GetRadians(), a.GetDegrees());
            Console.WriteLine("Ángulo. Radianes {0}, Grados {1}", a.Radians, a.Degrees);
            a.Radians = 10;
            Console.WriteLine(a);
        }
    }

}

