# Water Engine
The goal of this project is to create a small mesh/material viewer that also includes realistically rendered water. This engine is implemented using [physically based rendering](https://en.wikipedia.org/wiki/Physically_based_rendering) and IBL. 
Meshes and/or materials will be viewable above an ocean-like plane with waves simulated using FFT, in addition to IBL and ray-traced reflections of the viewed mesh.

Additionally, I'm looking to add rendering techniques like:
- Parallax occlusion mapping & self-shadowing
- Shadow mapping
- DLSS/DLAA
- Anything else that's often found in modern engines

It will be built off of the water shading logic I wrote [here](https://www.poshbrolly.net/shader/l0Ty1LFCvmCia8MqWn7C), but improved.

The overall goal is to learn as much as possible. lesgo

# Showcase
![stones](./showcase/stones.png)
![overhead_bump](./showcase/overhead_bump.png)
