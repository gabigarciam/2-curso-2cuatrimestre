﻿using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClasesListas;

namespace ListaPruebas
{
    class Prueba
    {
        static void Main()
        {
            List<int> l = new List<int>();
            l.Add(3);
            l.Add(7);
            l.Add(23);
            l.Add(33);
            Console.WriteLine("Número de elementos en la lista: {0}", l.GetNumberOfElements);

            l.Remove(3);
            Console.WriteLine("Número de elementos en la lista: {0}", l.GetNumberOfElements);

            Console.WriteLine(l.GetElement(4));
        }
    }
}
