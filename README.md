# heck.exe
Fully featured CS:GO external cheat.

# Disclaimer
That was my first C++ project.

As of publication signatures are probably outdated.

No ESP.

# Features
## Aim:
* Aimbot:
  - Enable
  - VKey
  - Team check
  - Auto fire
  - Hitscan:
    - Enable
    - Priority (1 - most dmg, 2 - closest)
    - Head
    - Body
    - Shoulders
    - Legs
    - Toes
  - Pseudo auto wall
  
  - Rage:
    - Enable
    - Prioritize bone
    - FOV
    - Auto scope
    - Body aim with AWP
    - Silent aim
    - Hit chance:
      - Enable
      - Pistols %
      - SMGs %
      - Rifles %
      - Machineguns %
      - Shotguns %
      - Auto-snipers %
      - SSG08 %
      - AWP  %
      
  - Weapon category settings:
    - Prioritize bone
    - Scale FOV by distance
    - FOV
    - Speed
    - Ignore enemies in air
    - Disable when flashed
    - Silent aim

* RCS:
  - Enable
  - Always on
  - Vertical %
  - Horizontal %

* Triggerbot:
  - Enable
  - VKey
  - Disable when flashed

* Auto pistol
* Backtrack:
  - Enable
  - Max [1-12]

## Visuals:
* Team check
* Glow ESP:
  - Players
  - Style (0 - outside, 1 - silhouette, 2 - inside)
  - Patch flicker
  - Color
  - Color health based
    - Color 0 hp
    - Color 100 hp
  - Show vunerable 
  - Vunerable color
  - Dropped C4
  - Grenades

* Model tone:
  - Enable
  - Color

* Show enemies on radar
* Update delay (ms)

## Misc:
* Auto jump:
  - Enable
  - Legit looking

* Fake lag:
  - Enable
  - Toggle VKey (0 - no key)
  - Ticks lag
  - Ticks pass
  - Disable when shooting
  - Only in air
  
* Hitsound:
  - Enable
  - Style 
  - Volume %
  
* Nightmode:
  - Enable
  - Lightscale
  
* Skybox name
* Enable "name" command
* Auto accept
* Reveal ranks
* Disable post-processing
* No smoke
* No sniper scope
* Visual no recoil (1 - no punch, 2 - no recoil)
* Max flash %
* Viewmodel FOV
* View FOV
* Load next config vkey
* Insult vkey
* Bot mount vkey

# Compile
You can compile with or without "say insult" feature. 

To compile with it you'll need a libcurl. 
Compile libcurl, fix library include paths, select "Release" configuration and compile a cheat.

Otherwise simply select "Release (no curl)" configuration and compile.

# Usage
* Edit the config to enable/disable features (0 - off, 1 - on)
* Start the cheat

Config parsing depends on the order of lines (e.g. 1st setting must be "aimbot enable").

You'll most likely get "Warning: MapVirtualKey returned 0" if you break the order of settings.

# Credits
* nuggah for external UserCmd manipulation
* Forza for signature finder
* ReactiioN for hitbox enum
* keybode for bsp parser
