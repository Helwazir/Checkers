# M4OEP-Graphics-helwazir
Created by Hamzah Elwazir

This builds on my M2OEP-Class-Relationships-helwazir project
# Checkers
This is a simple graphical version of the two player game of Checkers. This version is made with the intention of 
having two players take turns making moves. This version of the game does not support jumping over multiple pieces
at a time. Players take turns clicking the piece they wish to move and then clicking the space they wish to move it 
to. To jump over a piece a player should click on the landing spot, not the piece they are jumping over.

# Setup
In order to run this program FreeGLUT must be installed and set up in the project.
#### Setup on Mac:
- No additional setup required on OSX.
#### Setup on Linux:
- Use the CMakeLists-Linux.txt file
#### Setup on PC:
- Dowload FreeGLUT from `http://freeglut.sourceforge.net/index.php#download` and add the `include/` and `lib/` folders
to `C:/Program Files/Common Files/freeglut/`. If the directory does not exist then create it.
- Add `freeglut.dll` from `freeglue/bin/` to the cmake-build-debug folder.

# Keyboard and Mouse Commands
The 's' key is used to dismiss the rules and begin playing the game. The mouse is used to indicate which piece a player 
wants to move and the space they wish to move it to. The 'esc' key can be pressed at any time in order to exit the 
program. 
