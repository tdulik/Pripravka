#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265359

// Funkce pro zápis trojúhelníku do STL souboru
void triangle(FILE *file,
              float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3);
void circle2D(FILE *file, float x, float y, float radius, int segments);
void rectangle2D(FILE *file, float x, float y, float w, float h, float angle);

// Funkce pro zápis vrcholu do STL souboru
void write_vertex(FILE *file, float x, float y, float z) {
    fprintf(file, "      vertex %f %f %f\n", x, y, z);
}

void write_facet(FILE *file, float nx, float ny, float nz, float v1[3], float v2[3], float v3[3]) {
    fprintf(file, "  facet normal %f %f %f\n", nx, ny, nz);
    fprintf(file, "    outer loop\n");
    fprintf(file, "      vertex %f %f %f\n", v1[0], v1[1], v1[2]);
    fprintf(file, "      vertex %f %f %f\n", v2[0], v2[1], v2[2]);
    fprintf(file, "      vertex %f %f %f\n", v3[0], v3[1], v3[2]);
    fprintf(file, "    endloop\n");
    fprintf(file, "  endfacet\n");
}


void triangle(FILE *file,
              float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3) {
    fprintf(file, "  facet normal 0 0 1\n"
                  "    outer loop\n");
    write_vertex(file, x1, y1, z1);
    write_vertex(file, x2, y2, z2);
    write_vertex(file, x3, y3, z3);
    fprintf(file, "    endloop\n");
    fprintf(file, "  endfacet\n");
}
// Funkce pro vytvoření kruhu (disku)
void circle2D(FILE *file, float x, float y, float radius, int segments) {
    float angle_step = 2 * PI / segments;
    for (int i = 0; i < segments; i++) {
        float angle1 = i * angle_step;
        float angle2 = (i + 1) * angle_step;
        // Výpočet vrcholů trojúhelníku
        float x1 = radius * cos(angle1)+x;
        float y1 = radius * sin(angle1)+y;
        float x2 = radius * cos(angle2)+x;
        float y2 = radius * sin(angle2)+y;
        // Normála pro rovinný kruh směřující vzhůru (v ose Z)
        triangle(file, x, y, 0,  x1, y1, 0,  x2, y2, 0);
    }
}
// Funkce pro otočení bodu podle úhlu
void rotate_point(float *x, float *y, float angle) {
    float new_x = (*x) * cos(angle) - (*y) * sin(angle);
    float new_y = (*x) * sin(angle) + (*y) * cos(angle);
    *x = new_x;
    *y = new_y;
}
void rectangle2D(FILE *file, float x, float y, float w, float h, float angle) {
    float rad = angle * M_PI / 180.0;  // Convert angle to radians
    float cos_a = cos(rad);
    float sin_a = sin(rad);
    float hw = w / 2.0;
    float hh = h / 2.0;
    float x0 = x - hw * cos_a + hh * sin_a;
    float y0 = y - hw * sin_a - hh * cos_a;
    float x1 = x + hw * cos_a + hh * sin_a;
    float y1 = y + hw * sin_a - hh * cos_a;
    float x2 = x - hw * cos_a - hh * sin_a;
    float y2 = y - hw * sin_a + hh * cos_a;
    float x3 = x + hw * cos_a - hh * sin_a;
    float y3 = y + hw * sin_a + hh * cos_a;
    // Write the facets of the rectangle
    triangle(file, x0,y0,0,x1,y1,0,x2,y2,0);
    triangle(file, x2,y2,0,x1,y1,0,x3,y3,0);
}

