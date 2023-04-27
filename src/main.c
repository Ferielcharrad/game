


#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>


SDL_Renderer *ren;

typedef struct {

    int up;
    int down;
    int right;
    int left;
    bool shoot;
    bool start;
    bool quit;


}Keys;

typedef struct { 
int x;
int y;
int dx;
int dy;
int hp;
int isAttacking;
SDL_Texture* texture;
}Character;





const int DISPLAY_W = 700;
const int DISPLAY_H = 400;

Keys keys;


void do_key_up(SDL_KeyboardEvent *event );
void do_key_down(SDL_KeyboardEvent *event);
SDL_Rect *draw_texture(SDL_Renderer **renderer, SDL_Texture *texture, int x, int y);
void level1(void)

{

    SDL_Window *window;
    SDL_Event ev;
    SDL_SetMainReady();
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
            fputs(SDL_GetError(), stderr);

        }
        if (TTF_Init() == -1)
        {
           fputs("couldn't load ttf",stdout);

        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
        {
            fputs(SDL_GetError(), stderr);

        }

        if (!(window = SDL_CreateWindow("Infinity stone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN))) {
                fputs(SDL_GetError(), stderr);

            }

        if (!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
            fputs(SDL_GetError(), stderr);

        }

        



        //SDL_Texture *soldier_texture = IMG_LoadTexture(ren,"");
       SDL_Texture *background  = IMG_LoadTexture(ren, "../background.jpg");
       SDL_Texture *knight_texture = IMG_LoadTexture(ren,"../knight.jpg");
       SDL_Texture *enemie_texture = IMG_LoadTexture(ren,"../enemy.jpg");

        SDL_Rect *background_rect = NULL;
        SDL_Rect *knight_rect = NULL;
        SDL_Rect *enemie_rect = NULL;



        Character knight;
        knight.x = 20
        ;
        knight.y = 200;

        knight.texture = knight_texture;
        knight.hp = 1;

        Character enemie;
        enemie.x = 500;
        enemie.y = 200;
        enemie.texture = enemie_texture;
        enemie.hp = 1;
        


        bool quit = false;
          while(!quit)
          {




              while (SDL_PollEvent(&ev)) {

                  switch (ev.type)
                  {
                      case SDL_QUIT:
                          quit = true;
                          break;

                      case SDL_KEYDOWN:

                          do_key_down(&ev.key);

                          break;

                      case SDL_KEYUP:
                          do_key_up(&ev.key);
                          break;

                      default:
                          break;
                  }


              }

            SDL_RenderClear(ren);
            background_rect =  draw_texture(&ren ,background , 0,0);
          enemie_rect = draw_texture(&ren,enemie.texture, enemie.x, enemie.y);
           knight_rect = draw_texture(&ren , knight.texture , knight.x , enemie.y);
            SDL_RenderPresent(ren);
            free(enemie_rect);
            free(knight_rect);
            free(background_rect);
          }




}







int main(int argc , char * argv [])

{
    (void)argc;
    (void)argv;

   level1();
return 0;

}


void do_key_up(SDL_KeyboardEvent *event )
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            keys.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            keys.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            keys.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            keys.right = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            keys.shoot = false;
        }



    }
}


void do_key_down(SDL_KeyboardEvent *event)
{



    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_F1)
        {
            keys.start = true;

        }

        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            keys.up = 1;

        }

        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            keys.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            keys.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            keys.right = 1;
        }

        if(event->keysym.scancode == SDL_SCANCODE_SPACE)
        {

            keys.shoot = true;
        }




    }
}

SDL_Rect *draw_texture(SDL_Renderer **renderer, SDL_Texture *texture, int x, int y)
{

	

    SDL_Rect *rect = malloc(sizeof(rect));

    rect->x = x;
    rect->y = y;
    rect->w = 0;
    rect->h = 0;

    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);

    SDL_RenderCopy(*renderer, texture, NULL, rect);
    return rect;
}












