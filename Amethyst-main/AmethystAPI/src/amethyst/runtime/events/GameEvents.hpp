#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ClientInstance;
class Level;
class Minecraft;

/*
Called when loading into a world
 - Called on ApplicationView thread
*/
class OnStartJoinGameEvent : public BaseEvent {
public:
    ClientInstance& client;

    OnStartJoinGameEvent(ClientInstance& client) 
        : client(client) {}
};

class OnRequestLeaveGameEvent : public BaseEvent {
public:
    ClientInstance& client;

    OnRequestLeaveGameEvent(ClientInstance& client)
        : client(client) {}
};

/**
 * Called every frame
 * - Called on both client and server thread
 */
class UpdateEvent : public BaseEvent {
public:
    Minecraft& mMinecraft;

    UpdateEvent(Minecraft& mc) : mMinecraft(mc) {}
};

class OnLevelConstructedEvent : public BaseEvent {
public:
    Level& mLevel;

    OnLevelConstructedEvent(Level& level) 
        : mLevel(level) {}
};

class OnLevelDestroyedEvent : public BaseEvent {
public:
    OnLevelDestroyedEvent() {};
};

/**
 * Called every 1/20 seconds before every game tick
 * - Called on both client and server thread
 */
class BeforeTickEvent : public BaseEvent {
public:
	Level& mLevel;

	BeforeTickEvent(Level& level) 
		: mLevel(level) {}
};

/**
 * Called every 1/20 seconds after every game tick
 * - Called on both client and server thread
 */
class AfterTickEvent : public BaseEvent {
public:
	Level& mLevel;

	AfterTickEvent(Level& level) 
		: mLevel(level) {}
};