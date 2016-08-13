#include "../include/Window.hpp"
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QApplication>
Window::Window():exitAct(tr("Exit Game"),this),opt(tr("Options"),this),
    newgame(tr("New Game"),this),newgame2(tr("New 2P Game"),this),
    aboutAct(tr("About"),this),manualAct(tr("Manual"),this){
bool (&br)[3]=b;
player=true;
s.checkCapacity(br);/*Checks the capacity of the question hashes*/
f0.setChecked(false);
f1.setChecked(true);
f2.setChecked(true);
f3.setChecked(true);
optedit.insert(QString::number(s.getfanzahl()));
if(b[0]==false){/*Sets the option dialogs Checkboxes*/
   f1.setChecked(false);
   f1.setDisabled(true);
}
if(b[1]==false){
   f2.setChecked(false);
   f2.setDisabled(true);
}
if(b[2]==false){
   f3.setChecked(false);
   f3.setDisabled(true);
}
cons=true;
optokay();/*Calls the optokay functions to set the start mode according to the available questions*/
cons=false;
//editor.setVisible(false);
build();
}
Window::~Window(){
    delete(b1);
    delete(b2);
    delete(b3);
    delete(b4);
}

void Window::slotLanguageChanged(QAction* action)
{
 if(0 != action) {
  // load the language dependant on the action content
  loadLanguage(action->data().toString());
  setWindowIcon(action->icon());
 }
}

void switchTranslator(QTranslator& translator, const QString& filename)
{
 // remove the old translator
 qApp->removeTranslator(&translator);

 // load the new translator
 if(translator.load(filename))
  qApp->installTranslator(&translator);
}

void Window::loadLanguage(const QString& rLanguage)
{
 if(m_currLang != rLanguage) {
  m_currLang = rLanguage;
  QLocale locale = QLocale(m_currLang);
  QLocale::setDefault(locale);
  QString languageName = QLocale::languageToString(locale.language());
  switchTranslator(m_translator, QString("TranslationExample_%1.qm").arg(rLanguage));
  switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
  statusBar()->showMessage(tr("Current Language changed to %1").arg(languageName));
 }
}


/*! \fn void Window::manual()
 *  \brief creates and pops up a window including the manual of the game
 *  \return void
 */
void Window::manual(){
QMessageBox msgBox2;
 msgBox2.setWindowTitle(tr("Manual"));
 msgBox2.setText("<html>The game can be played in single and 2P Mode.<br>Questions of the type multiple choice, free questions and image questions are asked.<br>Depending on the kind of question there are different possibilities to answer.<br>In the 2-Player-Mode a button has to be pressed prior to answering in order to decide which player is allowed to answer first.<br>Player 1 owns the <b>left Ctrl-Key</b> and Player 2 the <b>AltGr-Key</b>.<br>If a player answers a question incorrectly a point is awarded to his opponent.</html>");
 msgBox2.exec();
}
/*! \fn void Window::about()
 *  \brief creates and pops up a window including about informations
 *  \return void
 */
void Window::about(){
 QMessageBox msgBox;
 msgBox.setWindowTitle(tr("About"));
 msgBox.setText("Quiz v1.0\nCopyright 2010 by Timo Homburg\nDCSM Hochschule RheinMain");
 msgBox.exec();
}
/*! \fn void Window::rightanzeige(QString a)
 *  \brief displays if the answer is correct or wrong
 *  \param a a QString: the answer of the user
 *  \return void
 */
void Window::rightanzeige(QString a){
QString wrong("<html><font size=4><b>Falsch!</b><br>Die richtige Antwort war:<br><b>");
    if(s.getindex()==2){/*If an edit field is displayed, it has to be hidden and a label should be shown instead*/
        edit.setVisible(false);
        lab2.setVisible(true);
    }
    if (s.isright(a,player)){/*if the question is answered correctly the positive string is build otherwise the negative string is built*/
        lab2.setText("<html><font size=4><b>Richtig!</b></font></html>");
    }
    else{
        wrong.append(s.getAnswerText());
        wrong.append("</b></font></html>");
        lab2.setText(wrong);
    }
    statusBar()->showMessage(tr(qPrintable(s.statusupdate(true))));
    timer.start();

}
/*! \fn void Window::acttimer()
 *  \brief the timer for waiting for the next question to display
 *  \return void
 */
void Window::acttimer(){
    if (s.getround()<game){/*Decides if we are at the end of the game*/
        lab.setText(s.getFrage());
        visibility(false);
    }
    else
        visibility(true);
    timer.stop();
}
/*! \fn void Window::ngame(bool b)
 *  \brief Calls the appropriate functions to start a new game
 *  \param b a bool: indicates a 1p or 2P-Game
 *  \return void
 */
