Battleship (C Console Game)

A simple console-based Battleship game written in C.
The player and the AI place ships on a 10×10 grid and take turns firing shots.
The project includes saving/loading game state and seed-based ship generation.

How to Run
Compile the code (Linux/macOS):
gcc *.c -o battleship

Run the game:
./battleship [seed]

seed is optional; if not provided, a random seed is used.
Example:
./battleship 12345

Play using coordinates like A0, B5, etc.
Use commands save, load, or final during the game.
