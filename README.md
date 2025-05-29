# AsteroidSDL3

## Requirements
You need to have a x64 computer and visual studio 2022.

## About
A 2D classical Asteroid game.

## How to build

1) Run the build.bat. It will generate the solution automatically.
2) Run the generated solution and happy compiling!

## Main features
- Loggin system to register different levels of severity and channels in both the output console of visual studio, a logging file, and the command line.
- Implemented collision system using the concept of the grid. The grid is divided into equal sized rectangles and records which entities reside in that rectangle. Only the spheres around the entities in that rectangle are tested against each other for collision. The scheme used here is inspired by tiled deferred shading method for registering point lights in tiles.
- Implemented an event management system using std::function and lambdas in order to register events such as start of animations of explosion and warp, delayed activation and deactivation of collision state of asteroids before spawning and in the middle of the explosion animation etc.
- Implemented time rewind up to 30 seconds back in time by keeping track of only the important data of each frame in a ring buffer in order to be able to reconstruct the frame again as we go back in time.
- Implemented the game using entity component architecture which makes use of composition more than inheritance. This results in a more scalable, modular, and reusable code than if we were to favour inheritance over composition. Not to mention diamond problem is most likely going to show up in that case.
-  Implemented custom memory allocator that uses memory pools scheme using the following [article](https://arxiv.org/pdf/2210.16471). This highly reduces memory fragmentation on the heap. This is mainly used at the moment to store the components.
-  Implemented object pools in order to spawn bullets and asteroids from them. This prevents allocation on the heap for the mentioned entities at runtime which results in a far better performance. An object pool for each entity is allocated before the start of the game loop.
-  Implemented a relatively smooth movement system for player to move the ship around with just holding left mouse button. The acceleration is determined by how far the custom mouse in the screen is from the ship. It accelerates towards it and deccelerates when it gets closer to it.
-  Implemented an input system that wraps over SDL3 events, tailored to our needs.

  
