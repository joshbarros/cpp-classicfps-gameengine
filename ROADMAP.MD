# Project Roadmap: Quake-like Game Development
## Phase 1: Core Engine Infrastructure

### Engine Foundation
- [x] Setup development environment
  - [x] Configure build system (CMake)
  - [x] Setup version control
  - [x] Configure unit testing framework
- [x] Implement core engine loop
  - [x] Window creation and management
  - [x] Input handling system
  - [x] Game loop timing
  - [x] Logging system

### Graphics System
- [x] OpenGL rendering system
  - [x] Shader management
  - [x] Basic texture loading
  - [x] Model loading system
- [ ] BSP rendering
  - [ ] BSP tree implementation
  - [ ] Visibility determination
  - [ ] Frustum culling
- [ ] Lighting system
  - [ ] Static lighting
  - [ ] Dynamic lights
  - [ ] Shadow mapping

## Phase 2: Game Physics and Movement

### Physics Implementation
- [ ] Collision detection
  - [ ] BSP collision
  - [ ] AABB collision
  - [ ] Ray casting
- [x] Movement system
  - [x] Quake-style player movement
  - [x] Air control
  - [x] Jumping mechanics
  - [x] Crouching
  - [ ] Sliding
- [ ] Projectile physics
  - [ ] Trajectory calculation
  - [ ] Collision response
  - [ ] Splash damage

### Map System
- [ ] TrenchBroom integration
  - [ ] Map file parser
  - [ ] Texture management
  - [ ] Entity placement
- [ ] Level loading
  - [ ] Resource streaming
  - [ ] Entity instantiation
  - [ ] Collision setup

## Phase 3: Gameplay Systems

### Weapon System
- [ ] Basic weapon framework
  - [ ] Weapon switching
  - [ ] Ammunition tracking
  - [ ] Reload mechanics
- [ ] Implement weapons
  - [ ] Shotgun
    - [ ] Spread pattern
    - [ ] Sound effects
    - [ ] Visual effects
  - [ ] Rocket launcher
    - [ ] Projectile physics
    - [ ] Explosion effects
    - [ ] Splash damage
  - [ ] Lightning gun
    - [ ] Beam effects
    - [ ] Hit detection
    - [ ] Particle effects

### Power-up System
- [ ] Core power-up framework
  - [ ] Pickup system
  - [ ] Duration tracking
  - [ ] Effect stacking
- [ ] Implement power-ups
  - [ ] Health packs
  - [ ] Armor
  - [ ] Quad damage
  - [ ] Speed boost

## Phase 4: Enemy AI and Boss

### Enemy System
- [ ] AI framework
  - [ ] Pathfinding
  - [ ] State machine
  - [ ] Target acquisition
- [ ] Basic enemies
  - [ ] Grunt
    - [ ] Movement AI
    - [ ] Attack patterns
    - [ ] Animation
  - [ ] Flying enemy
    - [ ] Flight patterns
    - [ ] Attack behavior
    - [ ] Evasion tactics
- [ ] Boss enemy
  - [ ] Multiple attack phases
  - [ ] Special abilities
  - [ ] Arena interaction

## Phase 5: Polish and Features

### Audio System
- [ ] Sound engine
  - [ ] 3D positional audio
  - [ ] Sound occlusion
  - [ ] Reverb zones
- [ ] Sound assets
  - [ ] Weapon sounds
  - [ ] Ambient sounds
  - [ ] Music system

### Visual Effects
- [ ] Particle system
  - [ ] Particle emitters
  - [ ] Particle physics
  - [ ] Particle rendering
- [ ] Post-processing
  - [ ] Screen-space effects
  - [ ] Color grading
  - [ ] Motion blur

### UI/UX
- [x] Debug overlay
  - [x] FPS counter
  - [x] Position display
  - [x] Movement info
- [ ] Game UI
  - [ ] Health/Armor display
  - [ ] Weapon selection
  - [ ] Ammunition counter
- [ ] Menu system
  - [ ] Main menu
  - [ ] Options menu
  - [ ] Save/Load system