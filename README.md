# Infection Simulation - Pokémon Lab
**Author:** Josh Forbes 
**Date:** November 2023  
**Instructors:** Stefan Brandle, Josh Forbes  
**File:** `Board.cpp`

---

## 🧪 Project Overview

This simulation models a Pokémon infection scenario involving **trainers**, **rangers**, and **Pokémon** on a 2D board. The goal is to simulate how Pokémon either become "caught" (converted into trainers or rangers) or escape to safety in a PokéCenter.

Each time step of the simulation:
- **Humans (trainers and rangers)** move randomly.
- **Pokémon** attempt to reach the PokéCenter.
- If a Pokémon is adjacent to an infected human or another infected Pokémon, it becomes infected.
- If a Pokémon reaches the PokéCenter before being infected, it is safe.

---

## 🧩 How It Works

### 🧑 Humans (Trainers & Rangers)
- 8 total humans, first 4 are **trainers** (ID = 0), next 4 are **rangers** (ID = 1).
- Humans move randomly each time step.
- They infect any Pokémon adjacent to them.

### 🐾 Pokémon
- Start randomly on the board (excluding PokéCenter).
- Move each step in an attempt to reach the PokéCenter.
- If they are adjacent to an infected entity (human or Pokémon), they are **converted** to the same type (trainer or ranger).
- If they reach the PokéCenter while still uninfected, they are **safe** and cannot be infected.

### 🏥 PokéCenter
- A special area on the board.
- Once a Pokémon enters it, it is considered **safe** and becomes inactive in the simulation.

---

## ⚙️ Board.cpp Summary

### `Board::run()`
- Initializes humans and Pokémon.
- Runs the main simulation loop for up to 60 time steps.
- Manages infection spread, movement, drawing, and output.

### `processInfection()`
- Checks adjacency between Pokémon and humans or other infected Pokémon.
- Infects (or "converts") Pokémon based on proximity.

### `allInfected()`
- Returns true when all Pokémon have either been caught or reached the PokéCenter.

---

## 🧮 Stats Displayed Each Step

- Total Pokémon caught by Trainers
- Total Pokémon caught by Rangers
- Total Pokémon that reached the PokéCenter
- Total Pokémon still free
- Current simulation time

---

## 🏆 Ending Condition

After 60 steps (or once all Pokémon are infected/safe), the winner is declared based on who caught the most Pokémon:
- **Trainer Victory**
- **Ranger Victory**
- **Pokémon Victory** if more escape than are caught

---

## 🚧 Notes

- Humans and Pokémon are stored as arrays of pointers.
- Board dimensions, human count, and Pokémon count are configurable.
- Uses `usleep()` to control the simulation's pacing.
- Requires `conio.h` for screen and cursor handling (platform-specific).
