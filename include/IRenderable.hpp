#pragma once

// ============================================================
// TODO 2a — IRenderable interface
// ============================================================
// In C++, interfaces are expressed as abstract base classes:
// classes with at least one "pure virtual" method (= 0).
//
// Any struct/class that inherits from IRenderable MUST implement
// the render() method, or it will be an abstract class too.
//
// WHY are interfaces useful here?
//   GameEngine does not need to know whether it is rendering
//   the snake, the board, or the HUD.
//   It just calls render() on everything.
//
// TO DEFINE THE INTERFACE:
//   class IRenderable {
//   public:
//       virtual void render() const = 0;   ← pure virtual
//       virtual ~IRenderable() = default;  ← always add a virtual destructor
//   };
//
// LATER: Renderer, Snake, Board can all inherit from IRenderable
//        and provide their own render() behaviour.
// ============================================================

// TODO 2a-1: define class IRenderable with:
//   - pure virtual render() const
//   - virtual destructor
