using System;
using System.Collections.Generic;
using System.Linq;

namespace TPP.Laboratory.Functional.Lab06 {

    public static class MetodosExtensores
    {
        public static void Show<T>(this IEnumerable<T> d)
        {
            foreach (var e in d)
            {
                Console.WriteLine(e);
            }
        }

        public static IEnumerable<T2> Map<T1, T2>(this IEnumerable<T1> d, Func<T1, T2> function)
        {
            T2[] result = new T2[d.Count()];
            int i = 0;
            foreach (T1 x in d)
            {
                result[i++] = function(x);
            }
            return result;
        }

        public static T Find<T>(this IEnumerable<T> collection, Predicate<T> p)
        {
            foreach (T elem in collection)
            {
                if (p(elem))
                    return elem;
            }
            return default(T);
        }
        public static IEnumerable<T> Filter<T>(this IEnumerable<T> collection, Predicate<T> p)
        {
            T[] result = new T[collection.Count()];
            int i = 0;
            foreach (T elem in collection)
            {
                if (p(elem))
                {
                    result[i] = elem;
                    i++;
                }
            }
            Array.Resize(ref result, i);
            if (result.Length == 0)
                return default(T[]);
            return result;
        }

        public static TCD Reduce<TD, TCD>(this IEnumerable<TD> collection, Func<TCD, TD, TCD> f, TCD defecto = default(TCD))
        {
            foreach (TD t in collection)
            {
                defecto = f(defecto, t);
            }
            return defecto;
        }
    }

    class Program {

        static int Addition(int a, int b) {
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

       

        static void Main() {
            Console.WriteLine(Addition(1, 2));
            Console.WriteLine(CurryedAdd(1)(2));
            Console.WriteLine(Multiplica(2,3,4));
            Console.WriteLine(CurryedMult(2)(3)(4));

            //Cubic 
            Func<int, int> cubic = x => CurryedMult(x)(x)(x);
            //Square
            Func<int,int> square = x => CurryedMult(x)(x)(1);
            //Double
            Func<int, int> doubleF = x => CurryedMult(x)(2)(1);

            Console.WriteLine("{0} \n",cubic(2));
            //Dado un array de números, calcular el cubo de cada uno e imprimir el resultado

            int[] a = new int[] {1,2,3,4,5,6,7};
            a.Map<int,int>(cubic).Show<int>();
            Console.WriteLine("\n");
            //Dados 10 números, obtener 10 números aleatorios e imprimirlos
            int[] b = new int[10];
            Random rand = new Random();
            b.Map<int,int>(x => rand.Next()).Show();
            Enumerable.Range(0, 10).Map<int,int>(x => rand.Next()).Show();
        }

    }
}
