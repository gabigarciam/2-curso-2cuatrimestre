using System;
using System.Text;

namespace angle
{
    public class Angle
    {
        private double radians;

        public double Radians
        {
            get { return this.radians; }
            set { this.radians = value; }
        }

        public String Name
        {
            get; set; 
        }

        public double Degrees { 
            get { return this.radians / Math.PI * 180; }
         }

        public Angle(double radians)
        {
            Console.WriteLine("Constructor de Ángulo");
            this.radians = radians;
        }

        ~Angle()
        {
            Console.WriteLine("Destructor de Ángulo");
        } 

        public double Sine()
        {
            return Math.Sin(this.radians);
        }
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Ángulo. Grados: ").Append(this.Degrees);
            return base.ToString();
        }
    }
}
