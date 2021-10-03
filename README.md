# Project 1

## About

### Task 1
- Bubbles agents
- Spawn in randomly within the viewport with random velocity

### Task 2
- Forces were added using simple kinematics
- If agents were too far, then an acceleration would be added toward that direction
- Vice versa if agents were too close
- Forces takes into account all agents, not just nearby ones

### Task 3
- Clouds are obstacles
- Spawned randomly within the viewport
- If a bubble hits a cloud, it will bounce in the opposite direction

### Task 4
- Birb is the player
- Bubbles pass through the player
- If bubbles come close, they expand due to the heat of the birb and thermodynamics

### Task 5
- Gameplay can be found in the `gameplay.mp4` file

### Perlin Noise
- Perlin noise is used to generate the backdrop
- Backdrop is supposed to be clouds
- See more in [Background Generation](#background-generation)

## Building
```
mkdir build && cd build && cmake ..
```

## Running
```
make -C build/ && ./build/PA01 ./levels/level004.txt
```

## Background Generation

### Dependencies
```
pip3 install numpy noise Pillow
```

### Running
```
python3 generate_background.py
```
This will generate `imgs/backdrop4.jpg` using Perlin noise.

## Contributors

- Tori Broadnax
- Jeffrey Do
- Richard Roberts
- Minh Vu
