void setup() {
  Serial.begin(9600);
}

void loop() {
  
}

/*


            Botones necesarios para el funcionamiento de la maquina
- Boton para movimiento X+
- Boton para movimiento X-
- Boton para movimiento Y+
- Boton para movimiento Y-
OJO: El tema de los movimientos XY también se pueden (o quizá deben) ir por medio de una 
palanca. Si es así igual trendrían que haber 4 botones y con la palanca presionarlos.
- Boton para movimiento automatico en Z
- Boton para que la maquina suelte el peluche

            Flujo de la Aplicacion

Primero se debe de detectar que ingresen las fichas necesarias para llegar a 1Q. Se podran
ingresar monedas de 0.25Q, 0.50Q y 1Q. Cuando llegue al valor necesario (1Q) dentro de la
aplicación debe de sonar algo y luego se debe de seleccionar el modo de uso de la garra. 
Existiran dos tipos:

  - Modo mecánico
  - Modo aplicación

En ambos modos se siguen los mismos movimientos, solamente se usarán distintos modos de enviar
señales a el arduino. Cuando el usuario quiera bajar la garra esta debe de bajar automaticamente
para intentar agarrar el peluche u objeto. Esto quiere decir que cuando se presione el botón
de bajar la garra ocurrirán tres movimientos automaticos: Movimiento de bajada en Z. Movimiento
para cerrar la garra para agarrar el peluche. Y movimiento de subida. Durante el movimiento
de la garra debe de mostrarse el camino de la garra en una matriz de LEDs.

Cuando el usuario pida que baje la garra habrán dos casos:

- Si agarra el peluche: 
Si consigue el peluche, en la matriz de LEDs debe de quedar titiritando
la posición donde se consiguió el peluche. 

También si se da este caso los movimientos siguientes deben de realizarse de
manera manual, quiere decir que el usuario debe de llevar la garra hasta el tobogán. Si se 
lográ llevar el peluche al tobogán se deberá de enviar un mensaje de felicitaciones a la aplicación
Android. 

- Si no agarra el peluche: 
En este caso la matriz de LEDs debe de borrarse el rastro de la garra y debe de mostrarse una
cara triste en la matriz de LEDs.
Si sucede este caso debe de regresar la garra a su posición inicial,
es decir, encima del tobogán de manera automática. Cuando no agarre el peluche se debe de mandar
un mensaje de Game Over a la aplicación Android. 

Se debe de tener una puerta en el tobogán. En caso se logre dejar el peluche en el tobogán
Se debe de abrir esta puerta. En caso contrario siempre permanecerá cerrada. 

*/
