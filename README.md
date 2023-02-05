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

## Sort of a game!

Another Wolfenstein Clone (AWC) is my first "game" project. Originally meant as a homework assignment (Cub3D, from 42) this project was supposed to replicate a raycasting graphical engine to display walls, plain floors and ceilings, as well as some sprites. This was meant as an introduction to graphical projects.
After a few months of having fun with it, this is the result. AWC is a very customizable game, you can easily make maps from the ground up, create sprites and enemies, animate them, and place them around your own levels.

However, it kind of sucks! I'm very new to this, and what this project turned into has almost nothing to do with the original project. As such, the limitations of the original project impact AWC's current form. Fixing these limitations would take time and effort that would be better spent on learning how to make games that don't suck, so I'll do that instead.

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
