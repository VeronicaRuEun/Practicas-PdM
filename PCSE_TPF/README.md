El proyecto consiste en mostrar los valores de un acelerómetro ADXL345 en una pantalla LCD al presionar un PUSH_BUTTON.
Cuando comienza, la pantalla LCD muestra un mensaje “Presiona el push para iniciar” (esto indica que debe presionar el 
botón para iniciar con la muestra de aceleraciones), cuando el usuario presiona dicho botón, la pantalla procede a 
mostrar los valores de aceleración, además, mientras está en la lectura de las aceleraciones, un LED permanece encendido.
Cuando el usuario presiona de nuevo el botón, deja de mostrar las aceleraciones regresando al mensaje inicial en la 
pantalla “Presiona el push para iniciar” y el LED se apaga.
Una máquina de estados es implementada para controlar los estados de lo que se muestra en el LCD y el comportamiento 
de un LED.
