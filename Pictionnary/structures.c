#include <stdlib.h> // Pour pouvoir utiliser exit()	
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <string.h>
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFX/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFX/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFX/ESLib.h" // Pour utiliser valeurAleatoire()
#include "structures.h"
#include "affichage.h"
#include "calcul.h"

/**
 * @brief Initalize a color structure
 * @param r for red value
 * @param g for green value
 * @param b for blue value
 * @param *c for color adress
 */
void initColor(color* c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

/** 
 * @brief Initalize all the colors of colorsTab structure
 * @param *c for colorTab adress
 */
void initColorsTab(colorsTab* c)
{
	
	c->red.r = 255;
	c->red.g = 0;
	c->red.b = 0;
	
	c->blue.r = 0;
	c->blue.g = 0;
	c->blue.b = 255;
	
	c->yellow.r = 255;
	c->yellow.g = 244;
	c->yellow.b = 79;
	
	c->lightblue.r = 0;
	c->lightblue.g = 125;
	c->lightblue.b = 198;
	
	c->black.r = 0;
	c->black.g = 0;
	c->black.b = 0;
	
	c->drawColor=c->black;
	
	c->color1=c->lightblue;
	
	c->color2=c->black;
}

/** 
 * @brief Initalize a button structure
 * @param *b for button adress
 * @param x1 for the abscisse of the bottom left point of the rectangle
 * @param y1 for the ordinate of the bottom left point of the rectangle
 * @param x2 for the abscisse of the top right point of the rectangle
 * @param y2 for the ordinate of the top right point of the rectangle
 * @param st for the text size
 * @param *txt for the text value
 * @param cb for the background color
 * @param ct for the text color
 */
void initButton(button* b, int x1, int y1, int x2, int y2, int st, char* txt, color* cb, color *ct)
{
	b->x1 = x1;
	b->y1 = y1;
	b->x2 = x2;
	b->y2 = y2;
	b->xt = x2-(x2-x1)/2-tailleChaine(txt,st)/2; // center the text on the abscisses
	b->yt = y2-(y2-y1)/2-st/2; // center the text on the ordinates
	b->st = st; 
	b->txt = txt;
	b->cb = cb;
	b->ct = ct;
}

/**
 * @brief Test a button by printing it on the console
 * @param b for the button that need to be tested
 */
void printButton(button b)
{
	printf("x1: %d\n",b.x1);
	printf("y1: %d\n",b.y1);
	printf("x2: %d\n",b.x2);
	printf("y2: %d\n",b.y2);
	printf("xt: %d\n",b.xt);
	printf("yt: %d\n",b.yt);
	printf("st: %d\n",b.st);
	printf("txt: %s\n",b.txt);
	printf("background color: %d %d %d\n",b.cb->r,b.cb->g,b.cb->b);
	printf("text color: %d %d %d\n",b.ct->r,b.ct->g,b.ct->b);
	
}

/**
 * @brief Display a button
 * @param b for the button that need to be display
 */
void displayButton(button b)
{
	// concerning the background
	couleurCourante(b.cb->r,b.cb->g,b.cb->b);
	rectangle(b.x1,b.y1,b.x2,b.y2);
	
	// concerning the content
	couleurCourante(b.ct->r,b.ct->g,b.ct->b);
	epaisseurDeTrait(3);
	afficheChaine(b.txt,b.st,b.xt,b.yt);
}

segment initSegmentFomPoints(pts p0, pts p1)
{
	segment s;
	
	s.p0 = p0;
	s.p1 = p1;
	
	return s;
}
