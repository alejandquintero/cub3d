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
