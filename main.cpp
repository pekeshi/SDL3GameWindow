#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    // --- Init ---
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // --- Create window ---
    SDL_Window* window = SDL_CreateWindow("SDL3 Window", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // --- Create renderer ---
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // --- Main loop ---
    bool running = true;
    SDL_Event event;

    while (running) {
        // 1. Poll events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                }
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                SDL_Log("Resized to %dx%d", event.window.data1, event.window.data2);
            }
        }

        // 2. Update (game logic, physics, etc.)
        // ...

        // 3. Render
        SDL_SetRenderDrawColor(renderer, 30, 30, 46, 255); // dark background
        SDL_RenderClear(renderer);

        // Draw a simple rectangle as a visual test
        SDL_SetRenderDrawColor(renderer, 255, 214, 0, 255);
        SDL_FRect rect = { 100.0f, 100.0f, 200.0f, 150.0f };
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        // 4. Cap frame rate (optional)
        SDL_Delay(16); // ~60 FPS
    }

    // --- Cleanup ---
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}   