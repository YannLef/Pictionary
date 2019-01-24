#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFX/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFX/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFX/ESLib.h" // Pour utiliser valeurAleatoire()
#include "structures.h"
#include "affichage.h"
#include "calcul.h"

void displayPage0(float page, DonneesImageRGB* pictionaryImage, colorsTab c, DonneesImageRGB* settingsImage)
{
	
	if(page==0)
	{
		// concerning PLAY button
		button playButton;
		initButton(&playButton,432,400,864,550,50,"PLAY",&(c.color1),&(c.color2));
		displayButton(playButton);
		
		// concerning RULES button
		button rulesButton;
		initButton(&rulesButton,432,230,864,380,50,"RULES",&(c.color1),&(c.color2));
		displayButton(rulesButton);
		
		// concerning QUIT button
		button quitButton;
		initButton(&quitButton,432,60,864,210,50,"QUIT",&(c.color1),&(c.color2));
		displayButton(quitButton);
		
		// concerning settings logo
		if (settingsImage != NULL) // If picture loading succeed
		//printf("test\n");
			{
				
				ecrisImage(largeurFenetre()-40-settingsImage->largeurImage, 40, settingsImage->largeurImage, settingsImage->hauteurImage, settingsImage->donneesRGB);
			}
			
		
		// concerning PICTIONARY logo
		if (pictionaryImage != NULL) // If picture loading succeed
			{
				ecrisImage((largeurFenetre()-pictionaryImage->largeurImage)/2, 650, pictionaryImage->largeurImage, pictionaryImage->hauteurImage, pictionaryImage->donneesRGB);
			}
			
		
		
	}
}

void displayPoints(pts* allPoints, int nbPts, float page, int drawSize, color drawColor)
{
	if(page==5)
	{
		couleurCourante(drawColor.r,drawColor.g,drawColor.b);
		epaisseurDeTrait(drawSize);
		for(int i=0;i<nbPts;i++)
		{
			if(allPoints[i].x != -1)
			{
				point(allPoints[i].x,allPoints[i].y);
			}
		}
	}
}



void displaySegments(segment* s, int nbPts, float page, int nbSeg, int drawSize, color drawColor)
{
	epaisseurDeTrait(drawSize);
	if(page==5)
	{
		for(int i=1;i<nbSeg;i++)
		{
				ligne(s[i].p0.x,s[i].p0.y,s[i].p1.x,s[i].p1.y);
		}
	}
}

void displayPage2(float page, colorsTab c)
{
	if(page == 2)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("RULES",60,(largeurFenetre()-tailleChaine("RULES",60))/2,700);
		
		epaisseurDeTrait(2);
		
		// concerning first rule
		afficheChaine("1. Choose your difficulty: easy, medium or hard",35,(largeurFenetre()-tailleChaine("1. Choose your difficulty: easy, medium or hard",35))/2,600);
		
		// concerning second rule
		afficheChaine("2. Look at the word written on the card, be careful:",35,(largeurFenetre()-tailleChaine("2. Look at the word written on the card, and careful:",35))/2,500);
		afficheChaine("the word will last for only 3 seconds..",35,(largeurFenetre()-tailleChaine("the word will last for only 3 seconds..",35))/2,450);
		
		// concerning third rule
		afficheChaine("3. Draw the word, be careful:",35,(largeurFenetre()-tailleChaine("3. Draw the word, be careful:",35))/2,350);
		afficheChaine("you will have only 60 seconds to draw it",35,(largeurFenetre()-tailleChaine("you will have only 60 seconds to draw it",35))/2,300);
		
		// concerning QUIT button
		button quitButton;
		initButton(&quitButton,432,60,864,210,50,"QUIT",&(c.color1),&(c.color2));
		displayButton(quitButton);
	}
}

