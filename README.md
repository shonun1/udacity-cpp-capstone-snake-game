# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

https://github.com/user-attachments/assets/19720bf2-877e-4f3a-9c85-91bb7f9585bf

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* clang-format >= 18.1.8
  * For Linux: `sudo apt-get install clang-format`
  * For Mac: `brew install clang-format`
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_ttf >= 2.22.0
  * Details on how to install SDL2_ttf can be found [here](https://wiki.libsdl.org/SDL2_ttf) (libsdl2-ttf-dev on Ubuntu)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Execute `make` command, which will cleanup any old builds and build the project from scratch and finally run the project.

## Font attribution

The font Jersey 10 used in the project was designed by Sarah Cadigan-Fried and published under the OFL license. Please refer to the Google Fonts page for more information: https://fonts.google.com/specimen/Jersey+10/about

## Code structure

The code is separate into logially grouped files:

1. `main.cpp` - The main entry point of the application. Initializes some top level classes and starts the game loop.
2. `controller.cpp` - The controller class handles the user input.
3. `game.cpp` - The game class that handles all game logic, including the main game loop and all game state updates.
4. `renderer.cpp` - The renderer class that handles the rendering of the game.
5. `snake.cpp` - The snake class that implements the snake logic and all of its components.
6. `weapon.cpp` - The weapon class implementation, which is used as a member of a snake.
7. `missile.cpp` - Missile implementation, a member of the weapon class.
8. `game_structures.cpp` - All other structures that were used in the game, such as the game settings, grid size etc.

## New features

The following features were added to the original code:

* The game saves high scores to a file called `scores.txt`. The file is created if it does not exist. The file is read at the beginning of the game and written at the end of the game (when the snake is no longer alive). Snake dying also terminates the game.
* The snake can shoot missiles by pressing the space bar. Missiles are shot in the direction the snake is facing. The current weapon and snake ammo are displayed in the window top bar. Multiple weapon types were implemented, however I lacked time to make extra use of them. The weapon has a chance to change into a special weapon each time the snake eats food and does not have a special weapon. If a missile of any type of weapon hits the food, it is counted as if the snake ate the food.
* The snake can pick up ammo by eating food. The ammo is displayed in the window top bar. The amount of current score of ammo is added each time the snake eats food.
* Game settings were introduced into the game, which are loaded and saved into the `settings.txt` file. Currently, the settings contain only the username, which will be saved to the high scores file (possible to update only directly through the settings file), and the grid size, which can be updated through the game options.
* The game has a pause feature, which can be toggled by pressing the `ESC` key. Pausing the game will display a menu with the following options:
  * Continue - Continue the game.
  * Grid Size - Change the grid size, which toggles the size between three options: 32x32, 48x48 and 64x64. The game continues after the grid size is changed, food might get placed in a different location if it was out of the new grid size bounds.
  * Exit - Exit the game.
* Food is rendered with a random color each time it is placed on the grid. Additionally, some of the food is toxic, which is also random, but somewhat consistent with the color as when the generated random color number is divisible by 3 and a toxic food can be spawned at that time, the food will be toxic. Toxic food slows down the snake for around 5 seconds.

I honestly see a lot of potential for so many more features that would be interesting to implement that unfortunately I was unable to do due to time constraints. I will probably end up implementing them in the future, but this finalizes my submission for the project.

## Rubric points

**Please note that all the file line references were created at the git ref 9550ac5e3596d64e15ff113d460a172409d35bb3. Please refer to [this branch](https://github.com/shonun1/udacity-cpp-capstone-snake-game/tree/9550ac5e3596d64e15ff113d460a172409d35bb3) for accurate line references.**

The main fix afterwards was related to [correct usage of shared pointer](https://github.com/shonun1/udacity-cpp-capstone-snake-game/commit/ca27ee99f3d1cddefe86a42c1a59fe7258581402) and [Ubuntu compilation error fixes](https://github.com/shonun1/udacity-cpp-capstone-snake-game/commit/37b740295026e05dec16936fb8b9631ecff4794b), since I was developing the project locally.

1. README - all points satisfied with the current README file.
2. Compilaition - the code compiles and runs without errors. Stuck with make, with only slight improvement with the top level `Makefile`.
3. Loops, Functions, I/O:

* The project demonstrates an understanding of C++ functions and control structures:
  * The project is grouped into logical classes and functions. Use of control structures is essentially unavoidable, some examples would be in: `weapon.cpp:13-27; weapon.cpp:29-39`
* The project reads data from a file and process the data, or the program writes data to a file.
  * Settings and scores are read and written to files, e.g. `game.cpp:134-140; game_structures.cpp:20-44`
* The project accepts user input and processes the input.
  * Snake can shoot missiles by pressing the space bar, pause the game by pressing the `ESC` key, and menu actions can be confirmed by pressing the `ENTER` key, e.g. `controller.cpp:47-64`
* The project uses data structures and immutable variables.
  * Multiple instances of various structures are used, such as vectors, maps, a list and use of immutable variables e.g. `game_structures.cpp:6-18; weapon.h:27; weapon.cpp:13-27`

4. Object Oriented Programming:

* One or more classes are added to the project with appropriate access specifiers for class members.
  * Multiple classes were added to the project with appropriate access specifiers (I have also made use of structs for simple data types that can have public members), e.g. `weapon.h:9-30; game_structures.h`
* Class constructors utilize member initialization lists.
  * All classes constructors with arguments use member initialization lists (with possible extra processing in the constructor), e.g. `missile.h:7-9; game_structures.cpp:79-96`
* Classes abstract implementation details from their interfaces.
  * All implemented functions have clear names which clearly state their purpose with some additional comments where necessary. Member functions don't change the state in unexpected ways, e.g. `weapon.cpp; missile.cpp`.

5. Memory Management:

* The project makes use of references in function declarations.
  * Multiple functions use pass-by-reference, e.g. `game_structures.h:98-101; game.h:23-24 renderer.h:19-20`
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  * The project uses RAII inside the game class for the Snake class instance, which is a unique pointer. The game class is responsible for the Snake instance, the instance is created in the game class constructor and naturally destroyed when the game class instance is destroyed - `game.cpp:8-36`
* The project uses smart pointers instead of raw pointers.
  * A few smart pointers are used in the project, one example being the previously mentioned Snake class instance - `game.cpp:8-36`, but also Snake weapon instance and a shared pointer for the GameSettings instance - `snake.h:43; main.cpp:13-31`

6. Concurrency:

**Note: After receiving submission feedback I have implemented completely different concurrency features than the ones I initially had. Please review the concurrency features, that were commited [here](https://github.com/shonun1/udacity-cpp-capstone-snake-game/commit/bff888313a597a77f8bcbbc653630dd45586d3de).**

* As can be seen in the commit, the project uses a separate thread that is launched when the snake eats toxic food. The thread is responsible for slowing down the snake for a certain amount of time. Additionally saving the settings to a file was modified to use async execution. Using concurrency required using mutexes and locks across the project, which can be seen in the commit. This satisfies the concurrency rubric points about multithreading and locking.

## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
