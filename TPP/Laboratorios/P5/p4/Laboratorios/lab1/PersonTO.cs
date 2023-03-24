using System;

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
	
  /* Considering that many fields are optional (IDNumber, Nationality, 
     DateOfBirth and Gender)
   * How many constructors should be defined?   */
  }
  
  enum Gender { Male, Female };
  
}

