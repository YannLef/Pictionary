typedef struct droite {
	int a,b,c;
}droite;

typedef struct pts{
	float x,y;
}pts;

typedef struct segment {
	pts p0,p1;
	float path;
	float size;
	droite d;
	char eq[30];
}segment;

typedef struct color{
	int r,g,b; // value of red, green and blue (0->255)
}color;

typedef struct colorsTab{
	color red,blue,yellow,lightblue,black,drawColor,color1,color2; // all colors that are available in colorsTab
}colorsTab;

typedef struct button{
	int x1,y1,x2,y2; //button coordonate
	int xt,yt; //texte coordonate
	int st; // text size
	color *cb; // background color
	color *ct; // text color
	char *txt; //name inside the rectangle (dynamic allocation);
}button;





typedef struct buttonsTab{
	button play,rules, quit; // all buttons that are available in buttonsTab
}buttonsTab;

typedef struct pathern{
	int nbSeg;
	float size;
	float time;
}pathern;


void initColor(color* c, int r, int g, int b); // initialize the value of a color passing by the adress

void initColorsTab(colorsTab* c);

void initButton(button* b, int x1, int y1, int x2, int y2, int st, char* txt, color *cb, color *ct); // initialize the value of a button passing by the adress

void displayButton(button b); // display an inisialized button on the screen

segment initSegmentFomPoints(pts p0, pts p1); // initalize a segment out of 2 points 
