# Orbital Simulation (WIP)

A C++ and SFML physics engine that simulates N-body gravity within a discrete grid environment. This project bridges the gap between continuous orbital mechanics and cellular automata.

### Features
* **N-Body Gravity:** Real-time gravitational attraction between all particles ($O(N^2)$).
* **Grid-Based Physics:** Floating-point velocity and acceleration translated to a grid via Bresenham's algorithm.
* **Interaction Modes:**
    * **Drawing:** Place "Rock" particles directly onto the grid.
    * **Velocity (Slingshot):** Click and drag to launch particles with specific velocity vectors.
* **Collision Logic:** Basic occupancy checks with a "jiggle" mechanic to simulate organic stacking.
* **Velocity Visualization:** Dynamic color shifting based on particle speed.

### Controls
* **1 / 2:** Toggle between Drawing and Velocity modes.
* **Left Click:** Place particles or drag to set velocity.
* **Mouse Wheel:** Adjust brush size.

### Technical Stack
* **Language:** C++
* **Graphics:** SFML

### Planned Updates
* **Optimization:** Quadtree spatial partitioning to improve performance.
* **Stability:** Double-buffering the grid state for deterministic updates.
* **Architecture:** Standardizing coordinate types and improving collision response.
