# C++ Raycaster & 2D Level Editor

**Created by Arpit Omre**

This project is a small 2D raycasting engine and level editor built using **C++ and Raylib**. The project demonstrates how a basic 3D-style rendering system can be created from a 2D environment using mathematical ray-wall intersection calculations.

The program includes a simple level editor where walls can be drawn using the mouse. The player can move and rotate around the created level, while the raycaster casts multiple rays across a configurable field of view to detect walls. The distance to each wall is used to calculate the height of the rendered wall slices, creating a 3D-like perspective.

The renderer also includes **fish-eye correction**, distance-based shading, configurable ray length and FOV, and connected-corner detection for additional wall shading. Player movement includes basic wall collision and sliding along walls.

The project is organized into separate C++ header and source files for the player, walls, and raycasting system. It was developed using **Visual Studio Code, C++, and Raylib**, with **Git** used for version control.

## Controls

* **W / S** - Move forward / backward
* **A / D** - Rotate player
* **E** - Switch between editor and raycaster mode
* **Left Mouse Button** - Draw walls in editor mode
* **Shift + C** - Clear the current level

## Technologies Used

* C++
* Raylib
* Visual Studio Code
* Git
* Vector mathematics
* Ray-wall intersection mathematics

## Author

**Arpit Nitin Omre**