void cube(FILE *file,  float x, float y, float z, float width, float depth, float height) {

    float vertices[8][3] = {
        {x, y, z},                          // spodní čtverec: 4 vrcholy
        {x + width, y, z},
        {x + width, y + depth, z},
        {x, y + depth, z},
        {x, y, z + height},                 // horní čtverec: 4 vrcholy
        {x + width, y, z + height},
        {x + width, y + depth, z + height},
        {x, y + depth, z + height}
    };
    // Spodní plocha
    write_facet(file, 0, 0, -1, vertices[0], vertices[1], vertices[2]);
    write_facet(file, 0, 0, -1, vertices[0], vertices[2], vertices[3]);

    // Horní plocha
    write_facet(file, 0, 0, 1, vertices[4], vertices[5], vertices[6]);
    write_facet(file, 0, 0, 1, vertices[4], vertices[6], vertices[7]);

    // Boční plocha 1
    write_facet(file, -1, 0, 0, vertices[0], vertices[3], vertices[7]);
    write_facet(file, -1, 0, 0, vertices[0], vertices[7], vertices[4]);

    // Boční plocha 2
    write_facet(file, 1, 0, 0, vertices[1], vertices[5], vertices[6]);
    write_facet(file, 1, 0, 0, vertices[1], vertices[6], vertices[2]);

    // Boční plocha 3
    write_facet(file, 0, -1, 0, vertices[0], vertices[4], vertices[5]);
    write_facet(file, 0, -1, 0, vertices[0], vertices[5], vertices[1]);

    // Boční plocha 4
    write_facet(file, 0, 1, 0, vertices[2], vertices[6], vertices[7]);
    write_facet(file, 0, 1, 0, vertices[2], vertices[7], vertices[3]);

}

void cylinder(FILE *file, float radius, float height, int segments) {
    float angle_step = 2 * PI / segments;


    for (int i = 0; i < segments; i++) {
        float angle1 = i * angle_step;
        float angle2 = (i + 1) * angle_step;

        float v1_top[3] = {radius * cos(angle1), radius * sin(angle1), height};
        float v2_top[3] = {radius * cos(angle2), radius * sin(angle2), height};
        float v3_top[3] = {0, 0, height};

        float v1_bottom[3] = {radius * cos(angle1), radius * sin(angle1), 0};
        float v2_bottom[3] = {radius * cos(angle2), radius * sin(angle2), 0};
        float v3_bottom[3] = {0, 0, 0};

        float v1_side1[3] = {radius * cos(angle1), radius * sin(angle1), 0};
        float v2_side1[3] = {radius * cos(angle2), radius * sin(angle2), 0};
        float v3_side1[3] = {radius * cos(angle1), radius * sin(angle1), height};

        float v1_side2[3] = {radius * cos(angle2), radius * sin(angle2), 0};
        float v2_side2[3] = {radius * cos(angle2), radius * sin(angle2), height};
        float v3_side2[3] = {radius * cos(angle1), radius * sin(angle1), height};

        write_facet(file, 0, 0, 1, v1_top, v2_top, v3_top);
        write_facet(file, 0, 0, -1, v1_bottom, v2_bottom, v3_bottom);

        float nx1 = cos(angle1);
        float ny1 = sin(angle1);
        float nx2 = cos(angle2);
        float ny2 = sin(angle2);

        write_facet(file, nx1, ny1, 0, v1_side1, v2_side1, v3_side1);
        write_facet(file, nx2, ny2, 0, v1_side2, v2_side2, v3_side2);
    }

}

void star(FILE * file, int x, int y) {
//doplňte váš kód:

}
void skyWithStars(FILE * file) {
    //doplňte váš kód:

}
void rocket(FILE *file, float x, float y, int w, int h) {
    //doplňte váš kód:

}

void tree(FILE *file, float x, float y, int size) {
    //doplňte váš kód:

}
void man(FILE *f, float x, int size) {
    //doplňte váš kód:

}
void trees(FILE *f, float x, float y) {
    //doplňte váš kód:
}
int main() {
    srand(time(NULL));
    FILE *file = fopen("model.stl", "w");
    if (file == NULL) {
        printf("Nelze otevrit soubor!\n");
        return 1;
    }
    fprintf(file, "solid obrazek\n");
    skyWithStars(file);
    rocket(file, 50,300,30,150);
    for (int i = 0; i < 3; ++i) {
        man(file, 200+90*i, 100-4*i);
    }
    trees(file, 500,0);
    cylinder(file, 100, 50, 20);
    cube(file, 500,0,0, 20,20,50);
    fprintf(file, "endsolid obrazek\n");
    fclose(file);
    printf("Soubor STL byl vytvoren.\n");
    return 0;
}
