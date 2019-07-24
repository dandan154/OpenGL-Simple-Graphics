# OpenGL-Simple-Graphics
An introductory exercise to the world of graphical programming. A simple program where 3 aeroplanes are drawn to screen and rotate around one another, lit using static lighting. 'sandbox.cpp' serves as the main entry point of the program. 

Textures and objects have been excluded due to licensing. 

## Functionality
The goal of this program was to display a textured object (in this case, an aeroplane) and then demonstrate an understanding of moving objects by having them rotate around one another. It also served as a way to demonstrate simple static lighting.

## Techniques
Below is a sampling of the techiques employed throughout development: 

* Nested Object Movement - generated objects rotated one another, demonstrating the OpenGl model-view-projection model. 

* Blinn-Phong Model - Lighting model applied to generate efficient (albiet simple) per-vertex shading. 

* Model Loading - Plane model is loaded from parsed .obj file, improves reusability of code. 

## Libraries Used

* [SOIL2](https://bitbucket.org/SpartanJ/soil2/src/default/) - Texture Loader, allowed .PNGs to be applied to objects.

* [GLEW](http://glew.sourceforge.net/install.html) - OpenGL Extension Wrangler Library.

* [GLFW](https://www.glfw.org/) - OpenGL Implementation Library.
 