void Window::ngame(bool b){
    if (s.newgame(b)){/*Calls the newgame function in class Steuerung and sets the appropriate windows settings if the function succeeds*/
        game=s.getfanzahl();
        lab.setVisible(true);
        lab.setText(s.getFrage());
        visibility(false);
        statusBar()->showMessage(tr(qPrintable(s.statusupdate(true))));
    }
}
/*! \fn void Window::option()
 *  \brief performs assorted tasks for creating the options window
 *  \return void
 */
void Window::option(){
    switch(s.getMode()){/*choosing the appropriate values for the checkboxes depending on the game mode*/
    case -1:f1.setChecked(false);f2.setChecked(false);f3.setChecked(false);break;
    case 0:f1.setChecked(true);f2.setChecked(false);f3.setChecked(false);break;
    case 1:f1.setChecked(false);f2.setChecked(true);f3.setChecked(false);break;
    case 2:f1.setChecked(false);f2.setChecked(false);f3.setChecked(true);break;
    case 3:f1.setChecked(true);f2.setChecked(true);f3.setChecked(false);break;
    case 4:f1.setChecked(true);f2.setChecked(false);f3.setChecked(true);break;
    case 5:f1.setChecked(false);f2.setChecked(true);f3.setChecked(true);break;
    case 6:f1.setChecked(true);f2.setChecked(true);f3.setChecked(true);
    }
    optedit.clear();/*Clearing the LineEdit Field and filling it with the current value*/
    optedit.insert(QString::number(s.getfanzahl()));
    optok.setFocus();
    options.setVisible(true);
}
/*! \fn void Window::optokay()
 *  \brief provides functionality for applying the settings in the option dialog
 *  \return void
 */
void Window::optokay(){
int input=0;
QMessageBox msgBox;
    if ((input=optedit.text().toInt())!=0 && (f1.checkState()==2 || f2.checkState()==2 || f3.checkState()==2)){/*If a value is inserted and a question type is selected*/
        if (s.getround()<input)/*if the game is running and the parameter is changed*/
            game=input;
        else{
            msgBox.setWindowTitle("Information!");
            msgBox.setText("<html>The entered amount of questions is lower than<br>the current question in the continuing game.<br>The change will take effect in the next game!</html>");
            msgBox.exec();
        }
        s.setfanzahl(input);/*if at least one field is selected set the resulting mode*/
        s.setlog(f0.checkState());
        if(f1.checkState()==2 && f2.checkState()==0 && f3.checkState()==0)
            s.setMode(0);
        else if(f1.checkState()==0 && f2.checkState()==2 && f3.checkState()==0)
            s.setMode(1);
        else if(f1.checkState()==0 && f2.checkState()==0 && f3.checkState()==2)
            s.setMode(2);
        else if(f1.checkState()==2 && f2.checkState()==2 && f3.checkState()==0)
            s.setMode(3);
        else if(f1.checkState()==2 && f2.checkState()==0 && f3.checkState()==2)
            s.setMode(4);
        else if(f1.checkState()==0 && f2.checkState()==2 && f3.checkState()==2)
            s.setMode(5);
        else if(f1.checkState()==2 && f2.checkState()==2 && f3.checkState()==2)
            s.setMode(6);
    }
    else{/*Otherwise we have to check if we are initialising the game or the user selects an option*/
        if (cons){
            s.setMode(-1);
            s.newgame(true);
        }
        else if(s.getMode()!=-1){/*If the user has selected an option he is informed by a message window*/
            msgBox.setWindowTitle("Fehler!");
            msgBox.setText("<html>Please choose at least one question type<br>and/or insert a correct question amount (greater than 0)!</html>");
            msgBox.exec();
            return;
        }
    }
    options.setVisible(false);
}
/*! \fn void Window::abutton()
 *  \brief calls rightanzeige() for button A
 *  \return void
 */
void Window::abutton(){
if (!s.getPlayerx2() || (s.getblocked() && s.getPlayerx2()))
    rightanzeige("A");
}
/*! \fn void Window::bbutton()
 *  \brief calls rightanzeige() for button B
 *  \return void
 */
void Window::bbutton(){
if (!s.getPlayerx2() || (s.getblocked() && s.getPlayerx2()))
    rightanzeige("B");
}
/*! \fn void Window::cbutton()
 *  \brief calls rightanzeige() for button C
 *  \return void
 */