void displayPage3(float page, colorsTab c, int drawSize)
{
	if(page == 3)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("SETTINGS",60,(largeurFenetre()-tailleChaine("SETTINGS",60))/2,700);
		
		// concerning coming soon ..
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(2);
		afficheChaine("more settings coming soon ...",30,(largeurFenetre()-tailleChaine("more settings coming soon ...",30))/2,800);
		
		//concerning theme color
		epaisseurDeTrait(2);
		afficheChaine("theme color :",30,400,620);
		
		//main
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("main :",30,663,620);
			
			//lightblue
			couleurCourante(c.lightblue.r,c.lightblue.g,c.lightblue.b);
			rectangle(800,610,840,650);
			
			//red
			couleurCourante(c.red.r,c.red.g,c.red.b);
			rectangle(860,610,900,650);
			
			//black
			couleurCourante(c.black.r,c.black.g,c.black.b);
			rectangle(920,610,960,650);
			
			//yellow
			couleurCourante(c.yellow.r,c.yellow.g,c.yellow.b);
			rectangle(980,610,1020,650);
		
		//minor
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("minor :",30,650,560);
		
			//lightblue
			couleurCourante(c.lightblue.r,c.lightblue.g,c.lightblue.b);
			rectangle(800,550,840,590);
			
			//red
			couleurCourante(c.red.r,c.red.g,c.red.b);
			rectangle(860,550,900,590);
			
			//black
			couleurCourante(c.black.r,c.black.g,c.black.b);
			rectangle(920,550,960,590);
			
			//yellow
			couleurCourante(c.yellow.r,c.yellow.g,c.yellow.b);
			rectangle(980,550,1020,590);
		
		// concerning drawSize
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("drawing size :",30,400,495);
		epaisseurDeTrait(4);
		couleurCourante(0,0,0);
		ligne(698,500,largeurFenetre()-298,500);
		epaisseurDeTrait(20);
			point(698+drawSize*20,500); // drawSize goes from 0 to 15, and pixels available go from 698 to 998 (300) => proportionality x20 :0x20=0 and 15*20 = 300 :)
			
		epaisseurDeTrait(2);
		char ch[3];
		sprintf(ch,"%d",drawSize);
		
		afficheChaine(ch,30,largeurFenetre()-270,495);
		
		// concerning drawColor
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("drawing color :",30,400,420);
		
		couleurCourante(c.drawColor.r,c.drawColor.g,c.drawColor.b);
		rectangle(1160,260,1200,445);
		
		// red
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("red :",30,650,420);
		
		epaisseurDeTrait(4);
		couleurCourante(c.drawColor.r,0,0);
		ligne(800,425,1055,425);
		
		epaisseurDeTrait(20);
			point(800+c.drawColor.r,425); // drawColor goes from 0 to 255, and pixels available go from 800 to 1055 (255) => proportionality x1
		
		rectangle(1100,405,1140,445);
			
		// green
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("green :",30,615,350);
		
		epaisseurDeTrait(4);
		couleurCourante(0,c.drawColor.g,0);
		ligne(800,350,1055,350);
		
		epaisseurDeTrait(20);
			point(800+c.drawColor.g,350); // drawColor goes from 0 to 255, and pixels available go from 800 to 1055 (255) => proportionality x1
			
		rectangle(1100,330,1140,370);
			
		// blue
		epaisseurDeTrait(2);
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		afficheChaine("blue :",30,640,280);
		
		epaisseurDeTrait(4);
		couleurCourante(0,0,c.drawColor.b);
		ligne(800,280,1055,280);
		
		epaisseurDeTrait(20);
			point(800+c.drawColor.b,280); // drawColor goes from 0 to 255, and pixels available go from 800 to 1055 (255) => proportionality x1
		
		rectangle(1100,260,1140,300);
		
		// concerning QUIT button
		button quitButton;
		initButton(&quitButton,432,60,864,210,50,"QUIT",&(c.color1),&(c.color2));
		displayButton(quitButton);
		
		// concerning warning
		epaisseurDeTrait(2);
		couleurCourante(255,0,0);
		afficheChaine("*make sure that the main color is different from the drawing color or you won't see what you're drawing",20,(largeurFenetre()-tailleChaine("*make sure that the main color is different from the drawing color or you won't see what you're drawing",20))/2,20);
		
	}
}

