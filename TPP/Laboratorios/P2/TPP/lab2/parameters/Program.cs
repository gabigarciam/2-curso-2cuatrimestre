using System;

namespace parameters
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int a = 1;
            int b = 0;
            String nombre;
            String apellido;
            String uo;
            Swap(ref a, ref b);
            Console.WriteLine("a {0}, b {1}", a, b);
            AskForData(out nombre, out apellido, out uo);
            Console.WriteLine("Nombre: {0} {1}, UO: {2}", nombre, apellido, uo);
        }

        public static void Swap(ref int a, ref int b)
        {
            int aux = a;
            a = b;
            b = aux;
        }

        public static Tuple<string, string, string> AskForData()
        {
            return new Tuple<string, string, string>(Console.ReadLine(), Console.ReadLine(), Console.ReadLine());
        }

        public static (string, string, string) AskForData2()
        {
            return (Console.ReadLine(), Console.ReadLine(), Console.ReadLine());
        }

        public static void AskForData(out string nombre, out string apellido, out string uo)
        {
            Console.WriteLine("Escriba su nombre:");
            nombre = Console.ReadLine();

            Console.WriteLine("Escriba su apellido:");
            apellido = Console.ReadLine();

            Console.WriteLine("Escriba su uo:");
            uo = Console.ReadLine();
        }
    }
}
