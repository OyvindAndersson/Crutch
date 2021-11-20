
# Crutch Game Engine

## Build
Crutch build configurations are set up using premake5.
Currently only tested on windows platform.

```js
Run ".Build/Win-CreateProjectFiles.bat" to generate files for Visual Studio [2019 as default]
```
```js
The helper bat "./Build/DeleteAll_VS Files.bat" recursively deletes *all* solution and project files created. Optionally also deletes temp files.
```

**Future plans**
- Test build system on linux and macos
- Take in msvs version as a console arg when running .bat
- Split up premake files to have one in each project dir, to allow better context when editing the premake files

## Main project goals
- Learn how to create a clean application structure, easy to use by client projects
    - Subsystems
    - Platform abstraction
    - Eloquent code and structures
- Learn the basics of graphics programming
    - Using Open GL first
    - Try on DirectX later
- Learn maths with code: purpously re-invent the wheel in some cases, to get to know the maths better (even though perf could/*will* suffer)
    - Vectors, Matrices, etc
    - Perhaps try to allow for faster ops using simd
- Learn how to use and implement third-party libraries and abstract away from game code (i.e: Box2D physics, GLFW)
- Learn more about data-structures and their applications more intuitively by doing a large project
- Learn how to setup the build system so it can easily be shared without hiccups
- Improve c++ knowledge and gain better understanding of the low level stuff
- Create a simple 2D game with physics, sound, lighting, textures, UI etc.

## References
- Yan Chernikov ( Youtube: TheCherno::Game Engine Series - Hazel )
    - For getting started with a basic structure of a game engine
    - Open GL basics
- Unreal Engine
    - I'm used to using UE4, so the conventions are similar