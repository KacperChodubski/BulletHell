#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

extern "C" {
#include <SDL.h>
//  #include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define PI				  3.1415
#define FPS_CAP			 60

#define PLAYER_SPEED 5 // pixele na sekunde
#define PLAYER_TIME_BETWEEN_BULLETS 0.2 //sekundy
#define PLAYER_SPEED_OF_BULLETS 6 //pixele na sekunde
#define PLYAER_RELOAD_TIME 0
#define PLAYER_MAGAZINE_CAPACITY 4
#define PLAYER_STARTING_POS_X 100 // pixele
#define PLAYER_STARTING_POS_Y 100 // pixele
#define PLAYER_RANGE 500 //pixele
#define PLAYER_HP 100
#define PLAYER_DMG 20
#define PLAYER_INVULNERABLE_TIME 0.1 // w sekundach

#define NUMBER_OF_ENEMIES 3
#define ENEMY_RELOAD_TIME 20 // w sekundach
#define ENEMY_TIME_BETWEEN_BULLETS 0.5 // w sekundach
#define	ENEMY_SPEED_OF_BULLETS 4 // pixele / sekunde
#define ENEMY_BULLETS_IN_PATTERN 5
#define ENEMY_RANGE 700 // pixele
#define ENEMY_MAGAZINE_CAPACITY 0
#define ENEMY_STARTING_POS_X 400 // pixele od lewego gornego rogu
#define ENEMY_STARTING_POS_Y 400 // pixele od lewego gornego rogu
#define ENEMY_HP 100
#define ENEMY_DMG 10
#define ENEMY_SPEED 0

#define ENEMY2_SPEED 2

#define HUD_OFFSET_X 20 // pixele
#define HUD_OFFSET_Y 32 // pixele


#define LEVEL_HEIGHT 25
#define LEVEL_WIDTH 25


//indexy assetow
#define NUMBER_OF_OBSTACLES 5
#define NUMBER_OF_ASSETS 30
#define SIZE_OF_ONE_TILE 32
#define FLOOR_1 0
#define FLOOR_2 1
#define WALL_MIDDLE 2
#define	WALL_LEFT 3
#define	WALL_RIGHT 4
#define EDGE_BOTTOM_LEFT 5
#define EDGE_BOTTOM_RIGHT 6
#define	EDGE_TOP_LEFT 7
#define	EDGE_TOP_RIGHT 8
#define EDGE_TOP 9
#define EDGE_LEFT 10
#define	EDGE_RIGHT 11
#define FLOOR_3 12
#define FLOOR_4 13
#define FLOOR_5 14
#define FLOOR_6 15

//obraz mapy w oparciu o indexy assetow
int map [LEVEL_HEIGHT][LEVEL_WIDTH] =
        {
                {7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8},
                {10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 15, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 15, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
                {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6}
        };

typedef struct {
    int w;
    int h;
    SDL_Texture* texture;
}texture_t;

typedef struct {
    float pos_x;
    float pos_y;
    float height;
    float width;
}Camera_t;

typedef struct {
    bool active;
    float pos_x;
    float pos_y;
    texture_t tex;
    SDL_Rect destRect;
    SDL_Rect scrRect;
}GameObject;

typedef struct {
    bool active;
    GameObject gameobject;
    float dmg;
    float liveTime;
    float shotTime;
    float speed_x;
    float speed_y;
}bullet_t;

typedef struct {
    float reloadTime;
    float timeBetweenBullets;
    float range;
    float dmg;
    float timeOfLastShot;
    float speedOfBullets;
    int magazineCapacity;
    int maxBullets;
    texture_t bulletTex;
}Volley_t;

typedef struct {
    float speed;
    float hp_max;
    float invulnerableTime;
}statistics_t;

typedef struct {
    int bulletsShooted;
    bool invisible;
    float hp_cur;
    float timeOfBeingHit;
    bool invulnerable;
    int numberOfHits;
    float PlayerCurSpeed_right;
    float PlayerCurSpeed_left;
    float PlayerCurSpeed_up;
    float PlayerCurSpeed_down;
}playerInfo_t;

typedef struct {
    GameObject gameobject;
    Volley_t volleyParametrs;
    bullet_t* ArrOfBullets;
    statistics_t stats;
    playerInfo_t info;
} Player_t;

typedef struct {
    SDL_Surface *Level;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screen, *charset;
    SDL_Texture *scrtex;
}graphic_t;

typedef struct{
    double worldTime;
    double fps;
    int quit;
    bool gameOver;
} GameInfo_t;

typedef struct {
    GameInfo_t GameInfo;
    SDL_Event event;
    graphic_t graphic;
}Game_Handler_t;

typedef struct rob {
    GameObject gameobject;
    Volley_t volley;
    void (*shootingPattern)(rob* enemy);
    bullet_t *ArrOfEnemyBullets;
    int NumberOfBullets;
    float hp_max;
    float hp_cur;
    float speed;
}Enemy_t;

typedef struct {
    texture_t gameOver_tex;
    int hp_ammount;
    texture_t hpFull_tex;
    texture_t hpEmpty_tex;
    int magazine_ammount;
    texture_t magazine_tex;
}HUD_t;


SDL_Surface *assets[NUMBER_OF_ASSETS];
Game_Handler_t game;
Player_t player;
Enemy_t enemies [NUMBER_OF_ENEMIES];
Camera_t camera;
HUD_t HUD;
GameObject *obstacles;



int czarny;
int zielony;
int czerwony;
int niebieski;
int bialy;


//zwolnienie powierzchni SDL
void CleaningSDL ()
{
    SDL_FreeSurface(game.graphic.charset);
    SDL_FreeSurface(game.graphic.screen);
    SDL_DestroyTexture(game.graphic.scrtex);
    SDL_DestroyWindow(game.graphic.window);
    SDL_DestroyRenderer(game.graphic.renderer);
    SDL_Quit();
    game.GameInfo.quit = 1;
}

//Wartosc bezwzgledna z x
float absolut_float (float x)
{
    if (x < 0)
    {
        return -1 * x;
    }
    return x;
}
//Obliczanie dystansu miedzy punktami x1,y1 i x2,y2
float distance (float x1, float y1, float x2, float y2)
{
    float h = y1 - y2;
    float w = x1 - x2;
    h = absolut_float(h);

    w = absolut_float(w);

    return sqrt(h*h + w*w);
}


//Ładowanie textury o danej ściezce
texture_t LoadTexture (const char *file)
{
    SDL_Surface *tempSurface = SDL_LoadBMP(file);
    if (tempSurface == NULL)
    {
        printf("Faild to load file:%s", file);
        CleaningSDL();
        exit (1);
    }
    texture_t tex;
    tex.texture = SDL_CreateTextureFromSurface(game.graphic.renderer, tempSurface);
    tex.w = tempSurface->w;
    tex.h = tempSurface->h;
    SDL_FreeSurface(tempSurface);
    return tex;
}
//tworenie gameobjekt razem z sciezka do texturu
GameObject CreateGameObject (const char *textureFile, float x, float y)
{
    GameObject obj;
    obj.tex = LoadTexture(textureFile);

    obj.pos_x = x;
    obj.pos_y = y;

    obj.scrRect.h = obj.tex.h;
    obj.scrRect.w = obj.tex.w;
    obj.scrRect.x = 0;
    obj.scrRect.y = 0;

    obj.destRect.x = obj.pos_x - obj.tex.w/2;
    obj.destRect.y = obj.pos_y - obj.tex.h/2;
    obj.destRect.h = obj.tex.h;
    obj.destRect.w = obj.tex.w;

    obj.active = true;

    return obj;
}
//tworzenie gameobject o danej texturze
GameObject CreateGameObject (texture_t texture, float x, float y)
{
    GameObject obj;
    obj.tex = texture;

    obj.pos_x = x;
    obj.pos_y = y;

    obj.scrRect.h = obj.tex.h;
    obj.scrRect.w = obj.tex.w;
    obj.scrRect.x = 0;
    obj.scrRect.y = 0;

    obj.destRect.x = obj.pos_x - obj.tex.w/2;
    obj.destRect.y = obj.pos_y - obj.tex.h/2;
    obj.destRect.h = obj.tex.h;
    obj.destRect.w = obj.tex.w/2;

    obj.active = true;

    return obj;
}
//inicjacja gracza
void initPlayer (const char *file, float pos_x, float pos_y)
{
    player.stats.speed = PLAYER_SPEED;
    player.stats.hp_max = player.info.hp_cur = PLAYER_HP;
    player.stats.invulnerableTime = PLAYER_INVULNERABLE_TIME;

    player.volleyParametrs.timeBetweenBullets = PLAYER_TIME_BETWEEN_BULLETS;
    player.volleyParametrs.reloadTime = PLYAER_RELOAD_TIME;
    player.volleyParametrs.speedOfBullets = PLAYER_SPEED_OF_BULLETS;
    player.volleyParametrs.magazineCapacity = PLAYER_MAGAZINE_CAPACITY;
    player.volleyParametrs.maxBullets = (PLAYER_RANGE / PLAYER_SPEED_OF_BULLETS) / PLAYER_TIME_BETWEEN_BULLETS;
    player.volleyParametrs.range = PLAYER_RANGE / FPS_CAP;
    player.volleyParametrs.timeOfLastShot = 0;
    player.volleyParametrs.bulletTex = LoadTexture("./assets/bullet_player.bmp");
    player.volleyParametrs.dmg = PLAYER_DMG;

    player.info.bulletsShooted = 0;
    player.info.numberOfHits = 0;
    player.info.invulnerable = false;
    player.info.invisible = false;

    player.ArrOfBullets = new bullet_t [player.volleyParametrs.maxBullets + 1];

    for (int i = 0; i < player.volleyParametrs.maxBullets + 1; i++)
    {
        player.ArrOfBullets[i].active = false;
    }

    player.gameobject = CreateGameObject(file, pos_x, pos_y);
}
//inicjacja camery
void initCamera ()
{
    camera.pos_x = player.gameobject.pos_x;
    camera.pos_y = player.gameobject.pos_y;
    camera.width = SCREEN_WIDTH;
    camera.height = SCREEN_HEIGHT;
}

// narysowanie napisu txt na powierzchni screen, zaczynaj�c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj�ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while(*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};
//Rysowanie levelu w miejscu o wspolrzedych x i y
//liczonych od lewego gornego rogu
void DrawLevel (SDL_Surface *screen, SDL_Surface *Level)
{
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.h = SCREEN_HEIGHT;
    dest.w = SCREEN_WIDTH;


    SDL_Rect FragmentOfLevel;

    FragmentOfLevel.h = camera.height;
    FragmentOfLevel.w = camera.width;
    FragmentOfLevel.x = camera.pos_x - camera.width/2;
    FragmentOfLevel.y = camera.pos_y - camera.height/2;

    SDL_BlitSurface(game.graphic.Level, &FragmentOfLevel, game.graphic.screen, &dest);

}
//Rysowanie obrazka od jego lewego gornego rogu
void DrawSurfaceCorner (SDL_Surface *screen, SDL_Surface *sprite, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
}
// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32 *)p = color;
};


// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1)
// b�d� poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for(int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};


// rysowanie prostok�ta o d�ugo�ci bok�w l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for(i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

//renderowanie objektu jezeli jest w zasiegu camery
void RenderObject (GameObject obj)
{
    float disFromCamera_x = camera.pos_x - obj.pos_x;
    float disFromCamera_y = camera.pos_y - obj.pos_y;
    if (absolut_float(disFromCamera_x) <= camera.width/2 && absolut_float(disFromCamera_y) <= camera.height/2 && obj.active)
    {
        obj.destRect.x = camera.width/2  - disFromCamera_x - obj.scrRect.w/2;
        obj.destRect.y = camera.height/2 - disFromCamera_y - obj.scrRect.h/2;

        SDL_RenderCopy(game.graphic.renderer, obj.tex.texture, &obj.scrRect, &obj.destRect);
    }
//renderowanie objektu jezeli jest w zasiegu kamery pod danym katem (stopnie)
}
void RenderObjectAngle (GameObject obj, double angle)
{
    float disFromCamera_x = camera.pos_x - obj.pos_x;
    float disFromCamera_y = camera.pos_y - obj.pos_y;
    if (absolut_float(disFromCamera_x) <= camera.width/2 && absolut_float(disFromCamera_y) <= camera.height/2 && obj.active)
    {
        obj.destRect.x = camera.width/2  - disFromCamera_x - obj.scrRect.w/2;
        obj.destRect.y = camera.height/2 - disFromCamera_y - obj.scrRect.h/2;


        SDL_RenderCopyEx(game.graphic.renderer, obj.tex.texture, &obj.scrRect, &obj.destRect, angle, NULL, SDL_FLIP_NONE);

    }
}

//Obliczanie dystansu miedzy środkami hitboxow i badanie czy doszło do przecięcia okręgow
bool CheckingCollisions(GameObject A, GameObject B)
{
    if
            (
            A.pos_x + A.scrRect.w/2 >= B.pos_x - B.scrRect.w/2 &&
            B.pos_x + B.scrRect.w/2 >= A.pos_x - A.scrRect.w/2 &&
            A.pos_y + A.scrRect.h/2 >= B.pos_y - B.scrRect.h/2 &&
            B.pos_y + B.scrRect.h/2 >= A.pos_y - A.scrRect.h/2 &&
            B.active && A.active
            )
    {
        return 1;
    }
    return 0;
}

//obsluga trafienia playera
void playerHit (bullet_t *bullet)
{
    if (!player.info.invulnerable)
    {
        bullet->active = false;
        player.info.hp_cur -= bullet->dmg;
        player.info.invulnerable = true;
        player.info.timeOfBeingHit = game.GameInfo.worldTime;
    }
}

//przesuwanie bulletow przeciwnika
void MovingBullets (Enemy_t* enemy)
{

    for (int i = 0; i < enemy->volley.maxBullets; i++)
    {
        bullet_t* bullet = &enemy->ArrOfEnemyBullets[i];
        if (bullet->active)
        {
            bullet->gameobject.pos_x += bullet->speed_x;
            bullet->gameobject.pos_y += bullet->speed_y;

            if (CheckingCollisions(bullet->gameobject, player.gameobject))
            {
                playerHit(bullet);
            }
            if (game.GameInfo.worldTime - bullet->shotTime >= bullet->liveTime)
            {
                bullet->active = false;
            }
        }
    }

}

//przesuwanie bulletow playera
void MovingBullets (Player_t* player)
{
    for (int i = 0; i < player->volleyParametrs.maxBullets; i++)
    {
        bullet_t* bullet = &player->ArrOfBullets[i];
        if (bullet->active)
        {
            bullet->gameobject.pos_x += bullet->speed_x;
            bullet->gameobject.pos_y += bullet->speed_y;
            for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
            {
                Enemy_t *enemy = &enemies[i];
                if (CheckingCollisions(bullet->gameobject, enemy->gameobject))
                {
                    bullet->active = false;
                    enemy->hp_cur -= bullet->dmg;
                    player->info.numberOfHits++;
                }
                if (game.GameInfo.worldTime - bullet->shotTime >= bullet->liveTime)
                {
                    bullet->active = false;
                }
            }
        }
    }
}

//renderowanie bulletow przeciwnika
void RenderingBullets (Enemy_t *enemy)
{
    if (enemy->gameobject.active)
    {
        for (int i = 0; i < enemy->volley.maxBullets; i++)
        {
            bullet_t bulletToRender = enemy->ArrOfEnemyBullets[i];
            if (bulletToRender.active)
            {
                float x = bulletToRender.speed_x;
                float y = bulletToRender.speed_y;
                double z = sqrt(x*x + y*y);

                double angleRad = PI/2 + asin(y/z);
                double angleDeg = angleRad * 360 / (2 * PI);
                if (bulletToRender.speed_x < 0)
                {
                    angleDeg *= -1;
                }
                RenderObjectAngle(bulletToRender.gameobject, angleDeg);
            }
        }
    }
}

//renderowanie bulletow playera
void RenderingBullets (Player_t* player)
{
    for (int i = 0; i < player->volleyParametrs.maxBullets; i++)
    {
        bullet_t bulletToRender = player->ArrOfBullets[i];
        if (bulletToRender.active)
        {
            float x = bulletToRender.speed_x;
            float y = bulletToRender.speed_y;
            double z = sqrt(x*x + y*y);

            double angleRad = PI/2 + asin(y/z);
            double angleDeg = angleRad * 360 / (2 * PI);
            if (bulletToRender.speed_x < 0)
            {
                angleDeg *= -1;
            }
            RenderObjectAngle(bulletToRender.gameobject, angleDeg);
        }
    }
}

//tworzenie objektu bulleta z predkocia w odpowiednim kierunku
bullet_t CreatingPlayerBullet()
{
    float x = player.gameobject.pos_x;
    float y = player.gameobject.pos_y;

    bullet_t bullet;
    bullet.active = true;
    bullet.gameobject = CreateGameObject(player.volleyParametrs.bulletTex, x, y);
    bullet.speed_y = 0;
    bullet.speed_x = 0;
    bullet.liveTime = player.volleyParametrs.range / player.volleyParametrs.speedOfBullets;
    bullet.shotTime = game.GameInfo.worldTime;
    bullet.dmg = player.volleyParametrs.dmg;

    if (player.info.PlayerCurSpeed_left > 0)
    {
        bullet.speed_x = -1 * player.volleyParametrs.speedOfBullets;
    }
    if (player.info.PlayerCurSpeed_right > 0)
    {
        bullet.speed_x = player.volleyParametrs.speedOfBullets;
    }
    if (player.info.PlayerCurSpeed_up > 0)
    {
        bullet.speed_y = -1 * player.volleyParametrs.speedOfBullets;
    }
    if (player.info.PlayerCurSpeed_down > 0)
    {
        bullet.speed_y = player.volleyParametrs.speedOfBullets;
    }
    if (player.info.PlayerCurSpeed_up + player.info.PlayerCurSpeed_right + player.info.PlayerCurSpeed_left + player.info.PlayerCurSpeed_down == 0)
    {
        bullet.speed_x = player.volleyParametrs.speedOfBullets;
    }

    return bullet;
}

//obsuga strzelania przez gracza
void PlayerShooting ()
{
    int maxBullets = player.volleyParametrs.maxBullets;
    float time = game.GameInfo.worldTime;

    if (player.info.bulletsShooted != maxBullets && player.info.bulletsShooted != player.volleyParametrs.magazineCapacity)
    {

        if (time - player.volleyParametrs.timeOfLastShot >= player.volleyParametrs.timeBetweenBullets)
        {
            player.volleyParametrs.timeOfLastShot = time;
            player.ArrOfBullets[player.info.bulletsShooted] = CreatingPlayerBullet();
            player.info.bulletsShooted++;
        }

    }
}

//pattern strzelania na okolo
void CirShooting (Enemy_t *enemy)
{
    int bulletsInPattern = 1;
    Volley_t volleyParametrs = enemy->volley;
    float speed_x;
    float speed_y;
    static double angle = 0;

    speed_x = cos(angle) * volleyParametrs.speedOfBullets;
    speed_y = sin(angle) * volleyParametrs.speedOfBullets;
    angle = (angle + PI/18);

    if (angle > 2 * PI)
    {
        angle -= 2*PI;
    }

    bullet_t curBullet;
    curBullet.gameobject = CreateGameObject(volleyParametrs.bulletTex, enemy->gameobject.pos_x, enemy->gameobject.pos_y);
    curBullet.gameobject.pos_x = enemy->gameobject.pos_x;
    curBullet.gameobject.pos_y = enemy->gameobject.pos_y;
    curBullet.speed_x = speed_x;
    curBullet.speed_y = speed_y;
    curBullet.active = true;
    curBullet.shotTime = game.GameInfo.worldTime;
    curBullet.liveTime = volleyParametrs.range / (volleyParametrs.speedOfBullets);
    curBullet.dmg = volleyParametrs.dmg;
    enemy->ArrOfEnemyBullets[enemy->NumberOfBullets] = curBullet;
    enemy->NumberOfBullets += bulletsInPattern;
}

//pattern strzelania falami po 5 pociskow w strone playera
void WaveShooting (Enemy_t *enemy)
{
    int bulletsInPattern = 5;
    Volley_t volleyParametrs = enemy->volley;
    float angleBetweenBullets = PI/15;

    for (int i = 0; i < bulletsInPattern; i++)
    {
        float x = enemy->gameobject.pos_x - player.gameobject.pos_x;
        float y = enemy->gameobject.pos_y - player.gameobject.pos_y;
        float speed_x;
        float speed_y;
        double z = sqrt(x*x + y*y);

        double angle = acos(x/z) + PI;

        if (y < 0)
        {
            angle *= -1;
        }

        angle = angle - (i - bulletsInPattern/2) * angleBetweenBullets;

        speed_x = cos(angle) * volleyParametrs.speedOfBullets;
        speed_y = sin(angle) * volleyParametrs.speedOfBullets;
        bullet_t curBullet;
        curBullet.gameobject = CreateGameObject(volleyParametrs.bulletTex, enemy->gameobject.pos_x, enemy->gameobject.pos_y);
        curBullet.gameobject.pos_x = enemy->gameobject.pos_x;
        curBullet.gameobject.pos_y = enemy->gameobject.pos_y;
        curBullet.speed_x = speed_x;
        curBullet.speed_y = speed_y;
        curBullet.active = true;
        curBullet.shotTime = game.GameInfo.worldTime;
        curBullet.liveTime = volleyParametrs.range / (volleyParametrs.speedOfBullets);
        curBullet.dmg = volleyParametrs.dmg;
        enemy->ArrOfEnemyBullets[enemy->NumberOfBullets] = curBullet;
        enemy->NumberOfBullets++;

    }

}

//pattern strzelania pojedynczego pocisku w strone gracza
void DirectShooting (Enemy_t *enemy)
{
    int bulletsInPattern = 5;
    Volley_t volleyParametrs = enemy->volley;
    float angleBetweenBullets = PI/10;


    float x = enemy->gameobject.pos_x - player.gameobject.pos_x;
    float y = enemy->gameobject.pos_y - player.gameobject.pos_y;
    float speed_x;
    float speed_y;
    double z = sqrt(x*x + y*y);

    double angle = acos(x/z) + PI;

    if (y < 0)
    {
        angle *= -1;
    }



    speed_x = cos(angle) * volleyParametrs.speedOfBullets;
    speed_y = sin(angle) * volleyParametrs.speedOfBullets;
    bullet_t curBullet;
    curBullet.gameobject = CreateGameObject(volleyParametrs.bulletTex, enemy->gameobject.pos_x, enemy->gameobject.pos_y);
    curBullet.gameobject.pos_x = enemy->gameobject.pos_x;
    curBullet.gameobject.pos_y = enemy->gameobject.pos_y;
    curBullet.speed_x = speed_x;
    curBullet.speed_y = speed_y;
    curBullet.active = true;
    curBullet.shotTime = game.GameInfo.worldTime;
    curBullet.liveTime = volleyParametrs.range / (volleyParametrs.speedOfBullets);
    curBullet.dmg = volleyParametrs.dmg;
    enemy->ArrOfEnemyBullets[enemy->NumberOfBullets] = curBullet;
    enemy->NumberOfBullets++;



}

//obsuga strzelania przez przeciwnika
void shooting(Enemy_t* enemy)
{

    float x = enemy->gameobject.pos_x;
    float y = enemy->gameobject.pos_y;

    float time = game.GameInfo.worldTime;

    if (time - enemy->volley.timeOfLastShot >= enemy->volley.timeBetweenBullets)
    {
        enemy->shootingPattern(enemy);
        enemy->volley.timeOfLastShot = time;
    }
    if (enemy->NumberOfBullets >= enemy->volley.maxBullets)
    {
        enemy->NumberOfBullets = 0;
    }

}

//inicjacja HUDu
void initHud ()
{
    HUD.hpFull_tex = LoadTexture("./assets/hp_full.bmp");
    HUD.hpEmpty_tex = LoadTexture("./assets/hp_empty.bmp");
    HUD.magazine_tex = LoadTexture("./assets/bm.bmp");
    HUD.gameOver_tex = LoadTexture("./assets/game_over.bmp");
}

//renderowanie HUDu
void renderHUD()
{
    SDL_Rect destHp, destBm, destGO;
    destHp.x = HUD_OFFSET_X;
    destHp.y = SCREEN_HEIGHT - HUD_OFFSET_Y;
    destHp.w = HUD.hpFull_tex.w;
    destHp.h = HUD.hpFull_tex.h;

    destBm.h = HUD.magazine_tex.h;
    destBm.w = HUD.magazine_tex.w;
    destBm.x = HUD_OFFSET_X;
    destBm.y = destHp.y - destBm.h;

    destGO.x = SCREEN_WIDTH/2- HUD.gameOver_tex.w/2;
    destGO.y = SCREEN_HEIGHT/2 - HUD.gameOver_tex.h/2;
    destGO.h = HUD.gameOver_tex.h;
    destGO.w = HUD.gameOver_tex.w;

    for (int i = 0; i < player.stats.hp_max; i+=10)
    {
        if(i < player.info.hp_cur)
        {
            SDL_RenderCopy(game.graphic.renderer, HUD.hpFull_tex.texture, NULL, &destHp);
        }
        else
        {
            SDL_RenderCopy (game.graphic.renderer, HUD.hpEmpty_tex.texture, NULL, &destHp);
        }
        destHp.x += destHp.w;
    }
    for (int i = 0; i < player.volleyParametrs.magazineCapacity - player.info.bulletsShooted; i++)
    {
        SDL_RenderCopy(game.graphic.renderer, HUD.magazine_tex.texture, NULL, &destBm);
        destBm.x += destBm.w;
    }
    if (game.GameInfo.gameOver)
    {
        SDL_RenderCopy(game.graphic.renderer, HUD.gameOver_tex.texture, NULL, &destGO);
    }
}

//renderowanie przeszkod
void renderObstacles ()
{
    for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
    {
        RenderObject(obstacles[i]);
    }
}

//Nanoszenie obrazkow na level
bool BuildBoard ()
{
    SDL_FillRect(game.graphic.Level, NULL, czarny);

    bool loadError = 0;


    for (int i = 0; i < LEVEL_HEIGHT; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            int index_of_tile = map[i][j];
            DrawSurfaceCorner(game.graphic.Level, assets[index_of_tile], j*SIZE_OF_ONE_TILE, i*SIZE_OF_ONE_TILE);
        }
    }

    return !loadError;
}


