#include "./main.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int game_state = 0;

int main(int argc, char* argv[]) {

    game_state = initialize_SDL();
    if (game_state) {
        printf("Initialized everything");
    }
    setup_tanks();
    int window_width;
    int window_height;

    while (game_state) {
        SDL_GetWindowSize(window, &window_width, &window_height);
        process_input(&game_state);
        update(window_width, window_height);
        render(renderer, window_width, window_height);
    }
    destroy_window();
    return 0;
}

int initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        fprintf(stderr, "Unable to initialize anything\n");
        return FALSE;
    }

    window = SDL_CreateWindow("Tank Wars",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    if (!window) {
        fprintf(stderr, "Unable to Initialize Window\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "Unable to Initialize Renderer\n");
        return FALSE;
    }

    return TRUE;
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
