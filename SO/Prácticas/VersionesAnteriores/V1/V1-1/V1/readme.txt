Ejercicios 4 al 7 hechos:
Ej4: Modificada la función OperatingSystem_CreateProcess() para que devuelva el valor NOFREEENTRY. En el apartado b, lo mismo, pero para el caso de creación de proceso con fracaso, creando un nuevo error 103.
Ej5: Al igual que en el ejercicio anterior, pero en este caso devolvemos PROGRAMDOESNOTEXIST, en caso de que el programa no exista, o PROGRAMNOTVALID, si no se encuentran los valores del tamaño y la prioridad. El error es uno nuevo, el 104.
Ej6: Al igual que en el ejercicio 5, pero en este caso devolvemos el valor TOOBIGPROCESS cuando el tamaño de memoria es superior. Utilizando el mensaje 105
Ej7: Al igual que en el ejercicio 6, pero en este caso devolvemos el valor cuando el programa tiene más instrucciones de las indicadas