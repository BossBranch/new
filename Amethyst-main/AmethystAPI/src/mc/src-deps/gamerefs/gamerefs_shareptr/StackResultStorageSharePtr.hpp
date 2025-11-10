#pragma once
#include <memory>

template <typename T>
class StackResultStorageSharePtr {
public:
	std::shared_ptr<T> mPtr;
};