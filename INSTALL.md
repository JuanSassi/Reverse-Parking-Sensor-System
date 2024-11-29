# Instalación y Configuración

## Requisitos Previos

Antes de comenzar con la compilación y programación del proyecto, asegúrese de tener los siguientes elementos instalados y configurados:

1. *MCUXpresso IDE* (para compilar y cargar el código a la placa LPC1769).
2. *Python 3.x* (para ejecutar la interfaz UART y realizar la comunicación).
3. *Drivers de UART* (para asegurar la correcta comunicación entre la LPC1769 y la computadora).
4. *Visual Studio Code* (opcional, si se desea usar este entorno para ejecutar el script de Python).

---

## Especificaciones de Hardware

Antes de comenzar con la instalación del software y la programación del proyecto, asegúrese de tener el siguiente hardware disponible:

### 1. *Placa de Desarrollo: LPC1769*
   - *Modelo*: NXP LPC1769 (compatible con MCUXpresso IDE)
   - *Microcontrolador*: ARM Cortex-M3 a 120 MHz
   - *Memoria Flash*: 512 KB
   - *Memoria SRAM*: 64 KB
   - *Puertos GPIO*: Varios pines GPIO para la interacción con sensores, LEDs, botones y otros periféricos.
   - *Comunicación Serial (UART)*: Puerto UART para la comunicación con la computadora (se usará en este proyecto para la transmisión de datos).

### 2. *Adaptador UART (PL2303 o similar)*
   - *Interfaz*: USB a UART
   - *Función*: Para la comunicación entre la placa LPC1769 y la computadora.
   - *Drivers*: Asegúrese de instalar los drivers adecuados para que el adaptador sea reconocido correctamente por el sistema operativo.

### 3. *Periféricos Conectados*
   - *Sensores de Proximidad*: Utilizados para detectar la distancia de objetos cercanos.
   - *LEDs*: Indicadores visuales para representar el estado del sistema.
   - *Buzzer*: Para alertas audibles en función de la proximidad o el estado del sistema.
   - *Pantalla LCD (opcional)*: Para mostrar información adicional sobre el estado del sistema (por ejemplo, valores de sensores o mensajes).
   - *Botones/Switches*: Para controlar modos del sistema, como activar o desactivar las notificaciones.

### 4. *Cables y Conexiones*
   - *Cable USB*: Para conectar la placa LPC1769 a la computadora.
   - *Cables Jumper*: Para conectar periféricos adicionales como sensores, LEDs y el buzzer a los pines de la placa.
   - *Resistencias*: Para el control de corriente en algunos de los periféricos (por ejemplo, LEDs y buzzer).

