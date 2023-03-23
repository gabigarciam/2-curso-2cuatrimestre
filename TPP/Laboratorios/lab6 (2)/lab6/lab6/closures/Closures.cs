using System;

namespace TPP.Laboratory.Functional.Lab06 {

    /// <summary>
    /// Try to guess the behavior of this program without running it
    /// </summary>
    class Closures {

        /// <summary>
        /// Version with a single method
        /// </summary>
        static (Func<int>, Func<int>, Action<int>) Counter() {
            int counter = 0;
            (Func<int>, Func<int>, Action<int>) tuple =(() => counter++, () => counter--, (x) => counter = x);
            return tuple;
        }

        static void Main() {
            var counter = Counter();
            counter.Item1();
            Console.WriteLine(counter.Item1());
            Console.WriteLine(counter.Item2());
            
            var anotherCounter = Counter();
            anotherCounter.Item3(14);
            Console.WriteLine(anotherCounter.Item1());
            Console.WriteLine(anotherCounter.Item2());

            Console.WriteLine(counter);
            Console.WriteLine(counter);

            //Tuple<int, int> tup = new Tuple<int, int>(10, -10);
            (int, int) tupla = (10, -10);
            tupla.Item1 = -10;
            (int a, int b) t = (10, 90);
        }
    }

    class Counter
    {
        int counter ;

        public Counter(int value)
        {
            counter = value;
        }

        public void setValue(int value)
        {
            counter = value;
        }

        public int Decrementar() //Func<int>
        {
            return counter--;
        }

        public int Incrementar() //Func<int>
        {
            return counter++;
        }
    }

}
