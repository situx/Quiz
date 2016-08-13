#include "../include/Steuerung.hpp"
#include "ParseXML.cpp"
#include <cstdlib>
#include <iostream>
#include <QInputDialog>
#include <QMessageBox>
#include <ctime>

Steuerung::Steuerung(){
    mult.parse("res/multiplechoice.xml");/*Calling the parsefunctions for the XML files*/
    image.parse("res/imagequestion.xml");
    free.parse("res/freequestion.xml");
    log=false;
    mode=6;/*Setting the mode to the highest possibility including all questiontypes*/
    old=-1;/*resetting the value of the last displayed question*/
    fanzahl=10;/*setting the standard value for the question to be answered*/
    srand((unsigned)time(NULL));/*generating a random start number*/
    asXML();
}
Steuerung::~Steuerung(){
}
/*! \fn bool Steuerung::newgame(bool b)
 *  \brief Resets all concerned variables and performs actions to begin a new game
 *  \param b a bool: indicates if a 1P or 2P Game shall begin
 *  \return a bool: indicates if the function succeeded
 */
bool Steuerung::newgame(bool b){
    bool ok;
    QWidget w;
    QMessageBox msgBox;
    if(mult.getHash().capacity()==0 && free.getHash().capacity()==0 && image.getHash().capacity()==0){/*Checks if any questions are available*/
        msgBox.setWindowTitle(QMessageBox::tr("Error"));
        msgBox.setText("<html>No questions could be loaded  into the Quiz!<br>Please consult the console log and the file error.log<br>and check the corresponding XML files for correct tag usage!<br>Korrekte Tags:<br>&lt;Multchoice A=\"A\" B=\"B\" C=\"C\" D=\"D\" Right=\"A\"&gt;Frage&lt;/Multchoice&gt;<br>&lt;Image A=\"A\" B=\"B\" C=\"C\" D=\"D\" Right=\"A\" Img=\"Pfad\"&gt;Frage&lt;/Image&gt;<br>&lt;Fragefrei Right=\"Antwort\"&gt;Frage&lt;/Fragefrei&gt;</html>");
        msgBox.exec();
        return false;
    }
    player1 = QInputDialog::getText(&w,QString("Name"), QString("Player 1, please enter your name:"), QLineEdit::Normal,QString::null, &ok);
    if ( ok && !player1.isEmpty() ){
        playerx2=false;
        punkte=0;
    }
    else/*if the cancel button is pressed the beginning of a new game is aborted*/
        return false;
    if (b){
        player2 = QInputDialog::getText(&w,QString("Name"), QString("Player 2, please enter your name:"), QLineEdit::Normal,QString::null, &ok);
        if ( ok && !player2.isEmpty() ){
            playerx2=true;
            punkte2=0;

        }
        else
            return false;
    }
    if (log){
        mult.clearState();
        image.clearState();
        free.clearState();
    }
    old=-1;/*the value of the last question is set to -1*/
    round=0;/*the round variable is resetted*/
    blocked=false;/*the block variable for the 2P-Mode is resetted*/
return true;
}

void Steuerung::asXML(){
QString start="<?xml version=\"1.0\" encoding=\"UTF-8\" ?><data>";
QString mults=start,frees=start,images=start;
QList<Frage> temp = mult.getHash().values();
QList<Fragefrei> temp2 = free.getHash().values();
QList<Frageimg> temp3 = image.getHash().values();
std::cout<<"hello"<<std::endl;
for(int i=0;i<temp.size();i++){
    mults+=temp.at(i).toXML();
}
for(int i=0;i<temp2.size();i++){
    frees+=temp2.at(i).toXML();
}
for(int i=0;i<temp3.size();i++){
    images+=temp3.at(i).toXML();
}
mults+="</data>";
frees+="</data>";
images+="</data>";
QFile* multfile = new QFile("multiplechoice2.xml");
if (!multfile->open(QFile::WriteOnly|QFile::Text)){
        std::cerr<<"Multchoice.xml could not be written"<<std::endl;
}
multfile->write(mults.toUtf8());
multfile->close();
delete(multfile);
QFile* imagefile = new QFile("imagequestion2.xml");
if (!imagefile->open(QFile::WriteOnly|QFile::Text)){
        std::cerr<<"Imagequestion.xml could not be written"<<std::endl;
}
imagefile->write(images.toUtf8());
imagefile->close();
delete(imagefile);
QFile* freefile = new QFile("freequestion2.xml");
if (!freefile->open(QFile::WriteOnly|QFile::Text)){
        std::cerr<<"Freequestion.xml could not be written"<<std::endl;
}
freefile->write(mults.toUtf8());
freefile->close();
delete(multfile);
}
/*! \fn QString Steuerung::getFrage()
 *  \brief Depending on the users choice and the availability of the questions the next question is chosen using this function
 *  \return a QString: the next question
 */
