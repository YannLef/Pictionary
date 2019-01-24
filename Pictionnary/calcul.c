#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFX/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFX/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFX/ESLib.h" // Pour utiliser valeurAleatoire()
#include "structures.h"
#include "affichage.h"
#include "calcul.h"
#include "string.h"


pts* getPoints(pts* allPoints, int* nbPts, int rec, float page, int* nbPath)
{
		
	pts* p;
	p = (pts*)malloc(sizeof(pts)*(*nbPts+1));
	if(p==NULL) printf("erreur\n");
	
	
			for(int i=0;i<(*nbPts);i++)
			{
				p[i].x=allPoints[i].x;
				p[i].y=allPoints[i].y;
			}
			
			
			if(rec==1) // if the user use the mouse left clic
			{
				if(page==5) // the path must be on the drawing page
				{
					if(abscisseSouris() > largeurFenetre()/10 && abscisseSouris() < 9*largeurFenetre()/10 && ordonneeSouris() > hauteurFenetre()/10 && ordonneeSouris() < 7*hauteurFenetre()/10) // if the mouse is on the drawing area
					{
						p[*nbPts].x=abscisseSouris();
						p[*nbPts].y=ordonneeSouris();
	
						(*nbPts)++;
					}
					else
					{
						if(p[*nbPts-1].x != -1) // if the mouse isn't on the drawing area
						{
							p[*nbPts].x=-1;
							p[*nbPts].y=-1;
							(*nbPts)++;
							(*nbPath)++;
						}
					}
				}
			}
			else // if the user stop clicking 
			{
				if(p[*nbPts-1].x != -1)
				{
					p[*nbPts].x=-1;
					p[*nbPts].y=-1;
					(*nbPts)++;
					(*nbPath)++;
				}
			}
			
			couleurCourante(255,0,0);
			epaisseurDeTrait(5);
			
			for(int i=1;i<*nbPts-1;i++)
			{
				//if(p[i-1].x != -1 && p[i].x != -1)
					//ligne(p[i-1].x,p[i-1].y,p[i].x,p[i].y);
			}
			
			
	// developping log tests
	//printf("%d\t",*nbPts);
	//if(rec==0)
		//printf("%f %f\n",p[*nbPts-1].x, p[*nbPts-1].y);
	//else printf("%f %f\n",p[*nbPts-1].x, p[*nbPts-1].y);
	
		
	return p;
}

segment* getSegments(pts* p, int nbPts, int* nbSeg, int nbPath, segment* allSeg)
{
	segment* s;
	s = (segment*)malloc(sizeof(segment)*(nbPts));
	if(s==NULL) printf("erreur\n");
	*nbSeg=1;
	float k=0.5;
	for(int i=1;i<nbPts-1;i++)
			{
				if(p[i-1].x != -1 && p[i].x != -1)
				{
					s[*nbSeg].p0 = p[i-1];
					s[*nbSeg].p1 = p[i];
					s[*nbSeg].path = k;
					//printf("%f\n",s[*nbSeg].path);
					(*nbSeg)++;
					
				}
				else
				k=k+0.5;
			}
		//printf("%f\n",k);
	
	return s;
}

void managePlayButtonFromPage0(int x, int y, float* page)
{
	if(*page == 0) // this button is part of the page 0
	{
		if(x>432 && x<864 && y>400 && y<550)
		{
			*page = 1;
		}
	}
}

void manageRulesButtonFromPage0(int x, int y, float* page)
{
	if(*page == 0) // this button is part of the page 0
	{
		if(x>432 && x<864 && y>230 && y<380)
		{
			*page = 2;
		}
	}
}

void manageSettingsButtonFromPage0(int x, int y, float* page)
{
	if(*page == 0) // this button is part of the page 0
	{
		if(x>largeurFenetre()-115 && x<largeurFenetre() && y>40 && y<115)
		{
			*page = 3;
		}
	}
}

void manageQuitButtonFromPage0(int x, int y, float* page)
{
	if(*page == 0) // this button is part of the page 0
	{
		if(x>432 && x<864 && y>60 && y<210)
		{
			termineBoucleEvenements();
		}
	}
}

void manageQuitButtonFromPage2(int x, int y, float* page)
{
	if(*page == 2) // this button is part of the page 0
	{
		if(x>432 && x<864 && y>60 && y<210)
		{
			*page=0;
		}
	}
}

void manageQuitButtonFromPage3(int x, int y, float* page)
{
	if(*page == 3) // this button is part of the page 0
	{
		if(x>432 && x<864 && y>60 && y<210)
		{
			*page=0;
		}
	}
}

void manageQuitButtonFromPage1(int x, int y, float* page)
{
	if(*page == 1) // this button is part of the page 1
	{
		if(x>30 && x<80 && y>hauteurFenetre()-80 && y<hauteurFenetre()-30)
		{
			*page=0;
		}
	}
}

