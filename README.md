# Doodle

This was a test task as requirement to join an UE bootcamp.

The requirement was to create a Doodle Jump clone as close as possible within a week.

[I used my old attempt to build an ECS-based game](https://github.com/Aeomanate/SpaceshipBP). 
For 4 first days I've been trying to adapt my old work to the newest C++26 standard 
and my new vision of how things should be done. Next 4 days I've spent on implementing the game itself.

The actual gameplay code is pretty simple and plain, thanks to my ECS architecture. 
I'm interested in pushing bounds of my ECS implementation: where it could be wrong?

Originally, I had a "proprietary" implementation of graphics framework which I shouldn't have committed.
So, I replaced it with my own framework implementation. 
Now, it's [updated to be usable via CMake fetch](https://github.com/Aeomanate/AeoGameFramework), like rapidjson-cpp. 

## Controls 

Just arrow keys or WSAD.

## Architecture

* I chose reflect-cpp lib to have the simplest config and further save-load logic.
* The core is my implementation of ECS pattern [in a separated "simulation" layer](./src/Simulation/ECS)
  * Entity - is a simple class. 
  * Compnent - is a some data structure which stores a map of Entity to filter them by component for O(1).
  * System - is a runtime logic around entities which have designed components.
* [A level](./src/Simulation/GameLevels/Level1.cpp) stores systems and entities arrays. 
  Each exact level just creates appropriate entities, systems and components via 
  handful interfaces based on variadic templates.
* There is also an implementation of Qt/UE-signal-like reactive messaging system. 
  [It's the Observer pattern implementation](./src/EventsHandling), which helps in transferring input events to systems.
* Dependencies are handled via CMake fetch from GitHub appropriate repositories. 
  An overall count of files you need to compile is around 228.

## TODO

There should have been:
* A mouse-based firing system
* A menu with the pause screen
* A system for current score based on simple number images
  (thus, it would have been my own image-based font)
* A range of planform types (regular, crashable, movable, etc.)

But the deadline went pass me. The scope was too large for me than.

There are some bugs in the code, need to fix them sometime:

* The character input may stuck to left or right after releasing these buttons.
* The whole game could crash at some point
* The character movement must be adjusted to be more smooth and not so hard to control.
* Extract Simulation into a separated library to make it easy testable.

## Build

* You need a MinGW compiler with C++26 support
* You need a newest CMake
* I'm using CLion, so you shouldn't print it by yourself: 

  cmake.exe --build cmake-build-release --target install -j 8

## Notes

* The AI agents wasn't used while implementing this game and framework.
I've only started to use them to migrate from a propriate Framework to my own implementation of its interface.