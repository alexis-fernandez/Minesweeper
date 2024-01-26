# Minesweeper Game

This is a Minesweeper game implemented in C using the SDL2 library for graphics.

## Instructions

1. **Download:** Download the code file (`main_Graphic.c`) from this repository.

2. **Download PNG Images:** Download the included PNG images (17 in total).

3. **Important:** Move the PNG images to the same directory as your `main_Graphic.c` code.

4. **Important:** Copy the path of each PNG image and update the corresponding paths in the code.

5. **Compile Code:**
    ```bash
    gcc main_Graphic.c -o minesweeper -lSDL2 -lSDL2_image
    ```

6. **Run Program:**
    ```bash
    ./minesweeper
    ```

7. A window will appear with the Minesweeper title screen.

8. Click "Play" to start the game or "Quit" to exit.

9. In the game, click cells to reveal content. Avoid hitting bombs.

10. The game ends when you reveal all safe cells or hit a bomb.

11. After the game ends, close the window and rerun `./minesweeper` in the terminal to restart.

## Code

The code includes functionality for creating a Minesweeper game board, handling user input, and displaying graphics using SDL2. PNG images enhance the gaming experience.

## Dependencies

- SDL2 Library
- SDL2 Image Library

## Resources for Learning SDL

- [SDL Basics: Creating a Window](https://en.wikibooks.org/wiki/SDL_(Simple_DirectMedia_Layer)/Basics/Creating_a_window)
- [Using SDL2 in C (with C too)](https://dev.to/noah11012/using-sdl2-in-c-and-with-c-too-1l72)
- [Rendering Text in SDL2](https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2)
- [Drawing Rectangles in SDL2](https://dev.to/noah11012/using-sdl2-drawing-rectangles-3hc2)

## Acknowledgments

Thanks to the open-source community and contributors to SDL2 for providing the tools to create this Minesweeper game.
