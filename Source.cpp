#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;
struct player {
	int highscore;
	string name;
}p[15];
RenderWindow window(VideoMode(1000, 700), "PAC MAN");
fstream allScores, name;
int fileSize = 0;
Texture menubg;
Sprite menuback;
Texture pacmanbg;
Sprite pacmanback;
Texture pac;
Sprite pacman;
const float pacmanscale = 1.5;
Texture die;
Texture ghost1;
Sprite ghostb;
Texture ghost2;
Sprite ghostp;
Texture ghost3;
Sprite ghostr;
Texture ghost4;
Sprite ghostg;
Texture ghost5;
Sprite ghosto;
Texture ghost6;
Sprite ghostbr;
Texture lives1;
const int cons = 4;
Sprite lives2[cons];
Font men;
Text menu[4];
Text pmenu[3];
Font sco;
Text scor;
Text paus;
Font endgame;
Text over;
Text victor;
Font star;
Text spacetostart;
Text logo;
Font koulen;
Text enterforname;
SoundBuffer diebuffer;
Sound diesound;
SoundBuffer eat;
Sound eatsound;
SoundBuffer playingbuffer;
Sound playingsound;
Music gamemusic;
SoundBuffer go;
Sound gameover;
Clock  dieclock, dclock, bclock, gclock, pclock, rclock, oclock, brclock, animation_clock, deltaclock, mouseclock;
int  xanimation_indicator = 0, yanimation_indicator = 0, die_indicator = 0, nav = 0, lives = 4, score = 0, phase = 0;
bool menuwind = true, pausewind = false, nodiagonal = true, startmove = false, blevel1 = false, blevel2 = false, pacpos1 = false, pacpos2 = false;
bool dead = false, bdying = false, rdying = false, pdying = false, gdying = false, odying = false, brdying = false, ghostpos1 = false, ghostpos2 = false;
bool moveghostb1 = 1, moveghostb2 = 1, moveghostr1 = 1, moveghostr2 = 1, moveghostg1 = 1, moveghostg2 = 1, moveghostp1 = 1, moveghostp2 = 1, moveghosto = 1, moveghostbr = 1;
bool pacolor = 0;
bool mainmenu();
void pacdie(bool dying);
bool pausemenu();
void ghostmovex(Sprite& ghost, Clock& cclock, bool& movingghost, bool blevel, int speed, int start, int end);
void ghostmovey(Sprite& ghost, Clock& cclock, bool& movingghost, bool blevel, int speed, int start, int end);
void getName(player arr[]);
void displayHighscore(player arr[], int);
void sortArray(player p[], int size);
void credits();