void Window::cbutton(){
if (!s.getPlayerx2() || (s.getblocked() && s.getPlayerx2()))
    rightanzeige("C");
}
/*! \fn void Window::dbutton()
 *  \brief calls rightanzeige() for button D
 *  \return void
 */
void Window::dbutton(){
if (!s.getPlayerx2() || (s.getblocked() && s.getPlayerx2()))
    rightanzeige("D");
}
/*! \fn void Window::exit()
 *  \brief calls the close SLOT and hides the options window if opened
 *  \return void
 */
void Window::exit(){
    options.setVisible(false);
    close();
}
/*! \fn void Window::okay()
 *  \brief calls rightanzeige() for the OK button
 *  \return void
 */
void Window::okay(){
if (!s.getPlayerx2() || (s.getblocked() && s.getPlayerx2())){
    if (edit.text()!="")
        rightanzeige(edit.text());
}
edit.setFocus();
}
/*! \fn void Window::ngame2()
 *  \brief calls ngame() for a 2P-Game
 *  \return void
 */
void Window::ngame2(){
    ngame(true);
}
/*! \fn void Window::keyPressEvent(QKeyEvent *e)
 *  \brief KeyListener for the 2P-Game
 *  \param *e a QKeyEvent
 *  \return void
 */
void Window::keyPressEvent(QKeyEvent *e){
    if (e->key()==16777249 && s.getPlayerx2() && !s.getblocked()){
        s.setblocked(true);
        player=true;
        statusBar()->showMessage(tr(qPrintable(s.statusupdate(true))));
        if(s.getindex()==2)/*if a freequestion is asked the edit field should be set Readonly unless a player for answering has been chosen*/
            edit.setReadOnly(false);
    }
    if (e->key()==16781571 && s.getPlayerx2() && !s.getblocked()){
        s.setblocked(true);
        player=false;
        statusBar()->showMessage(tr(qPrintable(s.statusupdate(false))));
        if(s.getindex()==2)/*if a freequestion is asked the edit field should be set Readonly unless a player for answering has been chosen*/
            edit.setReadOnly(false);
    }
}
/*! \fn void Window::visibility(bool end)
 *  \brief toggles the visibilities between the different questions and the end screen
 *  \param end a bool: indicates if the endscreen should be displayed
 *  \return void
 */
void Window::visibility(bool end){
    if (end){/*Modifications for the ending screen display*/
        edit.setVisible(false),
        lab.setVisible(false);
        bgroup.setVisible(false);
        lab3.setVisible(false);
        ok.setVisible(false);
        if (s.getindex()==1){/*If we got a question type 1 we have to change the labels position to the center of the window*/
            grid.removeWidget(&lab2);
            grid.addWidget(&lab2,100,100,Qt::AlignCenter);
        }
        lab2.setVisible(true);
        lab2.setText(s.sende(game));
        game=-1;/*Setting the game flag to -1 to indicate that no game is played*/
    }
    else{/*If the game is not over yet*/
        if (s.getindex()==0 && s.getold()!=-1){/*If the previous question is not of type 0 and the next question should be of type 0*/
            if (s.getold()==1){
                grid.removeWidget(&lab2);
                lab3.setVisible(false);
                grid.addWidget(&lab2,100,100,Qt::AlignCenter);
            }
            else if(s.getold()==2){
                edit.setVisible(false);
                ok.setVisible(false);
            }
            lab2.setText(s.getAnswerString());
            lab2.setVisible(true);
            bgroup.setVisible(true);
        }
        else if(s.getindex()==1 && s.getold()!=-1){/*If the previous question is not of type 1 and the next question should be of type 1*/
                if (s.getold()==2){
                    edit.setVisible(false);
                    ok.setVisible(false);
                }
                lab2.setText(s.getAnswerString(false));
                lab2.setVisible(true);
                pix.load(s.getAnswerString(true));
                pix=pix.scaled(200,200);
                lab3.setPixmap(pix);
                lab3.setVisible(true);
                bgroup.setVisible(true);
                grid.removeWidget(&lab2);
                grid.addWidget(&lab2,100,100,Qt::AlignRight);
        }
        else if(s.getindex()==2 && s.getold()!=-1){/*If the previous question is not of type 2 and the next question should be of type 2*/
                if (s.getold()==1){
                    grid.removeWidget(&lab2);
                    lab3.setVisible(false);
                    grid.addWidget(&lab2,100,100,Qt::AlignCenter);
                }
                edit.clear();
                edit.setFocus();
                lab2.setVisible(false);
                bgroup.setVisible(false);
                ok.setVisible(true);
                edit.setVisible(true);
                if(s.getPlayerx2())
                    edit.setReadOnly(true);
        }
    }
}
/*! \fn void Window::createMenus()
 *  \brief creates the menu for the main window
 *  \return void
 */