void displayPage1(float page, colorsTab c, DonneesImageRGB* crossImage)
{
	if(page == 1)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("CHOOSE A CARD",60,(largeurFenetre()-tailleChaine("CHOOSE A CARD",60))/2,700);
		
		// concerning EASY card
		button easyButton;
		initButton(&easyButton,largeurFenetre()/20,150,6.33*(largeurFenetre())/20,600,50,"EASY",&(c.color1),&(c.color2));
		displayButton(easyButton);
		
		// concerning MEDIUM card
		button mediumButton;
		initButton(&mediumButton,7.33*(largeurFenetre()/20),150,12.66*(largeurFenetre()/20),600,50,"MEDIUM",&(c.color1),&(c.color2));
		displayButton(mediumButton);
		
		// concerning HARD card
		button hardButton;
		initButton(&hardButton,13.66*(largeurFenetre()/20),150,19*(largeurFenetre()/20),600,50,"HARD",&(c.color1),&(c.color2));
		displayButton(hardButton);
		
		// concerning CROSS logo
		if (crossImage != NULL) // If picture loading succeed
			{
				ecrisImage(30, hauteurFenetre()-30-crossImage->hauteurImage, crossImage->largeurImage, crossImage->hauteurImage, crossImage->donneesRGB);
			}
	}
}

void displayPage4(float page, colorsTab c, DonneesImageRGB* crossImage, int difficulty, char word[30])
{
	if(page == 4)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("YOUR WORD:",60,(largeurFenetre()-tailleChaine("YOUR WORD:",60))/2,700);
		epaisseurDeTrait(7);
		afficheChaine(word,120,(largeurFenetre()-tailleChaine(word,120))/2,400);
		
		
		// concerning CROSS logo
		if (crossImage != NULL) // If picture loading succeed
			{
				ecrisImage(30, hauteurFenetre()-30-crossImage->hauteurImage, crossImage->largeurImage, crossImage->hauteurImage, crossImage->donneesRGB);
			}
			
		// concerning the counter
		couleurCourante(c.color1.r,c.color1.g,c.color1.b);
		rectangle(largeurFenetre()-100,hauteurFenetre()-100,largeurFenetre()-30,hauteurFenetre()-30);
		
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(2);
		afficheChaine("time left :",20,1070,hauteurFenetre()-70);
	}
}

void afficheCpt3(float cpt3, float page, colorsTab c)
{
	if(page == 4) // this counter is part of the page 4
	{
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(2);
		
		char ch[20];
		sprintf(ch,"%.2f",cpt3);
		
		afficheChaine(ch,20,largeurFenetre()-100+(70-tailleChaine(ch,20))/2,hauteurFenetre()-70);
	}
}

void displayPage5(float page, colorsTab c, DonneesImageRGB* crossImage, int difficulty)
{
	if(page == 5)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("TIME TO DRAW :",60,(largeurFenetre()-tailleChaine("TIME TO DRAW :",60))/2,700);
		
		// concerning drawing area
		couleurCourante(c.color1.r,c.color1.g,c.color1.b);
		rectangle(largeurFenetre()/10,hauteurFenetre()/10,9*largeurFenetre()/10,7*hauteurFenetre()/10);
		
		// concerning CROSS logo
		if (crossImage != NULL) // If picture loading succeed
			{
				ecrisImage(30, hauteurFenetre()-30-crossImage->hauteurImage, crossImage->largeurImage, crossImage->hauteurImage, crossImage->donneesRGB);
			}
			
		// concerning the counter
		couleurCourante(c.color1.r,c.color1.g,c.color1.b);
		rectangle(largeurFenetre()-100,hauteurFenetre()-100,largeurFenetre()-30,hauteurFenetre()-30);
		
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(2);
		afficheChaine("time left :",20,1070,hauteurFenetre()-70);
	}
}

void afficheCpt60(float cpt60, float page, colorsTab c)
{
	if(page == 5) // this counter is part of the page 4
	{
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(2);
		
		char ch[20];
		sprintf(ch,"%.2f",cpt60);
		
		afficheChaine(ch,20,largeurFenetre()-100+(70-tailleChaine(ch,20))/2,hauteurFenetre()-70);
	}
}

void displayPage6(float page, colorsTab c)
{
	if(page == 6)
	{
		// concerning title
		couleurCourante(c.color2.r,c.color2.g,c.color2.b);
		epaisseurDeTrait(4);
		afficheChaine("THE END",60,(largeurFenetre()-tailleChaine("THE END",60))/2,700);
		
		// concerning HOME PAGE button
		button homePageButton;
		initButton(&homePageButton,432,400,864,550,50,"HOME PAGE",&(c.color1),&(c.color2));
		displayButton(homePageButton);
		
		// concerning QUIT button
		button quitButton;
		initButton(&quitButton,432,230,864,380,50,"QUIT",&(c.color1),&(c.color2));
		displayButton(quitButton);
	}
}



