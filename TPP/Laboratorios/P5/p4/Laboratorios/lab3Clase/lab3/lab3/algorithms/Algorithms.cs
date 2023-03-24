
using System;

namespace TPP.Laboratory.ObjectOrientation.Lab03 {

    public interface IComparador
    {
        bool SonIguales(object a, object b);
    }

    public class ComparaAngulosMismoCuadrante: IComparador
    {
        public bool SonIguales(object a, object b)
        {
            Angle angle1 = a as Angle;
            Angle angle2 = b as Angle;
            if (angle1 == null || angle2 == null)
                return false;
            return angle1.Cuadrante() == (angle2.Cuadrante());
        }
    }

    public class ComparaPersonasNombre : IComparador
    {
        public bool SonIguales(object a, object b)
        {
            Person person = a as Person;
            Person person2 = b as Person;
            if (person == null || person2 == null)
                return false;
            return person.FirstName.Equals(person2.FirstName);
        }
    }
    public static class Extensores
    {
        public static int? indexOf(this object[] array, object o, IComparador comparador = null)
        {
            
            for (int i = 0; i < array.Length; i++)
            {
                if (comparador == null)
                {
                    if (array[i].Equals(o))
                    {
                        return i;
                    }
                }
                else
                {
                    if(comparador.SonIguales(array[i], o))
                    {
                        return i;
                    } 
                }
            }
            return null;
        }
    }

    class Algorithms {

        // Exercise: Implement an IndexOf method that finds the first position (index) 
        // of an object in an array of objects. It should be valid for Person, Angle and future classes.

        

        static Person[] CreatePeople() {
            string[] firstnames = { "María", "Juan", "Pepe", "Luis", "Carlos", "Miguel", "Cristina" };
            string[] surnames = { "Díaz", "Pérez", "Hevia", "García", "Rodríguez", "Pérez", "Sánchez" };
            int numberOfPeople = 100;

            Person[] printOut = new Person[numberOfPeople];
            Random random = new Random();
            for (int i = 0; i < numberOfPeople; i++)
                printOut[i] = new Person(
                    firstnames[random.Next(0, firstnames.Length)],
                    surnames[random.Next(0, surnames.Length)],
                    random.Next(9000000, 90000000) + "-" + (char)random.Next('A', 'Z')
                    );
            return printOut;
        }

        static Angle[] CreateAngles() {
            Angle[] angles = new Angle[(int)(Math.PI * 2 * 10)];
            int i = 0;
            while (i < angles.Length) {
                angles[i] = new Angle(i / 10.0);
                i++;
            }
            return angles;
        }

        static void Main() {
            var people = CreatePeople();
            Console.WriteLine(people.indexOf(new Person("Juan", "García", "1234"), new ComparaPersonasNombre()));
            Console.WriteLine(people.indexOf(people[85]));
            Console.WriteLine(people.indexOf(new Person(people[12].FirstName, people[12].SurName, people[12].IDNumber)));
            Console.WriteLine(people.indexOf(new Person(people[12].FirstName, people[14].SurName, people[15].IDNumber)));

            var angles = CreateAngles();
            Console.WriteLine(angles.indexOf(new Person("Gabriel", "García", "1234")));
            Console.WriteLine(angles.indexOf(new Angle(Math.PI)));
            Console.WriteLine(angles.indexOf(angles[1]));
            Console.WriteLine(angles.indexOf(new Angle(angles[2].Radians)));
        }

    }

}
