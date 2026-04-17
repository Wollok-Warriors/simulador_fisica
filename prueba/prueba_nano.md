Mientras el goat aprende, va a ir probando cosas en 'prueba_nano.md' Estos se puede tomar como un diario, donde se van a ir anotando, experiencias, inquietudes, o lo que el goat crea necesario.


Una vez se experimeto un poco con correr el programa y que aparezca el circulo, lo que sería el 'Hello world', de este programa, se hará que se pueda mover el circulo con el teclado, pero que si choca con la pared rebote.

Ya no se escapa de los bordes la particula.
A diferencia de lo que esperaba el (0;0) esta ubicado sobre la esquina izquierda, no en el centro.
Ahora toca que tenga velocidad cte la particula, y que cuando choque con una pared, esta le cambie la direccion. 

Ya la pelota rebota al tocar con la pared. La se pone desde la terminal, habría que ver como implementar que se pueda cambiar. La idea es que no sea con lad flechas de mover, pues puede ser díficil poner un a velocidad especifica. 

Ahora llega el momento de la aceleración. Creo que no tiene sentido poner una aceleración constante, sino mas bien tomar el concepto de fuerza y tiempo. Aunque todavía no se va a introducir el concepto de fuerza, esta forma de usar la aceleración ayudará a la implementación de esta. La idea principal es que no se pueda cambiar directamente la aceleración, pues esta se mantiene constante a menos de que se introduzca una fuerza externa. Como el programa tiene fines educativos, si se puede cambiar la aceleración sin la presencia de una fuerza externa serpía un error conceptual, entoces para el futuro del programa la aceleración no se podrá cambiar a mano, sino se podrá introducir una fuerza, y esta será la cual cambie la aceleración.
Ya esatá funcionando el tema de la aceleración. 
La proxima implementación es la posibilidad de definir una aceleración gravitatoria constante, y que la aceleración cambie por una fuerza. Para esto se deberá incluir el concepto de masa.
La primera implementación de la fuerza no fue tan buena como esperaba. Posibles mejoras son la cración de la clase o datatype Fuerza. A diferencia de los atributos que se venian definiendo hasta ahora, las fuerzas no son inherentes a un objeto.  
Nazareno José Rodriguez Moyano    17/04/2026
