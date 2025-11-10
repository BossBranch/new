#pragma once
#include <vector>

class ExperimentsStorage {
public:
    std::vector<bool> mExperimentData;
    std::vector<bool> mDeprecatedData;
    bool mExperimentsEverToggled;

    ExperimentsStorage()
        : mExperimentData(),
          mDeprecatedData(),
          mExperimentsEverToggled(false) {}

    ExperimentsStorage(const ExperimentsStorage& other)
        : mExperimentData(other.mExperimentData),
          mDeprecatedData(other.mDeprecatedData),
          mExperimentsEverToggled(other.mExperimentsEverToggled) {}
};