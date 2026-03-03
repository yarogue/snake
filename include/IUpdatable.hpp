#pragma once

struct IUpdatable
{
    virtual void update() = 0;
    virtual ~IUpdatable() = default;
};