//import assetow
void importBMP ()
{

    game.graphic.charset = SDL_LoadBMP("./cs8x8.bmp");
    if(game.graphic.charset == NULL)
    {
        CleaningSDL();
    }
    SDL_SetColorKey(game.graphic.charset, true, 0x000000);

    assets[FLOOR_1] = SDL_LoadBMP("./assets/floor_1.bmp");
    assets[FLOOR_2] = SDL_LoadBMP("./assets/floor_2.bmp");
    assets[WALL_MIDDLE] = SDL_LoadBMP("./assets/wall_middle.bmp");
    assets[WALL_LEFT] = SDL_LoadBMP("./assets/wall_left.bmp");
    assets[WALL_RIGHT] = SDL_LoadBMP("./assets/wall_right.bmp");
    assets[EDGE_BOTTOM_LEFT] = SDL_LoadBMP("./assets/edge_bottom_left.bmp");
    assets[EDGE_BOTTOM_RIGHT] = SDL_LoadBMP("./assets/edge_bottom_right.bmp");
    assets[EDGE_TOP_LEFT] = SDL_LoadBMP("./assets/edge_top_left.bmp");
    assets[EDGE_TOP_RIGHT] = SDL_LoadBMP("./assets/edge_top_right.bmp");
    assets[EDGE_TOP] = SDL_LoadBMP("./assets/edge_top.bmp");
    assets[EDGE_LEFT] = SDL_LoadBMP("./assets/edge_left.bmp");
    assets[EDGE_RIGHT] = SDL_LoadBMP("./assets/edge_right.bmp");
    assets[FLOOR_3] = SDL_LoadBMP("./assets/floor_3.bmp");
    assets[FLOOR_4] = SDL_LoadBMP("./assets/floor_4.bmp");
    assets[FLOOR_5] = SDL_LoadBMP("./assets/floor_5.bmp");
    assets[FLOOR_6] = SDL_LoadBMP("./assets/floor_6.bmp");


    for (int i = 0; i < EDGE_RIGHT; i++)
    {
        if (assets[i] == NULL)
        {
            printf("load error\n");
            CleaningSDL();
        }
    }

}

