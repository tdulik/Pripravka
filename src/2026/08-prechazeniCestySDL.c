#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum { NAKLADNI, OSOBNI, SANITKA, POPELAR, CLOVEK, DOLAR } tTypObjektu;
typedef struct {
    int x, y, w, h;
    int dx, dy;
    tTypObjektu typ;
    bool aktivni;
    int r, g, b;     // Barva objektu
} tGrafickyObjekt;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
#define MAX_AUT 40
#define POCET_PRUHU 4
#define SILNICE_Y1 160
#define SILNICE_Y2 440
// Globální proměnná pro kreslení
SDL_Renderer *renderer = NULL;
/* ================================================================
   ZÁKLADNÍ KRESLICÍ FUNKCE
   ================================================================ */
void nakresli_kruh(int x, int y, float radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    double pi = 3.14159265359;
    int precision = 40;
    double step = pi / (double) (precision - 1);
    for (int i = 0; i < precision; i++) {
        float x1 = cos(-i * step) * radius + x;
        float y1 = sin(-i * step) * radius + y;
        float x2 = cos(i * step) * radius + x;
        float y2 = sin(i * step) * radius + y;
        SDL_RenderDrawLine(renderer, (int) x1, (int) y1, (int) x2, (int) y2);
    }
}
void nakresli_blok(int x, int y, int sirka, int vyska, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = {x, y, sirka, vyska};
    SDL_RenderFillRect(renderer, &rect);
}

void nakresli_vozidlo(tGrafickyObjekt *a) {
    int x = a->x;
    int y = a->y;
    int w = a->w;
    int h = a->h;
    int radius = h / 5; //poloměr kol
    switch (a->typ) {
        case OSOBNI:
            // doplňte váš kód
            break;
        case NAKLADNI:
            // doplňte váš kód
            break;
        case POPELAR:
            // doplňte váš kód
            break;
        case SANITKA:
            // doplňte váš kód
            break;
        default: break;
    }
    //Tento řádek smažte - je to "dummy" generické tělo vozidla:
    nakresli_blok(x, y + 5, w, h-12, 240, 240, 240);
    /* Kola mají všechna vozidla stejná */
    nakresli_kruh(x + w / 5, y + h - 5, radius, 25, 25, 25);
    nakresli_kruh(x + w * 4 / 5, y + h - 5, radius, 25, 25, 25);
    nakresli_kruh(x + w / 5, y + h - 5, radius / 2, 160, 160, 160);
    nakresli_kruh(x + w * 4 / 5, y + h - 5, radius / 2, 160, 160, 160);
}

void nakresli_cloveka(tGrafickyObjekt *c) {
    int x = c->x;
    int y = c->y;
    // hlava
    nakresli_kruh(x + c->w / 2, y + 7, 7, 255, 210, 160);
    // tělo
    nakresli_blok(x + 6, y + 14, c->w - 12, 13, 40, 100, 255);
    // nohy
    nakresli_blok(x + 6, y + 27, 5, c->h - 27, 30, 30, 80);
    nakresli_blok(x + c->w - 11, y + 27, 5, c->h - 27, 30, 30, 80);
}

void nakresli_dolar(tGrafickyObjekt *d) {
    int cx = d->x + d->w / 2;
    int cy = d->y + d->h / 2;
    // zlatá mince
    nakresli_kruh(cx, cy, d->w / 2, 255, 210, 20);
    // jednoduché "$" bez fontu
    SDL_SetRenderDrawColor(renderer, 80, 100, 20, 255);
    // svislá čára
    SDL_RenderDrawLine(renderer, cx, cy - 8, cx, cy + 8);
    // horní část S
    SDL_RenderDrawLine(renderer, cx - 5, cy - 5, cx + 5, cy - 5);
    SDL_RenderDrawLine(renderer, cx - 5, cy - 5, cx - 5, cy);
    // střed
    SDL_RenderDrawLine(renderer, cx - 5, cy, cx + 5, cy);
    // dolní část
    SDL_RenderDrawLine(renderer, cx + 5, cy, cx + 5, cy + 5);
    SDL_RenderDrawLine(renderer, cx - 5, cy + 5, cx + 5, cy + 5);
}

