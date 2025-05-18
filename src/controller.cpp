#include <iostream>
#include <SDL2/SDL.h>
#include "engine.hpp"

void handleController() {
	if (engineParams.controller != nullptr) {
		return;
	}
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			engineParams.controller = SDL_GameControllerOpen(i);
			if (engineParams.controller) {
				std::cout << "Controller detected." << std::endl;
				break;
			}
			else {
				std::cerr << "Controller invalid." << std::endl;
			}
		}
	}
}