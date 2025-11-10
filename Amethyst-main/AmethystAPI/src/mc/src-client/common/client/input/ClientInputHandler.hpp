#pragma once
#include "mc/src-deps/input/InputHandler.hpp"

class ClientInstance;

class ClientInputHandler {
public:
    ClientInstance* mClient;
    std::byte padding[8];
    InputHandler* mInputHandler;
};