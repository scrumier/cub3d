
# Cub3D 🕹️

**Cub3D** is a 3D graphics project inspired by classic FPS games. It leverages raycasting to create a 3D view from a 2D map, allowing players to explore and interact within a virtual environment.

## Controls
- **WASD**: Move forward, backward, and strafe left/right.
- **Left/Right Arrows**: Rotate the player’s view.
- **F**: Open and close doors.

## Configuration
All game variables can be adjusted in the `define` section of the header file, allowing customization of settings like movement speed and visual parameters.

## Installation

### Prerequisites
- **Make** and **gcc**: Ensure these are installed to build the project.
- **MLX Library**: The MiniLibX graphics library is required.

### Build and Run
1. Clone the repository:
   ```bash
   git clone https://github.com/scrumier/cub3d.git
   cd cub3d
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run the game:
   ```bash
   ./cub3D path/to/map.cub
   ```

## Features
- **Raycasting Engine**: Simulates a 3D perspective in real-time.
- **Door Mechanics**: Adds interactivity with open/close functionality.
- **Configurable Settings**: Easily tweak parameters in the header file to modify gameplay.

## Example Maps
Several example maps are provided within the `maps` directory to showcase different layouts and settings.

---

Enjoy exploring the world of Cub3D!
