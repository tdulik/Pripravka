/* ================================================================
   KRESLENÍ RŮZNÝCH VOZIDEL
   ================================================================ */
void nakresli_vozidlo(tGrafickyObjekt *a) {
    int x = a->x;
    int y = a->y;
    int w = a->w;
    int h = a->h;
    int radius = h / 5;
    switch (a->typ) {
        /* --------------------------------------------------------
           OSOBNÍ AUTO
           -------------------------------------------------------- */
        case OSOBNI:
            // karoserie
            nakresli_blok(x, y + 12, w, h - 16, a->r, a->g, a->b);
            // střecha
            nakresli_blok(x + w / 4, y + 2, w / 2, 18, a->r, a->g, a->b);
            // okna
            nakresli_blok(x + w / 3, y + 5, w / 7, 12, 160, 220, 255);
            nakresli_blok(x + w / 2 + 3, y + 5, w / 7, 12, 160, 220, 255);
            break;
        /* --------------------------------------------------------
           NÁKLAĎÁK
           -------------------------------------------------------- */
        case NAKLADNI:
            if (a->dx > 0) {
                // jede doprava: náklad vzadu vlevo, kabina vpředu vpravo
                // nákladový prostor
                nakresli_blok(x, y + 2, w * 2 / 3, h - 10, a->r, a->g, a->b);
                // kabina
                nakresli_blok(x + w * 2 / 3, y + 12, w / 3, h - 20, 230, 120, 30);
                // okno kabiny
                nakresli_blok(x + w * 3 / 4, y + 15, w / 7, 12, 160, 220, 255);
            } else {
                // jede doleva: kabina vpředu vlevo, náklad vzadu vpravo
                // kabina
                nakresli_blok(x, y + 12, w / 3, h - 20, 230, 120, 30);
                // okno kabiny
                nakresli_blok(x + w / 10, y + 15, w / 7, 12, 160, 220, 255);
                // nákladový prostor
                nakresli_blok(x + w / 3, y + 2, w * 2 / 3, h - 10, a->r, a->g, a->b);
            }
            break;
        case POPELAR:
            if (a->dx > 0) {
                // jede doprava
                // kontejner
                nakresli_blok(x, y + 5, w * 2 / 3, h - 13, 50, 150, 70);
                // kabina
                nakresli_blok(x + w * 2 / 3, y + 13, w / 3, h - 21, 100, 190, 100);
                // okno
                nakresli_blok(x + w * 3 / 4, y + 16, w / 7, 11, 170, 220, 255);
            } else {
                // jede doleva
                // kabina
                nakresli_blok(x, y + 13, w / 3, h - 21, 100, 190, 100);
                // okno
                nakresli_blok(x + w / 10, y + 16, w / 7, 11, 170, 220, 255);
                // kontejner
                nakresli_blok(x + w / 3, y + 5, w * 2 / 3, h - 13, 50, 150, 70);
            }
            break;
        /* --------------------------------------------------------
           SANITKA
           -------------------------------------------------------- */
        case SANITKA:
            // bílé tělo
            nakresli_blok(x, y + 5, w, h - 12, 240, 240, 240);
            // červený pruh
            nakresli_blok(x, y + h / 2, w, 5, 220, 30, 30);
            // červený kříž
            nakresli_blok(x + w / 2 - 3, y + 10, 6, 22, 220, 30, 30);
            nakresli_blok(x + w / 2 - 10, y + 18, 20, 6, 220, 30, 30);
            // modrý maják
            nakresli_blok(x + w / 3, y, 15, 6, 30, 100, 255);
            break;
        default: break;
    }
    /* Kola mají všechna vozidla */
    nakresli_kruh(x + w / 5, y + h - 5, radius, 25, 25, 25);
    nakresli_kruh(x + w * 4 / 5, y + h - 5, radius, 25, 25, 25);
    nakresli_kruh(x + w / 5, y + h - 5, radius / 2, 160, 160, 160);
    nakresli_kruh(x + w * 4 / 5, y + h - 5, radius / 2, 160, 160, 160);
}