//obsuga kolizji z obiektu z przeszkoda
bool collisionWithObstacles (GameObject obj)
{
    bool collison = false;

    for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
    {
        if (CheckingCollisions(obstacles[i], obj))
        {
            collison = true;
        }
    }
    return collison;
}


//Obsługa ruchu gracza
void PlayerMovement ()
{
    GameObject playerPostMovement = player.gameobject;
    playerPostMovement.pos_y = player.gameobject.pos_y + (player.info.PlayerCurSpeed_down - player.info.PlayerCurSpeed_up);
    playerPostMovement.pos_x = player.gameobject.pos_x + (player.info.PlayerCurSpeed_right - player.info.PlayerCurSpeed_left);

    if (!collisionWithObstacles(playerPostMovement))
    {
        if (playerPostMovement.pos_y + player.gameobject.scrRect.h/2 <= game.graphic.Level->h && playerPostMovement.pos_y - player.gameobject.scrRect.h/2 >= 0)
        {
            player.gameobject.pos_y = playerPostMovement.pos_y;
        }
        if (playerPostMovement.pos_x + player.gameobject.scrRect.w/2 <= game.graphic.Level->w && playerPostMovement.pos_x - player.gameobject.scrRect.w/2 >= 0)
        {
            player.gameobject.pos_x = playerPostMovement.pos_x;
        }
    }



    //ustawienie kamery gracza tak zeby nie wychodzila po za mape po X
    if (player.gameobject.pos_x + camera.width/2 < game.graphic.Level->w && player.gameobject.pos_x - camera.width/2 > 0)
    {
        camera.pos_x = player.gameobject.pos_x;
    }
    else if (player.gameobject.pos_x + camera.width/2 >= game.graphic.Level->w)
    {
        camera.pos_x = game.graphic.Level->w - camera.width/2;
    }
    else
    {
        camera.pos_x = camera.width/2;
    }

    //ustawienie kamery gracza tak zeby nie wychodzila po za mape po Y
    if (player.gameobject.pos_y + camera.height/2 < game.graphic.Level->h && player.gameobject.pos_y - camera.height/2 > 0)
    {
        camera.pos_y = player.gameobject.pos_y;
    }
    else if (player.gameobject.pos_y + camera.height/2  >= game.graphic.Level->h)
    {
        camera.pos_y = game.graphic.Level->h - camera.height/2;
    }
    else
    {
        camera.pos_y = camera.height/2;
    }

}

