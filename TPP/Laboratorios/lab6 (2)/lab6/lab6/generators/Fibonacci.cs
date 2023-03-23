using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TPP.Laboratory.Functional.Lab06 {

    static class Fibonacci {

        static internal IEnumerable<int> InfiniteFibonacci() {
            int first = 1, second = 1;
            while (true) {
                yield return first;
                int addition = first + second;
                first = second;
                second = addition;
            }
        }

        static internal IEnumerable<int> FibonacciLazy(int source, int target)
        {
            return InfiniteFibonacci().Skip(source - 1).Take(target - source + 1);
        }

        internal static int LimitedFibonacci(int n)
        {
            return n <= 2 ? 1 : LimitedFibonacci(n - 2) + LimitedFibonacci(n - 1);
        }

        static internal IEnumerable<int> FibonacciEag(int source, int target)
        {
            IList<int> r = new List<int>();
            for (int i = 0; i <= target; i++)
            {
                r.Add(LimitedFibonacci(i));
            }
            return r.Skip(source);
        }

    }

}
