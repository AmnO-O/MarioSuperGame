# MarioSuperGame

## Overview

MarioSuperGame is a 2D platformer inspired by classic Super Mario titles. Implemented in **C++** using the **raylib** library, the game demonstrates core platformer mechanics: side-scrolling, jumping, coin collection, enemies, and level interaction through blocks, power-ups, and hazards. It is designed as an educational project and a starting point for hobbyist game development, emphasizing clean object-oriented design and modularity.

Here is our demo video: [link]{https://www.youtube.com/watch?v=LbuX6IFkD8g}


## Features

* **Classic Platformer Mechanics** — running, jumping, crouch (if implemented), collisions with blocks and enemies.
* **Level Design** — support for tiled maps with different block types: floors, bridges, lifts, breakable blocks, question blocks, spikes, and hazards like fire or sewers.
* **Enemy Types** — basic enemy AI (patrol, chase, simple gravity interaction) and defeat mechanics (stomp, power-up hit).
* **Collectibles & Power-ups** — coins, 1-Up, mushroom-like power-up, temporary invulnerability.
* **Animations & Transitions** — frame-based sprite animations, smooth transitions between scenes, and particle effects for jump/coin/power-up events.
* **Scoreboard** — persistent high scores stored in a text file (e.g., `scores.txt`) and displayed on the title/score screen.
* **Assets Management** — organized folders for sprites, fonts, maps, and sounds.
* **Modular Codebase** — separate headers & source files for Player, Enemy, Block, Map, AudioManager, UI, etc., to make extension easy.

---

## Project Structure (Suggested)

```
MarioSuperGame/
├─ assets/
│  ├─ sprites/
│  ├─ maps/
│  ├─ sounds/
│  └─ fonts/
│
├─ include/
│  ├─ Animation/
│  │  ├─ Animation.h
│  │  ├─ Appearance.h
│  │  ├─ LerpMover.h
│  │  └─ TransitionScene.h
│  │
│  ├─ Blocks/
│  │  ├─ Block.h
│  │  ├─ Brick.h
│  │  ├─ Bridge.h
│  │  ├─ Coin.h
│  │  ├─ Fire.h
│  │  ├─ Flag.h
│  │  ├─ Floor.h
│  │  ├─ Invisible.h
│  │  ├─ Lift.h
│  │  ├─ Question.h
│  │  └─ Sewer.h
│  │
│  ├─ Character/
│  │  ├─ Character.h
│  │  ├─ CharacterState.h
│  │  ├─ Global.h
│  │  ├─ PlayerAction.h
│  │  └─ PlayerMovement.h
│  │
│  ├─ Enemy/
│  │  ├─ Blaze.h
│  │  ├─ Bowser.h
│  │  ├─ Enemy.h
│  │  ├─ EnemyFactory.h
│  │  ├─ Goomba.h
│  │  ├─ Koopa.h
│  │  ├─ ParaKoopa.h
│  │  └─ Piranha.h
│  │
│  ├─ Object/
│  │  ├─ Fireball.h
│  │  ├─ FireballManager.h
│  │  ├─ GameObject.h
│  │  └─ PowerUp.h
│  │
│  ├─ Observer/
│  │  ├─ ICollidable.h
│  │  └─ Observer.h
│  │
│  ├─ Resources/
│  │  ├─ Map.h
│  │  ├─ ResourceManager.h
│  │  ├─ SoundManager.h
│  │  ├─ StateManager.h
│  │  ├─ StatsManager.h
│  │  └─ Timer.h
│  │
│  ├─ States/
│  │  ├─ AboutMenu.h
│  │  ├─ EndResult.h
│  │  ├─ GameOverMenu.h
│  │  ├─ LevelMenu.h
│  │  ├─ MainMenu.h
│  │  ├─ NameInputPopUp.h
│  │  ├─ ScoreBoard.h
│  │  ├─ SettingsMenu.h
│  │  ├─ SubMenu.h
│  │  └─ World.h
│  │
│  ├─ Widgets/
│  │  ├─ Button.h
│  │  ├─ PopUpMenu.h
│  │  └─ VolumeSlider.h
│  │
│  ├─ Exceptions.h
│  ├─ Game.h
│  ├─ MyCamera2D.h
│  └─ tinyfiledialogs.h
│
├─ src/
│  ├─ Animation/
│  │  ├─ Animation.cpp
│  │  ├─ Appearance.cpp
│  │  ├─ LerpMover.cpp
│  │  └─ TransitionScene.cpp
│  │
│  ├─ Blocks/
│  │  ├─ Block.cpp
│  │  ├─ Brick.cpp
│  │  ├─ Bridge.cpp
│  │  ├─ Coin.cpp
│  │  ├─ Fire.cpp
│  │  ├─ Flag.cpp
│  │  ├─ Floor.cpp
│  │  ├─ Invisible.cpp
│  │  ├─ Lift.cpp
│  │  ├─ Question.cpp
│  │  └─ Sewer.cpp
│  │
│  ├─ Character/
│  │  ├─ Character.cpp
│  │  ├─ CharacterState.cpp
│  │  ├─ Global.cpp
│  │  ├─ PlayerAction.cpp
│  │  └─ PlayerMovement.cpp
│  │
│  ├─ Enemy/
│  │  ├─ Blaze.cpp
│  │  ├─ Bowser.cpp
│  │  ├─ Enemy.cpp
│  │  ├─ EnemyFactory.cpp
│  │  ├─ Goomba.cpp
│  │  ├─ Koopa.cpp
│  │  ├─ ParaKoopa.cpp
│  │  └─ Piranha.cpp
│  │
│  ├─ Object/
│  │  ├─ Fireball.cpp
│  │  ├─ FireballManager.cpp
│  │  ├─ GameObject.cpp
│  │  └─ PowerUp.cpp
│  │
│  ├─ Observer/
│  │  ├─ ICollidable.cpp
│  │  └─ Observer.cpp
│  │
│  ├─ Resources/
│  │  ├─ Map.cpp
│  │  ├─ ResourceManager.cpp
│  │  ├─ SoundManager.cpp
│  │  ├─ StateManager.cpp
│  │  ├─ StatsManager.cpp
│  │  └─ Timer.cpp
│  │
│  ├─ States/
│  │  ├─ AboutMenu.cpp
│  │  ├─ EndResult.cpp
│  │  ├─ GameOverMenu.cpp
│  │  ├─ LevelMenu.cpp
│  │  ├─ MainMenu.cpp
│  │  ├─ NameInputPopUp.cpp
│  │  ├─ ScoreBoard.cpp
│  │  ├─ SettingsMenu.cpp
│  │  ├─ SubMenu.cpp
│  │  └─ World.cpp
│  │
│  ├─ Widgets/
│  │  ├─ Button.cpp
│  │  ├─ PopUpMenu.cpp
│  │  └─ VolumeSlider.cpp
│  │
│  ├─ Exceptions.cpp
│  ├─ Game.cpp
│  ├─ MyCamera2D.cpp
│  └─ tinyfiledialogs.c
│
├─ build/
├─ main.cpp
├─ CMakeLists.txt
├─ README.md
└─ scores.txt


```

---

## Dependencies

* **raylib** (2.0+) — for graphics, input, audio. Install from: [https://www.raylib.com](https://www.raylib.com) (or your package manager).
* **C++17** (recommended) or later
* A C++ compiler (g++, clang, MSVC)
* Optional tools: `cmake` or `make` for cross-platform builds

---

## Build & Run

### Using CMake (recommended)

```bash
# Create build dir
mkdir -p build && cd build
cmake ..
cmake --build .
# Run
./MarioSuperGame
```

> If raylib is installed in a custom path, set `CMAKE_PREFIX_PATH` or provide `-Draylib_DIR=/path/to/raylib`.

### Quick compile with g++ (Linux/macOS)

```bash
g++ -std=c++17 src/*.cpp -Iinclude -lraylib -lGL -lm -lpthread -ldl -o MarioSuperGame
./MarioSuperGame
```

### Windows (MSYS2 / MinGW)

```bash
g++ -std=c++17 src/*.cpp -Iinclude -L/mingw64/lib -lraylib -lopengl32 -lgdi32 -o MarioSuperGame.exe
MarioSuperGame.exe
```

*Adjust libraries/flags depending on your raylib build*.

---

## Key Design Notes

* **Map format**: Use a simple tiled format (CSV or JSON). A `Map` loader converts tiles to in-game `Block` objects.
* **Collision**: Use AABB for player-block and enemy-block collisions. Separate vertical/horizontal resolution for stable platformer physics.
* **State Machine (Player)**: Idle, Run, Jump, Fall, Hurt, Dead, PowerUp — use an enum and switch updates.
* **Animation**: Frame index with timer per animation state, texturesheets (spritesheets) with `DrawTextureRec`.
* **Audio**: Centralize in `AudioManager` to control music, SFX, and volume.
* **Persistent Scores**: Simple read/write `scores.txt` on game start/end. Keep format human-readable: `name score date`.

---

## Controls (Default)

* **Left / Right**: Arrow keys or A / D
* **Jump**: Space or W
* **Run / Dash**: Left Shift
* **Pause / Menu**: Esc

Customize in `input` manager if needed.

---

## TODO / Roadmap

* Add more enemy types and improved AI
* Level editor integration / export map format
* Save/Load player progress
* Networked co-op (advanced)
* Polish UI and add a level-select screen

---

## License

This project is open for learning and personal use — add a license file (e.g., MIT) if you plan to share or publish.

---

## Contributing

PRs and issues are welcome. Try to keep changes modular and document any new assets or third-party tools added.


---

If you want, I can also:

* Generate a starter `CMakeLists.txt` and example `main.cpp` + minimal `Player` class.
* Produce a simple CSV map loader and tile renderer.
* Create a small level and placeholder sprites to help you prototype.

Tell me which of those you want and I will create the files for you.
