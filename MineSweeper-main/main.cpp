#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;

typedef pair < int, int > pii;
int maxMine, sizeRowBoard, sizeColumnBoard;
const int sizeSquare = 35;

int sizeNumber = 50;
int c_pad, r_pad;
int a[35][35];
int clickedSquare[35][35];
/// -1: revealed, 0: chua lam gi, 1: dat co, 2: da co so;
int dong[] = {-1, -1, -1, 0, 1, 1, 1, 0}, cot[] = {-1, 0, 1, 1, 1, 0, -1, -1};
bool dx[35][35];
int remainMine, sumCell, level, quit;

BaseObject f;
SDL_Renderer* renderer;
SDL_Window* window;

void drawPressFunc(bool Back, int Restart)
{
    if(Back) f.renderTexture(f.greenBack, 0, 650, 50, 50);
    else f.renderTexture(f.orangeBack, 0, 650, 50, 50);

    if(Restart == 0) f.renderTexture(f.orangeRestart, 0, 0, 50, 50);
    if(Restart > 0) f.renderTexture(f.greenRestart, 0, 0, 50, 50);
}

void drawBackGround()
{
    SDL_RenderClear(renderer);
    f.renderTexture(f.backGround, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    f.renderTexture(f.meme, 0, 0, 200, 200);
    //SDL_RenderPresent(renderer);
}

int selectMenu() /// first page
{
    SDL_Event e;
    while(1)
    {
        if(SDL_PollEvent(&e) == 0)
        {
            if(!Mix_PlayingMusic()) Mix_PlayMusic(f.helloMusic, 0);
            continue;
        }
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) return -1;
        drawBackGround();
        f.renderTexture(f.welcome, 150, 0, 1190, 230);
        //f.renderTextureFont(f.ThanhHungO, 1070, 10, 230, 50);
        renderTextureFont("Thanh Hung", "Font/thanhhung.otf", 50, f.Orange, 1070, 10, 230, 50);
        //f.renderTextureFont(f.StartO, 600, 350, 100, 40);
        //f.renderTextureFont(f.ExitO, 600, 410, 85, 40);
        renderTextureFont("Start", "Font/font.ttf", 50, f.Orange, 600, 350, 100, 40);
        renderTextureFont("Exit", "Font/font.ttf", 50, f.Orange, 600, 410, 85, 40);

        if(e.type == SDL_MOUSEMOTION)
        {
            if(!Mix_PlayingMusic()) Mix_PlayMusic(f.helloMusic, 0);
            int x = e.motion.x, y = e.motion.y;
            if(600 <= x && x <= 700 && 350 <= y && y <= 390)
                renderTextureFont("Start", "Font/font.ttf", 50, f.Green, 600, 350, 100, 40);
            if(600 <= x && x <= 685 && 410 <= y && y <= 450)
                renderTextureFont("Exit", "Font/font.ttf", 50, f.Green, 600, 410, 85, 40);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x = e.button.x, y = e.button.y;
            if(600 <= x && x <= 700 && 350 <= y && y <= 390)
            {
                Mix_PlayChannel(-1, f.kungfuChunk, 0); Mix_HaltMusic();
                return 1;
            }
            if(600 <= x && x <= 685 && 410 <= y && y <= 450)
            {
                Mix_PlayChannel(-1, f.kungfuChunk, 0); Mix_HaltMusic();
                return -1;
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void drawMainBackground(int level)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    f.renderTexture(f.mainBackground, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //f.renderTextureFont(f.ThanhHungO, 1070, 10, 230, 50);
    //f.renderTextureFont(f.remainMineO[remainMine], (SCREEN_WIDTH - 230) / 2, 0, 230, 50);
    renderTextureFont("Thanh Hung", "Font/thanhhung.otf", 50, f.Orange, 1070, 10, 230, 50);
    renderTextureFont("Remain Mine: " + intToString(remainMine), "Font/font.ttf", 50, f.Orange, (SCREEN_WIDTH - 230) / 2, 0, 230, 50);
    if(level == 1) f.renderTexture(f.tivi, c_pad - 15, r_pad - 20, sizeColumnBoard * sizeSquare + 28, sizeRowBoard * sizeSquare + 85);
    if(level == 2) f.renderTexture(f.tivi, c_pad - 24, r_pad - 37, sizeColumnBoard * sizeSquare + 45, sizeRowBoard * sizeSquare + 110);
    if(level == 3) f.renderTexture(f.tivi, c_pad - 24, r_pad - 37, sizeColumnBoard * sizeSquare + 45, sizeRowBoard * sizeSquare + 105);
    drawPressFunc(0, 0);
}

void prepare(int maxMine, int level)
{
    srand(time(NULL));
    remainMine = maxMine;
    memset(a, 0, sizeof(a));
    memset(clickedSquare, 0, sizeof(clickedSquare));
    quit = 0;
    for(int i = 1; i <= maxMine; i++)
    {
        int d = Rand(0, sizeRowBoard - 1), c = Rand(0, sizeColumnBoard - 1);
        while(1)
        {
            if(a[d][c] != -1)
            {
                a[d][c] = -1;
                break;
            }
            else
            {
                d = Rand(0, sizeRowBoard - 1);
                c = Rand(0, sizeColumnBoard - 1);
            }
        }
    }
    for(int d = 0; d < sizeRowBoard; d++)
        for(int c = 0; c < sizeColumnBoard; c++)
            if(a[d][c] != -1)
            {
                for(int k = 0; k < 8; k++)
                {
                    int dm = d + dong[k], cm = c + cot[k];
                    if(dm >= 0 && dm < sizeRowBoard && cm >= 0 && cm < sizeColumnBoard)
                        a[d][c] += (a[dm][cm] == -1);
                }
            }
    drawMainBackground(level);
    for(int i = 0; i < sizeRowBoard; i++)
        for(int j = 0; j < sizeColumnBoard; j++)
            f.renderTexture(f.emptySquare, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
    SDL_RenderPresent(renderer);
}

void drawBoard(int level)
{
    drawMainBackground(level);
    for(int i = 0; i < sizeRowBoard; i++)
        for(int j = 0; j < sizeColumnBoard; j++)
        {
            if(clickedSquare[i][j] == -1)
                f.renderTexture(f.revealed, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
            else if(clickedSquare[i][j] == 0)
                f.renderTexture(f.emptySquare, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
            else if(clickedSquare[i][j] == 1)
                f.renderTexture(f.flag, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
            else
                f.renderTexture(f.number[a[i][j]], c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
        }
    SDL_RenderPresent(renderer);
}

void BFS(int x, int y)
{
    memset(dx, false, sizeof(dx));
    queue < pii > q; q.push(make_pair(x, y)); dx[x][y] = true;
    while(q.size())
    {
        pii u = q.front(); q.pop();
        int d = u.first, c = u.second;
        clickedSquare[d][c] = -1;
        for(int k = 0; k < 8; k++)
        {
            int dm = d + dong[k], cm = c + cot[k];
            if(dm >= 0 && dm < sizeRowBoard && cm >= 0 && cm < sizeColumnBoard)
            {
                if(!dx[dm][cm])
                {
                    dx[dm][cm] = true;
                    if(a[dm][cm] == 0) q.push(make_pair(dm, cm));
                    if(1 <= a[dm][cm] && a[dm][cm] <= 8) clickedSquare[dm][cm] = 2;
                }
            }
        }
    }
}

void process(int d, int c, int level)
{
    if(clickedSquare[d][c] == 0)
    {
        if(a[d][c] == -1)
        {
            Mix_PlayChannel(-1, f.boaaaChunk, 0); quit = Rand(1, 2);

            if(quit == 1) {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.aaaMusic, 0);}
            else {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.hahaMusic, 0);}
            //play_sound(0, "lose.mp3", 0);
            drawBoard(level);
            for(int i = 0; i < sizeRowBoard; i++)
                for(int j = 0; j < sizeColumnBoard; j++)
                    if(a[i][j] == -1 && clickedSquare[i][j] != 1)
                        f.renderTexture(f.revealedMine, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
            return;
        }
        else if(a[d][c] == 0) Mix_PlayChannel(-1, f.checkChunk, 0), BFS(d, c);
        else Mix_PlayChannel(-1, f.checkChunk, 0), clickedSquare[d][c] = 2;
    }
    else if(clickedSquare[d][c] == 2)
    {
        int cnt = 0;
        for(int k = 0; k < 8; k++)
        {
            int dm = d + dong[k], cm = c + cot[k];
            if(dm >= 0 && dm < sizeRowBoard && cm >= 0 && cm < sizeColumnBoard)
                cnt += (clickedSquare[dm][cm] == 1);
        }
        if(cnt == a[d][c])
        {
            Mix_PlayChannel(-1, f.checkChunk, 0);
            for(int k = 0; k < 8; k++)
            {
                int dm = d + dong[k], cm = c + cot[k];
                if(dm >= 0 && dm < sizeRowBoard && cm >= 0 && cm < sizeColumnBoard)
                    if(clickedSquare[dm][cm] == 0)
                    {
                        if(a[dm][cm] == 0) BFS(dm, cm);
                        else if(a[dm][cm] == -1)
                        {
                            drawBoard(level);
                            for(int i = 0; i < sizeRowBoard; i++)
                                for(int j = 0; j < sizeColumnBoard; j++)
                                    if(a[i][j] == -1 && clickedSquare[i][j] != 1)
                                        f.renderTexture(f.revealedMine, c_pad + j * sizeSquare, r_pad + i * sizeSquare, sizeSquare, sizeSquare);
                            Mix_PlayChannel(-1, f.boaaaChunk, 0); quit = Rand(1, 2);
                            if(quit == 1) {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.aaaMusic, 0);}
                            else {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.hahaMusic, 0);}
                            //play_sound(0, "lose.mp3", 0);
                            return;
                        }
                        else clickedSquare[dm][cm] = 2;
                    }
            }
        }
        else Mix_PlayChannel(-1, f.ohnoChunk, 0);
    }
    drawBoard(level);
    SDL_RenderPresent(renderer);
}

int drawSelectLevel()
{
    SDL_Event e;
    int Start_x = 10, Start_y = 230;
    int sizeBeginner = 250, dis = 45;
    int x[] = {Start_x, Start_x + sizeBeginner + dis, Start_x + 2 * sizeBeginner + 150 + dis * 2};
    int y[] = {Start_y, Start_y, Start_y};
    int w[] = {sizeBeginner, sizeBeginner + 150, SCREEN_WIDTH - x[2] - Start_x};
    int h[] = {w[0] * 350 / 351, w[1] * 560 / 562, w[2] * 560 / 1052};
    while(1)
    {
        SDL_Delay(10);
        if(SDL_PollEvent(&e) == 0)
        {
            if(!Mix_PlayingMusic()) Mix_PlayMusic(f.TTYCAMusic, 0);
            continue;
        }
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) break;
        drawBackGround();
        
        //f.renderTextureFont(f.ExitO, 0, 650, 50, 50);
        renderTextureFont("Exit", "Font/font.ttf", 50, f.Orange, 0, 650, 50, 50);

        f.renderTexture(f.choose, 150, 0, 1190, 230);
        renderTextureFont("Thanh Hung", "Font/thanhhung.otf", 50, f.Orange, 1070, 10, 230, 50);
        //f.renderTextureFont(f.ThanhHungO, 1070, 10, 230, 50);

        f.renderTexture(f.Beginner, x[0], y[0], w[0], h[0]);
        renderTextureFont("Beginner(9x9)", "Font/font.ttf", 50, f.Orange, x[0] + (w[0] - 120) / 2, y[0] + h[0] + 10, 120, 35);
        //f.renderTextureFont(f.BeginnerO, x[0] + (w[0] - 120) / 2, y[0] + h[0] + 10, 120, 35);

        f.renderTexture(f.Intermediate, x[1], y[1], w[1], h[1]);
        renderTextureFont("Intermediate(16x16)", "Font/font.ttf", 50, f.Orange, x[1] + (w[1] - 180) / 2, y[1] + h[1] + 10, 180, 35);
        //f.renderTextureFont(f.IntermediateO, x[1] + (w[1] - 180) / 2, y[1] + h[1] + 10, 180, 35);

        f.renderTexture(f.Expert, x[2], y[2], w[2], h[2]);
        renderTextureFont("Expert(16x30)", "Font/font.ttf", 50, f.Orange, x[2] + (w[2] - 120) / 2, y[2] + h[2] + 10, 120, 35);
        //f.renderTextureFont(f.ExpertO, x[2] + (w[2] - 120) / 2, y[2] + h[2] + 10, 120, 35);

        if(e.type == SDL_MOUSEMOTION)
        {
            int x_ = e.motion.x, y_ = e.motion.y;
            if((x[0] <= x_ && x_ <= x[0] + w[0] && y[0] <= y_ && y_ <= y[0] + h[0]) ||
               (x[0] + (w[0] - 120) / 2 <= x_ && x_ <= x[0] + (w[0] - 120) / 2 + 120 && y[0] + h[0] + 10 <= y_ && y_ <= y[0] + h[0] + 10 + 35))
                //f.renderTextureFont(f.BeginnerG, x[0] + (w[0] - 120) / 2, y[0] + h[0] + 10, 120, 35);
                renderTextureFont("Beginner(9x9)", "Font/font.ttf", 50, f.Green, x[0] + (w[0] - 120) / 2, y[0] + h[0] + 10, 120, 35);
            if((x[1] <= x_ && x_ <= x[1] + w[1] && y[1] <= y_ && y_ <= y[1] + h[1]) ||
               (x[1] + (w[1] - 180) / 2 <= x_ && x_ <= x[1] + (w[1] - 180) / 2 + 180 && y[1] + h[1] + 10 <= y_ && y_ <= y[1] + h[1] + 10 + 35))
                //f.renderTextureFont(f.IntermediateG, x[1] + (w[1] - 180) / 2, y[1] + h[1] + 10, 180, 35);
                renderTextureFont("Intermediate(16x16)", "Font/font.ttf", 50, f.Green, x[1] + (w[1] - 180) / 2, y[1] + h[1] + 10, 180, 35);
            if((x[2] <= x_ && x_ <= x[2] + w[2] && y[2] <= y_ && y_ <= y[2] + h[2]) ||
               (x[2] + (w[2] - 120) / 2 <= x_ && x_ <= x[2] + (w[2] - 120) / 2 + 120 && y[2] + h[2] + 10 <= y_ && y_ <= y[2] + h[2] + 10 + 35))
                //f.renderTextureFont(f.ExpertG, x[2] + (w[2] - 120) / 2, y[2] + h[2] + 10, 120, 35);
                renderTextureFont("Expert(16x30)", "Font/font.ttf", 50, f.Green, x[2] + (w[2] - 120) / 2, y[2] + h[2] + 10, 120, 35);
            if(0 <= x_ && x_ <= 50 && 650 <= y_ && y_ <= 700)
                //f.renderTextureFont(f.ExitG, 0, 650, 50, 50);
                renderTextureFont("Exit", "Font/font.ttf", 50, f.Green, 0, 650, 50, 50);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x_ = e.button.x, y_ = e.button.y;
            if(0 <= x_ && x_ <= 50 && 650 <= y_ && y_ <= 700)
               {Mix_PlayChannel(-1, f.punchChunk, 0); return 0;}
            if((x[0] <= x_ && x_ <= x[0] + w[0] && y[0] <= y_ && y_ <= y[0] + h[0]) ||
               (x[0] + (w[0] - 120) / 2 <= x_ && x_ <= x[0] + (w[0] - 120) / 2 + 120 && y[0] + h[0] + 10 <= y_ && y_ <= y[0] + h[0] + 10 + 35))
               {Mix_PlayChannel(-1, f.punchChunk, 0); return 1;}
            if((x[1] <= x_ && x_ <= x[1] + w[1] && y[1] <= y_ && y_ <= y[1] + h[1]) ||
               (x[1] + (w[1] - 180) / 2 <= x_ && x_ <= x[1] + (w[1] - 180) / 2 + 180 && y[1] + h[1] + 10 <= y_ && y_ <= y[1] + h[1] + 10 + 35))
               {Mix_PlayChannel(-1, f.punchChunk, 0); return 2;}
            if((x[2] <= x_ && x_ <= x[2] + w[2] && y[2] <= y_ && y_ <= y[2] + h[2]) ||
               (x[2] + (w[2] - 120) / 2 <= x_ && x_ <= x[2] + (w[2] - 120) / 2 + 120 && y[2] + h[2] + 10 <= y_ && y_ <= y[2] + h[2] + 10 + 35))
               {Mix_PlayChannel(-1, f.punchChunk, 0); return 3;}
        }
        SDL_RenderPresent(renderer);
    }
    return 0;
}

void selectLevel() /// return to page 2
{
    level = drawSelectLevel();
    if(level == 0) exit(0);
    if(level == 1) maxMine = 10, sizeRowBoard = sizeColumnBoard = 9;
    if(level == 2) maxMine = 40, sizeRowBoard = sizeColumnBoard = 16;
    if(level == 3) maxMine = 99, sizeRowBoard = 16, sizeColumnBoard = 30;
    c_pad = (SCREEN_WIDTH - sizeColumnBoard * sizeSquare) / 2;
    r_pad = (SCREEN_HEIGHT - sizeRowBoard * sizeSquare) / 2;

    prepare(maxMine, level);
}

int playAgain(bool tt)
{
    int wP = 200, hP = 40, wE = 85, hE = 40, dis = (138 - hP - hE) / 3;
    int xP = (SCREEN_WIDTH - wP) / 2, yP = 562 + dis, xE = xP, yE = yP + hP + dis;
    SDL_Event e;
    while(1)
    {
        SDL_Delay(10);
        if(SDL_PollEvent(&e) == 0)
        {
            if(!tt)
            {
                f.renderTexture(f.lose, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                if(quit == 1) {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.aaaMusic, 0);}
                else {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.hahaMusic, 0);}
                //play_sound(0, "lose.mp3", 0);
            }
            else
            {
                f.renderTexture(f.win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                if(!Mix_PlayingMusic()) Mix_PlayMusic(f.win2Music, 0);
            }
            continue;
        }
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) break;

        if(tt)
        {
            f.renderTexture(f.win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            if(!Mix_PlayingMusic()) Mix_PlayMusic(f.win2Music, 0);
        }
        else
        {
            f.renderTexture(f.lose, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            if(quit == 1) {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.aaaMusic, 0);}
            else {if(!Mix_PlayingMusic()) Mix_PlayMusic(f.hahaMusic, 0);}
        }

        renderTextureFont("Play Again", "Font/font.ttf", 50, f.Orange, xP, yP, wP, hP);
        renderTextureFont("Exit", "Font/font.ttf", 50, f.Orange, xE, yE, wE, hE);
        //f.renderTextureFont(f.AgainO, xP, yP, wP, hP);
        //f.renderTextureFont(f.ExitO, xE, yE, wE, hE);

        if(e.type == SDL_MOUSEMOTION)
        {
            int x = e.motion.x, y = e.motion.y;
            if(xP <= x && x <= xP + wP && yP <= y && y <= yP + hP)
                //f.renderTextureFont(f.AgainG, xP, yP, wP, hP);
                renderTextureFont("Play Again", "Font/font.ttf", 50, f.Green, xP, yP, wP, hP);
            if(xE <= x && x <= xE + wE && yE <= y && y <= yE + hE)
                //f.renderTextureFont(f.ExitG, xE, yE, wE, hE);
                renderTextureFont("Exit", "Font/font.ttf", 50, f.Green, xE, yE, wE, hE);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_HaltMusic();
            int x = e.button.x, y = e.button.y;
            if(xP <= x && x <= xP + wP && yP <= y && y <= yP + hP) {Mix_PlayChannel(-1, f.kungfuChunk, 0); return 0;}
            if(xE <= x && x <= xE + wE && yE <= y && y <= yE + hE) {return -1;}
        }
        SDL_RenderPresent(renderer);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    initSDL();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    f.loadImages();
    f.loadSound();

    int type = selectMenu();
    if(type == -1) return 0;

    selectLevel();

    SDL_Event e;

    while(1)
    {
        SDL_Delay(10);
        if(SDL_PollEvent(&e) == 0)
        {
            if(!Mix_PlayingMusic()) Mix_PlayMusic(f.TTYCAMusic, 0);
            continue;
        }
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) break;
        if(quit)
        {
            SDL_RenderPresent(renderer);
            SDL_Delay(500);
            f.renderTexture(f.lose, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            Mix_HaltMusic();
            int type = playAgain(0);
            if(type == -1) return 0;
            prepare(maxMine, level);
        }
        if(!Mix_PlayingMusic()) Mix_PlayMusic(f.TTYCAMusic, 0);
        if(e.type == SDL_MOUSEMOTION)
        {
            int x = e.motion.x, y = e.motion.y;
            if(0 <= x && x <= 50 && 650 <= y && y <= 700) drawPressFunc(1, 0);
            else if(0 <= x && x <= 50 && 0 <= y && y <= 50) drawPressFunc(0, 1);
            else drawPressFunc(0, 0);
            SDL_RenderPresent(renderer);
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x = e.button.x, y = e.button.y;
            if(0 <= x && x <= 50 && 650 <= y && y <= 700)
            {
                Mix_PlayChannel(-1, f.kungfuChunk, 0);
                drawPressFunc(1, 0);
                selectLevel();
                continue;
            }
            if(0 <= x && x <= 50 && 0 <= y && y <= 50) /// reStart
            {
                Mix_PlayChannel(-1, f.checkChunk, 0);
                drawPressFunc(0, 1);
                prepare(maxMine, level);
                continue;
            }
            if(x < c_pad || y < r_pad) continue;
            x = (x - c_pad) / sizeSquare;
            y = (y - r_pad) / sizeSquare;
            if(x >= sizeColumnBoard || y >= sizeRowBoard) continue;
            if(e.button.button == SDL_BUTTON_LEFT) process(y, x, level);
            else
            {
                if(clickedSquare[y][x] == 1) remainMine++, clickedSquare[y][x] = 1 - clickedSquare[y][x], Mix_PlayChannel(-1, f.surpriseChunk, 0);
                else if(!clickedSquare[y][x]) remainMine--, clickedSquare[y][x] = 1 - clickedSquare[y][x], Mix_PlayChannel(-1, f.surpriseChunk, 0);
                drawBoard(level);
            }
            sumCell = 0;
            for(int i = 0; i < sizeRowBoard; i++)
                for(int j = 0; j < sizeColumnBoard; j++)
                    sumCell += (clickedSquare[i][j] == -1 || clickedSquare[i][j] == 2);
            if(sumCell == sizeRowBoard * sizeColumnBoard - maxMine)
            {
                SDL_Delay(500);
                f.renderTexture(f.win, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                Mix_HaltMusic();
                //play_sound(0, "win2.mp3", 0);
                int type = playAgain(1);
                if(type == -1) return 0;
                prepare(maxMine, level);
            }
        }
    }

    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL();
    return 0;
}
