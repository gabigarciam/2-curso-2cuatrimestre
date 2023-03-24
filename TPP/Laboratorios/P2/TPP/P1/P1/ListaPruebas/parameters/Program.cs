using System;

namespace parameters
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int a = 1;
            int b = 0;
            Swap(ref a, ref b);
            Console.WriteLine("a {0}, b {1}", a, b);
        }

        public static void Swap(ref int a, ref int b)
        {
            int aux = a;
            a = b; 
            b = aux;
        } 
    }
}
