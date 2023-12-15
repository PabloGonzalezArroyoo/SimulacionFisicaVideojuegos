Funciones implementadas:
- Generalización de todo el códido a través de la clase Actor
- Implementación de ambos generadores uniforme y gausiano, con sus variantes estáticas y dinámicas
- Implementación de todas las fuerzas: viento, tornado, explosión y gravedad (esta última no es necesaria)

Controles:
- R -> gravedad
- G -> generador gausiano estático
- H -> generador gausiano dinámico
- U -> generador uniforme estático
- I -> generador uniforme dinámico
- Q -> viento (si se pulsa una vez, aparecen los generados; al pulsarla de nuevo, el viento deja de ser efectivo y viceversa)
- T -> tornado
- E -> explosión (si se pulsa una vez, aparecen las partículas; al pulsarla de nuevo, se realiza la explosión)
- Z -> [No activable] anchored
- X -> spring
- C -> [No activable] slinky
- V -> bouyancy

Funciones que se ha intentado implementar pero no funcionan:
- Los muelles. Realmente todos están implementados y teórica mente deberían funcionar ya que lo único que he cambiado es la generalización, pero solo el Spring y el Buoyancy funcionan correctamente. El resto por más que lo he intentado, no consigo que funcionen y como no los pedía la práctica como tal...

Errores conocidos:
Al pulsar la tecla de otra de las pruebas se hace una limpieza de la escena y de la memoria dinámica generada. Esta, por algún motivo, de vez en cuando deja basura que luego hace que el programa explote al querer seguir haciendo pruebas. Por más que he mirado, me ha sido imposible detectar de donde viene el fallo... intentaré corregirlo aunque se haya pasado la fecha de entrega puesto que es molesto (y se me queda la espinita clavada, qué rabia >:(, en fin)