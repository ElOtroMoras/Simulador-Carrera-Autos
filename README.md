# Simulador de Carrera de Autos
### Sección 2
### Autores
- [Ignacio Mora Barrientos](https://github.com/ElOtroMoras) 
- [Joaquín Pérez Larrañaga](https://github.com/JoacoPL21)

### Correos
- ignacio.mora2001@alumnos.ubiobio.cl
- joaquin.perez2101@alumnos.ubiobio.cl
  
### ¿Cómo Compilar?
Esto puede realizarse mediante el comando make, el cual, por defecto, generará dos archivos: `output`, que es el simulador, y `outputDebug`, el cual es el simulador con impresiones adicionales con el fin de controlar la salida.

Además existen parámetros adicionales para el comando `make`, los cuales son:
- **normal:** Para la compilación del archivo `output`.
- **debug:** Para la compilación del archivo `outputDebug`.
- **clean:** Para eliminar los archivos resultantes de la compilación.

```
make
make normal
make debug
make clean
```

### Ejecutar
Al momento de ejecutar el programa es necesario que se realice de la siguiente manera:

```
./<output> <metros> <autos>
```

Donde:
- **output:** Nombre que tiene el archivo creado a la hora de compilar.
- **metros:** Cantidad de metros que debe de tener la carrera a simular, debe ser un numero entre **50 y 100**.
- **autos:** Cantidad de competidores deseados para la carrera a simular, debe ser un numero mayor o igual a **2**.

```
./output 100 6
./outputDebug 100 6
```

### Resultados
Al momento de ejecutar el programa se mostrara una linea de tiempo de todos los competidores, y luego de eso, una tabla que contiene la posicion final de cada competidor.