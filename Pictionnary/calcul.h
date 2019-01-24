pts* getPoints(pts* allPoints, int* nbPts, int rec, float page, int* nbPath);

segment* getSegments(pts* p, int nbPts, int* nbSeg, int nbPath, segment* allSeg);

void managePlayButtonFromPage0(int x, int y, float* page);

void manageRulesButtonFromPage0(int x, int y, float* page);

void manageSettingsButtonFromPage0(int x, int y, float* page);

void manageQuitButtonFromPage0(int x, int y, float* page);

void manageQuitButtonFromPage2(int x, int y, float* page);

void manageQuitButtonFromPage3(int x, int y, float* page);

void manageQuitButtonFromPage1(int x, int y, float* page);

void manageEasyButtonFromPage1(int x, int y, float* page, int* difficulty);

void manageCpt3(float* cpt3, float* page);

void manageQuitButtonFromPage4(int x, int y, float* page, float* cpt3, int* numWord);

void manageMediumButtonFromPage1(int x, int y, float* page, int* difficulty);

void manageHardButtonFromPage1(int x, int y, float* page, int* difficulty);

void manageQuitButtonFromPage5(int x, int y, float* page, float* cpt60, int* numWord, pts* allPoints, int* nbPts, int* nbPath, float* minSize, float* maxSize, float* averageSize, segment* allSeg);

void manageCpt60(float* cpt60, float* page, int difficulty, char word[30], int nbPts, int nbSeg, pathern* path, int nbPath, float minSize, float maxSize, float averageSize, pts* allPoints, segment* allSeg);

void loadWord(float page, int difficulty, int* numWord, char word[30]);

void save(int difficulty, float page, char word[30], int nbPts, int nbSeg, pathern* path, int nbPath, float minSize, float maxSize, float averageSize, pts* allPoints, segment* allSeg);

void getSizeSegments(segment* allSegments, int nbSeg);

pathern* getpath(pathern* path, int nbSeg, int nbPath, segment* allSeg, float page);

float getMinSize(int nbPath, pathern* path, float page);

float getMaxSize(int nbPath, pathern* path, float page);

float getAverageSize(int nbPath, pathern* path, float page);

droite initialiseDroite(segment S);

void exprimeEquationDroite(char expression[30], droite d);

void getEqSegments(segment* allSegments, int nbSeg);

void manageQuitButtonFromPage6(int x, int y, float* page);

void manageHomePageButtonFromPage6(int x, int y, float* page, float* cpt60, int* numWord, pts* allPoints, int* nbPts, int* nbPath, float* minSize, float* maxSize, float* averageSize, segment* allSeg);

void getDrawSize(float page, int* drawSize, int rec, int x, int y);

void getDrawColor(float page, color* drawColor, int rec, int x, int y);

void getThemeColor(float page, int x, int y, colorsTab* c);