//aktualizowanie playera
void UpdatePlayer ()
{
    PlayerMovement();
    MovingBullets(&player);
    float time = game.GameInfo.worldTime;
    if
            (
            player.info.bulletsShooted == player.volleyParametrs.maxBullets ||
            (
                    time - player.volleyParametrs.timeOfLastShot >= player.volleyParametrs.reloadTime &&
                    player.info.bulletsShooted == player.volleyParametrs.magazineCapacity
            )

            )
    {
        player.info.bulletsShooted = 0;
    }
    if (player.info.hp_cur <= 0)
    {
        player.gameobject.active = false;
        game.GameInfo.gameOver = true;
    }
    static int delay = 0;
    const int fadingFrames = 6;
    if (player.info.invulnerable && (++delay %= fadingFrames) == 0)
    {
        player.info.invisible = !player.info.invisible;
    }
    if (time - player.info.timeOfBeingHit >= player.stats.invulnerableTime)
    {
        player.info.invulnerable = false;
        player.info.invisible = false;
        delay = 0;
    }
}

//obsuga ruchu przeciwnika
void MovingEnemy (Enemy_t *enemy)
{
    float x = enemy->gameobject.pos_x - player.gameobject.pos_x;
    float y = enemy->gameobject.pos_y - player.gameobject.pos_y;
    float speed_x;
    float speed_y;
    double z = sqrt(x*x + y*y);

    double angle = acos(x/z) + PI;

    if (y < 0)
    {
        angle *= -1;
    }



    speed_x = cos(angle) * enemy->speed;
    speed_y = sin(angle) * enemy->speed;

    enemy->gameobject.pos_x += speed_x;
    enemy->gameobject.pos_y +=speed_y;

}

