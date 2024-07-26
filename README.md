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
Once the Gravel is built, you should get an executable which will open a window and display nothing. In the 'app.cpp' file, you can see an example of a very simple Gravel application. It just creates a camera and begins the 3d and 2d rendering. There's alot more to Gravel than that, of course. But that is only a simple example. 

# How To Use? 
The usage of Gravel is different than the usual library or framework you might be familiar with. While you can build Gravel and use it as a dll or static lib, Gravel is missing a couple of pieces when you first build it. Gravel's _purpose_ is mainly a foundational base at which the games will be built upon. It is only a mixture of types and functions that will help you make games easier. It does not have a generic editor. No scenes. No entities. You do not have to worry about OpenGL, GLFW, audio, reading shaders, or any of that. However, making the _structure_ of your game, is indeed of _your_ concern. Not Gravel's. Therefore, the way you use Gravel is just the way you would build it. If you followed the steps up above to build Gravel, then you have done 90% of the work in order to get Gravel up and running. You can take the folder you cloned, rename it to your project's desired name, and then do one more step. 

In the "CMakeLists.txt" file, there's a line at the very beginning of the file that defines the project's name:

```cmake
project(Gravel)
```

All you have to do is change _Gravel_ into whatever you want the project's name to be. Once that is done, you can start the build process and get a resulting executable from that. Again, this is not "ordinary" as far as libraries go. However, as I said, Gravel is designed to be added to and customized.

Once that is done, you can start hooking an application to Gravel. There are mainly two files that we will start with. "main.cpp" and "app.cpp". They should be in the "app" folder when you clone Gravel. 

The _main_ function has the following code: 

```cpp
#include "engine/core/app_desc.h"
#include "engine/core/engine.h"
#include "app/app.h"

int main() {
  AppDesc desc = {
    .window_width = 800, 
    .window_height = 600, 
    .window_title = "Gravel", 
    
    .init_func = app_init,
    .shutdown_func = app_shutdown,
    .update_func = app_update, 
    .render_func = app_render, 

    .user_data = nullptr, 
    .has_editor = false,
  };

  engine_init(desc);
  engine_run(desc);
  engine_shutdown(desc);
}
```

As you can see, we define the width, height, and title of the window inside this struct called `AppDesc` which we will later feed into the `engine_*` functions. Now, there are also 4 function pointers that will be the backbone of the _whole_ application:

```cpp
// Will be called upon the engine's startup. 
bool init_func(void* user_data); 

// Will be called when we exit the application.
void shutdown_func(void* user_data); 

// Will be called every frame. update_func will be called first, however, followed by render_func.
void update_func(void* user_data); 
void render_func(void* user_data); 
```

The `user_data` all the functions take as a parametar, will be taken from the `.user_data` memeber of the `AppDesc` struct every function call. And, as for the last member of the `AppDesc` struct--`.has_editor`-- will be used to determine if the engine will use an editor or not. Pretty obvious.

After defining the `AppDesc` struct, we will feed it into the `engine_init` function and all the functions after that. `engine_run` will update and render the application until something wrong happens or the user exits. It will call the `update_func` and `render_func` function pointers of the `AppDesc` struct in the process as well as update other systems of the engine. As for the `engine_shutdown` function, it will call the `shutdown_func` function pointer of the `AppDesc` struct as will as deallocate and close any contexts. Some cleanup basically.

There are multiple ways you can make these function pointers and feed them into the `AppDesc` struct. For example, you can also use a static instance of a struct or class called `App` inside the "app.cpp" translation unit and _still_ ignore the `user_data` parametar. This is the same example you will see in the current "app.cpp" file: 

```cpp
struct App {
  Camera camera;
  Camera* current_cam;

  Font* font;
};

static App s_app;
```
And here are the functions: 

```cpp
bool app_init(void* user_data);
void app_shutdown(void* user_data);
void app_update(void* user_data);
void app_render(void* user_data);
```

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
- 3D physics
