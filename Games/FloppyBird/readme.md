NOTE: OLD BUILD. CHECK MY OTHER REPO'S FOR LATEST STABLE BUILD OF THIS GAME.

Floppy Bird 2D Scroller Game  (alpha build v0.2)

Requirement:

SOIL image loader library : `sudo apt-get install libsoil-dev`

Freeglut : `sudo apt-get install freeglut3-dev`

If required packages are satisfied, then just enter `make` to compile the code & enter ./floppybird to run.

Changelog:
1. Added Parallax tree effect.
2. tweaking of movement and collision.

Known Issue:

1. stuttering/frameskip issue, needs to properly implement vsync using glew. Adjust fps and run with vlbank_mode=0 option as a temp fix.
2. Collision detecition and gravity algorithm tweaking required
3. Initial game rendering delay/stutter.

![Alt text](/WorkOut/temp_files/floppy.jpg?raw=true "floppy")