//aktualizacja aktywnego przeciwnika
void UpdateEnemies ()
{
    int activeEnemy = 0;
    while (activeEnemy < NUMBER_OF_ENEMIES && enemies[activeEnemy].gameobject.active == false)
    {
        activeEnemy++;
    }
    Enemy_t *enemy = &enemies[activeEnemy];
    if (enemy->hp_cur <= 0)
    {
        enemy->gameobject.active = false;
        if (activeEnemy < NUMBER_OF_ENEMIES)
        {
            enemies[++activeEnemy].gameobject.active = true;
        }
    }
    if (enemy->gameobject.active)
    {
        shooting(enemy);
        MovingBullets(enemy);
        MovingEnemy(enemy);
    }

}

//inicjowanie przeciwnika
Enemy_t initEnemy (const char* file, float x, float y)
{
    Enemy_t enemy;
    enemy.gameobject= CreateGameObject(file, x, y);
    enemy.gameobject.active = true;

    enemy.hp_max = enemy.hp_cur = ENEMY_HP;
    enemy.volley.reloadTime = ENEMY_RELOAD_TIME;
    enemy.volley.timeBetweenBullets = ENEMY_TIME_BETWEEN_BULLETS;
    enemy.volley.timeOfLastShot = 0;
    enemy.volley.speedOfBullets = ENEMY_SPEED_OF_BULLETS;
    enemy.volley.magazineCapacity = ENEMY_MAGAZINE_CAPACITY;
    enemy.volley.range = ENEMY_RANGE / FPS_CAP;
    enemy.volley.dmg = ENEMY_DMG;
    enemy.shootingPattern = DirectShooting;
    enemy.volley.bulletTex = LoadTexture("./assets/bullet_enemy.bmp");

    enemy.volley.maxBullets = ((ENEMY_RANGE / ENEMY_SPEED_OF_BULLETS) / ENEMY_TIME_BETWEEN_BULLETS) * ENEMY_BULLETS_IN_PATTERN;
    enemy.ArrOfEnemyBullets = new bullet_t [enemy.volley.maxBullets + 1];
    enemy.speed = ENEMY_SPEED;

    for (int i = 0; i < enemy.volley.maxBullets; i++)
    {
        enemy.ArrOfEnemyBullets[i].active = false;
    }

    enemy.NumberOfBullets = 0;

    return enemy;
}

