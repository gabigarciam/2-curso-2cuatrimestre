using System;
using System.Text;

namespace TPP.Laboratory.ObjectOrientation.Lab01 {

  /// <summary>
  /// Example class that only holds data: (Data) Transfer Object or Value Object
  /// </summary>
  class PersonTO {
  
    public string FirstName { get; set; }
	
    public string Surname { get; set; }
	
    public string Nationality { get; set; }
	
    public string IDNumber { get; set; }
	
    public DateTime DateOfBirth { get; set; }
	
    public Gender Gender { get; set; }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Nombre: ").Append(this.FirstName).Append(this.Surname);
            return sb.ToString();
        }
  /* Considering that many fields are optional (IDNumber, Nationality, 
     DateOfBirth and Gender)
   * How many constructors should be defined?   */
  }
  
  enum Gender { Male, Female };
  
}

