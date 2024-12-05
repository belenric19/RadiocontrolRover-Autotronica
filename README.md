# RadiocontrolRover-Autotronica

En la fase inicial, se utiliza un transmisor FlySky FS-i6 operando en la banda de 2.4 GHz para controlar el rover. El transmisor envía señales PWM a un receptor FlySky FS-iA6B, que se conectan a un Arduino para el procesamiento de las señales y el control de los actuadores.

Funcionalidades del Proyecto:
- Control de movimiento: Los dos canales principales permiten controlar el movimiento hacia adelante y atrás, y la dirección (izquierda/derecha) del rover.
- Control de servos: Se utilizan canales adicionales para controlar 4 servos de forma independiente, por ejemplo, para herramientas o cámaras.
- Comunicaciones en tiempo real: El sistema utiliza señales PWM para controlar los motores y servos, y realiza una lectura en tiempo real para verificar las posiciones.
