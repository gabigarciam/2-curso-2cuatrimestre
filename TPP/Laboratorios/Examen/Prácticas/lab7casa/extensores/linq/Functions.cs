using System.Linq;
using System.Collections.Generic;
using System;

namespace TPP.Laboratory.Functional.Lab07 {

    static public class Functions {

        public static IEnumerable<TResult> Map<TElement, TResult>(this IEnumerable<TElement> collection, Func<TElement, TResult> function) {
            TResult[] result = new TResult[collection.Count()];
            int i = 0;
            foreach (TElement x in collection)
            {
                result[i++] = function(x);
            }
            return result;
        }

        public static IEnumerable<TResult> MapLazy<TElement, TResult>(this IEnumerable<TElement> collection, Func<TElement, TResult> function)
        {
            foreach (TElement x in collection)
            {
                yield return function(x);
            }
            yield break;
        }

        public static void ForEach<T>(this IEnumerable<T> d, Action<T> action)
        {
            foreach (var e in d)
            {
                action(e);
            }
        }

        public static int Media(this IEnumerable<int> integers)
        {

            //V1
            //return integers.Aggregate((x,y) => x + y) / integers.Count();   
            //V2
            //int count = 0;
            //return integers.Aggregate((x, y) => {
            //    count++; 
            //    return x + y;
            //    }) / count;
            //V3
            var result = integers.Aggregate<int, (int sum, int cuenta)>((0,0),(acumulacion, actual) =>
            {
                return (acumulacion.sum + actual, acumulacion.cuenta + 1);
            });
            return result.sum / result.cuenta;
        }

        public static int MediaImperativo(this IEnumerable<int> integers)
        {
            int media = 0;
            int count = 0;
            foreach (var n in integers)
            {
                media += n;
                count++;
            }
            return media / count;
        }

        public static T Find<T>(this IEnumerable<T> collection, Predicate<T> p)
        {
            foreach (T element in collection)
            {
                if (p(element))
                    return element;
            }
            return default;
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

        public static TCD Reduce<TD, TCD>(this IEnumerable<TD> collection, Func<TCD, TD, TCD> f, TCD defecto = default)
        {
            foreach (TD t in collection)
            {
                defecto = f(defecto, t);
            }
            return defecto;
        }

    }
}
