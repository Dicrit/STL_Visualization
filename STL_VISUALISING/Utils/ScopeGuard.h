#pragma once
#include <iostream>
#include <functional>

class ScopeGuard
{
    using funcType = std::function<void()>;
    funcType func;
public:
    ScopeGuard(funcType f) : func(f)
    {
    }
    ~ScopeGuard()
    {
        if (func)
        {
            func();
        }
    }
};