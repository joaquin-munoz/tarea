tarea 1 : Joaquin muñoz 
### Sistema de administracion sobre tickets de soporte técnico en una empresa,

# Descripción

Este sistema permite a los usuarios administrar tickets de soporte técnico en una empresa, siguiendo un sistema de colas con prioridades.Los datos de cada ticket incluyen: ID, descripción del problema, nivel de prioridad (Alto, Medio, Bajo), y hora de registro. La aplicación permitirá registrar nuevos tickets, modificar su prioridad, procesar el siguiente ticket según urgencia, y mostrar la lista de tickets pendientes.

# Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando "Visual Studio Code" junto con una extensión para C/C++, como "C/C++ Extension Pack" de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

# Requisitos previos:

- Tener instalado [Visual Studio Code],puede intalarlo en el siguiente link : https://code.visualstudio.com.
- Instalar la extensión "C/C++" de Microsoft.
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

# Pasos para compilar y ejecutar:

1. Descarga y descomprime el archivo (.zip) en una carpeta de tu elección donde mas te acomode.
2. Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona (Archivo > Abrir carpeta...) y elige la carpeta donde descomprimiste el proyecto.
3. Compila el código
    - Abre el archivo principal por ejemplo en tarea1.c
    - Abre la terminal integrada Terminal > Nueva terminal, puedes usar la terminal que desees , recomendada git bash.
    - En la terminal, compila el programa con el siguiente comando: 
        (gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1)
        
4. Ejecuta el programa
    - Una vez compilado, puedes ejecutar la aplicación con:
        (./tarea1)        

## Funcionalidades 
    ### **Funcionalidades para la aplicación:**

1. *Registrar ticket*:
    - El usuario ingresa el ID y la descripción del problema.
    - La aplicación registra el ticket con la hora de registro actual y asigna automáticamente prioridad "Bajo".

2. *Asignar prioridad a ticket*:
    - El usuario ingresa el ID del ticket y el nuevo nivel de prioridad ("Alto", "Medio", "Bajo").
    - La aplicación actualiza la prioridad del ticket. Si el ID no existe, se muestra un aviso.

3. *Mostrar lista de tickets pendientes*:
    - Muestra todos los tickets ordenados por prioridad (de "Alto" a "Bajo") y,
    dentro de la misma prioridad, por hora de registro (orden de llegada).

4. *Procesar siguiente ticket* :
    - Selecciona el ticket con mayor prioridad y más antiguo dentro de su nivel para ser atendido.
    - Elimina el ticket de la lista y muestra sus datos (ID, descripción, prioridad y hora de registro).
    - Si no hay tickets pendientes, muestra un aviso.

5. *Buscar ticket por ID y mostrar detalles* :
    - El usuario ingresa un ID, y la aplicación busca el ticket correspondiente en la lista.
    - Si existe, muestra todos sus datos (descripción, prioridad, hora de registro).
    - Si no existe, muestra un mensaje de error.

# Funcionando correctamente:
- Registrar tickets con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los tickets.
- Ver la lista de espera de tickets, ordenada por prioridad y hora de registro.
- Atender al siguiente tickets, respetando el orden de prioridad.

# Problemas conocidos:

- posibles errores de segmentacion si el cliente ingresa datos con un tamaño mayor al establecido 

# A mejorar:

- crear atajos en caso de que el usuario se equivoque y salte error para poder intentarlo nuevamente sin tener que volver al inicio o en que caso que quiera devolverse hacia atras.

# Ejemplo de uso
**Paso 1: Registrar un Nuevo Ticket**

        se comienza registrando un nuevo ticket ingresando al sistema.

        ```
        Opción seleccionada: 1) Registrar ticket:
        ingresar ID: 1234
        ingresar problema: (problema)
        ```

        El sistema registra A Joaquin con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde.

**Paso 2: Asignar Prioridad a un Paciente**

        el usuario puede asignar un nivel de prioridad para su problema.

        ```
        Opción seleccionada: 2) Asignar prioridad a ticket
        Ingrese el ID de Joaquin: 1234
        Seleccione el nuevo nivel de prioridad (Alto, Medio, Bajo): Alto
        ```

        El sistema actualiza la prioridad de Joaquin a "Alto", asegurando que será una de los proximos usuarios en ser atendido.

**Paso 3: Ver la Lista de Espera**

        El usuario revisa la lista de espera para ver todos los tickets y sus prioridades.

        ```
        Opción seleccionada: 3) Mostrar lista de espera
        ```

        La lista muestra a Joaquin , indicando su prioridad alta y que al ser el primero seria el primero en ser atendido.

**Paso 4: Atender al Siguiente Paciente**

        Joaquin es llamado para ser atendido basándose en su prioridad.

        ```
        Opción seleccionada: 4) Atender al siguiente ticket
        ```

        El sistema muestra que Joaquin está siendo atendido y la elimina de la lista de espera.
**Paso 5: Buscar ticket por ID y mostrar detalles**
        - Joaquin ingresa su ID, la aplicación busca el ticket correspondiente en la lista.Si existe, muestra todos sus datos (descripción, prioridad, hora de registro). Si no existe, muestra un mensaje de error.
        
        ```
        Opción seleccionada: 5) Buscar ticket por ID:
        ingrese su ID : 1234
        descripción: (problema)
        prioridad : Alto
        hora de registro (hora a la que se ingreso el ticket inicialmente)

        ```