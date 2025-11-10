#pragma once
#include <cstdint>
#include <amethyst/Imports.hpp>

class InputMapping;

class InputMappingFactory {
public:
    /// @vidx { 0, this }
    MC virtual ~InputMappingFactory();

    /// @vidx { 1, this }
    MC virtual const InputMapping* getMapping(const std::string& mappingName);
};

class InputMappingFactoryMap {
public:
    virtual ~InputMappingFactoryMap();
    virtual InputMappingFactory& getInputMappingFactory(int32_t controllerId);
};