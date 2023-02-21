# Sprite Config

## Textures

```
#SPRITE TEXTURES
TEXTURES	6

{
# TXNBR PATH
  1     ./assets/sprites/decorations/pot_small.xpm
  2     ./assets/sprites/decorations/pot_med.xpm
  3     ./assets/sprites/decorations/pot_tall.xpm

# PROJECTILE GREEN FIREBALL
  4     ./assets/projectiles/green_fireball/green_fireball_1.xpm
  5     ./assets/projectiles/green_fireball/green_fireball_2.xpm
  6     ./assets/projectiles/green_fireball/green_fireball_3.xpm
}
```
The path to every sprite texture used in this config.

This requires the correct number of textures to be specified after TEXTURES.

Each texture needs a number, which serves as an index for future reference. Each number is then associated to an xpm file that will be loaded when the file is parsed.

Each file needs to be a .xpm, and the image's width and height must me a multiple of 2 for it to work properly.

## Player Projectile

```
#PLAYER PROJECTILE          TEXNBR
PLAYER_PROJECTILE           4

PLAYER_PROJECTILE_EXPLOSION 7
```
Player projectile specification.

This is more of a remnant of an earlier version of the project than an actual feature. Oops!

Define which sprites to use as a player projectile, and that projectile's explosion. See below for animations.

## Animations

```
#SPRITE ANIMATION
ANIMATION

{
# FRAME1  FRAME2  DELAY (IN SECONDS)

#PROJECTILE GREEN FIREBALL
  4       5       0.075
  5       6       0.075
  6       4       0.075

#MOB DEMON ATTACK
  20      21      0.2
  22      23      0.2
  24      END     0.4
}
```
Sprite animations

Here you can manually define animations for your sprites

Simply specify from which frame to which frame to animate, and after what delay.

You can create looping animations by having the last frame lead to the first one (like the fireball example above), or have it end by specifying 'END' as an argument for FRAME2

## Sprite Types

```
#SPRITE TYPES
INFO	4

{
# TYPENBR TXNBR POSZ  H_DIV W_DIV COLLISION TYPE
# POTS (SMALL - MED - TALL)
  1       1     DOWN  1     1     Y         REMOVEABLE
  2       2     DOWN  1     1     Y         REMOVEABLE
  3       3     DOWN  1     1     Y         REMOVEABLE

#MOBS
# DEMON
  4       20    MID   1     1     Y         NONE
}
```
Define each type of sprites for this config.

This requires the correct number of sprite types to be specified after INFO.

TYPENBR: The assigned number or "index" for this type of sprite

TXNBR: The texture index to be used to render this sprite

POSZ: The vertical position of this sprite. Accepted arguments are: "UP", "DOWN' and "MID"

H_DIV: Factor/Ration to divide the sprite's screenheight with. a value of "2" means the sprite will be half as tall

W_DIV: Same as H_DIV, but for the sprite's width.

COLLISION: Whether the player can collide with the sprite or not. Accepted arguments are: "Y", "N"

TYPE: The sprite's type. Accepted arguments are:
  - NONE - does nothing
  - REMOVEABLE - Will disappear after a hit
  - COLLECTIBLE - Will disappear after it is walked over by the player
  - TELEPORT - Marks the sprite as a teleporter (Pretty sure this doesn't do anything anymore)
  - HEAL_1: Heals 1 heart when walked over
  - GOAL: Marks the sprite as a goal

## Monsters
```
#MOB_INFO
MOB	2
{
# TYPENBR SPTYPE  WALK  ATTACK  PROJ  EXPL  HURT  DEATH AI
  1       25      113   114     80    83    117   119   TURRET
  2       26      129   126     80    83    133   134   FIGHTER
}
```
Defines each type of monster

This requires the correct number of monster types to be specified after MOB.

TYPENBR: The assigned number or "index" for this type of monster

SPTYPE: The sprite index to be used for this type of monster (this will be their idle animation as well)

WALK: The texture index to be displayed when the monster is walking

ATTACK: The texture index to be displayed when the monster is attacking

PROJ: The texture index to be displayed for a monster's projectile

EXPL: The texture index to be displayed for a monster's projectile's explosion

HURT: The texture index to be displayed when a monster is hurt by a player attack

DEATH: The texture index to be displayed when a monster dies. You can leave their corpse on the ground by having their animation not loop.

AI: The monster's AI. Accepted arguemtns are: "TURRET" (does not move and uses projectiles) or "FIGHTER" (moves and only attacks in melee)
