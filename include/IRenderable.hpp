#pragma once

struct IRenderable {

    virtual void render() const = 0;
    virtual ~IRenderable() = default;

    // LATER: Renderer, Snake, Board can all inherit from IRenderable
    //        and provide their own render() behaviour.
};