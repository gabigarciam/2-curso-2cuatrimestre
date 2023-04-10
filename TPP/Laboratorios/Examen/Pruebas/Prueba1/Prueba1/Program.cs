using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.Reflection;

namespace Prueba1
{

    static class Extensor
    {
        public static int number(this IList<int> list, Predicate<int> pred)
        {
            int counter = 0;
            foreach (int i in list)
            {
                if (pred(i))
                {
                    counter++;
                }
            }
            return counter;
        }
        //Para que sea Lazy es necesario que sea IEnumerable
        public static IEnumerable<int> NumberLazy(this IEnumerable<int> list, Predicate<int> pred)
        {

            foreach (int i in list)
            {
                if (pred(i))
                    yield return i;
            }
            yield break;
        }
    }

    class Currificacion
    {
        static int Addition(int a, int b)
        {
            return a + b;
        }

        static Func<int, int> CurryedAdd(int a)
        {
            return b => b + a;
        }

        static int Multiplica(int a, int b, int c)
        {
            return a * b * c;
        }

        static Func<int, Func<int, int>> CurryedMult(int a)
        {
            return b => c => a * b * c;
        }

        static Func<int, int> resta(int a)
        {
            return b => b - a;
        }

        static Func<int, Func<int, int>> Division(int a)
        {
            return b => c => a / b / c;
        }

        //Cubic 
        //Func<int, int> cubic = x => CurryedMult(x)(x)(x);
    }

    static class Memoized
    {
        private static IDictionary<int, int> values = new Dictionary<int, int>();

        internal static int Fibonacci(int n)
        {
            if (values.Keys.Contains(n))
                // * If the value was already computed, the cached value is returned
                return values[n];
            // * Otherwise, it is computed and stored
            int value = n <= 2 ? 1 : Fibonacci(n - 2) + Fibonacci(n - 1);
            values.Add(n, value);
            return value;
        }
    }

    static class Generator
    {
        /// <summary>
        /// Generador(infinito) que devuelve los números divisibles por todos los del 
        /// array que se le pasa como parámetro. Es infinito por el while(true)
        /// </summary>
        /// <param name="array"></param>
        /// <returns></returns>
        static internal IEnumerable<int> Divisores(int[] array)
        {
            int num = 1;
            while (true)
            {
                int counter = 0;
                for (int i = 0; i < array.Length; i++)
                {
                    if (num % array[i] != 0)
                    {
                        break;
                    }
                    else
                    {
                        counter++;
                    }
                }
                if (counter == array.Length - 1)
                {
                    yield return num;
                }
                num++;
            }
            yield break;
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            IList<int> a = new List<int>
            {
                1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
            };
            Predicate<int> r = (a => a>=10);
            //Console.WriteLine(a.number(r));
            //Console.WriteLine(a.number(a => a >= 10));
            int[] array = new int[] { 2, 4 };
            foreach (int value in Generator.Divisores(array))
            {
                Console.Write(value + " ");
            }
        }

    }
}