QString Steuerung::getFrage(){
int other=2;
bool full[3]={false,false,false};
old=index;
index=0;
if(mult.full())/*checking if some of the question types have already been told completely*/
    full[0]=true;
if(image.full())
    full[1]=true;
if(free.full())
    full[2]=true;
switch (mode){/*choosing the question type randomly depending on the chosen options*/
case 0: index=0;break;
case 1: index=1;break;
case 2: index=2;break;
case 3: if((index=rand()%2)==0) other=1; else other=0; break;
case 4: if((index=rand()%2)==1){
            index+=1;
            other=0;
        }
        else
            other=2;break;
case 5: if((index=rand()%2+1)==1)other=2; else other=1;break;
default: index=rand()%3;
}
if(mode>2 && full[index] && !full[other])/*checking if all alternatives for asking a not yet asked question have been taken into account*/
    index=other;
else if (mode==6 && full[index] && full[other] && !full[(3-other-index)])
    index=(3-other-index);
else if(full[index] && full[other] && ((mode<6 && mode>2) || (mode==6 && full[(3-other-index)]))){
    mult.clearState();
    image.clearState();
    free.clearState();
}
switch (index){/*choosing a question out of the chosen question type hash*/
    case 0: if (mult.full())/*if we are playing a game with only one question type it has to be deleted if it is full*/
                mult.clearState();
            while(mult.getState().contains(fragen=rand()%mult.getHash().size()));/*While no new question is found continue searching*/
            f=mult.getHash().value(fragen);
            answertext=f.getAnswerText();
            return f.getFrage();
    case 1:if (image.full())
                image.clearState();
            while(image.getState().contains(fragen=rand()%image.getHash().size()));
            fi=image.getHash().value(fragen);
            answertext=fi.getAnswerText();
            return fi.getFrage();
    case 2:if (free.full())
                free.clearState();
            while(free.getState().contains(fragen=rand()%free.getHash().size()));
            ff=free.getHash().value(fragen);
            answertext=ff.getAnswerText();
            return ff.getFrage();
}
return NULL;
}
/*! \fn bool Steuerung::isright(QString r, bool player)
 *  \brief Checks whether the question is answered correctly, logs the correctly answered questions and distributes the points
 *  \param r a QString: the given answer from the user
 *  \param player a bool: the player who has given the answer
 *  \return a bool: right or wrong
 */
bool Steuerung::isright(QString r,bool player){
    bool right=false;
    round++;
    if (playerx2)/*If we are in 2P-Mode, we have to reset the block variable to ensure that the keyPressEvent has to be pressed when the next question appears*/
        blocked=false;
    if (index==0 && (right=f.right(r)))/*If a question is answered correctly it is added to the Loglist of its type*/
        mult.insertState(fragen);
    else if (index==1 && (right=fi.right(r)))
        image.insertState(fragen);
    else if((right=ff.right(r)))
        free.insertState(fragen);
    if (right){/*if the question is answered correctly, the player variable is asked which player answered it and his points are increased*/
       if (player)
           punkte++;
       else
           punkte2++;
    return true;
    }
    if (player)/*Otherwise an increasement of the opponents points is performed*/
       punkte2++;
    else
       punkte++;
    return false;
}
/*! \fn QString Steuerung::statusupdate(bool dran)
 *  \brief Creates the QString used for updating the windows' statusbar
 *  \param dran a bool: indicates who is allowed to answer in 2P-Mode
 *  \return a QString
 */
QString Steuerung::statusupdate(bool dran){
    QString status=player1;
    status.append(" Points: ");
    status.append(QString::number(punkte));
    if (playerx2){/*status updates in 2P-Mode*/
        status.append("  ");
        status.append(player2);
        status.append(" Points: ");
        status.append(QString::number(punkte2));
        if (dran && blocked){/*status update in 2P-Mode if a player has pressed a button*/
            status.append("     ");
            status.append(player1);
            status.append(" is allowed to answer");
        }
        else if(!dran && blocked){
            status.append("     ");
            status.append(player2);
            status.append(" is allowed to answer");
        }
    }
return status;
}
/*! \fn void Steuerung::checkCapacity(bool b[3])
 *  \brief A capacity check for the questions
 *  \param b bool[3] a bool array: in which is stored if there are questions of each type
 *  \return void
 */
