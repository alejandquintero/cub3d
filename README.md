# [Cub3d | 42 School - Rank 04]

Cub3D is a C project based on a raycasting rendering engine inspired by Wolfenstein 3D. It uses MLX42 for graphics and libft_v2 as a utility library.
This project was developed collaboratively by [@alejandquintero](https://github.com/alejandquintero) and [@lgandarillas](https://github.com/lgandarillas).

## Cloning the Repository
This project uses submodules (`libft_v2` and `MLX42`), so it's important to clone it correctly using the `--recursive` option:
```bash
git clone --recursive git@github.com:alejandquintero/cub3d.git
```
If you have already cloned the repository without this option, you can initialize and update the submodules manually:
```bash
git submodule update --init --remote
```

## Dependencies
Before compiling, ensure you have the necessary dependencies installed. Run the following command:
```bash
sudo apt update && sudo apt install -y build-essential cmake libglfw3 libglfw3-dev libx11-dev xorg-dev
```

This installs:
- `build-essential` → C compiler (gcc), make, and essential development tools.
- `cmake` → Required for building MLX42.
- `libglfw3 & libglfw3-dev` → Necessary for MLX42.
- `libx11-dev & xorg-dev` → X11 development libraries for windowing support.


## Compilation
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
```
To fully recompile from scratch:
```bash
make re
```

## Dependencies
...

## Execution
...
