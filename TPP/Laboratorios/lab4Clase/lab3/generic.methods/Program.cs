using System;
using System.Collections;

namespace generic.methods
{
    internal class Program
    {
         
        static void Main(string[] args)
        {
            String a = "aa";
            String b = "Hola";
            Swap(ref a, ref b);
            Console.WriteLine("a: {0}, b: {1}", a, b);

            var array = new int[] { 1, 2, 3, 4, 5 , 6 };

            IEnumerator e = array.GetEnumerator();
            while (e.MoveNext())
            {
                Console.WriteLine(e.Current);
            }           
        }

        public static void Swap<T>(ref T a, ref T b)
        {
            T aux = a;
            a = b;
            b = aux;
        }

        public static T Max<T> (T a, T b) where T : IComparable<T>
        {
            if (a.CompareTo(b) > 0) return a;
            return b;
        }
        public static IComparable Max(IComparable a, IComparable b) 
        {
            if (a.CompareTo(b) > 0) 
                return a;
            return b;
        }

      
    }
}
