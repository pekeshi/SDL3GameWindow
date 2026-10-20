#include <iostream>
#include <print>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
using namespace std;

int main() {
    std::cout << "Hello, Terminal!" << std::endl;
    print("Hello, SDL3!\n");

    // SDL Init
    SDL_Init(SDL_INIT_VIDEO);

    // SDL Window and Renderer
    SDL_Window* window = SDL_CreateWindow("My SDL3 Window", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, "Renderer");

    bool running = true;
    while (running) {
        
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);  // <-- this is what makes the window visible on Wayland
        SDL_Delay(16);  // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}