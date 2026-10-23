# Doodle

This was a test task required to join an Unreal Engine (UE) bootcamp.

The requirement was to create a Doodle Jump clone as closely as possible within one week.

[I based this on my previous attempt to build an ECS-based game](https://github.com/Aeomanate/SpaceshipBP). 
For the first 4 days, I worked on adapting my old project to the latest C++26 standard 
and my updated vision of how things should be structured. I spent the next 4 days implementing the game itself.

The gameplay code itself is quite simple and straightforward, thanks to my ECS architecture. 
I'm interested in pushing the boundaries of my ECS implementation: where could it be improved or flawed?

Originally, I used a proprietary graphics framework that I should not have committed. 
So, I replaced it with my own framework implementation. 
Now, it has been [updated to be usable via CMake FetchContent](https://github.com/Aeomanate/AeoGameFramework), similar to rapidjson-cpp. 

## Controls 

Arrow keys or WASD.

## Architecture

* I chose the `reflect-cpp` library for simple configuration and future save/load logic.
* The core is my implementation of the ECS pattern [in a separate "simulation" layer](./src/Simulation/ECS):
  * **Entity** - a simple class representing an object. 
  * **Component** - a data structure that stores a map of Entities to filter them by component in O(1) time.
  * **System** - runtime logic operating on entities, processing all entities that have the required components.
* [A level](./src/Simulation/GameLevels/Level1.cpp) stores arrays of systems and entities. 
  Each specific level creates the appropriate entities, systems, and components using 
  convenient interfaces based on variadic templates.
* There is also an implementation of a Qt/UE-signal-like reactive messaging system. 
  [It is an Observer pattern implementation](./src/EventsHandling), which helps dispatch input events to systems.
* Dependencies are fetched from their respective GitHub repositories via CMake FetchContent. 
  In total, there are around 228 files to compile.

## TODO

Features originally planned:
* A mouse-based shooting system
* A pause menu screen
* A scoring system rendered using simple digit images
  (effectively a custom image-based font)
* A variety of platform types (regular, breakable, moving, etc.)

However, I ran out of time before the deadline. The scope was too large for me back then.

Known bugs to fix:

* Character input can get stuck moving left or right after releasing the keys.
* The game may occasionally crash.
* Character movement needs smoothing to make controls less clunky.
* Extract Simulation into a separate library to make it easily testable.

## Build

* A MinGW compiler with C++26 support
* The latest CMake version
* I'm using CLion, but if you want to build from the command line: 

  ```
  cmake.exe --build cmake-build-release --target install -j 8
  ```

## Notes

* AI agents were not used while implementing this game and framework.
  I only started using them to migrate from the proprietary framework to my own implementation of its interface.