void Steuerung::checkCapacity(bool b[3]){
    if(mult.getHash().capacity()>0)
        b[0]=true;
    if(image.getHash().capacity()>0)
        b[1]=true;
    if(free.getHash().capacity()>0)
        b[2]=true;
}
/*! \fn QString Steuerung::sende(int p)
 *  \brief Creates the string used for displaying when the game has ended
 *  \param p a int: the current amount of questions to answer
 *  \return a QString
 */
QString Steuerung::sende(int p){
QString ende="<html><font size=10 align=center>Game Over</font><br><font size=4 align=center>";
    round=0;
    if (playerx2){
       ende.append("<b>");
       if (punkte>punkte2){/*checking which player has won the game or if it results in a draw*/
            ende.append(player1);
            ende.append(" won!");
       }
       else if (punkte<punkte2){
            ende.append(player2);
            ende.append(" won!");
       }
       else
            ende.append("Draw!");
       ende.append("<br></b>");
       ende.append(player1);/*output of the points*/
       ende.append(" : ");
       ende.append(QString::number(punkte));
       ende.append("/");
       ende.append(QString::number(p));
       ende.append(" Punkten<br>");
       ende.append(player2);
       ende.append(" : ");
       ende.append(QString::number(punkte2));
       ende.append("/");
       ende.append(QString::number(p));
       ende.append(" Points");
    }
    else{/*end message of a 1P-Game*/
       ende.append("Correctly answered questions:<br>");
       ende.append(QString::number(punkte));
       ende.append("/");
       ende.append(QString::number(p));
    }
    ende.append("</font></html>");
return ende;
}
/*! \fn int Steuerung::getround()
 *  \brief returns the current amount of answered questions
 *  \return a int
 */
int Steuerung::getround(){
    return round;
}
/*! \fn int Steuerung::getfanzahl()
 *  \brief returns the amount of questions per game
 *  \return a int
 */
int Steuerung::getfanzahl(){
    return fanzahl;
}
/*! \fn void Steuerung::setfanzahl(int i)
 *  \brief sets the amount of questions per game
 *  \param i a int: the new amount of questions
 *  \return void
 */
void Steuerung::setfanzahl(int i){
    fanzahl=i;
}
/*! \fn void Steuerung::setMode(int i)
 *  \brief sets the mode of questions for the game
 *  \param i a int: the mode parameter
 *  \return void
 */
void Steuerung::setMode(int i){
    mode=i;
}
/*! \fn int Steuerung::getMode()
 *  \brief returns the current mode parameter
 *  \return a int: the mode parameter
 */
int Steuerung::getMode(){
    return mode;
}
/*! \fn bool Steuerung::getPlayerx2()
 *  \brief returns if the game is in 2P or in 1P Mode
 *  \return a bool: the mode status
 */
bool Steuerung::getPlayerx2(){
    return playerx2;
}
/*! \fn bool Steuerung::getblocked()
 *  \brief checks if a player has yet pressed a key in the 2P-Game
 *  \return a bool: pressed or not pressed
 */
bool Steuerung::getblocked(){
    return blocked;
}
/*! \fn void Steuerung::setlog(bool b)
 *  \brief sets if the log should be deleted after each game
 *  \param b a bool: the decision indicator
 *  \return void
 */
void Steuerung::setlog(bool b){
    log=b;
}
/*! \fn void Steuerung::setblocked(bool b)
 *  \brief sets the KeyPressed status indicator
 *  \param b a bool: the keyPressed value
 *  \return void
 */
void Steuerung::setblocked(bool b){
    blocked=b;
}
/*! \fn QString Steuerung::getAnswerText()
 *  \brief returns the formatted answerText of the current question
 *  \return a QString: the answerText
 */
QString Steuerung::getAnswerText(){
    return answertext;
}
/*! \fn QString Steuerung::getAnswerString(bool b)
 *  \brief returns the formatted text of the answering possibilities of the current question
 *  \param b a bool: indicates for image questions if the image path is returned
 *  \return a QString: the answering possibilities
 */
QString Steuerung::getAnswerString(bool b){
    if (index==0)
        return f.answerString();
    if(index==1 && b)
        return fi.getImg();
    if(index==1 && !b)
        return fi.answerString();
    return NULL;
}
/*! \fn int Steuerung::getindex()
 *  \brief returns the index of the current question asked
 *  \return an int
 */
int Steuerung::getindex(){
    return index;
}
/*! \fn int Steuerung::getold()
 *  \brief returns the value of the previous question asked
 *  \return an int
 */
int Steuerung::getold(){
    return old;
}
