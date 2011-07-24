# About

- Building under WinXP with Visual Studio 2010 Express.
- I use a VirtualBox to keep the for compilation configured system detached from my normal system.
- Added #define PATH\_MAX 255 (HACK)
- I test Gish with the original Levels, because I want to keep the original functionality.
- LF, not CRLF.

- convert this to a fork, although I don't know if one ever wants to merge.


# Features

- g toggle godmode
- y,z zoom in and out
- f toggle framerate
- k shows keys like in tutorial (TODO: toggle)

- moved some init code out of game loop
- started to replace some magic numbers.


# Wishlist

- COMMENTS in code! Naa, I like riddles.
- gish resolution from 16 particles to 32. Depends on scattered magic nums.
- spawn objects ingame
- enlarge ai and godmode 'area' if zoomed out.
- Change physics to simulate gishs volume (unkompressable tar)
- Whole level screenshot (with a good resolution)
- make time measure real seconds
- fix sticky-spikes texture stretching. sticky-spikes should always be the same size
- make shattered blocks stay longer.
- make gish stickable only on a section (one third to a quarter or something)
  Perhaps makes funny things possible, like going up pipes.
- improve options to setup all additional keys
- measure ai, physics, video times to find out what eats performance.
- stats for userlevels
- stats with enemy kills: killed 4 of 6
- other stats for other gamemodes
  1. Don't kill enemies
  2. Kill with lava
  3. Other weird ideas.


# TODOs / BUGs

- some Gish (1.6) Levels are painfully slow at the beginning. Why?
- Arrows for keyboard cursors are not displayed. I don't get it, as A is ascii 65 and at pos 65 there is an A in the texture. So the texture matches the ascii table. The arrows (I think) are at pos 81 82 83 84 and the labels are (proved with hex editor) the chars with these values.
- movie (image) save results in damaged image files
- replace magic numbers. You just cannot understand anything.


# I don't know
- I don't know which VS2010 files have to be included.
- if git keeps the LF and does not replace it with CRLF.







