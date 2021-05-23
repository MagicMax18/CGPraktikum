
#include "WireframeRenderer.hpp"

/**
** Zeichnet alle Dreiecke der Scene als Wireframe-Rendering unter Verwendung des
* Bresenham-Algorithmus
** Precondition: Sowohl mImage als auch mScene müssen gesetzt sein.
** (Aufgabenblatt 2 - Aufgabe 1)
**/
void WireframeRenderer::renderScene(Color color) {
}

/**
** Zeichnet unter Verwendung des Bresenham Algorithmus eine Linie zwischen p1
* und p2 (nutzt x & y Komponente - z Komponente wird ignoriert)
** Precondition: Das mImage muss gesetzt sein.
** (Aufgabenblatt 1 - Aufgabe 2)
**/
void WireframeRenderer::drawBresenhamLine(GLPoint p1, GLPoint p2, Color color) {
    //Vorbedingung: mImage muss gesetzt sein
    if (this->mImage == NULL)
        return;

    //Steigung berechnen
    double delta_x = p2(0) - p1(0);
    double delta_y = p2(1) - p1(1);

    //Fallunterscheidung nach Oktanten
    if (delta_x >= 0 && delta_y >= 0 && delta_x >= delta_y) {
        //Oktant 1
        drawBresenhamLineOct1(p1, p2, color);
    } else if (delta_x >= 0 && delta_y >= 0 && delta_x < delta_y) {
        //Oktant 2
        drawBresenhamLineOct2(p1, p2, color);
    } else if (delta_x < 0 && delta_y >= 0 && delta_x * -1 <= delta_y) {
        //Oktant 3
        drawBresenhamLineOct3(p1, p2, color);
    } else if (delta_x < 0 && delta_y >= 0 && delta_x * -1 > delta_y) {
        //Oktant 4
        drawBresenhamLineOct4(p1, p2, color);
    } else if (delta_x < 0 && delta_y < 0 && delta_x <= delta_y) {
        //Oktant 5
        drawBresenhamLineOct5(p1, p2, color);
    } else if (delta_x < 0 && delta_y < 0 && delta_x > delta_y) {
        //Oktant 6
        drawBresenhamLineOct6(p1, p2, color);
    } else if (delta_x >= 0 && delta_y < 0 && delta_x <= delta_y * -1) {
        //Oktant 7
        drawBresenhamLineOct7(p1, p2, color);
    } else if (delta_x >= 0 && delta_y < 0 && delta_x > delta_y) {
        //Oktant 8
        drawBresenhamLineOct8(p1, p2, color);
    }
}

void WireframeRenderer::drawBresenhamLineOct1(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = 2 * delta_y - delta_x;

    for (int i = 1; i <= delta_x; ++i) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            ++y;
            e -= 2 * delta_x;
        }
        ++x;
        e += 2 * delta_y;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct2(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = 2 * delta_x - delta_y;

    for (int i = 1; i <= delta_y; ++i) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            ++x;
            e -= 2 * delta_y;
        }
        ++y;
        e += 2 * delta_x;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct3(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = -2 * delta_x - delta_y;

    for (int i = 1; i <= delta_y; ++i) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            --x;
            e -= 2 * delta_y;
        }
        ++y;
        e -= 2 * delta_x;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct4(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = 2 * delta_y + delta_x;

    for (int i = 1; i <= delta_x * -1; i++) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            ++y;
            e += 2 * delta_x;
        }
        --x;
        e += 2 * delta_y;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct5(GLPoint p1, GLPoint p2, Color color) {
    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);    
    int e = -2 * delta_y + delta_x;

    for (int i = 1; i <= delta_x * -1; i++) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            --y;
            e += 2 * delta_x;
        }
        --x;
        e -= 2 * delta_y;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct6(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);    
    int e = -2 * delta_x + delta_y;

    for (int i = 1; i <= delta_y * -1; ++i) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            --x;
            e += 2 * delta_y;
        }
        --y;
        e -= 2 * delta_x;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct7(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = 2 * delta_x + delta_y;

    for (int i = 1; i <= delta_y * -1; ++i) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            ++x;
            e += 2 * delta_y;
        }
        --y;
        e += 2 * delta_x;
    }
    mImage->setValue(x, y, color);
    return;
}

void WireframeRenderer::drawBresenhamLineOct8(GLPoint p1, GLPoint p2, Color color) {

    int delta_x = p2(0) - p1(0);
    int delta_y = p2(1) - p1(1);

    int x = p1(0);
    int y = p1(1);
    int e = -2 * delta_y - delta_x;

    for (int i = 1; i <= delta_x; i++) {
        mImage->setValue(x, y, color);
        if (e > 0) {
            --y;
            e -= 2 * delta_x;
        }
        ++x;
        e -= 2 * delta_y;
    }
    mImage->setValue(x, y, color);
    return;
}

/**
** Füllt einen vorgegebenen Bereich (abgegrenzt durch Randfarbe/borderColor) mit einer vorgegebenen Farbe (fillColor).
** Precondition: Das mImage muss gesetzt sein.
** (Aufgabenblatt 1 - Aufgabe 3) 
**/
void WireframeRenderer::seedFillArea(GLPoint seed, Color borderColor, Color fillColor) {
}
