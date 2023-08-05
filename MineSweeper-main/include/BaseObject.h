#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../CommonFunction.h"

class BaseObject
{
    public:
        SDL_Texture *greenBack, *orangeBack, *greenRestart, *orangeRestart;
        SDL_Texture *backGround, *mainBackground, *meme, *welcome, *tivi;
        SDL_Texture *emptySquare, *revealed, *flag, *revealedMine, *number[10];
        SDL_Texture *choose, *Beginner, *Intermediate, *Expert;
        SDL_Texture *lose, *win;
        void loadImages();
        SDL_Texture *loadTexture(const std::string &file);
        void renderTexture(SDL_Texture *tex, int x, int y);
        void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
        SDL_Color Orange = { 243, 156, 18 };
        SDL_Color Green = {0, 255, 0};
        Mix_Music *aaaMusic, *boaaaMusic, *checkMusic, *hahaMusic, *helloMusic, *kungfuMusic, *ohnoMusic, *punchMusic;
        Mix_Music *loseMusic, *nikoMusic, *surpriseMusic, *TTYCAMusic, *winMusic, *win2Music;
        Mix_Chunk *aaaChunk, *boaaaChunk, *checkChunk, *hahaChunk, *helloChunk, *kungfuChunk, *ohnoChunk, *punchChunk;
        Mix_Chunk *loseChunk, *nikoChunk, *surpriseChunk, *TTYCAChunk, *winChunk, *win2Chunk;
        void loadSound();
};

extern BaseObject f;
extern SDL_Renderer* renderer;
extern SDL_Window* window;

#endif // BASEOBJECT_H