void nakresli_silnici(void) {
    // tráva nahoře
    nakresli_blok(0, 0, WINDOW_WIDTH, SILNICE_Y1, 40, 120, 50);
    // tráva dole
    nakresli_blok(0, SILNICE_Y2, WINDOW_WIDTH, WINDOW_HEIGHT - SILNICE_Y2, 40, 120, 50);
    // chodníky
    nakresli_blok(0, SILNICE_Y1 - 30, WINDOW_WIDTH, 30, 150, 150, 150);
    nakresli_blok(0, SILNICE_Y2, WINDOW_WIDTH, 30, 150, 150, 150);
    // asfalt
    nakresli_blok(0, SILNICE_Y1, WINDOW_WIDTH, SILNICE_Y2 - SILNICE_Y1, 55, 55, 55);
    // okraje silnice
    nakresli_blok(0, SILNICE_Y1 + 3, WINDOW_WIDTH, 4, 240, 240, 240);
    nakresli_blok(0, SILNICE_Y2 - 7, WINDOW_WIDTH, 4, 240, 240, 240);
    /* ------------------------------------------------------------
       Dělicí čára mezi protisměry
       ------------------------------------------------------------ */
    nakresli_blok(0, 297, WINDOW_WIDTH, 6, 255, 220, 0);
    /* ------------------------------------------------------------
       Přerušované čáry mezi pruhy
       ------------------------------------------------------------ */
    for (int x = 0; x < WINDOW_WIDTH; x += 70) {
        // horní dva pruhy
        nakresli_blok(x, 227, 40, 3, 230, 230, 230);
        // dolní dva pruhy
        nakresli_blok(x, 367, 40, 3, 230, 230, 230);
    }
}
/* ================================================================
   DETEKCE KOLIZE
   ================================================================ */
bool kolize(tGrafickyObjekt *a, tGrafickyObjekt *b) {
    return a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h &&
           a->y + a->h > b->y;
}
/* ================================================================
   VYTVOŘENÍ NOVÉHO AUTA v poli aut
   ================================================================ */
void vytvor_auto(tGrafickyObjekt auta[], int pruh) {
    // Najdeme volnou položku v poli
    int i;
    for (i = 0; i < MAX_AUT; i++) {
        if (!auta[i].aktivni) break;
    }
    // žádné místo
    if (i == MAX_AUT) return;
    tGrafickyObjekt *a = &auta[i];
    a->aktivni = true;
    // náhodný typ auta
    a->typ = rand() % 4;
    // Velikost podle typu
    switch (a->typ) {
        case NAKLADNI: a->w = 125; break;
        case SANITKA: a->w = 100; break;
        case POPELAR: a->w = 115; break;
        default: a->w = 80 + rand() % 25; break;
    }
    a->h = 42;
    // Náhodná barva
    a->r = 50 + rand() % 180;
    a->g = 50 + rand() % 180;
    a->b = 50 + rand() % 180;
    /* Pruhy:
       0. a 1.  -> auto pojede doprava
       2. a 3.   <- auto pojede doleva
    */
    const int yPruhu[POCET_PRUHU] = {174, 244, 314, 384};
    a->y = yPruhu[pruh];
    if (pruh < 2) {  // auto jede doprava
        a->x = -a->w - 10;
        a->dx = 2 + rand() % 4;
    } else {        // auto jede doleva
        a->x = WINDOW_WIDTH + 10;
        a->dx = -(2 + rand() % 4);
    }
    a->dy = 0;
}

/* ================================================================
   muze_vyjet_auto() kontroluje: JE U VJEZDU DO PRUHU VOLNO?
   Tj. brání vzniku několika aut přes sebe.
   ================================================================ */
