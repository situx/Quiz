#ifndef STEUERUNG_HPP_INCLUDED
#define STEUERUNG_HPP_INCLUDED
#include "ParseXML.hpp"
#include "Frage.hpp"
#include "Fragefrei.hpp"
#include "Frageimg.hpp"
/*! \class Steuerung Steuerung.hpp "Quiz/Steuerung.h"
 *  \brief A class for managing the games' status flags
 */
class Steuerung{
private:
int punkte/*!points of the first player*/,punkte2/*!points of the second player*/,fragen/*!the number of the current question type*/,mode/*!shows which question types are chosen*/,fanzahl/*!the amount of questions asked*/,round/*!the amount of questions that have already been asked*/,index/*!the index of the current questions*/,old/*!the index of the last question*/;
bool playerx2/*!indicator for the 2P-Game*/,blocked/*!shows if a player has already pressed a button in the 2P-Mode*/,log/*!decides if the log is deleted after every game*/;
QString player1/*!the name of player1*/,player2/*!the name of player2*/,answertext/*!the answertext of the current question*/;
ParseXML<Frage> mult;/*!an object of the class including alle the multiplechoice questions*/
ParseXML<Frageimg> image;/*!an object of the class including alle the image questions*/
ParseXML<Fragefrei> free;/*!an object of the class including alle the free questions*/
Frage f/*!an object of a multiple choice question*/;
Fragefrei ff/*!an object of a free question*/;
Frageimg fi/*!an object of an image question*/;
public:
Steuerung()/*!calls the parse functions for the three question types, initialises the parameters and creates a start number for the rand() function*/;
~Steuerung()/*!the default destructor*/;
QString statusupdate(bool dran);
QString sende(int p);
int getfanzahl();
int getround();
QString getAnswerText();
QString getAnswerString(bool b=0);
void setfanzahl(int i);
void setMode(int i);
int getMode();
bool getblocked();
int getindex();
int getold();
void setblocked(bool b);
void setlog(bool b);
bool getPlayerx2();
void checkCapacity(bool b[3]);
bool isright(QString r,bool player);
QString getFrage();
bool newgame(bool b);
void asXML();
};
#endif // STEUERUNG_HPP_INCLUDED
