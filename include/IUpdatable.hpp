#pragma once

// ============================================================
// TODO 2b — IUpdatable interface
// ============================================================
// Similar to IRenderable, IUpdatable marks anything that can be
// "ticked" — i.e., updated one step forward in game time.
//
// The GameEngine will call update() once per game tick on all
// updatable objects (the snake, potentially enemies later, etc.)
//
// MEMBER to define:
//   virtual void update() = 0;     ← pure virtual
//   virtual ~IUpdatable() = default;
//
// NOTE: You can inherit from BOTH interfaces at once:
//   struct Snake : public IRenderable, public IUpdatable { ... }
//   This is perfectly valid C++ (multiple inheritance of interfaces
//   is safe and common — it is only multiple inheritance of STATE
//   that gets complicated).
// ============================================================

// TODO 2b-1: define class IUpdatable with:
//   - pure virtual update()
//   - virtual destructor