![20241119_133821](https://github.com/user-attachments/assets/8a3f1fe7-d99c-4272-bc5d-0397236a64bd)

---

## Requisitos de Software

Asegúrese de tener los siguientes programas y herramientas instalados:

1. *[MCUXpresso IDE](https://www.nxp.com/design/mcuxpresso/mcuxpresso-ide)*
2. *[Python 3.x](https://www.python.org/downloads/)*
3. *[Drivers de UART (PL2303)](https://www.prolific.com.tw/US/ShowProduct.aspx?p_id=225&pcid=41)*
4. *[Visual Studio Code](https://code.visualstudio.com/)* (opcional, para ejecutar el script de Python)

---

## Pasos de Instalación

### 1. Instalación de MCUXpresso IDE
- Descargue e instale *MCUXpresso IDE* desde el sitio oficial de NXP.
- Durante la instalación, seleccione las opciones por defecto.

### 2. Instalación de Drivers de UART
- Asegúrese de tener los drivers adecuados para el adaptador *PL2303* (o el que esté utilizando para la comunicación UART).
  - Los drivers pueden descargarse desde el sitio oficial del fabricante del adaptador.
  - Instale los drivers siguiendo las instrucciones de instalación del fabricante.

### 3. Configuración del Entorno en MCUXpresso IDE
1. *Importar las librerías y configurar los includes*:
   - Asegúrese de que las librerías necesarias para el LPC1769 estén correctamente importadas en el IDE.
   - Verifique que las rutas de los archivos de cabecera (include) estén configuradas correctamente en el proyecto.
2. *Importar el proyecto en MCUXpresso IDE*:
   - Abra MCUXpresso IDE.
   - Importe el proyecto en el IDE usando la opción "Import Project".
3. *Compilación y carga del proyecto*:
   - Siga los pasos descritos en la sección *Compilación y Programación* para construir y cargar el programa en la placa LPC1769.

![Imagen de WhatsApp 2024-11-20 a las 01 13 56_0febe18b](https://github.com/user-attachments/assets/cdeed151-f3e4-4294-a681-4774b8487b58)


---

## Comunicación UART con Python

### 4. Configuración de UART
1. *Conectar el adaptador UART a la placa*:
   - Conecte el adaptador PL2303 o el dispositivo UART adecuado entre la LPC1769 y la computadora.
   - Asegúrese de conectar correctamente los pines TX/RX de la LPC1769 con los correspondientes del adaptador.
   
![image](https://github.com/user-attachments/assets/ebce889c-7e1c-4fbb-9c1b-cfb562900ebf)


2. *Verificar el puerto COM*:
   - En *Administrador de Tareas* de Windows, verifique qué puerto COM ha asignado al adaptador UART.
   - Este puerto será utilizado por la interfaz en Python para establecer la comunicación.

3. *Instalar los drivers de UART*:
   - Si no lo ha hecho aún, descargue e instale los drivers necesarios para el adaptador PL2303 o el UART que esté utilizando.
   - El puerto UART debe ser reconocido por la computadora en el administrador de dispositivos.

### 5. Ejecutar la Interfaz en Python
1. *Instalar las dependencias de Python*:
   - Asegúrese de tener *Python 3.x* instalado en su máquina.
   - Instale las dependencias necesarias para ejecutar el script, usando el siguiente comando:
   
     bash
     pip install pyserial customtkinter
     

2. *Ejecutar la interfaz*:
   - Abra *Visual Studio Code* (o el editor de su elección).
   - Cargue el archivo Python que contiene la interfaz de usuario para la lectura de datos UART.
   - Ejecute el script de Python. Esto abrirá una ventana de la interfaz que permitirá seleccionar el puerto COM y el baud rate para conectar a la LPC1769.

---

## Compilación y Programación

### 1. *Seleccionar el proyecto en el explorador de proyectos*
   - Abra el *MCUXpresso IDE* y localice el proyecto en el panel izquierdo.
   - Haga clic sobre el nombre del proyecto para seleccionarlo.

### 2. *Construir el proyecto*
   - Haga clic en el ícono de *Build* (martillo) en la barra de herramientas.
   - Verifique que no haya errores de compilación en la consola.

### 3. *Configurar el depurador*
   - Conecte la placa *LPC1769* a la computadora mediante USB.
   - Elija el depurador adecuado:
     - *CMSIS-DAP* (para placas con depuradores CMSIS integrados).
     - *LinkServer* (para placas LPCXpresso compatibles).
   - Configure la conexión desde el menú desplegable junto al botón *Debug*.

### 4. *Programar el microcontrolador*
   - Haga clic en el botón *Debug* (ícono de insecto verde).
   - El IDE detectará automáticamente la placa conectada y cargará el binario generado en la memoria flash.

### 5. *Depuración y ejecución del programa*
   - Active el modo de depuración y utilice las herramientas del IDE para:
     - Colocar puntos de interrupción.
     - Inspeccionar variables y registros.
     - Verificar el comportamiento del sistema.

---

## Resultados Esperados

- Una vez cargado el programa en la placa, los LEDs deberían parpadear según el comportamiento implementado en el código.
- La interfaz de Python debe mostrar los datos leídos del UART en tiempo real.

---

## Notas Adicionales

- *Verificación de conexión*: Si no se detecta la placa o el puerto UART, asegúrese de que los cables estén bien conectados y los drivers estén instalados correctamente.
- *Actualización del firmware*: Si experimenta problemas con la carga del programa, considere actualizar el firmware del depurador.
- *Puertos COM*: Asegúrese de seleccionar el puerto correcto en la interfaz de Python.