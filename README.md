# 🎡 Mini Park – OpenGL Computer Graphics Project

A 3D interactive Mini Park built using OpenGL, showcasing advanced computer-graphics concepts such as lighting, texture mapping, Bezier curves, and animated objects.
This project was developed as part of the CSE 4208 – Computer Graphics Laboratory course at Khulna University of Engineering & Technology (KUET).
## DEMO 

## 📌 Project Overview

- The Mini Park displays a lively virtual environment containing:
- A circular ride
- A sky-drive ride
- Play house with animated doors
- Haunted house with rotating doors
- Rotating entry gate
- Curved chairs, benches, table
- Bezier-curve-based tree model
- Dynamic movable objects
- Texture-mapped surfaces and objects
- Interactive light toggling (ambient, diffuse, specular)
- The project integrates multiple 3D geometric shapes (cube, sphere, cone, cylinder, Bezier curves) and uses shaders for realistic rendering.

## 🛠️ Technologies Used
- C++
- OpenGL
- GLFW / GLUT
- GLM (matrix transformations)
- Shader Programs
- Textures (Diffuse, Specular)
- VAO, VBO, EBO for efficient GPU data management

## 🔧 Key Features
### 🌆 Environment Components
- Entry gate with rotating animation
- Play house with auto-opening door
- Haunted house with rotating door
- Textured ground, walls, and decorative objects
- Curved chairs, table, sky-drive ride
- Bezier-curve-generated tree

### 💡 Lighting System
- Ambient, diffuse, and specular lighting
- Point light toggling (on/off) 
- Material shininess control
- Shader-handled lighting calculations

### 🎨 Rendering System
#### Modular functions:
- drawCubeWithTexture()
- drawSphereWithTexture()
- drawCylinderWithTexture()
- drawBezierCurveWithTexture()
- Reusable material + texture setup
- Smooth animations using timers

### 🌀 Animation
- Circular ride movement
- Sky-drive motion
- Door open/close animations
- Rotating textured sphere
- Movable objects (user-controlled or dynamic)
