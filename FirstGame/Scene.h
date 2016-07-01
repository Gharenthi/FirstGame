#pragma once

#include <list>

#include "Actor.h"

class Scene {
private:
	std::list<Actor*> actors;
	int size;

public:
	Scene() {}

	void render() {
		std::list<Actor*>::iterator it;
		for (it = actors.begin(); it != actors.end(); it++) {
			(*it)->render();
		}
	}

	void addActor(Actor* actor) {
		actors.push_back(actor);
		size++;
	}

	int getSize() {
		return size;
	}

	/*
	void removeActor() {
	}
	*/
};