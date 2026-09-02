#include <Engine.kdg.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void** appState, int argc, char** argv) {
	*appState = SDL_malloc(sizeof(KDG_EngineState));
	if (!*appState) {
		return SDL_APP_FAILURE;
	}
	SDL_memset(*appState, 0, sizeof(KDG_EngineState));
	KDG_EngineState* state = (KDG_EngineState*)*appState;

	if (!KDG_InitializeEngineState(state, argc, argv)) {
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event) {
	if (!appState) {
		return SDL_APP_FAILURE;
	}
	KDG_EngineState* state = (KDG_EngineState*)appState;

	if (!KDG_PollEngineState(state, event)) {
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appState) {
	if (!appState) {
		return SDL_APP_FAILURE;
	}
	KDG_EngineState* state = (KDG_EngineState*)appState;

	if (!KDG_IterateEngineState(state)) {
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appState, SDL_AppResult result) {
	if (!appState) {
		return;
	}
	KDG_EngineState* state = (KDG_EngineState*)appState;

	KDG_CleanupEngineState(state, result);

	SDL_free(state);
}
