using System;
using System.Diagnostics;

namespace TPP.Laboratory.Functional.Lab06 {

    class Program {
        static void Main() {
            int i = 0;
            foreach (int value in Fibonacci.InfiniteFibonacci()) {
                Console.Write(value + " ");
                if (++i == 10)
                    break;
            }
            Console.WriteLine();

            i = 0;
            foreach (int value in Fibonacci.InfiniteFibonacci()) {
                Console.Write(value + " ");
                if (++i == 10)
                    break;
            }
            Console.WriteLine();
            Stopwatch sw = new();
            sw.Start();
            foreach (int value in Fibonacci.FibonacciLazy(10, 1000))//forma lazy
            {
                Console.Write(value + " ");
            }
            sw.Stop();
            long r = sw.ElapsedMilliseconds;
            Console.WriteLine("Lazy: {0} ms \n", r);

            sw.Start();
            foreach (int value in Fibonacci.FibonacciEag(10, 1000))//forma lazy
            {
                Console.Write(value + " ");
            }
            sw.Stop();
            r = sw.ElapsedMilliseconds;
            Console.WriteLine("Eag: {0} ms \n", r);
        }
    }
}
