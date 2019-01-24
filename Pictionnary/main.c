#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GFX/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFX/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFX/ESLib.h" // Pour utiliser valeurAleatoire()
#include "structures.h"
#include "affichage.h"
#include "calcul.h"


// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1296
#define HauteurFenetre 864

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB *pictionaryImage = NULL; // Pictionary picture
	static DonneesImageRGB *settingsImage = NULL; // Settings picture
	static DonneesImageRGB *crossImage = NULL; // Settings picture
	static float page=0; // determine which page has to be display
	static colorsTab colorTab; // color palett that countains every color we might use (in order to simplify the code)
	static int nbPts=0; // number of points drawn by the user
	static pts* allPoints; // all poitns drawn by the user
	static segment* allSegments=NULL; // all segments drawn by the user
	static int rec=0; // if rec=1 => user is clicking whith the mouse
	static float cpt3=3; // 3 seconds counter
	static float cpt60=60; // 60 seconds counter
	static int difficulty=0; // difficulty choosen by user
	static int numWord=0; // number of the word randomly choosen
	static char word[30]; // word randomly choosen depending on difficulty
	static int nbSeg=1; // number of segments
	static int nbPath=-1; // number of path, start to -1 because it will increase by one when the program started (=> =0)
	static pathern* path=NULL;
	static float minSize; // minimum size of a path
	static float maxSize; // maximum size of a path
	static float averageSize; // average size of a path
	static int drawSize= 5; // size of segments that are displayed
		
	switch (evenement)
	{
		case Initialisation:
			pictionaryImage = lisBMPRGB("pictionary.bmp"); // load the pictionary picture
			settingsImage = lisBMPRGB("set.bmp"); // load the settings picture
			crossImage = lisBMPRGB("cross.bmp"); // load the cross picture
			
			initColorsTab(&colorTab); // initialise the color pallet
			
			
			demandeTemporisation(20);
			break;
		
		case Temporisation:
		
				manageCpt3(&cpt3, &page); // manage the counter of 3 sec
				manageCpt60(&cpt60, &page, difficulty, word, nbPts, nbSeg, path, nbPath, minSize, maxSize, averageSize, allPoints, allSegments); // manage the counter of 60 sec
				allPoints = getPoints(allPoints, &nbPts, rec, page, &nbPath); // determine points drawn out by the user
				allSegments = getSegments(allPoints, nbPts, &nbSeg, nbPath, allSegments); // determine segments using previous points
				getSizeSegments(allSegments, nbSeg); // determine the size of each segment
				path=getpath(path, nbSeg, nbPath, allSegments, page); // determine path ( additions of several segments)
				minSize = getMinSize(nbPath, path, page); // determine minimum size of path
				maxSize = getMaxSize(nbPath, path, page); // determine maximum size of path
				averageSize = getAverageSize(nbPath, path, page); // determine average size of path
				getEqSegments(allSegments, nbSeg); // determine all segments equations
				getDrawSize(page, &drawSize, rec, abscisseSouris(), ordonneeSouris()); // determine the size of the drawing according to settings
				getDrawColor(page, &(colorTab.drawColor), rec, abscisseSouris(), ordonneeSouris()); // determine the color of the drawing according to settings
				
				
		
			rafraichisFenetre();
			break;
			
		case Affichage:
		
			// Start with a white background
			effaceFenetre (255, 255, 255);
			
			// Display page 0 (home page)
			displayPage0(page, pictionaryImage, colorTab, settingsImage);
			
			// Display page 1 (choose a card)
			displayPage1(page, colorTab, crossImage);

			// Display page 2 (rules page)
			displayPage2(page, colorTab);
			
			// Display page 3 (settings page)
			displayPage3(page, colorTab, drawSize);
			
			// Display page 4 (play page)
			displayPage4(page, colorTab, crossImage, difficulty, word);
			
			// Display page 5 (play page)
			displayPage5(page, colorTab, crossImage, difficulty);
			
			// Display the counter of 3 sec (page 4 only)
			afficheCpt3(cpt3, page, colorTab);
			
			// Display the counter of 60 sec (page 5 only)
			afficheCpt60(cpt60, page, colorTab);
			
			// Display all points
			displayPoints(allPoints, nbPts, page, drawSize, colorTab.drawColor);
			
			// Display all segments
			displaySegments(allSegments, nbPts, page, nbSeg, drawSize, colorTab.drawColor);
			
			// Display page 6 (the end page)
			displayPage6(page, colorTab);
			
			// load a random word from file in order to display it to the user
			loadWord(page, difficulty, &numWord, word);
			
			
			
			
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
				
					libereDonneesImageRGB(&pictionaryImage);
					libereDonneesImageRGB(&settingsImage);
					libereDonneesImageRGB(&crossImage);
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				rec=1;
				
				
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				rec=0;
				manageEasyButtonFromPage1(abscisseSouris(), ordonneeSouris(), &page, &difficulty); // manage any clic on easy button from page 1 (choose a card page)
				manageMediumButtonFromPage1(abscisseSouris(), ordonneeSouris(), &page, &difficulty); // manage any clic on easy button from page 1 (choose a card page)
				manageHardButtonFromPage1(abscisseSouris(), ordonneeSouris(), &page, &difficulty); // manage any clic on easy button from page 1 (choose a card page)
				managePlayButtonFromPage0(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on the play button from page 0 (home page)
				manageRulesButtonFromPage0(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on rules button from page 0 (home page)
				manageQuitButtonFromPage0(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on quit button from page 0 (home page)
				manageQuitButtonFromPage2(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on quit button from page 2 (rules page)
				manageSettingsButtonFromPage0(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on settings button from page 0 (home page)
				manageQuitButtonFromPage3(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on quit button from page 1 (settings page)
				manageQuitButtonFromPage1(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on quit button from page 1 (choose a card page)
				manageQuitButtonFromPage4(abscisseSouris(), ordonneeSouris(), &page, &cpt3, &numWord); // manage any clic on quit button grom page 4 (play page)
				manageQuitButtonFromPage5(abscisseSouris(), ordonneeSouris(), &page, &cpt60, &numWord, allPoints, &nbPts, &nbPath, &minSize, &maxSize, &averageSize, allSegments); // manage any clic on quit button grom page 5 (play page)
				manageQuitButtonFromPage6(abscisseSouris(), ordonneeSouris(), &page); // manage any clic on the quit button from page 6 (end page)
				manageHomePageButtonFromPage6(abscisseSouris(), ordonneeSouris(), &page, &cpt60, &numWord, allPoints, &nbPts, &nbPath, &minSize, &maxSize, &averageSize, allSegments); // manage any clic on the home page button from page 6 (end page)
				getThemeColor(page, abscisseSouris(), ordonneeSouris(), &colorTab);
				
				
				
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}
