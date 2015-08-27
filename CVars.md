# Game #
```
g_playerspeed
```
# CGame #
## Weapon Loadouts ##
Values are the weapon IDs
```
cg_primary
cg_secondary (unused)
cg_pistol
cg_grenade
cg_misc
```
## Lagometer ##
```
cg_lagometerX
cg_lagometerY
```
Changes lagometer position
## Killfeed ##
```
cg_killfeed
cg_killfeedTime
cg_killfeedHeight
```
Controls the display of the killfeed and the time messages are displayed (in seconds).
Height sets the maximum lines displayed, from 1 to 32.

0: No killfeed, shows default death messages in the chat area.

1: Killfeed with images

2: Show only kills/deaths

3: Show kills/deaths with weapon/type
## Zooming ##
```
cg_zoomreset
cg_scopeType
```
Reset zoom on firing (only affects Barrett and Intervention) [working](not.md)

0: Default zooming

1: Experimental zooming with second refdef in view, buggy
## Misc ##
```
cg_temperatureUnit
```
Changes the unit shown on map loading, C, F and K are possible, default C
```
cg_showLegs
```
Experimental feature, 1 to enable, default 0

# UI #

# Renderer #
```
r_farclipFactor
```
minimum 1, default 2. Increases view distance, important for nuke