bool muze_vyjet_auto(tGrafickyObjekt auta[], int pruh) {
    // Y souřadnice jednotlivých jízdních pruhů.
    // Každé číslo určuje svislou pozici auta v daném pruhu.
    const int yPruhu[POCET_PRUHU] = {174, 244, 314, 384};
    // Zjistíme Y souřadnici pruhu, do kterého chceme přidat nové auto.
    int y = yPruhu[pruh];
    // Projdeme všechna auta v poli.
    for (int i = 0; i < MAX_AUT; i++) {
        // Pokud tato položka pole neobsahuje aktivní auto, nemusíme ji kontrolovat.
        if (!auta[i].aktivni) continue;
        // Zajímá nás pouze auto, které je ve stejném jízdním pruhu.
        // Pokud se Y souřadnice auta liší od Y souřadnice
        // kontrolovaného pruhu o více než 10 pixelů,
        // jde o jiný pruh a auto ignorujeme.
        if (abs(auta[i].y - y) > 10) continue;
        // Pruhy 0 a 1 jedou doprava.
        if (pruh < 2) {
            // Nové auto se v těchto pruzích objeví vlevo
            // a následně jede doprava.
            // Pokud už je nějaké auto blízko levého okraje,
            // nové auto zatím nevytvoříme.
            // Hodnota 170 určuje bezpečný odstup od místa,
            // kde vzniká nové auto.
            if (auta[i].x < 170) return false;
        }
        // Pruhy 2 a 3 jedou doleva.
        else {
            // Nové auto se zde objeví na pravém okraji
            // a následně jede doleva.
            // auta[i].x je levý okraj auta,
            // auta[i].x + auta[i].w je pravý okraj auta.
            // Pokud je pravý okraj nějakého auta příliš blízko
            // pravému okraji obrazovky, nové auto zatím nevytvoříme.
            if (auta[i].x + auta[i].w > WINDOW_WIDTH - 170) {
                return false;
            }
        }
    }
    // Pokud jsme prošli všechna auta a žádné nepřekáželo,
    // je u vjezdu do pruhu dost místa.
    return true;
}

void reset_hry(tGrafickyObjekt auta[], tGrafickyObjekt *hrac, tGrafickyObjekt *dolar,
               int *skore) {
    for (int i = 0; i < MAX_AUT; i++)
        auta[i].aktivni = false;
    // hráč začíná dole
    hrac->x = WINDOW_WIDTH / 2 - 12;
    hrac->y = 520;
    hrac->w = 24;
    hrac->h = 38;
    hrac->dx = 0;
    hrac->dy = 0;
    hrac->typ = CLOVEK;
    hrac->aktivni = true;
    // první dolar je nahoře
    dolar->x = 40 + rand() % (WINDOW_WIDTH - 80);
    dolar->y = 70;
    dolar->w = 24;
    dolar->h = 24;
    dolar->typ = DOLAR;
    dolar->aktivni = true;
    *skore = 0;
}

