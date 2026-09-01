#include "Engine.kdg.h"

#include <SDL3/SDL.h>

void KDG_TestBuild(void) {
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_INFORMATION, "KDG",
		"Hello from KDG.", nullptr
	);
}
