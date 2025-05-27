Secret Code Game

Secret Code Game is a C++ image-based puzzle game developed using the SFML (Simple and Fast Multimedia Library). The player must uncover and enter six hidden words in each stage by observing an image. The game challenges memory and observation skills under a time limit.

Features

8 challenging stages with unique images

6 hidden words per stage to discover

80-second timer for each stage

Immediate feedback for correct/incorrect inputs

Game over screen with failure image

Player records saved to a file

Clean input system with text rendering using SFML


How to Play

1. Enter your name to start the game.


2. Observe the displayed image carefully.


3. Type the hidden words one by one.


4. Press Enter after each word.


5. If all 6 words are correct, move to the next stage.


6. Game ends if a wrong word is entered or time runs out.



Files

main.cpp: Main game logic

images.txt: Contains image paths and associated hidden words

users.txt: Stores user names and the stage they reached

fonts/Roboto-Bold.ttf: Font used for displaying user input

images/: Folder containing all stage images and the failure screen


Requirements

C++ Compiler

SFML 2.5 or later


Setup Instructions

1. Install SFML: https://www.sfml-dev.org/download.php


2. Clone this repository:

git clone https://github.com/yourusername/secret-code-game.git


3. Build and run using your favorite IDE or command line (make sure SFML is linked properly).



Future Improvements

Add hint system

Display remaining time on screen

Background music and sound effects

High score leaderboard
