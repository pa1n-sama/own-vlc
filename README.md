# VFW - VLC From Wish

Welcome to **VFW (VLC From Wish)**! This app is your slightly janky, less polished cousin of that orange-cone player everyone loves. Built with C++ and Qt, this player kind of works most of the time and might leave you entertained (hopefully).

## What It Can Do (Mostly)

- Plays videos... when it's in a good mood.
- Opens directories as playlists so you can “accidentally” binge-watch everything.
- Fullscreen support, because windowed mode is for the weak.
- Seek slider to skip to the parts you actually care about.
- A few keyboard shortcuts, because we’re trying to look professional.

## Requirements

- **Qt Framework** (5.15+ recommended – newer means fewer headaches).
- A C++17 compatible compiler.

## How to Build (Best of Luck)

1. Clone the repository:
   ```bash
   git clone https://github.com/pa1n-sama/VFW
   cd VFW/main
   ```
2. run the run.sh script:
   ```bash
   bash run.sh
   ```
3. Run the application:
   ```bash
   cd build
   ./VFW
   ```

## Usage Guide

- **Open File**: Click to load a single video. Simple enough.
- **Open Playlist**: Load an entire directory as a playlist for uninterrupted viewing.
- **Controls**:
  - **Play/Pause**: Click the button or press `Space`.
  - **Stop**: Stops playback. You can always start again.
  - **Fullscreen**: Press `F` to enter fullscreen mode.
  - **Seek**: Drag the slider or use arrow keys to skip sections.

## Keyboard Shortcuts

- `Space`: Play/Pause
- `F`: Toggle Fullscreen
- `Esc`: Exit Fullscreen
- `Right Arrow (→)`: Fast Forward
- `Left Arrow (←)`: Rewind
- `Up/Down Arrows`: Adjust Volume

---

Use VFW at your own risk. It's functional, mostly, and any quirks are part of its charm.
