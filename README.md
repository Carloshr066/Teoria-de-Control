# Teoria-de-Control

Repositorio de github para el proyecto del pendulo invertido de la asignatura de Teoria de control. Tambien incluye las librerias de los PIDs de las prácticas de tiempo discreto.

## Estructura de archivos
- Pendulo_inv.ino: Codigo principal del pendulo invertido.
- Calibrate_sensor.ino: Codigo para calibrar el sensor del pendulo invertido.
- Archivos_diseño_pendulo: Carpeta que contiene los archivos de diseño del pendulo, tanto la PCB y esquema electrico como el modelo 3d del chasis.
- Librerias_PIDs: Carpeta que contiene los archivos de las librerias que implementan los distintos tipos de PIDs de tiempo discreto.

## Metodología seguida
- Selección de los componentes eléctricos y mecánicos para el proyecto
 
- Diseño del esquema electrico y PCB, seguiendo el esquema de conexiones de los componentes.

- Diseño del chasis en base a los componentes elegidos y la PCB diseñada.
 
- Montaje y prueba de los componentes en la PCB fabricada.
 
- Implementación del codigo inicial en la ESP32.
 
- Ajuste del codigo para su correcto funcionamiento.

## Componentes:

  - Esp32 devkit:
    Como parte central del pendulo se ha usado una Esp32 devkit para controlar el pendulo.
    
  - ROB-14450:
    Puente H capaz de controlar 2 motores DC a la vez, permite un voltaje de alimentación de hasta 15v.
    
  - SEN0142:
    Sensor con giroscopio y acelerometro incorporado, usado para medir el angulo del robot y corregirlo.
    
  - LM7805CT/NOPB:
    Transistor para regular el voltaje, tiene un voltaje de salida de 5V perfecto para alimentar la Esp32 devkit y permite hasta 35V de entrada.
    
  - Conectores XT30:
    Se han usado tres pares de conectores XT30 para conectar tanto la batería como los motores la placa.
    
  - Motores DC:
    Para mover el robot se han usado dos motores DC con un tren de engranajes reductor para incrementar el torque.
    
  - Ruedas:
    Se han usado un par de ruedas compatibles con el eje de los motores.
    
  - Batería:
    Se ha usado una batería recargable de 6V para todo el robot.
## Chasis:
El chasis se ha diseñado con la intención de tener un centro de gravedad alineado con el eje de los motores para maximizar la establidad del robot. El chasis en si es muy sencillo, una superficie plana con 4 agujeros para atornillar la placa al chasis y 2 ranuras en los laterales para poner los motores.

## Montaje:
El montaje de robot del robot ha sido principalmente soldar los componentes en la PCB, una vez esta esta lista se han usado unos separadores para que la placa que separada una cierta distancia del chasis, espacio en el que se ha puesto la batería para tener un perfil más bajo. Con la placa y la batería puestas solo falta colocar los motores en cada estremo del chasis y ponerles las ruedas.

## Ajuste del PID:
La constante Kp del PID se ha ido subiendo en pequeños incrementos hasta que se el robot ha sido capaz de levantarse por su cuenta. Debido a la estabilidad de base del robot poco más ha sido necesario. La constante Ki se ha incrementado hasta que el robot erá capaz de eliminar el pequeño error residual al encontrarse en una casi perpendicular a la superficie. La constante Kd se incremento muy ligeramente para aumentar la velocidad de respuesta del robot.
      