void manageEasyButtonFromPage1(int x, int y, float* page, int* difficulty)
{
	if(*page == 1) // this button is part of the page 1
	{
		if(x>largeurFenetre()/20 && x<6.33*(largeurFenetre())/20 && y>150 && y<600)
		{
			*page = 4; // in order to display page 5 (play in easy mode)
			*difficulty = 1;
		}
	}
}

void manageCpt3(float* cpt3, float* page)
{
	if(*page == 4) // this counter is part of the page 4
	{
		*cpt3 = *cpt3 - 0.02;
	}
	
	if(page == 0)
		*cpt3 = 3;
		
	if(*cpt3 <= 0)
	{
		*page = 5;
		*cpt3=3; // replace the counter to is initial value (3)
	}
}

void manageQuitButtonFromPage4(int x, int y, float* page, float* cpt3, int* numWord)
{
	if(*page == 4) // this button is part of the page 4
	{
		if(x>30 && x<80 && y>hauteurFenetre()-80 && y<hauteurFenetre()-30)
		{
			*page=0;
			*cpt3=3; // replace the counter to is initial value (3)
			*numWord=0;
		}
	}
}

void manageMediumButtonFromPage1(int x, int y, float* page, int* difficulty)
{
	if(*page == 1) // this button is part of the page 1
	{
		if(x>7.33*(largeurFenetre()/20) && x<12.66*(largeurFenetre()/20) && y>150 && y<600)
		{
			*page = 4; // in order to display page 6 (play in medium mode)
			*difficulty = 2;
		}
	}
}

void manageHardButtonFromPage1(int x, int y, float* page, int* difficulty)
{
	if(*page == 1) // this button is part of the page 1
	{
		if(x>13.66*(largeurFenetre()/20) && x<19*(largeurFenetre()/20) && y>150 && y<600)
		{
			*page = 4; // in order to display page 6 (play in medium mode)
			*difficulty = 3;
		}
	}
}

void manageQuitButtonFromPage5(int x, int y, float* page, float* cpt60, int* numWord, pts* allPoints, int* nbPts, int* nbPath, float* minSize, float* maxSize, float* averageSize, segment* allSeg)
{
	if(*page == 5) // this button is part of the page 5
	{
		if(x>30 && x<80 && y>hauteurFenetre()-80 && y<hauteurFenetre()-30)
		{
			*page=0;
			*cpt60=60; // replace the counter to is initial value (60)
			*numWord=0;
			*nbPts = 0;
			*nbPath = -1;
			*minSize = -1;
			*maxSize = -1;
			*averageSize = -1;
			*minSize = -1;
			*minSize = -1;
			
		}
	}
}

void manageCpt60(float* cpt60, float* page, int difficulty, char word[30], int nbPts, int nbSeg, pathern* path, int nbPath, float minSize, float maxSize, float averageSize, pts* allPoints, segment* allSeg)
{
	if(*page == 5) // this counter is part of the page 5
	{
		*cpt60 = *cpt60 - 0.02;
	}
	
	if(page == 0)
		*cpt60 = 60;
		
	if(*cpt60 <= 0)
	{
		*page = 6;
		*cpt60=60; // replace the counter to is initial value (60)
		save(difficulty,*page, word, nbPts, nbSeg, path, nbPath, minSize, maxSize, averageSize, allPoints, allSeg);
	}
}

void loadWord(float page, int difficulty, int* numWord, char ch[30])
{
	
	if(page==4 && *numWord==0)
	{
		if(difficulty==1) // easy
		{
			FILE* f = fopen("easy.txt","rt");
			if(f==NULL)
			{
				printf("erreur chargement fichier\n");
			}
			else
			{
				int wordCount; // number of words available in the file
				fscanf(f,"%d\n",&wordCount);
				
				float a = valeurIntervalleZeroUn(); // generate a random number between 0 and 1
				a=a*wordCount; // the number between 0 and 1 become a number between 0 and wordCount (number of words available in the file)
				*numWord=(int)a+1; // turn it into a proper int
				
				for(int i=0;i<*numWord;i++)
				{
					fscanf(f,"%s\n",ch);
				}
			}
			fclose(f);
		}
		
		if(difficulty==2) // medium
		{
			FILE* f = fopen("medium.txt","rt");
			if(f==NULL)
			{
				printf("erreur chargement fichier\n");
			}
			else
			{
				int wordCount; // number of words available in the file
				fscanf(f,"%d\n",&wordCount);
				
				float a = valeurIntervalleZeroUn(); // generate a random number between 0 and 1
				a=a*wordCount; // the number between 0 and 1 become a number between 0 and wordCount (number of words available in the file)
				*numWord=(int)a+1; // turn it into a proper int
				
				for(int i=0;i<*numWord;i++)
				{
					fscanf(f,"%s\n",ch);
				}
			}
			fclose(f);
		}
		
		if(difficulty==3) // hard
		{
			FILE* f = fopen("hard.txt","rt");
			if(f==NULL)
			{
				printf("erreur chargement fichier\n");
			}
			else
			{
				int wordCount; // number of words available in the file
				fscanf(f,"%d\n",&wordCount);
				
				float a = valeurIntervalleZeroUn(); // generate a random number between 0 and 1
				a=a*wordCount; // the number between 0 and 1 become a number between 0 and wordCount (number of words available in the file)
				*numWord=(int)a+1; // turn it into a proper int
				
				for(int i=0;i<*numWord;i++)
				{
					fscanf(f,"%s\n",ch);
				}
			}
			
			fclose(f);
		}
		
		
	}
}

