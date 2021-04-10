# README #

## General structure ##

* `doc` is for documentation, report, etc. Create a dir for your team there, e.g., `teamX`, and initialize the report document there.

## Templates ##

* `doc/report/project-report.tex` is the most documented example template in LaTeX, single column, more readable. To be able to compile LaTeX report, install and configure [MiKTeX](http://miktex.org) first (LaTeX backend compiler and styles and packages), then [TeXnicCenter](http://texniccenter.org) (GUI front-end to MikTeX, it will find MikTeX installation when installed after MikTeX). Open `project-report.tcp` project file for TeXnicCenter and compile it using F7 3 times; F5 to preview the PDF.

### Requirements ###

* CMake 3.17+
* VCPKG
* OpenGL
* 64-bit Libraries
    - GLFW
    - GLEW
    - GLM

### How do I get set up? ###

1. Download and Install [VCPKG](https://github.com/Microsoft/vcpkg)
2. Install the libraries from VCPKG using commandline argument "--triplet x64-windows" for 64-bit libraries on windows; "--help" to find equivalent for other OS
3. Set the CMake toolchain file for your IDE to ".../vcpkg-master/scripts/buildsystems/vcpkg.cmake"
4. Generate CMake cache
5. Build

### Controls ###

- `IJKL` will move the main FPS camera relative to the direction you are looking at.
- `Left Shift` will make you move faster.
- `Space` will move you vertically up along the `y-axis`.
- `Left Control` will move you down along the `y-axis`.
- `Home` will reset all world and camera transformations. 
- `Left Mouse Button` will make all vertical mouse movements a zoom in/out of the scene.
- `Z` will reset the zoom to its default value.
- `1 to 6` will select a model on the map. Default is `0`, which is the model at the center.
	- `Y` will move the model along `x`.
	- `H` will move the model along `-x`.
	- `A` will move the model along `z`.
	- `D` will move the model along `-z`.
	- `F` will move the model along `y`.
	- `V` will move the model along `-y`.
- `Mouse Button 4` will make mouse movements move the camera only along its `x-axis` and `y-axis` plane.
- `Middle Mouse Button` will make all vertical mouse movements change the camera's pitch.
- `Left Mouse Button` will make all horizontal mouse movements change the camera's yaw.
- `X` will toggle the textures on and off of all the models, except the skybox
- `[` will toggle the shadows cast by lights on and off

- `R` will switch to the main FPS camera of the scene
- `M` will switch to the front-view camera of the model
- `B` will switch to the back-view camera of the model
- `S` will switch to the top-down camera in front of the main spotlight looking at the origin
- `E` will switch to the circling camera always looking at the origin
- `Arrow Key Left` & `Arrow Key Right` will rotate the circling camera CW and CCW

- `C` will toggle the spotlight of the circling camera on and off
- `Q` will toggle the main spotlight of the scene on and off
- `N` will toggle the ceiling spotlight on and off

### References ###
- Code snippets for lighting calculations were taken from [https://learnopengl.com/]() and modified to fit the needs of the project.