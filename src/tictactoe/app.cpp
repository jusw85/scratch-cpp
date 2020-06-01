#include "app.h"
#include "constants.h"

SDL_Surface *screen = NULL;
SDL_Surface *sprite_x = NULL;
SDL_Surface *sprite_o = NULL;
SDL_Surface *sprite_win = NULL;
SDL_Surface *sprite_lose = NULL;
SDL_Surface *sprite_draw = NULL;

SDL_Surface *load_image(const std::string filename) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    return optimizedImage;
}

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if (screen == NULL) {
        return false;
    }

    SDL_WM_SetCaption(APP_NAME.c_str(), NULL);

    return true;
}

bool load_assets() {
    sprite_x = load_image(DATA_PATH + "x.png");
    sprite_o = load_image(DATA_PATH + "o.png");
    sprite_win = load_image(DATA_PATH + "win.png");
    sprite_lose = load_image(DATA_PATH + "lose.png");
    sprite_draw = load_image(DATA_PATH + "draw.png");

    if (sprite_x == NULL ||
        sprite_o == NULL ||
        sprite_win == NULL ||
        sprite_lose == NULL ||
        sprite_draw == NULL) {
        return false;
    }
    return true;
}

void clean_up() {
    SDL_FreeSurface(sprite_x);
    SDL_FreeSurface(sprite_o);
    SDL_FreeSurface(sprite_win);
    SDL_FreeSurface(sprite_lose);
    SDL_FreeSurface(sprite_draw);
    SDL_Quit();
}