int main()
{

	allScores.open("gamedata/allScores.txt", ios::in);
	if (allScores.is_open()) {
		int num;
		int i = 0;
		while (allScores >> num) {
			p[i].highscore = num;
			i++;
		}
		allScores.close();
	}

	name.open("gamedata/name.txt", ios::in);
	if (name.is_open()) {
		string line;
		int i = 0;
		while (getline(name, line)) {
			p[i].name = line;
			i++;
			fileSize++;
		}
		name.close();
	}
	float deltaTime = 0;
	Mouse ms;
	pacmanbg.loadFromFile("./pacmanbg.jpg");
	pacmanback.setTexture(pacmanbg);
	pac.loadFromFile("./pacman.png");
	pacman.setTexture(pac);
	pacman.setPosition(Vector2f(230, 340));
	pacman.setScale(pacmanscale, pacmanscale);
	pacman.setTextureRect(IntRect(0, 0, 16, 16));
	pacman.setOrigin(pacman.getLocalBounds().width / 2, pacman.getLocalBounds().height / 2);
	die.loadFromFile("./die.png");
	ghost1.loadFromFile("./blue.png");
	ghostb.setTexture(ghost1);
	ghostb.setScale(0.15, 0.15);
	ghost2.loadFromFile("./pink.png");
	ghostp.setTexture(ghost2);
	ghostp.setScale(0.08, 0.08);
	ghost3.loadFromFile("./red.png");
	ghostr.setTexture(ghost3);
	ghostr.setScale(0.08, 0.08);
	ghost4.loadFromFile("./green.png");
	ghostg.setTexture(ghost4);
	ghostg.setScale(0.10, 0.10);
	ghost5.loadFromFile("./orange.png");
	ghosto.setTexture(ghost5);
	ghosto.setScale(0.12, 0.12);
	ghost6.loadFromFile("./brown.png");
	ghostbr.setTexture(ghost6);
	ghostbr.setScale(0.25, 0.25);
	lives1.loadFromFile("./lives.png");
	for (size_t i = 0; i < cons; i++) {
		Sprite lives3(lives1);
		lives3.setPosition(12, 485 + (i * 40));
		lives3.setScale(0.02, 0.02);
		lives2[i] = lives3;
	}
	sco.loadFromFile("./Bullpen3D.ttf");
	scor.setFont(sco);
	scor.setString("SCORE :" + to_string(score));
	scor.setFillColor(Color::Cyan);
	scor.setPosition(0, 0);
	scor.setCharacterSize(32);
	paus.setFont(sco);
	paus.setString("PAUSE");
	paus.setFillColor(Color::Cyan);
	paus.setPosition(0, 40);
	paus.setCharacterSize(32);
	endgame.loadFromFile("./CollegiateFLF.ttf");
	over.setFont(endgame);
	over.setString("GAME OVER !");
	over.setFillColor(Color::Red);
	over.setPosition(310, 250);
	over.setCharacterSize(70);
	victor.setFont(endgame);
	victor.setString("VICTORY !");
	victor.setFillColor(Color::Green);
	victor.setPosition(320, 250);
	victor.setCharacterSize(70);
	star.loadFromFile("./BodoniFLF-Bold.ttf");
	spacetostart.setFont(star);
	spacetostart.setString("PRESS SPACE TO START.");
	spacetostart.setFillColor(Color::Yellow);
	spacetostart.setPosition(300, 140);
	spacetostart.setCharacterSize(40);
	koulen.loadFromFile("./Koulen.ttf");
	enterforname.setFont(koulen);
	enterforname.setString("PRESS SPACE TO SAVE HIGHSCORE.");
	enterforname.setFillColor(Color::White);
	enterforname.setPosition(300, 330);
	enterforname.setCharacterSize(40);
	eat.loadFromFile("./Laser_Shoot.wav");
	eatsound.setBuffer(eat);
	diebuffer.loadFromFile("./pacman-is-dead.wav");
	diesound.setBuffer(diebuffer);
	go.loadFromFile("./ggg.wav");
	gameover.setBuffer(go);
	gameover.setVolume(230);
	playingbuffer.loadFromFile("./playing2.ogg");
	playingsound.setBuffer(playingbuffer);
	playingsound.play();
	playingsound.setLoop(true);
	playingsound.setVolume(600);
	gamemusic.openFromFile("./police2.wav");
	gamemusic.setVolume(10);
	gamemusic.play();
	gamemusic.setLoop(true);

	int arr[35][25] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 2, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 2, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 2, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};
	RectangleShape r[35][25];
	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			r[i][j].setFillColor(Color(90, 100, 100, 150));
			r[i][j].setFillColor(Color::Transparent);
			r[i][j].setSize(Vector2f(40, 20));
			r[i][j].setPosition(j * 40, i * 20);
		}
	}
	int arr2[35][25] = {
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 1, 1, 0, 0, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	RectangleShape r2[35][25];
	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			r2[i][j].setFillColor(Color(50, 100, 180, 255));
			r2[i][j].setSize(Vector2f(40, 20));
			r2[i][j].setPosition(j * 40, i * 20);
		}
	}
	CircleShape s[35][25];
	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			s[i][j].setFillColor(Color(255, 150, 150, 255));
			s[i][j].setRadius(3);
			s[i][j].setScale(0.7, 0.7);
			s[i][j].setOrigin(1.5, 1.5);
			s[i][j].setPosition((j * 40) + 15, (i * 20) + 10);
		}
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (blevel1 && ghostpos1) {
			ghostb.setPosition(318, 150);
			ghostp.setPosition(830, 25);
			ghostr.setPosition(190, 625);
			ghostg.setPosition(718, 500);
			ghostpos1 = false;
		}
		if (blevel2 && ghostpos2) {
			ghostb.setPosition(297, 145);
			ghostp.setPosition(915, 63);
			ghostr.setPosition(903, 657);
			ghostg.setPosition(963, 657);
			ghosto.setPosition(530, 450);
			ghostbr.setPosition(462, 555);
			spacetostart.setFillColor(Color::Yellow);
			ghostpos2 = false;
		}
		if (blevel1 && pacpos1) {
			pacman.setPosition(Vector2f(230, 340));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					s[i][j].setScale(0.7, 0.7);
				}
			}
			pacpos1 = false;
		}
		if (blevel2 && pacpos2) {
			pacman.setPosition(Vector2f(400, 255));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					s[i][j].setScale(0.7, 0.7);
				}
			}
			pacpos2 = false;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) ||
			(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)))
		{
			nodiagonal = false;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) ||
			(Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down)))
		{
			nodiagonal = false;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right)) && nodiagonal == true && startmove == true && !dead && pacman.getPosition().x < 980) {
			pacman.move(Vector2f(2 * deltaTime, 0));
			if (animation_clock.getElapsedTime().asSeconds() > 0.2) {
				xanimation_indicator++;
				animation_clock.restart();
			}
			pacman.setScale(pacmanscale, pacmanscale);
			xanimation_indicator = xanimation_indicator % 3;
			pacman.setTextureRect(IntRect(xanimation_indicator * 16, 0, 16, 16));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr[i][j] == 1 && pacman.getGlobalBounds().intersects(r[i][j].getGlobalBounds()) && blevel1 == true)
						pacman.move(Vector2f(-2 * deltaTime, 0));
					if (arr2[i][j] == 1 && pacman.getGlobalBounds().intersects(r2[i][j].getGlobalBounds()) && blevel2 == true)
						pacman.move(Vector2f(-2 * deltaTime, 0));
				}
			}
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left)) && nodiagonal == true && startmove == true && !dead && pacman.getPosition().x > 50) {
			pacman.move(Vector2f(-2 * deltaTime, 0));
			if (animation_clock.getElapsedTime().asSeconds() > 0.2) {
				xanimation_indicator++;
				animation_clock.restart();
			}
			pacman.setScale(-pacmanscale, pacmanscale);
			xanimation_indicator = xanimation_indicator % 3;
			pacman.setTextureRect(IntRect(xanimation_indicator * 16, 0, 16, 16));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr[i][j] == 1 && pacman.getGlobalBounds().intersects(r[i][j].getGlobalBounds()) && blevel2 == false)
						pacman.move(Vector2f(2 * deltaTime, 0));
					if (arr2[i][j] == 1 && pacman.getGlobalBounds().intersects(r2[i][j].getGlobalBounds()) && blevel2 == true)
						pacman.move(Vector2f(2 * deltaTime, 0));
				}
			}
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && nodiagonal == true && startmove == true && !dead && pacman.getPosition().y > 20) {
			pacman.move(Vector2f(0, -2 * deltaTime));
			if (animation_clock.getElapsedTime().asSeconds() > 0.2) {
				yanimation_indicator++;
				animation_clock.restart();
			}
			pacman.setScale(pacmanscale, pacmanscale);
			yanimation_indicator = yanimation_indicator % 3;
			pacman.setTextureRect(IntRect(yanimation_indicator * 16, 32, 16, 16));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr[i][j] == 1 && pacman.getGlobalBounds().intersects(r[i][j].getGlobalBounds()) && blevel1 == true)
						pacman.move(Vector2f(0, 2 * deltaTime));
					if (arr2[i][j] == 1 && pacman.getGlobalBounds().intersects(r2[i][j].getGlobalBounds()) && blevel2 == true)
						pacman.move(Vector2f(0, 2 * deltaTime));
				}
			}
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down)) && nodiagonal == true && startmove == true && !dead && pacman.getPosition().y < 680) {
			pacman.move(Vector2f(0, 2 * deltaTime));
			if (animation_clock.getElapsedTime().asSeconds() > 0.2) {
				yanimation_indicator++;
				animation_clock.restart();
			}
			pacman.setScale(pacmanscale, -pacmanscale);
			yanimation_indicator = yanimation_indicator % 3;
			pacman.setTextureRect(IntRect(yanimation_indicator * 16, 32, 16, 16));
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr[i][j] == 1 && pacman.getGlobalBounds().intersects(r[i][j].getGlobalBounds()) && blevel1 == true)
						pacman.move(Vector2f(0, -2 * deltaTime));
					if (arr2[i][j] == 1 && pacman.getGlobalBounds().intersects(r2[i][j].getGlobalBounds()) && blevel2 == true)
						pacman.move(Vector2f(0, -2 * deltaTime));
				}
			}
		}
		if (pacman.getGlobalBounds().intersects(ghostb.getGlobalBounds()) && !dead) {
			pacdie(bdying);
		}
		if (pacman.getGlobalBounds().intersects(ghostr.getGlobalBounds()) && !dead) {
			pacdie(rdying);
		}
		if (pacman.getGlobalBounds().intersects(ghostp.getGlobalBounds()) && !dead) {
			pacdie(pdying);
		}
		if (pacman.getGlobalBounds().intersects(ghostg.getGlobalBounds()) && !dead) {
			pacdie(gdying);
		}
		if (pacman.getGlobalBounds().intersects(ghosto.getGlobalBounds()) && !dead) {
			pacdie(odying);
		}
		if (pacman.getGlobalBounds().intersects(ghostbr.getGlobalBounds()) && !dead) {
			pacdie(brdying);
		}
		if (dead)
		{
			if (die_indicator <= 11 && dclock.getElapsedTime().asMilliseconds() % 23 == 0)
			{
				die_indicator++;
				pacman.setTextureRect(IntRect(0, die_indicator * 44, 44, 44));
			}
		}
		if (dieclock.getElapsedTime().asSeconds() > 2 && dead && blevel1 == true) {
			dead = false;
			pacman.setTexture(pac);
			pacman.setTextureRect(IntRect(0, 0, 16, 16));
			pacman.setPosition(Vector2f(230, 340));
		}
		if (dieclock.getElapsedTime().asSeconds() > 2 && dead && blevel2 == true) {
			dead = false;
			pacman.setTexture(pac);
			pacman.setTextureRect(IntRect(0, 0, 16, 16));
			pacman.setPosition(Vector2f(400, 255));
		}
		ghostmovey(ghostb, bclock, moveghostb1, blevel1, 15, 130, 520);
		ghostmovex(ghostr, rclock, moveghostr1, blevel1, 15, 180, 820);
		ghostmovey(ghostg, gclock, moveghostg1, blevel1, 15, 150, 520);
		ghostmovex(ghostp, pclock, moveghostp1, blevel1, 15, 190, 820);
		ghostmovey(ghostb, bclock, moveghostb2, blevel2, 20, 165, 560);
		ghostmovex(ghostr, rclock, moveghostr2, blevel2, 35, 35, 935);
		ghostmovey(ghostg, gclock, moveghostg2, blevel2, 30, 10, 640);
		ghostmovex(ghostp, pclock, moveghostp2, blevel2, 35, 115, 930);
		ghostmovex(ghosto, oclock, moveghosto, blevel2, 35, 560, 830);
		ghostmovey(ghostbr, brclock, moveghostbr, blevel2, 30, 170, 540);
		for (int i = 0; i < 35; i++) {
			for (int j = 0; j < 25; j++) {
				if (arr[i][j] == 0 && pacman.getGlobalBounds().intersects(s[i][j].getGlobalBounds()) && blevel1) {
					s[i][j].setScale(0, 0);
					score++;
					scor.setString("SCORE :" + to_string(score));
					eatsound.play();
					eatsound.setVolume(30);
				}
				if (arr2[i][j] == 0 && pacman.getGlobalBounds().intersects(s[i][j].getGlobalBounds()) && blevel2) {
					s[i][j].setScale(0, 0);
					score++;
					scor.setString("SCORE :" + to_string(score));
					eatsound.play();
					eatsound.setVolume(30);
				}
			}
		}
		if (ms.getPosition().x > 470 && ms.getPosition().x < 590 &&
			ms.getPosition().y > 270 && ms.getPosition().y < 300) {
			pacolor = 1;
		}
		else {
			pacolor = 0;
		}
		if (pacolor == 1) {
			paus.setFillColor(Color::White);
			paus.setStyle(Text::Bold);
		}
		else {
			paus.setFillColor(Color::Cyan);
			paus.setStyle(Text::Regular);
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (ms.getPosition().x > 470 && ms.getPosition().x < 590 &&
				ms.getPosition().y > 270 && ms.getPosition().y < 300) {
				pausewind = true;
			}
		}
		if (pausewind) {
			pausewind = pausemenu();
			startmove = false;
		}
		if (menuwind) {
			menuwind = mainmenu();
		}
		nodiagonal = true;

		window.clear();
		if (menuwind)
		{
			window.draw(menuback);
			for (int i = 0; i < 4; i++)
			{
				window.draw(menu[i]);
			}
		}
		if ((nav == 1 && blevel1 == true && phase == 0))
		{
			window.draw(pacmanback);
			window.draw(pacman);
			window.draw(scor);
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr[i][j] == 1)
						window.draw(r[i][j]);
					else if (arr[i][j] == 0)
						window.draw(s[i][j]);
				}
			}
			window.draw(ghostb);
			window.draw(ghostp);
			window.draw(ghostr);
			window.draw(ghostg);
			for (int i = 0; i < lives; i++) {
				window.draw(lives2[i]);
			}
			if (lives == 0) {
				gameover.play();
				window.draw(over);
				window.draw(enterforname);
				pacman.setScale(0, 0);
				pacman.setPosition(5000, 5000);
				gamemusic.setLoop(false);
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					getName(p);
				}
			}
			if (score == 360)
			{
				blevel1 = false;
				blevel2 = true;
				pacpos1 = false;
				pacpos2 = true;
				ghostpos1 = false;
				ghostpos2 = true;
				startmove = false;
			}
			window.draw(spacetostart);
			if (Keyboard::isKeyPressed(Keyboard::Space) && !pausewind) {
				spacetostart.setFillColor(Color::Transparent);
				startmove = true;
			}
			window.draw(paus);
		}
		if ((nav == 1 && blevel2 == true && phase == 0))
		{
			for (int i = 0; i < 35; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					if (arr2[i][j] == 1)
						window.draw(r2[i][j]);
					else if (arr2[i][j] == 0)
						window.draw(s[i][j]);
				}
			}
			window.draw(pacman);
			window.draw(ghostb);
			window.draw(ghostp);
			window.draw(ghostr);
			window.draw(ghostg);
			window.draw(ghosto);
			window.draw(ghostbr);
			for (int i = 0; i < lives; i++) {
				window.draw(lives2[i]);
			}
			if (lives == 0) {
				gameover.play();
				window.draw(over);
				window.draw(enterforname);
				pacman.setScale(0, 0);
				pacman.setPosition(5000, 5000);
				gameover.setVolume(250);
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					getName(p);
				}
			}
			if (score == 823) {
				window.draw(victor);
				window.draw(enterforname);
				pacman.setPosition(5000, 5000);
				pacman.setScale(0, 0);
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					getName(p);
				}
			}
			window.draw(scor);
			window.draw(spacetostart);
			if (Keyboard::isKeyPressed(Keyboard::Space) && !pausewind) {
				spacetostart.setFillColor(Color::Transparent);
				startmove = true;
			}
			window.draw(paus);
		}
		if (phase == 1) {
			menuwind = true;
			pausewind = false;
			blevel1 = false;
			blevel2 = false;
			ghostpos1 = false;
			ghostpos2 = false;
			pacpos1 = false;
			pacpos2 = false;
			startmove = false;
			spacetostart.setFillColor(Color::Yellow);
			lives = 4;
			score = 0;
			scor.setString("SCORE :" + to_string(score));
		}
		if (pausewind) {
			for (int i = 0; i < 3; i++)
			{
				window.draw(pmenu[i]);
			}
		}
		if (nav == 4)
			credits();
		if (nav == 3)
			window.close();
		window.display();
		deltaTime = deltaclock.restart().asSeconds() * 100;
	}
	return 0;
}
bool mainmenu() {
	phase = 0;
	menubg.loadFromFile("./back.png");
	menuback.setTexture(menubg);
	menuback.setScale(1.38, 1.47);
	men.loadFromFile("./Monofett-Regular.ttf");
	for (int i = 0; i < 3; i++) {
		menu[i].setFont(men);
		menu[i].setFillColor(Color{ 80, 100, 200, 255 });
		menu[i].setCharacterSize(60);
	}
	menu[0].setString("NEW GAME");
	menu[0].setPosition(380, 400);
	menu[1].setString("HIGH SCORE");
	menu[1].setPosition(350, 470);
	menu[2].setString("EXIT");
	menu[2].setPosition(440, 540);
	menu[3].setString("CREDITS");
	menu[3].setPosition(450, 640);
	menu[3].setFont(endgame);
	menu[3].setFillColor(Color::White);
	menu[3].setCharacterSize(25);
	bool color[4] = { 0 };
	Mouse ms;
	if (ms.getPosition().x > 845 && ms.getPosition().x < 1105 &&
		ms.getPosition().y > 642 && ms.getPosition().y < 687) {
		color[0] = 1;
	}
	else {
		color[0] = 0;
	}
	if (ms.getPosition().x > 815 && ms.getPosition().x < 1145 &&
		ms.getPosition().y > 712 && ms.getPosition().y < 757) {
		color[1] = 1;
	}
	else {
		color[1] = 0;
	}
	if (ms.getPosition().x > 905 && ms.getPosition().x < 1050 &&
		ms.getPosition().y > 782 && ms.getPosition().y < 827) {
		color[2] = 1;
	}
	else {
		color[2] = 0;
	}
	if (ms.getPosition().x > 918 && ms.getPosition().x < 1036 &&
		ms.getPosition().y > 870 && ms.getPosition().y < 890) {
		color[3] = 1;
	}
	else {
		color[3] = 0;
	}
	for (int i = 0; i < 4; i++) {
		if (color[i] == 1) {
			menu[i].setFillColor(Color::White);
			menu[i].setStyle(Text::Bold);
			menu[3].setFillColor(Color::Red);
		}
		else {
			menu[i].setFillColor(Color{ 80, 100, 200, 255 });
			menu[i].setStyle(Text::Regular);
			menu[3].setFillColor(Color::White);
		}
	}
	//menu navigating
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (ms.getPosition().x > 845 && ms.getPosition().x < 1105 &&
			ms.getPosition().y > 642 && ms.getPosition().y < 687) {
			lives = 4;
			score = 0;
			nav = 1;
			blevel1 = true;
			blevel2 = false;
			pacpos1 = true;
			pacpos2 = false;
			ghostpos1 = true;
			ghostpos2 = false;
			menuwind = false;
			pausewind = false, startmove = false;
			pacman.setTexture(pac);
			pacman.setTextureRect(IntRect(0, 0, 16, 16));
			pacman.setScale(pacmanscale, pacmanscale);
			spacetostart.setFillColor(Color::Yellow);
			playingsound.pause();
		}
		else if (ms.getPosition().x > 815 && ms.getPosition().x < 1145 &&
			ms.getPosition().y > 712 && ms.getPosition().y < 757) {
			menuwind = true;
			nav = 2;
			displayHighscore(p, fileSize);
		}
		else if (ms.getPosition().x > 905 && ms.getPosition().x < 1050 &&
			ms.getPosition().y > 782 && ms.getPosition().y < 827) {
			menuwind = true;
			nav = 3;
		}
		else if (ms.getPosition().x > 918 && ms.getPosition().x < 1036 &&
			ms.getPosition().y > 870 && ms.getPosition().y < 890) {
			menuwind = false;
			nav = 4;
		}
	}
	return menuwind;
}
void pacdie(bool dying) {
	lives--;
	diesound.play();
	diesound.setVolume(500);
	pacman.setTexture(die);
	dying = true;
	if (dieclock.getElapsedTime().asSeconds() > 0.3) {
		die_indicator = 0;
		dclock.restart();
		dieclock.restart();
	}
	if (dying == true) {
		dead = true;
	}
}
void ghostmovex(Sprite& ghost, Clock& cclock, bool& movingghost, bool blevel, int speed, int start, int end) {
	if (cclock.getElapsedTime().asSeconds() > 0.2f && blevel == true) {
		if (ghost.getPosition().x < start)
			movingghost = 1;
		if (ghost.getPosition().x > end)
			movingghost = 0;
		if (movingghost)
			ghost.move(speed, 0);
		else
			ghost.move(-speed, 0);
		cclock.restart();
	}
}
void ghostmovey(Sprite& ghost, Clock& cclock, bool& movingghost, bool blevel, int speed, int start, int end) {
	if (cclock.getElapsedTime().asSeconds() > 0.2f && blevel == true) {
		if (ghost.getPosition().y < start)
			movingghost = 1;
		if (ghost.getPosition().y > end)
			movingghost = 0;
		if (movingghost)
			ghost.move(0, speed);
		else
			ghost.move(0, -speed);
		cclock.restart();
	}
}
bool pausemenu() {
	for (int i = 0; i < 3; i++) {
		pmenu[i].setFont(endgame);
		pmenu[i].setFillColor(Color::Yellow);
		pmenu[i].setCharacterSize(60);
	}
	pmenu[0].setString("RESUME");
	pmenu[0].setPosition(380, 220);
	pmenu[1].setString("MAIN MENU");
	pmenu[1].setPosition(320, 290);
	pmenu[2].setString("EXIT");
	pmenu[2].setPosition(430, 360);
	bool Pcolor[3] = { 0 };
	Mouse ms;
	if (ms.getPosition().x > 845 && ms.getPosition().x < 1120 &&
		ms.getPosition().y > 452 && ms.getPosition().y < 507) {
		Pcolor[0] = 1;
	}
	else {
		Pcolor[0] = 0;
	}
	if (ms.getPosition().x > 785 && ms.getPosition().x < 1185 &&
		ms.getPosition().y > 522 && ms.getPosition().y < 577) {
		Pcolor[1] = 1;
	}
	else {
		Pcolor[1] = 0;
	}
	if (ms.getPosition().x > 900 && ms.getPosition().x < 1055 &&
		ms.getPosition().y > 592 && ms.getPosition().y < 647) {
		Pcolor[2] = 1;
	}
	else {
		Pcolor[2] = 0;
	}
	for (int i = 0; i < 3; i++) {
		if (Pcolor[i] == 1) {
			pmenu[i].setFillColor(Color::White);
			pmenu[i].setStyle(Text::Bold);
		}
		else {
			pmenu[i].setFillColor(Color::Yellow);
			pmenu[i].setStyle(Text::Regular);
		}
	}
	//menu navigating
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (ms.getPosition().x > 845 && ms.getPosition().x < 1120 &&
			ms.getPosition().y > 452 && ms.getPosition().y < 507) {
			nav = 1;
			spacetostart.setFillColor(Color::Yellow);
			pausewind = false;
		}
		else if (ms.getPosition().x > 785 && ms.getPosition().x < 1185 &&
			ms.getPosition().y > 522 && ms.getPosition().y < 577) {
			menuwind = true;
			pausewind = false;
			blevel1 = false;
			blevel2 = false;
			ghostpos1 = false;
			ghostpos2 = false;
			pacpos1 = false;
			pacpos2 = false;
			startmove = false;
			spacetostart.setFillColor(Color::Yellow);
			lives = 4;
			score = 0;
			scor.setString("SCORE :" + to_string(score));
			playingsound.play();
			nav = 0;
		}
		else if (ms.getPosition().x > 900 && ms.getPosition().x < 1055 &&
			ms.getPosition().y > 592 && ms.getPosition().y < 647) {
			pausewind = false;
			nav = 3;
		}
	}
	return pausewind;
}
void sortArray(player p[], int size) {
	bool swapped = true;
	int temp;
	string temp2;
	do {
		swapped = false;
		for (int i = 0; i < size - 1; i++) {
			if (p[i].highscore < p[i + 1].highscore) {
				temp = p[i].highscore;
				p[i].highscore = p[i + 1].highscore;
				p[i + 1].highscore = temp;

				temp2 = p[i].name;
				p[i].name = p[i + 1].name;
				p[i + 1].name = temp2;
				swapped = true;
			}
		}
	} while (swapped);
}
void getName(player arr[]) {
	//phase = 1;
	allScores.open("gamedata/allScores.txt", ios::app);
	if (allScores.is_open()) {
		allScores << score << endl;
		allScores.close();
	}
	Texture logo;
	Sprite bgdlogo;
	logo.loadFromFile("./name.png");
	bgdlogo.setTexture(logo);
	Vector2u size = logo.getSize();
	string input_text;
	Font font;
	font.loadFromFile("Bullpen3D.ttf");
	Text nametxt;
	nametxt.setFont(font);
	Text scoretxt;
	scoretxt.setFont(font);
	scoretxt.setPosition(500, 200);
	scoretxt.setCharacterSize(50);
	scoretxt.setString(to_string(score));
	Clock clock;

	RenderWindow window1({ size.x,size.y }, "Enter name");
	int x = (size.x / 2) - 20;
	while (window1.isOpen())
	{
		Event event1;
		while (window1.pollEvent(event1))
		{
			if (event1.type == Event::Closed) {
				nav = 0;
				phase = 0;
				score = 0;
				lives = 4;
				pausewind = false, startmove = false, blevel1 = false, blevel2 = false, pacpos1 = false, pacpos2 = false;
				menuwind = true, dead = false, ghostpos1 = false, ghostpos2 = false;
				spacetostart.setFillColor(Color::Yellow);
				scor.setString("SCORE :" + to_string(score));
				gamemusic.setLoop(true);
				playingsound.play();
				window1.close();
			}
			else if (event1.type == Event::TextEntered) {
				if (isprint(event1.text.unicode)) {
					input_text += event1.text.unicode;
					x -= 10;
				}
			}
			else if (event1.type == Event::KeyPressed) {
				if (event1.key.code == Keyboard::BackSpace) {
					if (!input_text.empty()) {
						input_text.pop_back();
						x += 10;
					}
				}
				if (event1.key.code == Keyboard::Return) {
					nav = 0;
					phase = 0;
					score = 0;
					lives = 4;
					pausewind = false, startmove = false, blevel1 = false, blevel2 = false, pacpos1 = false, pacpos2 = false;
					menuwind = true, dead = false, ghostpos1 = false, ghostpos2 = false;
					spacetostart.setFillColor(Color::Yellow);
					scor.setString("SCORE :" + to_string(score));
					gamemusic.setLoop(true);
					playingsound.play();
					window1.close();
				}
			}
		}

		static Time text_effect_time;
		static bool show_cursor;
		text_effect_time += clock.restart();
		if (text_effect_time >= seconds(0.5f))
		{
			show_cursor = !show_cursor;
			text_effect_time = Time::Zero;
		}
		nametxt.setString(input_text + (show_cursor ? '_' : ' '));
		nametxt.setPosition(x, 580);

		window1.clear();
		window1.draw(bgdlogo);
		window1.draw(nametxt);
		window1.draw(scoretxt);
		window1.display();
	}

	name.open("gamedata/name.txt", ios::app);
	if (name.is_open()) {
		name << input_text << endl;
		fileSize++;
		name.close();
	}
	phase = 1;
}
void displayHighscore(player arr[], int size) {
	allScores.open("gamedata/allScores.txt", ios::in);
	if (allScores.is_open()) {
		int num;
		int i = 0;
		while (allScores >> num) {
			p[i].highscore = num;
			i++;
		}
		allScores.close();
	}

	name.open("gamedata/name.txt", ios::in);
	if (name.is_open()) {
		string line;
		int i = 0;
		while (getline(name, line)) {
			p[i].name = line;
			i++;
		}
		name.close();
	}
	sortArray(p, fileSize);
	Texture logo;
	Sprite bglogo;
	logo.loadFromFile("./highLogo.png");
	bglogo.setTexture(logo);
	bglogo.setPosition(200, 10);
	string input_text;
	Font font;
	font.loadFromFile("Bullpen3D.ttf");
	koulen.loadFromFile("./Koulen.ttf");
	Text playernametxt, playerscoretxt, entrtogoback;
	playernametxt.setFont(font);
	playerscoretxt.setFont(font);
	entrtogoback.setFont(koulen);
	entrtogoback.setString("Press ENTER to go back.");
	entrtogoback.setPosition(375, 750);
	entrtogoback.setFillColor(Color::White);
	entrtogoback.setCharacterSize(30);
	Clock clock;
	RenderWindow window2({ 1100, 800 }, "High Scores");
	while (window2.isOpen())
	{
		Event event2;
		while (window2.pollEvent(event2))
		{
			if (event2.type == Event::Closed)
				window2.close();

			if (event2.type == Event::KeyPressed) {
				if (event2.key.code == Keyboard::Return) {
					window2.close();
				}
			}
		}
		window2.clear();
		window2.draw(bglogo);
		int n;
		if (size < 10) {
			n = size;
		}
		else if (size >= 10) {
			n = 10;
		}
		for (int i = 0; i < n; i++) {
			playerscoretxt.setFillColor(Color::White);
			playernametxt.setString(p[i].name);
			playerscoretxt.setString(to_string(p[i].highscore));
			playernametxt.setPosition(300, 300 + 40 * i);
			playerscoretxt.setPosition(700, 300 + 40 * i);
			window2.draw(playernametxt);
			window2.draw(playerscoretxt);
		}
		window2.draw(entrtogoback);
		window2.display();
	}
}
void credits() {
	Texture team;
	Sprite teams;
	team.loadFromFile("./tm.png");
	teams.setTexture(team);
	teams.setScale(0.7, 0.7);
	koulen.loadFromFile("./Koulen.ttf");
	Text back;
	back.setFont(koulen);
	back.setString("Press ENTER to go back.");
	back.setPosition(420, 750);
	back.setFillColor(Color::White);
	back.setCharacterSize(30);
	RenderWindow window3({ 1100, 800 }, "CREDITS");
	while (window3.isOpen())
	{
		Event event3;
		while (window3.pollEvent(event3))
		{
			if (event3.type == Event::Closed) {
				nav = 0;
				phase = 0;
				score = 0;
				lives = 4;
				pausewind = false, startmove = false, blevel1 = false, blevel2 = false, pacpos1 = false, pacpos2 = false;
				menuwind = true, dead = false, ghostpos1 = false, ghostpos2 = false;
				gamemusic.setLoop(true);
				playingsound.play();
				window3.close();
			}

			if (event3.type == Event::KeyPressed) {
				if (event3.key.code == Keyboard::Return) {
					nav = 0;
					phase = 0;
					score = 0;
					lives = 4;
					pausewind = false, startmove = false, blevel1 = false, blevel2 = false, pacpos1 = false, pacpos2 = false;
					menuwind = true, dead = false, ghostpos1 = false, ghostpos2 = false;
					gamemusic.setLoop(true);
					playingsound.play();
					window3.close();
				}
			}
		}
		window3.clear();
		window3.draw(teams);
		window3.draw(back);
		window3.display();
	}
}