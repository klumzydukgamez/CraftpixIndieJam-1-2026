#include "Engine.kdg.h"

bool KDG_InitializeArena(KDG_Arena* arena, size_t capacity) {
	size_t remainder = capacity % 64;
	if (remainder)
		capacity += 64 - remainder;
	arena->buffer = SDL_aligned_alloc(64, capacity);
	if (!arena->buffer) {
		return false;
	}
	SDL_memset(arena->buffer, 0, capacity);
	arena->capacity = capacity;
	return true;
}

void* KDG_AllocateFromArena(KDG_Arena* arena, size_t size, size_t alignment) {
	size_t aligned = (arena->size + (alignment - 1)) & ~(alignment - 1);
	if (aligned + size > arena->capacity) {
		return nullptr;
	}
	Uint8* ptr = &(arena->buffer)[aligned];
	arena->size = aligned + size;
	return ptr;
}

void KDG_ResetArena(KDG_Arena* arena) {
	arena->size = 0;
}

void KDG_CleanupArena(KDG_Arena* arena) {
	if (arena->buffer)
		SDL_aligned_free(arena->buffer);
}

bool KDG_InitializeEngineState(KDG_EngineState* state, int argc, char** argv) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}

	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)) {
		return false;
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)) {
		return false;
	}
	if (!SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
		)) {
		return false;
	}

	state->window = SDL_CreateWindow(
		"KDG", 640, 360, SDL_WINDOW_OPENGL
	);
	if (!state->window) {
		return false;
	}

	state->glContext = SDL_GL_CreateContext(state->window);
	if (!state->glContext) {
		return false;
	}

	if (!SDL_GL_MakeCurrent(state->window, state->glContext)) {
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		return false;
	}

	return true;
}

bool KDG_PollEngineState(KDG_EngineState* state, SDL_Event* event) {
	switch (event->type) {
		case SDL_EVENT_QUIT:
			return false;
		default:
			break;
	}

	return true;
}

bool KDG_IterateEngineState(KDG_EngineState* state) {
	glViewport(0, 0, 640, 360);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!SDL_GL_SwapWindow(state->window)) {
		return false;
	}

	return true;
}

void KDG_CleanupEngineState(KDG_EngineState* state, SDL_AppResult result) {
	if (state->glContext)
		SDL_GL_DestroyContext(state->glContext);
	if (state->window)
		SDL_DestroyWindow(state->window);
	SDL_Quit();
}
