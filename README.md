# Doodle

This was a test task as requirement to join an UE bootcamp.

The requirement was to create a Doodle Jump clone as close as possible within a week.

I've used my old attempt to build an ECS-based game. 
For 4 first days I've been trying to adapt my old work to the newest C++26 standard 
and my new vision of how things should be done. Next 4 days I've spent on implementing the game itself.

The actual gameplay code is pretty simple and plain, thanks to my ECS architecture. 
I'm interested in pushing bounds of my ECS implementation: where it could be wrong?

## Controls 

Just arrow keys. 

There should have been: 
* A mouse-based firing system
* A menu with the pause screen
* A system for current score based on simple number images 
  (thus, it would have been my own image-based font)
* A range of planform types (regular, crashable, movable, etc.)

But the deadline went pass me. The scope was too large for me than.

## Architecture

* I chose reflect-cpp lib to have the simplest config and further save-load logic.
* The core is my implementation of ECS pattern [in a separated "simulation" layer](./src/Simulation/ECS)
  * Entity - is a simple class. 
  * Compnent - is a some data structure which stores a map of Entity.
  * System - is a runtime logic around entities which have designed components.

## TODO

There are some bugs in the code, need to fix them sometime.

* The character input may stuck to left or right after releasing these buttons.
* The whole game could crash at some point
* The character movement must be adjusted to be more smooth and not so hard to control.
* Extract Simulation into a separated library to make it easy testable.
