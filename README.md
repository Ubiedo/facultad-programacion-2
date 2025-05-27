# Programación 2 – Facultad de Ingeniería, UDELAR

Este repositorio contiene las tareas pedidas para la materia **Programación 2** de la Facultad de Ingeniería de la Universidad de la República (UDELAR).

## 📂 Contenido

Este repositorio contiene las tareas pedidas para la materia, organizadas en cuatro entregas:

- **Tarea 1**: Implementación de una agenda con eventos y fechas.
- **Tarea 2**: Manejo de estructuras de datos:
  - Jugada, jugador, partida.
  - Árbol binario para almacenamiento de jugadores, ordenada según fecha.
  - Lista doblemente enlazada para jugadores, ordenada según fecha.
- **Tarea 3**: Estructuras de pila y cola para manejo de jugadores:
  - Pila (LIFO) para guardar jugadores.
  - Cola (FIFO) para guardar jugadores.
  - Estructura de conjunto con capacidad finita para IDs de jugadores, que permite operaciones de unión, intersección y diferencia.
  - Funciones aplicadas: suma de números pares y menores que el resto.
- **Tarea 4**: Estructuras avanzadas:
  - Cola de prioridad (FIFO con prioridad).
  - Cola de estructuras de árboles de jugadores.
  - Tabla hash para búsqueda de jugadores por nombre.

> El código está desarrollado principalmente en **C++**, con algunos módulos en **C**.
> El `Makefile` fue proporcionado por la Facultad de Ingeniería como parte del material base del curso.

## 💻 Tecnologías utilizadas

- Lenguajes: C++, C
- Compilador: `g++` / `gcc`
- Sistema operativo: **Linux**
- Herramientas: Makefile

## 🐧 Requisitos

Este proyecto fue desarrollado específicamente para **sistemas Linux**. No se garantiza su funcionamiento en Windows o MacOS sin adaptaciones.

Asegurate de tener instalados:

```bash
sudo apt update
sudo apt install build-essential
```

## ▶️ Cómo compilar y ejecutar

Desde el directorio raíz del proyecto, en Linux:

```bash
make          # Compila el proyecto
./programa    # Ejecuta el binario generado (ajustar según el nombre)
```

## 👤 Autor

- [Federico Javier González Ubiedo](https://github.com/Ubiedo)
