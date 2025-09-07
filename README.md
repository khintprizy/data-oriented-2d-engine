# data-oriented-2d-engine
Lightweight, Data Oriented 2D Engine (C++/OpenGL). Engine structure and gameloop implemented with DOD principles.

Features
- **Data Oriented Core** – Structure of Arrays (SoA) layout, tight loops
- **ECS-lite** – Entity IDs with component pools for direct indexing

- **Rendering** - Sprite batching for thousands of sprites in a single draw call
- **Input** – Keyboard & mouse state buffering
- **Memory** – Custom allocators (free-list)
- **Platform Layer** – Windows (Visual Studio 2022), OpenGL backend
