#include "BaseObject.h"

void BaseObject::renderTexture(SDL_Texture *tex, int x, int y)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

void BaseObject::renderTexture(SDL_Texture *tex, int x, int y, int w, int h)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

SDL_Texture* BaseObject::loadTexture(const std::string &file)
{
    SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr) logSDLError(std::cout, "CreateTextureFromSurface");
	}
	else logSDLError(std::cout, "LoadImage");
	return texture;
}

void BaseObject::loadImages()
{
    greenBack = loadTexture("images/greenBack.png");
    orangeBack = loadTexture("images/orangeBack.png");
    greenRestart = loadTexture("images/greenRestart.png");
    orangeRestart = loadTexture("images/orangeRestart.png");
    backGround = loadTexture("images/background.jpg");
    mainBackground = loadTexture("images/mainBackground.jpg");
    meme = loadTexture("images/meme.png");
    welcome = loadTexture("images/welcome.png");
    tivi = loadTexture("images/tivi.png");
    emptySquare = loadTexture("images/empty.png");
    revealed = loadTexture("images/revealed.png");
    flag = loadTexture("images/flag.png");
    for(int i = 1; i <= 8; i++)
    {
        std::string ch = ""; ch = i + 48;
        number[i] = loadTexture("images/" + ch + ".png");
    }

    revealedMine = loadTexture("images/revealedMine.png");
    choose = loadTexture("images/choose.png");
    Beginner = loadTexture("images/beginner.png");
    Intermediate = loadTexture("images/intermediate.png");
    Expert = loadTexture("images/expert.png");
    lose = loadTexture("images/lose2.png");
    win = loadTexture("images/win2.png");
}

void BaseObject::loadSound()
{
    aaaMusic = Mix_LoadMUS("sounds/aaa.mp3"); aaaChunk = Mix_LoadWAV("sounds/aaa.mp3");
    boaaaMusic = Mix_LoadMUS("sounds/boaaa.mp3"); boaaaChunk = Mix_LoadWAV("sounds/boaaa.mp3");
    checkMusic = Mix_LoadMUS("sounds/check.mp3"); checkChunk = Mix_LoadWAV("sounds/check.mp3");
    hahaMusic = Mix_LoadMUS("sounds/haha.mp3"); hahaChunk = Mix_LoadWAV("sounds/haha.mp3");
    helloMusic = Mix_LoadMUS("sounds/hello.mp3"); helloChunk = Mix_LoadWAV("sounds/hello.mp3");
    kungfuMusic = Mix_LoadMUS("sounds/kungfu.mp3"); kungfuChunk = Mix_LoadWAV("sounds/kungfu.mp3");
    ohnoMusic = Mix_LoadMUS("sounds/ohno.mp3"); ohnoChunk = Mix_LoadWAV("sounds/ohno.mp3");
    punchMusic = Mix_LoadMUS("sounds/punch.mp3"); punchChunk = Mix_LoadWAV("sounds/punch.mp3");
    loseMusic = Mix_LoadMUS("sounds/lose.mp3"); loseChunk = Mix_LoadWAV("sounds/lose.mp3");
    nikoMusic = Mix_LoadMUS("sounds/niko.mp3"); nikoChunk = Mix_LoadWAV("sounds/niko.mp3");
    surpriseMusic = Mix_LoadMUS("sounds/surprise.mp3"); surpriseChunk = Mix_LoadWAV("sounds/surprise.mp3");
    TTYCAMusic = Mix_LoadMUS("sounds/TTYCA.mp3"); TTYCAChunk = Mix_LoadWAV("sounds/TTYCA.mp3");
    winMusic = Mix_LoadMUS("sounds/win.mp3"); winChunk = Mix_LoadWAV("sounds/win.mp3");
    win2Music = Mix_LoadMUS("sounds/win2.mp3"); win2Chunk = Mix_LoadWAV("sounds/win2.mp3");
}
