# RT

### What is RT?

RT is a fully featured Raytracer built as a project at 42. This project is intended to be a four person six week project, however I decided to attempt it by myself. Ray tracing is a technique for rendering images by simulating the path of light through an image plane. This project uses .ini files to configure the input.

### Coding Style

At 42, we follow a strict norm in order to teach us to follow style guides. This norm also prevents us from using many built-in functions. In this project, we are limited to using a barebones graphic library called minilibx. This library limits the functionality to creating windows, handling input hooks, and coloring specific pixels.

### Usage

RT takes it's starting configuration in the form of a .ini file. These files specify the window name and size, as well as which objects are to be rendered into the scene and their positions.  

Once loaded up, RT accepts basic arrow key and numpad input to control the camera, as well as command line input to interact with the scene. This allows objects to be added and removed, as well as the modification of their properties.

### Features
 
 - INI File Input
 - Keyboard Input
 - Live CLI
   - Adding/Removing Objects
   -  Modifying Objects
   -  Printing Debug Info
 - Reflections
    - Lambertian Shading
    - Blinn-Phong Shading
 - Refractions
 -     Density
 - Transparency
 - Anti-Aliasing
 - Supersampling
 - Perlin Noise
    - Marble Material
    - Bump Mapping
 - Triangle Intersections
 - Model (Parsed .OBJ) Input

### Images

![Mirrors](http://i.imgur.com/pEeEJua.png)

![Models](http://i.imgur.com/am0rMod.png)

![Shrek](http://i.imgur.com/1g5clE1.png)

![Marble](http://i.imgur.com/sWaQLFg.png)

![Bump Maps](http://i.imgur.com/NjneQVT.png)
