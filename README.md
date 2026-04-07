# Orbital Simulation (WIP)

A C++ and SFML physics engine that simulates N-body gravity within a discrete grid environment, bridging the gap between continuous orbital mechanics and cellular automata.

---

## Features

**Physics Engine:**
- **N-Body Gravity:** Real-time gravitational attraction between all particles.
- **Grid-Based Movement:** Floating-point physics translated to a grid via Bresenham's algorithm.
- **Collision Logic:** Occupancy checks with a "jiggle" mechanic for organic stacking.

**Interaction:**
- **Drawing Mode:** Manual placement of "Rock" particles.
- **Velocity Mode:** Slingshot mechanic to launch particles with custom vectors.
- **Visuals:** Speed-based dynamic color shifting.

---

## Controls
- **1 / 2:** Toggle Drawing vs. Velocity modes.
- **Left Click:** Place particles or drag to set velocity.
- **Mouse Wheel:** Adjust brush size.

---

## Tech Stack
- **Language:** C++20
- **Graphics:** SFML
- **Build System:** CMake

---

## How to Run
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
