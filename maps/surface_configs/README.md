# Surface Config

## Textures
```
#SPRITE TEXTURES
TEXTURES	4
{
# TXNBR	PATH
  1	./assets/surfaces/greybrick_1.xpm
  2	./assets/surfaces/greybrick_2.xpm
  3	./assets/surfaces/greybrick_3.xpm
  4	./assets/surfaces/greybrick_4.xpm
}
```
The path to every surface texture used in this config.
This requires the correct number of textures to be specified after TEXTURES.
Each texture needs a number, which serves as an index for future reference. Each number is then associated to an xpm file that will be loaded when the file is parsed.
Each file needs to be a .xpm, and the image's width and height must me a multiple of 2 for it to work properly.
Each path is a relative path from the root of the project.

Important to note: Each texture here is automatically assigned to an alphanumerical character, to then be used in a .cub file as either a wall, a ceiling or a floor texture
The order of assignment is as follows: '0' to '9', 'a' to 'z' (lowercase), then 'A' to 'Z' (uppercase).
This means that specifying 15 textures will assign them to '0123456789abcde'.
Any alphanumeric character that is 'above' the limit that used in a .cub file will use the first texture as a fallback.

## Skybox
```
#SKYBOX
#   PATH

SB  ./assets/skybox/sky_red.xpm
```
The skybox to use for this config.
PATH: A relative path from the root of the project to the .xpm image to be used for the skybox. 

## Animations

```
#SURFACE ANIM
ANIMATION
{
# FRAME1	FRAME2	DELAY (IN SECONDS)
  1		2		0.5
  2		1		0.5
}
```
Surface animations
Here you can manually define animations for your surface textures
Simply specify from which frame to which frame to animate, and after what delay.
You can create looping animations by having the last frame lead to the first one (like the fireball example above), or have it end by specifying 'END' as an argument for FRAME2
