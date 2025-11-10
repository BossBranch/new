#pragma once
#include <memory>
#include <mc/src/common/world/actor/Actor.hpp>

struct ActorOwnerComponent {
	std::unique_ptr<Actor> mActor;
};