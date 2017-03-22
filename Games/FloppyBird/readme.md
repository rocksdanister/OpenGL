Floppy Bird 2D Scroller Game  (alpha build v0.1)

Requirement:

SOIL image loader library : `sudo apt-get install libsoil-dev`

Freeglut : `sudo apt-get install freeglut3-dev`

If required packages are satisfied, then just enter `make` to compile the code & enter ./floppybird to run.

Changelog:
1. Added Parallax tree effect.
2. tweaking of movement and collision.

Known Issue:

1. stuttering/frameskip issue, needs to properly implement vsync using glew
2. Collision detecition and gravity algorithm tweaking required

![Alt text](/WorkOut/temp_files/floppy.jpg?raw=true "floppy")

Note: Collision,gravity,performance needs to be reworked.
