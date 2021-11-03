# another_wolfenstein_clone
A Wolfenstein3D-esque raycaster "game" coded in C using minilibx

## Setup

**This will only compile on a Linux system with X11**

Compile the binary using the Makefile, then launch the game using a mapfile, like so :
```
make
./awc maps/example.awc
```
Mapfiles have their own detailed explanation located in `maps/README`.
The gist of it is, there are 3 separate files you need for a level: its sprite config, its texture config (for walls), and the actual mapfile. 

Think of sprite configs and texture configs as "skins" for your sprites and wall textures; they contain paths to the textures they should load, as well as animations and object types.
Mapfiles on the other hand contain information like screen resolution and the actual map layout.

Controls:
- Move - WASD
- Look left/right - Q / E
- Look up/down - UpKey / DownKey
- Sprint - LeftShift
- Mace - O
- Fireball - P
- Minimap (toggle on/off) - M
- Exit - Escape

## Build your own game! (Kinda)

Another Wolfenstein Clone (AWC) is my first game project. Originally meant as a homework assignment (Cub3D, from 42) this project was supposed to replicate a raycasting graphical engine to display walls, plain floors and ceilings, as well as some sprites. This was meant as an introduction to graphical projects.
After a few months of having fun with it, this is the result. AWC is a build-your-own game, meaning you can easily make maps from the ground up, create sprites and enemies, animate them, and place them around your own levels.

However, it kind of sucks! I'm very new to this, and what this project turned into has almost nothing to do with the original project. As such, the limitations of the original project impact AWC's current form, and I'm way too lazy to fix it. To understand why this is something you might have fun with, but not invest hours in, read the "Self Critique" section below.

## Game Features

AWC features a really basic graphical engine, as well as some very basic gameplay elements...:

- Raycaster ("2.5D" Graphics) Engine
- Skybox
- Displaying animated sprites
- Distance-based shadows on textures and sprites
- Viewbobbing
- Basic UI
- Minimap
- Items to interact with (collectibles, destructibles, portals, potions...)
- Use a mace and shoot fireballs!
- Fight enemies and lose health when you're hit
- Sprint, look up and down
- And more?

Here's what AWC doesn't feature (yet?), however...
- Menus
- Any kind of reliable sound system
- Deathstates and Winstates
- Any kind of door, switch or puzzle that could serve as an obstacle
- An actual level editor would also be nice
- Other game things

## Disclaimer

I ripped a bunch of assets from games like Hexen and Doom to use as placeholder textures. This means none of the assets in `assets/` belong to me, they all belong to their respective creators.
I also probably won't update or fix this game. If it's broken or doesn't compile on your machine, tough luck!

## Self Critique

AWC is my very first video game project, which was mostly built from an originally unassuming homework assignment, and went far beyond its scope.
As such, I am quite proud of what I have made. It's janky, severely lacking in many aspects, but I never thought I could build a project even remotely this big.
My assignment states this took me about 6 months to hand in. Of those 6 months, 1 was spent on other projects, and about 1.5 were spent on the original project, which I almost entirely rebuilt. All in all, this took me anywhere between 3 and 4 months to complete. I think that's an okay time to build a game engine and a whole parsing system for people to easily (ish) make their own levels and designs, especially since I had 0 experience with this sort of stuff before now.

However this lack of experience really shows. Here's what's wrong with AWC:
- Bloated code. I did a very bad job at breaking up my header files (as in I didn't do it at all), and my data structures are very arbitrary, long-winded and difficult to understand.
- Functions are not annotated, making most of them a nightmare to understand
- Using various linked lists to store and deal with sprites, events and mobs instead of having a single entity list or something. I'm not sure how bad this is but it does make everything really confusing as you need to keep consistency between a mob and its sprite for example.
- Weird error handling, some functions return various error codes that must be handled differently and returned higher up the chain of functions, leading to chains of error returns and arbitrary error writes. Exitting the program isn't done in a pretty way if an error happens during the parsing section.
- Convoluted parsing. Good luck understanding it. To be fair I was limited by our school's C norm, and most functions were forbidden, but it's still a hot mess. This all results in the mapfile/sprite config/texture config mess that should either be built in, or all in the same file.
- Convoluted parse errors. They're precise enough to tell you in which section an error occurred, but not precise enough to tell you on which exact item it occurred. Makes debugging a bad texture path or whatever an actual nightmare.
- Only supports individual image assets, does not support spritesheets at all. Also any asset must have a size of 2^x. 
- Extremely unoptimized. Minilibx is more of a training wheel lib, and writing pixels directly to your CPU is terrible in terms of performances. Not only this, but I genuinely don't know how to further optimize the display of textures and sprites. Every pixel takes many operations to calculate, slowing down the game to a strained slog. A low resolution and compiling with optimization flags is the only way to make the game playable.
- No Multithreading
- Bad distance and Z-axis display. I don't know how to fix this bug, but items that are meant to be on the ground or on the ceiling will float at the wrong height depending on your distance between them, and some other factors like an item's modified size.
- Generally lacking in the gameplay department. No obstacles except enemies, virtually no enemy variety, weak gameplay loop, choppy controls, no deathstate or winstate, no menu, no sound...
- Lacking in direction, focus and vision. Features are kind of slapped on top of the base engine with no real care, most were improvised in a day or two, and it shows.

There's probably a lot more that's wrong with this, but to my untrained eye this is most of what I can see. Despite how janky and roughed up this is, I'm still extremely proud of it. I've learned so much through this project, and I want to keep learning more.
Thanks for reading through all this, hopefully you'll have 5 minutes of fun with this before leaving it where you found it. If you're an aspiring gamedev, maybe you can leard a few do's and don't's from this.
