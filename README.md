# Verdantia -- 2D Survival Base Building Game Design Document

## Project Overview

A cozy 2D survival/base-building game using the **Sprout Lands Asset Pack**.

The player gathers resources, farms crops, builds a home/base, survives environmental dangers and enemies, and expands into procedurally generated areas for rare resources and progression.

---

# Core Game Fantasy

> Build your homestead in a magical wilderness, survive the nights, explore procedural biomes, and grow from a tiny camp into a thriving settlement.

---

# Core Gameplay Loop

## Early Game
Explore → Gather → Craft → Build Shelter → Plant Crops → Survive → Repeat

### Tasks:
- Gather wood, stone, berries
- Craft basic tools
- Build campfire/shelter
- Plant starter crops
- Survive hunger/night

---

## Mid Game
Expand → Upgrade → Defend → Explore → Unlock → Repeat

### Tasks:
- Expand farm
- Build walls/defenses
- Unlock crafting stations
- Fight enemies
- Explore new biomes

---

## Late Game
Automate → Optimize → Explore Dangerous Areas → Conquer

### Tasks:
- Automate farming/resource production
- Build advanced structures
- Explore dungeons/rare biomes
- Fight bosses/events

---

# Core Systems

## Survival
- Hunger
- Health
- Energy/Stamina

## Resource Gathering
- Chop trees
- Mine rocks
- Harvest plants

## Farming
- Plant seeds
- Water crops
- Harvest food

## Building
- Floors
- Walls
- Furniture
- Crafting Stations

## Combat
- Basic enemies
- Nighttime raids/attacks
- Defensive structures

## Exploration
- Procedural world generation
- Rare biome/resource zones

---

# Procedural Generation Plan

## World Structure
Chunk-Based Generation:
- 16x16 or 32x32 tile chunks

## Terrain Types
- Grasslands
- Forests
- Lakes
- Mountains
- Ruins

## Noise Layers
### Terrain Noise
Determines biome layout.

### Detail Noise
Determines decorative placement:
- Grass
- Flowers
- Pebbles

### Object Noise
Determines:
- Trees
- Rocks
- Resources

---

# Suggested Unique Hook

## Floating Island Survival Builder

### Concept:
Player starts on a small floating island and expands by traveling to other procedurally generated islands.

### Gameplay Loop:
Spawn → Gather → Build Farm → Craft Travel Tools → Explore New Islands → Gather Rare Resources → Expand Base

### Why This Works:
- Fits cozy art style
- Makes procedural generation meaningful
- Adds exploration incentive
- Helps differentiate from similar farming games

---

# Development Roadmap

## Prototype 1 – Foundation
- Player movement
- Camera system
- Procedural terrain generation
- Tree/rock spawning
- Basic gathering mechanics

---

## Prototype 2 – Survival Systems
- Inventory system
- Item pickups
- Hunger/Stamina systems

---

## Prototype 3 – Crafting
- Crafting UI/system
- Workbench/Campfire
- Basic recipes

---

## Prototype 4 – Farming
- Soil tilling
- Seed planting
- Crop growth
- Harvesting

---

## Prototype 5 – Combat/Threats
- Enemy AI
- Day/Night cycle
- Combat system

---

# Technical Architecture

## Core Managers
GameManager  
WorldManager  
ChunkGenerator  
InventoryManager  
CraftingManager  
BuildingManager  
EnemySpawner  
AIManager  
SaveSystem  

---

# Asset Pack

Using:
**Sprout Lands Asset Pack**
https://cupnooble.itch.io/sprout-lands-asset-pack

---

# Design Goals

- Cozy but rewarding survival gameplay
- Strong exploration incentives
- Relaxing building/farming systems
- Procedural replayability
- Unique twist beyond generic farming sims

---

# Inspiration

Games influencing this project:
- Stardew Valley
- Core Keeper
- Forager
- Don’t Starve
- Terraria

---

# Final Vision

A polished indie survival/base-building game with:
- relaxing cozy aesthetics,
- satisfying progression,
- meaningful procedural exploration,
- and strong long-term replayability.