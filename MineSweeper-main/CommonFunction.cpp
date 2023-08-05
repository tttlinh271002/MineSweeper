#include "CommonFunction.h"

long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

std::string intToString(int x)
{
    std::stringstream ss;
    ss << x;
    std::string st; ss >> st;
    if (x < 10) st = "0" + st;
    if (x == 0) st = "00";
    return st;
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
     os << msg << " Error: " << SDL_GetError() << std::endl;
     if (fatal)
     {
        SDL_Quit();
        exit(1);
     }
}

void initSDL()
{
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
     if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
        logSDLError(std::cout, "SDL could not initialize!", true);
     if(TTF_Init() < 0)
        logSDLError(std::cout, "SDL_Font Error", true);

     window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
     //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
     if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
     //run at home
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
     //run in school
     //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
     if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        logSDLError(std::cout, "SDL_mixer could not initialize!", true);
     SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
     SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void waitUntilKeyPressed()
{
     SDL_Event e;
     while (true)
     {
         if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
         SDL_Delay(100);
     }
}

void renderTextureFont(const std::string &text, const std::string &font, int Size, SDL_Color fg, int x, int y, int w, int h)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedFont = TTF_RenderText_Solid(TTF_OpenFont(font.c_str(), Size), text.c_str(), fg);
    if(loadedFont != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedFont);
        SDL_FreeSurface(loadedFont);
        if(texture == nullptr) logSDLError(std::cout, "CreateTextureFromSurface");
    }
    else logSDLError(std::cout, "LoadFont");
    SDL_Rect srcRest, desRect;
	TTF_SizeText(TTF_OpenFont(font.c_str(), Size), text.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = 0;
	srcRest.y = 0;

	desRect.x = x; /// toa do cua text
	desRect.y = y;

	desRect.w = w;
	desRect.h = h;
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
}

/// Chunk: am thanh bi de len nhau khi goi ham moi
/// Music: am thanh bat dau lai


/*void play_sound(int type, const std::string &name, int loop)
{
    if(type)
    {
        Mix_Music* music = Mix_LoadMUS(("sounds/" + name).c_str());
        if(!Mix_PlayingMusic()) Mix_PlayMusic(music, loop);
    }
    else
    {
        Mix_Chunk* music = Mix_LoadWAV(("sounds/" + name).c_str());
        Mix_PlayChannel(-1, music, loop);
    }
}*/
