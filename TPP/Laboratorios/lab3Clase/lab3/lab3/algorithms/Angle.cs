
using System;

namespace TPP.Laboratory.ObjectOrientation.Lab03 {

    public class Angle {


        public double Radians { set; get; }

        public double Degrees {
            get {
                return this.Radians / Math.PI * 180;
            }
            set {
                this.Radians = value / 180 * Math.PI;
            }
        }

        public Angle(double radians) {
            this.Radians = radians;
        }

        static public Angle CreateAngleDegrees(double degrees) {
            Angle angle = new Angle(0);
            angle.Degrees = degrees;
            return angle;
        }

        public double Sine() {
            return Math.Sin(this.Radians);
        }

        public double Cosine() {
            return Math.Cos(this.Radians);
        }

        public double Tangent() {
            return Sine() / Cosine();
        }

        public override bool Equals(object obj)
        {
            Angle angle = obj as Angle;
            if (angle == null)
                return false;
            return this.Radians == angle.Radians;
        }

        public override int GetHashCode()
        {
            return (int)this.Radians * 1000;
        }

        

        public int Cuadrante()
        {
            if (this.Degrees >= 0 && this.Degrees < 90)
                return 1;
            else if (this.Degrees >= 90 && this.Degrees < 180)
                return 2;
            else if (this.Degrees >= 180 && this.Degrees < 270)
                return 3;
            else 
                return 4;
        }
    }

}