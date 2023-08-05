#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include "BaseObject.h"

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
const std::string WINDOW_TITLE = "MineSweeper";

long long Rand(long long l, long long h);
std::string intToString(int x);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL();
void quitSDL();
void waitUntilKeyPressed();

void renderTextureFont(const std::string &text, const std::string &font, int Size, SDL_Color fg, int x, int y, int w, int h);

#endif // COMMONFUNCTION_H_INCLUDED