//inicjowanie przeszkow
void initObstacles()
{
    obstacles = new GameObject[NUMBER_OF_OBSTACLES];

    obstacles[0] = CreateGameObject ("./assets/boxes.bmp", 200, 100);
    obstacles[1] = CreateGameObject ("./assets/boxes.bmp", 300, 100);
    obstacles[2] = CreateGameObject ("./assets/boxes.bmp", 500, 100);
    obstacles[3] = CreateGameObject ("./assets/boxes.bmp", 100, 300);
}

//inicjowanie calej gry
void InitGame ()
{
    const char *title = "Studing in my mind";
    printf("wyjscie printfa trafia do tego okienka\n");
    printf("printf output goes here\n");

    Uint32 flags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        game.graphic.window = SDL_CreateWindow(title, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
        game.graphic.renderer = SDL_CreateRenderer(game.graphic.window, 0, 0);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawColor(game.graphic.renderer, 0, 0, 0, 255);

    game.graphic.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                               0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    game.graphic.scrtex = SDL_CreateTexture(game.graphic.renderer, SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            SCREEN_WIDTH, SCREEN_HEIGHT);
    // wy��czenie widoczno�ci kursora myszy
    SDL_ShowCursor(SDL_DISABLE);
    czarny = SDL_MapRGB(game.graphic.screen->format, 0x00, 0x00, 0x00);
    zielony = SDL_MapRGB(game.graphic.screen->format, 0x00, 0xFF, 0x00);
    czerwony = SDL_MapRGB(game.graphic.screen->format, 0xFF, 0x00, 0x00);
    niebieski = SDL_MapRGB(game.graphic.screen->format, 0x11, 0x11, 0xCC);
    bialy = SDL_MapRGB(game.graphic.screen->format, 0xFF, 0xFF, 0xFF);

    game.GameInfo.quit = 0;
    game.GameInfo.worldTime = 0;
    game.GameInfo.gameOver = false;

    game.graphic.Level = SDL_CreateRGBSurface(0, LEVEL_WIDTH * SIZE_OF_ONE_TILE,
                                              LEVEL_HEIGHT * SIZE_OF_ONE_TILE,
                                              32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    importBMP();
    BuildBoard();
    initPlayer("./assets/hero.bmp", PLAYER_STARTING_POS_X, PLAYER_STARTING_POS_Y);
    initCamera ();

    enemies[0] = initEnemy("./assets/enemy.bmp", ENEMY_STARTING_POS_X, ENEMY_STARTING_POS_Y);
    enemies[0].shootingPattern = CirShooting;
    enemies[1] = initEnemy("./assets/enemy_2.bmp", ENEMY_STARTING_POS_X, ENEMY_STARTING_POS_Y);
    enemies[1].shootingPattern = WaveShooting;
    enemies[1].gameobject.active = false;
    enemies[2] = initEnemy("./assets/enemy_3.bmp", ENEMY_STARTING_POS_X, ENEMY_STARTING_POS_Y);
    enemies[2].shootingPattern = DirectShooting;
    enemies[2].gameobject.active = false;
    enemies[2].speed = ENEMY2_SPEED;

    initHud();
    initObstacles();
}

//obsługa zdarzeń
void handleEvents ()
{
    while(SDL_PollEvent(&game.event)) {
        SDL_Event event = game.event;
        SDL_Keycode KeyEvent = event.key.keysym.sym;
        switch(event.type) {
            case SDL_KEYDOWN:
                if (KeyEvent == SDLK_ESCAPE) game.GameInfo.quit = 1;
                if (KeyEvent == SDLK_UP) player.info.PlayerCurSpeed_up = player.stats.speed;
                if (KeyEvent == SDLK_DOWN) player.info.PlayerCurSpeed_down = player.stats.speed;
                if (KeyEvent == SDLK_RIGHT) player.info.PlayerCurSpeed_right = player.stats.speed;
                if (KeyEvent == SDLK_LEFT) player.info.PlayerCurSpeed_left = player.stats.speed;
                if (KeyEvent == SDLK_SPACE) PlayerShooting();
                if (KeyEvent == SDLK_n) InitGame();
                if (KeyEvent == SDLK_0)
                {
                    printf("Player: y:%f,x:%f, HP:%f\n", player.gameobject.pos_y, player.gameobject.pos_x, player.info.hp_cur);
                    printf("Enemy: x:%f, y:%f, HP:%f\n", enemies[0].gameobject.pos_x, enemies[0].gameobject.pos_y, enemies[0].hp_cur);
                    //printf ("bullet: x:%f, y:%f\n", game.GameInfo.BulletsOnBoard[0].gameobject.pos_x, game.GameInfo.BulletsOnBoard[0].gameobject.pos_x);
                }
                break;
            case SDL_KEYUP:
                if (KeyEvent == SDLK_UP) player.info.PlayerCurSpeed_up= 0;
                if (KeyEvent == SDLK_DOWN) player.info.PlayerCurSpeed_down = 0;
                if (KeyEvent == SDLK_RIGHT) player.info.PlayerCurSpeed_right = 0;
                if (KeyEvent == SDLK_LEFT) player.info.PlayerCurSpeed_left = 0;
                break;
            case SDL_QUIT:
                game.GameInfo.quit = 1;
                break;
        };

    }
}


//aktualizacja calej gry
void Update ()
{
    DrawLevel(game.graphic.screen, game.graphic.Level);
    UpdatePlayer();
    UpdateEnemies ();

    char text[128];
    // tekst informacyjny / info text
    DrawRectangle(game.graphic.screen, 4, 4, SCREEN_WIDTH / 2, 36, bialy, czarny);
    //            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
    sprintf(text, "Czas gry = %.1lf s  %.0lf klatek / s", game.GameInfo.worldTime, game.GameInfo.fps);
    DrawString(game.graphic.screen, 8, 10, text, game.graphic.charset);
    //	      "Esc - exit, \030 - faster, \031 - slower"
    sprintf(text, "Esc - wyjscie");
    DrawString(game.graphic.screen, 8, 26, text, game.graphic.charset);
    if (game.GameInfo.worldTime >= 12)
    {
        enemies[0].shootingPattern = DirectShooting;
    }

}

//renderowanie obiektow na ekran
void Render ()
{
    SDL_RenderClear(game.graphic.renderer);

    SDL_UpdateTexture(game.graphic.scrtex, NULL, game.graphic.screen->pixels, game.graphic.screen->pitch);
    SDL_RenderCopy(game.graphic.renderer, game.graphic.scrtex, NULL, NULL);
    for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        RenderingBullets(&enemies[i]);
    }
    RenderingBullets(&player);

    if (!player.info.invisible)
    {
        RenderObject(player.gameobject);
    }



    for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        RenderObject(enemies[i].gameobject);
    }
    renderObstacles();
    renderHUD();

    SDL_RenderPresent(game.graphic.renderer);
}



// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {

    int t1, t2;
    int frames = 0, rc;
    double fpsTimer = 0, delta = 0;

    InitGame();

    t1 = SDL_GetTicks();

    while(!game.GameInfo.quit) {
        t2 = SDL_GetTicks();

        // w tym momencie t2-t1 to czas w milisekundach,
        // jaki uplyna� od ostatniego narysowania ekranu
        // delta to ten sam czas w sekundach
        // here t2-t1 is the time in milliseconds since
        // the last screen was drawn
        // delta is the same time in seconds
        delta = (t2 - t1) * 0.001;
        t1 = t2;

        game.GameInfo.worldTime += delta;

        fpsTimer += delta;
        if(fpsTimer > 0.5) {
            game.GameInfo.fps = frames * 2;
            frames = 0;
            fpsTimer -= 0.5;
        };


        handleEvents();
        if (!game.GameInfo.gameOver)
        {
            Update();
        }
        Render();

        frames++;

        SDL_Delay(1000/FPS_CAP);
    }

    // zwolnienie powierzchni / freeing all surfaces
    CleaningSDL();



    return 0;
}




