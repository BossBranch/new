#pragma once

class ClientInstance;

class IClientInstance {
public:
    ClientInstance& asInstance() {
        return *(ClientInstance*)this;
    }
};