int main(int argc, char *argv[]) {
    /* ------------------------------------------------------------
       Inicializace SDL
       ------------------------------------------------------------ */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init chyba: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Prechazeni silnice", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Nelze vytvorit okno: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Nelze vytvorit renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    srand((unsigned int) time(NULL));
    /* ------------------------------------------------------------
       Herní objekty
       ------------------------------------------------------------ */
    tGrafickyObjekt auta[MAX_AUT] = {0};
    tGrafickyObjekt hrac;
    tGrafickyObjekt dolar;
    int skore = 0;
    reset_hry(auta, &hrac, &dolar, &skore);
    /* ------------------------------------------------------------
       Časy vzniku dalších aut
       ------------------------------------------------------------ */
    Uint32 dalsiAuto[POCET_PRUHU];
    Uint32 ted = SDL_GetTicks();
    for (int i = 0; i < POCET_PRUHU; i++) {
        dalsiAuto[i] = ted + 300 + rand() % 1000; // t=+300ms..+1300ms
    }
    bool running = true;
    bool konecHry = false;
    SDL_Event event;
    /* ============================================================
       HLAVNÍ HERNÍ SMYČKA
       ============================================================ */
    while (running) {
        /* --------------------------------------------------------
           Události
           -------------------------------------------------------- */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
                // Restart po prohře
                if (event.key.keysym.sym == SDLK_r && konecHry) {
                    konecHry = false;
                    reset_hry(auta, &hrac, &dolar, &skore);
                    Uint32 now = SDL_GetTicks();
                    for (int i = 0; i < POCET_PRUHU; i++) {
                        dalsiAuto[i] = now + 300 + rand() % 1000;
                    }
                }
            }
        }
        /* ========================================================
           LOGIKA HRY
           ======================================================== */
        if (!konecHry) {
            /* ----------------------------------------------------
               Pohyb hráče
               ---------------------------------------------------- */
            const Uint8 *klavesy = SDL_GetKeyboardState(NULL);
            int rychlostHrace = 4;
            if (klavesy[SDL_SCANCODE_LEFT] || klavesy[SDL_SCANCODE_A])
                hrac.x -= rychlostHrace;
            if (klavesy[SDL_SCANCODE_RIGHT] || klavesy[SDL_SCANCODE_D])
                hrac.x += rychlostHrace;
            if (klavesy[SDL_SCANCODE_UP] || klavesy[SDL_SCANCODE_W])
                hrac.y -= rychlostHrace;
            if (klavesy[SDL_SCANCODE_DOWN] || klavesy[SDL_SCANCODE_S])
                hrac.y += rychlostHrace;
            // Hráč nesmí opustit obrazovku
            if (hrac.x < 0) hrac.x = 0;
            if (hrac.x + hrac.w > WINDOW_WIDTH) hrac.x = WINDOW_WIDTH - hrac.w;
            if (hrac.y < 0) hrac.y = 0;
            if (hrac.y + hrac.h > WINDOW_HEIGHT) hrac.y = WINDOW_HEIGHT - hrac.h;
            /* ----------------------------------------------------
               Náhodné vytváření aut
               ---------------------------------------------------- */
            Uint32 now = SDL_GetTicks();
            for (int pruh = 0; pruh < POCET_PRUHU; pruh++) {
                if (now >= dalsiAuto[pruh]) {
                    if (muze_vyjet_auto(auta, pruh)) {
                        vytvor_auto(auta, pruh);
                    }
                    /*
                       Další auto se objeví
                       za 0.5 až 1.7 sekundy.
                    */
                    dalsiAuto[pruh] = now + 500 + rand() % 1200;
                }
            }
            /* ----------------------------------------------------
               Pohyb aut
               ---------------------------------------------------- */
            for (int i = 0; i < MAX_AUT; i++) {
                if (!auta[i].aktivni) continue;
                auta[i].x += auta[i].dx;
                // Auto vyjelo mimo obrazovku
                if (auta[i].x > WINDOW_WIDTH + 150 || auta[i].x + auta[i].w < -150) {
                    auta[i].aktivni = false;
                }
            }
            /* ----------------------------------------------------
               Srážka člověka s autem
               ---------------------------------------------------- */
            for (int i = 0; i < MAX_AUT; i++) {
                if (!auta[i].aktivni) continue;
                if (kolize(&hrac, &auta[i])) {
                    konecHry = true;
                    break;
                }
            }
            /* ----------------------------------------------------
               Sebrání dolaru
               ---------------------------------------------------- */
            if (kolize(&hrac, &dolar)) {
                skore++;
                // nové náhodné X
                dolar.x = 30 + rand() % (WINDOW_WIDTH - dolar.w - 60);
                // Jestli byl dolar nahoře, objeví se dole (a naopak).
                if (dolar.y < SILNICE_Y1) {
                    dolar.y = 520;
                } else {
                    dolar.y = 70;
                }
            }
        }
        /* ========================================================
           VYKRESLENÍ
           ======================================================== */
        SDL_SetRenderDrawColor(renderer, 15, 15, 30, 255);
        SDL_RenderClear(renderer);
        /* silnice */
        nakresli_silnici();
        /* dolar */
        nakresli_dolar(&dolar);
        /* auta */
        for (int i = 0; i < MAX_AUT; i++) {
            if (auta[i].aktivni) {
                nakresli_vozidlo(&auta[i]);
            }
        }
        /* hráč */
        nakresli_cloveka(&hrac);
        /* --------------------------------------------------------
           Při nehodě nakreslíme červený kříž
           -------------------------------------------------------- */
        if (konecHry) {
            SDL_SetRenderDrawColor(renderer, 255, 30, 30, 255);
            SDL_RenderDrawLine(renderer, 250, 100, 550, 500);
            SDL_RenderDrawLine(renderer, 550, 100, 250, 500);
        }
        /* --------------------------------------------------------
           Skóre zobrazíme v titulku okna.
           Díky tomu nepotřebujeme další knihovnu SDL_ttf.
           -------------------------------------------------------- */
        char titulek[150];
        if (konecHry) {
            snprintf(titulek, sizeof(titulek),
                     "KONEC HRY! Skore: %d   [R = restart, ESC = konec]", skore);
        } else {
            snprintf(titulek, sizeof(titulek),
                     "Prechazeni silnice - dolary: %d   [sipky/WASD]", skore);
        }
        SDL_SetWindowTitle(window, titulek);
        SDL_RenderPresent(renderer);
    }
    /* ============================================================
       ÚKLID
       ============================================================ */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