void Window::createMenus(){
     QMenu *fm;
     fm = menuBar()->addMenu(tr("Quiz"));
     fm->addAction(&newgame);
     fm->addAction(&newgame2);
     fm->addAction(&opt);
     fm->addSeparator();
     fm->addAction(&exitAct);
     fm = menuBar()->addMenu(tr("Help"));
     fm->addSeparator();
     fm->addAction(&manualAct);
     fm->addAction(&aboutAct);
}
/*! \fn void Window::createActions()
 *  \brief creates the actions for the main window menu
 *  \return void
 */
void Window::createActions(){
    connect(&newgame,SIGNAL(triggered(bool)),this,SLOT(ngame(bool)));
    connect(&newgame2,SIGNAL(triggered()),this,SLOT(ngame2()));
    connect(&opt,SIGNAL(triggered()),this,SLOT(option()));
    connect(&exitAct,SIGNAL(triggered()),this,SLOT(exit()));
    connect(&aboutAct,SIGNAL(triggered()),this,SLOT(about()));
    connect(&manualAct,SIGNAL(triggered()),this,SLOT(manual()));
    connect(b1,SIGNAL(clicked()),this,SLOT(abutton()));
    connect(b2,SIGNAL(clicked()),this,SLOT(bbutton()));
    connect(b3,SIGNAL(clicked()),this,SLOT(cbutton()));
    connect(b4,SIGNAL(clicked()),this,SLOT(dbutton()));
    connect(&ok,SIGNAL(clicked()),this,SLOT(okay()));
    connect(&optok,SIGNAL(clicked()),this,SLOT(optokay()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(acttimer()));
}
/*! \fn void Window::createGui()
 *  \brief creates the gui components of the main window
 *  \return void
 */
void Window::createGui(){
    d= QApplication::desktop();
    int x=(d->width()-width())/2;
    int y=(d->height()-height())/2;
    move(x,y);
    ok.setText(QString("Ok"));
    optok.setText(QString("Ok"));
    b1=bgroup.addButton("A",QDialogButtonBox::ActionRole);
    b2=bgroup.addButton("B",QDialogButtonBox::ActionRole);
    b3=bgroup.addButton("C",QDialogButtonBox::ActionRole);
    b4=bgroup.addButton("D",QDialogButtonBox::ActionRole);
    f0.setText("Log Reset after every round");
    f1.setText("Multiplechoice");
    f2.setText("Image Questions");
    f3.setText("Freetext questions");
    timer.setInterval(2000);
    lab.setVisible(false);
    lab.setWordWrap(true);
    lab3.setPixmap(pix);
    lab3.setVisible(false);
    bgroup.setVisible(false);
    ok.setVisible(false);
    edit.setVisible(false);
    ok.setShortcut(QKeySequence(Qt::Key_Enter));
    all.setLayout(&grid);
    grid.addWidget(&lab,100,100,Qt::AlignTop);
    grid.addWidget(&lab2,100,100,Qt::AlignCenter);
    grid.addWidget(&lab3,100,100,Qt::AlignLeft);
    grid.addWidget(&edit,100,100,Qt::AlignCenter);
    grid.addWidget(&ok,100,100,Qt::AlignBottom);
    grid.addWidget(&bgroup,100,100,Qt::AlignBottom);
    options.setLayout(&optgrid);
    optlab.setText("Amount of questions per game:");
    optgrid.addWidget(&optlab);
    optgrid.addWidget(&optedit);
    optgrid.addWidget(&f0);
    optgrid.addWidget(&f1);
    optgrid.addWidget(&f2);
    optgrid.addWidget(&f3);
    optgrid.addWidget(&optok);
    options.setWindowTitle(tr("Options"));
    options.setVisible(false);
    options.move(x+width()/5,y+height()/5);
    //editor.move(x+width()/5,y+height()/5);
    //editor.setVisible(false);
    //editor.setWindowTitle(tr("Editor"));
}
/*! \fn void Window::build()
 *  \brief the main function for building all of the windows' components
 *  \return void
 */
void Window::build(){
    createGui();
    createActions();
    createMenus();
    statusBar()->showMessage(tr("Quiz"));
    setCentralWidget(&all);
    lab2.setText("<html><b>Welcome to the Quiz!</b></html>");
    resize(400,400);
    setWindowTitle(tr("Quiz"));
    show();
    //editor.showMaximized();
}