void save(int difficulty, float page, char word[30], int nbPts, int nbSeg, pathern* path, int nbPath, float minSize, float maxSize, float averageSize, pts* allPoints, segment* allSeg)
{
	if(page==6)
	{
	
		FILE* f = fopen("results.txt","wt");
	
		fprintf(f,"difficuly : %d\n",difficulty);
		fprintf(f,"word : %s\n",word);
		fprintf(f,"amount of points : %d\n",nbPts);
		fprintf(f,"amount of segments : %d\n",nbPts-1);
		fprintf(f,"amount of paths : %d\n",nbPath);
		
		
		if(nbPath>0)
		{
			fprintf(f,"minimum size of paths : %f\n",minSize);
			fprintf(f,"maximum size of paths : %f\n",maxSize);
			fprintf(f,"average size of paths : %f\n",averageSize);
		}
		else
		{
			fprintf(f,"minimum size of paths : there is no paths\n");
			fprintf(f,"maximum size of paths : there is no paths\n");
			fprintf(f,"average size of paths : there is no paths\n");
		}
		
		fprintf(f,"\n");
		fprintf(f,"time of each path:\n");
		for(int i=1;i<=nbPath;i++)
		{
			fprintf(f,"path %d: %f\n",i,path[i].time);
		}
		
		fprintf(f,"\n");
		fprintf(f,"all segments equations (trajectory): \n");
		
		for(int i=1;i<nbSeg;i++)
		{
			fprintf(f,"segment %d: %s\n",i,allSeg[i].eq);
			fprintf(f,"\n");
			
		}
	
		fclose(f);
		
	}
}

void getSizeSegments(segment* allSegments, int nbSeg)
{
	
	for(int i=1; i<nbSeg;i++)
	{
		
		allSegments[i].size = sqrt( (allSegments[i].p0.x - allSegments[i].p1.x)*(allSegments[i].p0.x - allSegments[i].p1.x) + (allSegments[i].p0.y - allSegments[i].p1.y)*(allSegments[i].p0.y - allSegments[i].p1.y) );
		
	}
}

pathern* getpath(pathern* path, int nbSeg, int nbPath, segment* allSeg, float page)
{
	//printf("%d\n",nbPath);
	if(page==5 && nbPath!=0)
	{
		
		if(path==NULL)
		path = (pathern*)malloc(sizeof(pathern)*(nbPath+1));
		else
		{
			free(path);
			path = (pathern*)malloc(sizeof(pathern)*(nbPath+1));
			
		}
		
		for(int k=0;k<=nbPath;k++)
		{
		
		path[k].nbSeg=0;
		path[k].size=0;
		path[k].time=0;
		
		
			for(int i=0;i<=nbSeg;i++)
			{
				if(allSeg[i].path==k)
				{
					path[k].nbSeg++;
					path[k].size+=allSeg[i].size;
					path[k].time=path[k].nbSeg*0.02;
					
				}
				
			}
		}
		
		
		
	}
	
	return path;
}

float getMinSize(int nbPath, pathern* path, float page)
{
	
	float size=-1;
	if(page==5 && path!=NULL && nbPath>0)
	{
		size=path[1].size;
		for(int i=1;i<=nbPath;i++)
		{
			if(path[i].size < size)
				size= path[i].size;
		}
	}
	
	return size;
}

float getMaxSize(int nbPath, pathern* path, float page)
{
	
	float size=-1;
	if(page==5 && path!=NULL && nbPath>0)
	{
		size=path[1].size;
		for(int i=1;i<=nbPath;i++)
		{
			if(path[i].size > size)
				size= path[i].size;
		}
	}
	
	return size;
}

float getAverageSize(int nbPath, pathern* path, float page)
{
	float size=-1;
	if(page==5 && path!=NULL)
	{
		size=0;
		for(int i=1;i<=nbPath;i++)
		{
			size += path[i].size;
		}
		size=size/nbPath;
	}
	
	return size;
	
}

