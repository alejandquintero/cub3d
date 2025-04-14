# [Cub3d | 42 School - Rank 04]

Cub3D is a C project based on a raycasting rendering engine inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). It uses [MLX42](https://github.com/codam-coding-college/MLX42) for graphics and [libft_v2](https://github.com/lgandarillas/libft_v2) as a utility library.

This project was developed collaboratively by [@alejandquintero](https://github.com/alejandquintero) and [@lgandarillas](https://github.com/lgandarillas).

![Demo](assets/demo.gif)

## 🧠 What is Raycasting?
**Raycasting** is a rendering technique that simulates a 3D environment based on a 2D map. It works by casting a ray for each vertical stripe of the screen, finding intersections with walls in the map, and drawing vertical lines accordingly. This approach was used in early 3D games like Wolfenstein 3D to create a pseudo-3D effect efficiently.

## 📁 Project Structure
```bash
cub3d/
├── assets/         # Assets (demo GIF)
├── inc/            # Header files
│   ├── cub3d.h
│   ├── parsing.h
│   ├── raycasting.h
│   └── structs.h
├── libft_v2/       # Custom Libft (submodule)
├── MLX42/          # MLX42 graphics library (submodule)
├── mazes/          # Example .cub maps
├── src/            # Source files
│   ├── parsing/    # Maze parsing, validation
│   ├── raycasting/ # Movement, rendering, raycasting
│   ├── free.c      # Memory cleanup
│   ├── init.c      # Struct initialization
│   └── main.c      # Main entry point
├── textures/       # Texture images (.xpm42)
├── Makefile
└── README.md
```

### Cloning the Repository
Since the project uses submodules (`libft_v2` and `MLX42)`, clone it with:
```bash
git clone --recursive git@github.com:alejandquintero/cub3d.git
```
If you already cloned it without `--recursive`:
```bash
git submodule update --init --remote
```

#### ⚙️ Dependencies
Before compiling, make sure you have the following installed:
```bash
sudo apt update && sudo apt install -y build-essential cmake libglfw3 libglfw3-dev libx11-dev xorg-dev
```
This will install:
- `gcc`, `make`, etc.
- `cmake` for MLX42.
- `libglfw3` and X11 libraries for window management.

### 🛠️ Compilation
To compile the project, simply run:
```bash
make
```
If you want to compile in debug mode, use:
```bash
make debug
```
To clean up generated compilation files:
```bash
make clean  # Removes object files (.o)
make fclean # Removes object files and the executable
make re     # Recompile from scratch
```

### 🚀 Execution
After compiling, you can run Cub3D by passing a .cub map:
```bash
./cub3D mazes/42Example.cub
```
.cub maps define:
- Textures for North, South, East, West walls.
- Floor and Ceiling colors (RGB).
- The 2D layout of the maze.

Example Maze Snippet:
```bash
NO ./textures/north.xpm42
SO ./textures/south.xpm42
WE ./textures/west.xpm42
EA ./textures/east.xpm42
F 220,100,0
C 225,30,0

111111
100001
1020N1
100001
111111
```
- **1**: Wall
- **0**: Empty space
- **N, S, E, W**: Player starting position and direction

### 🎮 Controls
- **W** / **S** : Move forward / backward
- **A** / **D** : Strafe left / right
- **←** / **→** : Rotate view
- **ESC**       : Exit game