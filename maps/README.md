# Map Files

You can read the few availables .cub file to get an idea how everything works.

Here are some details about every section of these map files:

## Sprite and Surface Config

```
#SPRITE TEX & INFO & ANIMATION
#	PATH
SP_CONFIG	./maps/sprite_configs/final.spconfig

#SURFACE TEX & INFO & ANIMATION
#	PATH
SF_CONFIG	./maps/surface_configs/final.sfconfig
```

Sprite and Surface configs (SP_CONFIG and SF_CONFIG respectively) reference special files used to detail information about wall textures, sprite textures, as well as animations, sprite types, and mob types. See the sprite_config and surface_config folders for more information.

PATH: takes a path relative to the project's root.
These two settings need to be first in a .cub file

## Resolution

```
#RESOLUTION
#	X		Y
R	960		480
```
The generated window's resolution.

X: the window's width in pixels
Y: the window's height in pixels

Note: Some things don't display properly with a very small window, and the game runs very poorly with a big window

## Minimap

```
#MINIMAP INFO
#		RATIO_X	RATIO_Y	TILESIZE	WALL_COLOR		FLOOR_COLOR		PLAYER_COLOR
MINI	5		5		12			184,240,195		31,50,58		255,255,255
```
The minimap's settings

RATIO_X: The ratio of the total window screen the minimap should use for its width. Here, "5" means the minimap's width will be 1/5th of the screen's width
RATIO_Y: Same as above, but for height
TILESIZE: Number of tiles (see maps below) to be displayed around the player in the minimap
WALL_COLOR, FLOOR_COLOR and PLAYER_COLOR: RGB color arguments. Use a `xyz,xyz,xyz` format

## Sprites, Teleporters and Monsters

# For Sprites (SP), Teleportations (TP) and Monsters (MOB)
# The TYPE argument refers to a predefined sprite or monster type index
# As defined in the linked sprite config file (.spconfig)

```
#SPRITE POS
SP

{
#	TYPE	POSX	POSY
  1      5.5  5.5
}

TP

{
#	TYPE	POSX	POSY	TPOSX	TPOSY
  2     6.5   6.5   7.5   7.5
}

MOB
{
#	TYPE	POSX	POSY
  1     8.5   8.5
}
```
The position of every sprite, teleporter and monster.

Each setting requires brackets, and can receive any number of valid argument lines
For each line:
TYPE: This refers to a predefined sprite or montster type index, as defined in the linked sprite config file (.spconfig)
POSX, POSY: the sprite/teleporter/monster's starting position in the map
TPOSX, TPOSY: (Teleporters only) The coodinates to be teleported to.

## Next level

```
# NEXT LEVEL
#       PATH
NEXT	NONE
```
Which level to load when reaching a "goal" in the current map
PATH: either 'NONE', indicating there is no next level, or a path to a valid .cub file that will be loaded once a goal is reach.

This requires the sprite config (spconfig) to have declared a sprite of type "GOAL".

## Wall Map
```
#PLAYER & WALL MAP
#	LINENBR
MAP 3

{
111111111111111111111111111111
100000000000000N00000000000001
111111111111111111111111111111
}
```
The wall map for this level
'0' characters represent empty, walkable spaces
' ' represent empty, non-walkable spaces
The player's initial orientation is defined by one of the following characters : 'N' for North, 'E' for East, 'S' for South, 'W' for West
A wall is represented by any alphanumeric character that is not any of the following: '0', 'N', 'E', 'S', 'W'
Each alphanumeric character representing a wall has a different texture attached to it, granted that enough textures were provided in the surface config file (.sfconfig). See the surface_configs folder for more information

A valid wall map requires the following:
  -It must be closed off. This means every walkable space (0) must not be directly adjacent to an empty, non-walkable space (' ')
  -It must specify where the player character is starting, using one of 'NESW' as explained above. This follows the same rules as walkable spaces.
  -The LINENBR argument must specify how many rows of lines are present in the wall map

## Floor and Ceiling Maps

```
#FLOOR MAP
MAPF

{
111111111111111111111111111
111111111111111111111111111
111111111111111111111111111
}

#CEILING MAP
MAPC

{
111111111111111111111111111
111111111111111111111111111
111111111111111111111111111
}
```
The floor and ceiling maps for the current level.
This specifies only which textures to display for which tile, either on the floor or the ceiling.
Each of these maps requires the same number of lines as the wall map. The lines must not be any longer than their corresponding line in the wall map.
However, they do not have to match the length either.

For floor maps:
  - Any alphanumeric character can be used and will refer to a different texture, assuming there are enough textures set in the surface_config file.
For ceiling maps:
  - Any alphanumeric character can be used and will refer to a different texture, assuming there are enough textures set in the surface_config file.
  - An empty space displays the skybox instead of a texture. As such, fully empty lines in a ceiling map shall display no ceilings, and will instead display a full skybox, like so:
```
#CEILING MAP
MAPC

{



}
```
