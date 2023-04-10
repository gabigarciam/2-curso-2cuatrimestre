
using System;

namespace TPP.Laboratory.ObjectOrientation.Lab01 {

    /// <summary>
    /// Class that computes the power of a number
    /// </summary>
    class Power {

        static void Main() {
            uint theBase = 2;
            uint exponent = 32;

            uint result = 1;

            if (theBase == 0) {
                Console.WriteLine("Power: 0.");
                return;
            }

            while (exponent > 0) {
                result *= theBase;
                exponent--;
            }

            Console.WriteLine("Power: {0}.", result);
        }
    }

}

