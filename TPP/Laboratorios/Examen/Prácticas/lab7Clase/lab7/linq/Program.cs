using System.Collections.Generic;
using System;
using System.Linq;

namespace TPP.Laboratory.Functional.Lab07 {

    class Program {

        static void Main() {
            IEnumerable<int> integers = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

            //integers.Map(x => { Console.WriteLine(x * 2); return x*2; });
            Console.WriteLine("\n");
            var coll = integers.MapLazy(x => { Console.WriteLine(x * 2); return x*2; });
            var lazy = coll.Skip(5);
            //lazy.ForEach(Console.WriteLine);
            IList<int> lista = new List<int>();
            //lazy.ForEach(x => lista.Add(x));
            lazy.MediaImperativo();
            lazy.Average();

//          lazy.ForEach(x => Console.WriteLine(x));
            //int max = coll.Max();
            //lazy.Show();
            //var noLazy = lazy.ToArray();
            ///Console.WriteLine("----");
            //noLazy.First();
            //Console.WriteLine("\n{0}", lazy);

            //Map       - Select
            //Find      - First
            //Filter    - Reduce
            //Reduce    - Aggregate

        }

        
    }
}
