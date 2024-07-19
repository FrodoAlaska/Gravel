# What Is Gravel?  
A minimalist game framework built with GLFW and OpenGL. Brought to you by C++. 
The aim of Gravel is not to build a game engine capabale of doing what Unity or Unreal can. Rather, it is a foundational structure of which a lot of my future games and projects will be built upon. It is essentially a _game framework_ more than it is a _game engine_. 

I don't really have a plan for this framework. I was just tired of writing the same exact code to do the same exact things. Opening a window, getting input, playing audio, setting up OpenGL, loading models, loading shaders, etc... it was getting very annoying having to do this all the time. _Every_. _Single_. _Time_. This is meant to be a helper for that "problem". A codebase to get me up and running quickly. Anytime I feel like I need to add to it, I will. 

For the reasons above, this framework is by no means the best, nor is it even close. Does it work? Yes. Is it the most performant? No. Not by any stretch of the imagination. Features are only added as I need them for any game project I'm planning to make. 

If you plan to use this as your base for your projects (for some reason), I strongly encourage you to break it apart and tinker with it. Perhaps you are more knowledgeable than I am (very likely) and you may have a better solution to a specific feature or whatnot. 

# How To Build?
This project uses the CMake build system. I know, not the most ideal. Yet, it is the build system I'm most familiar with. If you worked with CMake before this should be easy for you and, even if you haven't, it shouldn't be much of a hassle. 

Gravel does use a couple of dependencies. However, most of them (apart from one), are header only. Meaning, most of the libraries used here are built with the project itself. The only library that Gravel uses that needs to be linked is GLFW. But, as you can see from the project files, there is a folder called _libs_ where GLFW resides.  

Gravel builds all of its libraries as well as its own files. It might take longer to build but it saves me from having to manage the dependencies. Run the commands below to build Gravel. You can also check the 'main.cpp' file to see how an application is started.

```
git clone https://github.com/MohamedAG2002/Gravel.git 
cd Gravel 
mkdir build && cd build 
cmake ..
make 
```
Once the Gravel is built, you should get an executable which will open a window and display nothing. In the 'app.cpp' file, you can see an example of a very simple Gravel application. It just creates a camera and begins there 3d and 2d rendering. There's alot more to Gravel than that, of course. But that is only a simple example. 

# How To Use? 
TODO

# Current Features
- 2D batch renderer
- Simple text rendering 
- 3D model loading 
- 3D instanced renderer (only works with cube meshes currently)
- Simple audio system 
- Resource manager 
- Shader loading
- ImGui integration 
- Simple 3D camera 
- Somewhat robust retained mode UI system with anchoring.
- Event system
- Simple 3D physics