droite initialiseDroite(segment S)
{
	droite d;
	
	if(S.p0.x == S.p1.x)
	{
		d.a=1;
		d.b=0;
		d.c=-S.p0.x;
	}
	else
	{
		d.a=S.p0.y-S.p1.y;
		d.b=S.p1.x-S.p0.x;
		d.c=(S.p0.x*S.p1.y)-(S.p1.x*S.p0.y);
	}
	
	return d;
}

void exprimeEquationDroite(char expression[30], droite d)
{
	strcpy(expression,"");
	
	char A[5];
	char B[5];
	char C[5];
	
	sprintf(A,"%d",d.a);
	sprintf(B,"%d",d.b);
	sprintf(C,"%d",d.c);
	
	strcat(expression,A);
	strcat(expression,"x");
	if(d.b > 0)
	{
		strcat(expression,"+");
		strcat(expression,B);
		strcat(expression,"y");
	}
	else if (d.b < 0)
	{
		strcat(expression,B);
		strcat(expression,"y");
	}
	if(d.c > 0)
	{
		strcat(expression,"+");
		strcat(expression,C);
	}
	if (d.c < 0)
		strcat(expression,C);
	
	strcat(expression,"=0");
	
}

void getEqSegments(segment* allSegments, int nbSeg)
{
	
	for(int i=1; i<nbSeg;i++)
	{
		
		allSegments[i].d = initialiseDroite(allSegments[i]);
		exprimeEquationDroite(allSegments[i].eq, allSegments[i].d);
	}
}

void manageQuitButtonFromPage6(int x, int y, float* page)
{
	if(*page == 6) // this button is part of the page 6
	{
		if(x>432 && x<864 && y>230 && y<380)
		{
			termineBoucleEvenements();
		}
	}
}

void manageHomePageButtonFromPage6(int x, int y, float* page, float* cpt60, int* numWord, pts* allPoints, int* nbPts, int* nbPath, float* minSize, float* maxSize, float* averageSize, segment* allSeg)
{
	if(*page == 6) // this button is part of the page 6
	{
		if(x>432 && x<864 && y>400 && y<550)
		{
			*page=0;
			*cpt60=60; // replace the counter to is initial value (60)
			*numWord=0;
			*nbPts = 0;
			*nbPath = -1;
			*minSize = -1;
			*maxSize = -1;
			*averageSize = -1;
			*minSize = -1;
			*minSize = -1;
		}
	}
}

void getDrawSize(float page, int* drawSize, int rec, int x, int y)
{
	if(page==3)
	{
		if(rec==1)
		{
			if(y>490 && y<510)
			{
				if(x>=698 && x<=largeurFenetre()-298)
					*drawSize=(abscisseSouris()-698)/20;
				else if(x<698)
					*drawSize=0;
				else if(x>largeurFenetre()-298)
					*drawSize=15;
			}
		}
	}	
}

void getDrawColor(float page, color* drawColor, int rec, int x, int y)
{
	if(page==3)
	{
		if(rec==1)
		{
			// red
			if(y>415 && y<435)
			{
				if(x>=800 && x<=1055)
					drawColor->r=abscisseSouris()-800;
				else if(x<800)
					drawColor->r=0;
				else if(x>1055)
					drawColor->r=255;
			}
			
			// green 800,350,1055,350);
			if(y>340 && y<360)
			{
				if(x>=800 && x<=1055)
					drawColor->g=abscisseSouris()-800;
				else if(x<800)
					drawColor->g=0;
				else if(x>1055)
					drawColor->g=255;
			}
			
			// green 800,350,1055,350);
			if(y>270 && y<290)
			{
				if(x>=800 && x<=1055)
					drawColor->b=abscisseSouris()-800;
				else if(x<800)
					drawColor->b=0;
				else if(x>1055)
					drawColor->b=255;
			}
		}
	}	
}

void getThemeColor(float page, int x, int y, colorsTab* c)
{
	if(page==3)
	{
		if(y>610 && y<650) // main color
		{
			if(x>800 && x<840)
				c->color1 = c->lightblue;
			if(x>860 && x<900)
				c->color1 = c->red;
			if(x>920 && x<960)
				c->color1 = c->black;
			if(x>980 && x<1020)
				c->color1 = c->yellow;
		}
		
		if(y>550 && y<590) // minor color
		{
			if(x>800 && x<840)
				c->color2 = c->lightblue;
			if(x>860 && x<900)
				c->color2 = c->red;
			if(x>920 && x<960)
				c->color2 = c->black;
			if(x>980 && x<1020)
				c->color2 = c->yellow;
		}
	}
}
















