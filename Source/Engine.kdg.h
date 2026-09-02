#if !defined __KDG_ENGINE_H__
#define __KDG_ENGINE_H__

#include <SDL3/SDL.h>
#include <glad/glad.h>

#if defined SDL_PLATFORM_WINDOWS
#define KDG_DLL __declspec(dllexport)
#else
#define KDG_DLL
#endif

typedef struct {
	Uint8* buffer;
	size_t capacity;
	size_t size;
} KDG_Arena;

bool KDG_InitializeArena(KDG_Arena* arena, size_t capacity);
void* KDG_AllocateFromArena(KDG_Arena* arena, size_t size, size_t alignment);
void KDG_ResetArena(KDG_Arena* arena);
void KDG_CleanupArena(KDG_Arena* arena);

typedef struct {
	SDL_Window* window;
	SDL_GLContext glContext;
} KDG_EngineState;

bool KDG_InitializeEngineState(KDG_EngineState* state, int argc, char** argv);
bool KDG_PollEngineState(KDG_EngineState* state, SDL_Event* event);
bool KDG_IterateEngineState(KDG_EngineState* state);
void KDG_CleanupEngineState(KDG_EngineState* state, SDL_AppResult result);

#endif /* __KDG_ENGINE_H__ */
