Steps to compile the projects:

1. Release configuration and x64 build (As the freeglut library and SOIL library is 64 byte. You can compile freeglut included in SDK folder to compile for other build configuration)

2. Change include directories(glut.h, SOIL.h) and Library(freeglut.lib, SOIL.lib) path to the one in the SDK

3. In Linker->input : add SOIL.lib

4. Compile and run.

5. You can also directly run the .exe I have created and included in the project->solarSystem->x64->Release  folder

6. If you have any questions please email me at gbhatt@iastate.edu
