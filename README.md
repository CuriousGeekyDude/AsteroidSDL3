# AsteroidSDL3

## About
A classical 2D Asteroid game made up of 2 levels.

## Requirements
You need to have a x64 computer and a Mscvc compiler that supports C++20.

## How to build

1) Run the build-vs2022.bat. It will generate a vs2022 solution. If you want some other solution then you need to trivially edit this batch file on windows or manually run premake executable on your OS of choice.
2) Run the generated solution and compile!

## Main features
- Implemented collision system using the concept of the grid. The grid is divided into equal sized rectangles and records which entities reside in that rectangle. Only the spheres around the entities in that rectangle are tested against each other for collision. The scheme used here is inspired by tiled deferred shading method for registering point lights in tiles.
- Implemented an event management system using std::function and lambdas in order to register events such as start of animations of explosion and warp, delayed activation and deactivation of collision state of asteroids before spawning and in the middle of the explosion animation etc.
- Implemented time rewind up to 30 seconds back in time by keeping track of only the important data of each frame in a ring buffer in order to be able to reconstruct the frame again as we go back in time.
- Implemented the game using entity component architecture which makes use of composition more than inheritance. This results in a more scalable, modular, and reusable code than if we were to favour inheritance over composition. Not to mention diamond problem is most likely going to show up in that case.
-  Implemented custom memory allocator that uses memory pools which are implemented using the following [paper](https://arxiv.org/pdf/2210.16471). This highly reduces memory fragmentation on the heap. This is mainly used at the moment to store the components.
-  Implemented object pools in order to spawn bullets and asteroids from them. This prevents allocation on the heap for the mentioned entities at runtime which results in a far better performance. An object pool for each entity is allocated before the start of the game loop.
-  Implemented a relatively smooth movement system for player to move the ship around with just holding left mouse button. The acceleration is determined by how far the custom mouse in the screen is from the ship. It accelerates towards it and deccelerates when it gets closer to it.
-  Implemented a simple finite state machine for asteroids in order to change between passive and aggressive depending on the level we are in.
- Logging system to register different levels of severity and channels in both the output console of visual studio, a logging file, and the command line.
-  Implemented an input system that wraps over SDL3 events, tailored to our needs.

## How to play
- In order to rotate and move the ship one first has to capture the mouse. For that you press the key C. The usual mouse is hidden and instead the custom mouse appears and the ship points in that direction. In order to move the ship one directs the custom mouse somewhere and holds the left button of the mouse. The further away the custom mouse is from the ship the higher its acceleration is going to be.
- Ship fires bullets by hitting the key F.
- You rewind back in time by holding the key T.
- In left top you will find a small window that displays the score, health, and seconds passed since the start of the level.
- You complete the first level by making sure you survive for 75 seconds and score at least 30 hits by hitting asteroids with bullets.
- You complete the second level which is the last one by surviving for 120 seconds and scoring at least 20 hits with the bullets.
- You win the game by completing all 2 levels.

## Show casing the game
- Level 1 gameplay : [Level 1](https://www.youtube.com/watch?v=8yb8TZ3AsAY)
- Level 2 gameplay: [Level 2](https://www.youtube.com/watch?v=GDKWZfirOok)


  
