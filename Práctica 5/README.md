Funciones implementadas:
- Generalización de todo el códido a través de la clase Actor
- Implementación de ambos generadores uniforme y gausiano, con sus variantes estáticas y dinámicas
- Implementación de todas las fuerzas: viento, tornado, explosión y gravedad (esta última no es necesaria)
- Implementación de todos los muelles: anchored, slinky, entre partículas y buoyancy

Controles:
- R -> gravedad
- G -> generador gausiano estático
- H -> generador gausiano dinámico
- U -> generador uniforme estático
- I -> generador uniforme dinámico
- Q -> viento (si se pulsa una vez, aparecen los generados; al pulsarla de nuevo, el viento deja de ser efectivo y viceversa)
- T -> tornado
- E -> explosión (si se pulsa una vez, aparecen las partículas; al pulsarla de nuevo, se realiza la explosión)
- Z -> anchored
- X -> spring
- C -> slinky
- V -> bouyancy

Errores conocidos:
Al pulsar la tecla de viento, luego la del anchored y luego otra vez la de viento, no se activa correctamente el estado de viento.