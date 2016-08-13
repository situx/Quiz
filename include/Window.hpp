#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QDesktopWidget>
#include <QMenu>
#include <QTranslator>
#include "Steuerung.hpp"
#include "Editor.hpp"
/*! \class Window Window.hpp "Quiz/Window.hpp"
 *  \brief A class representing the main window
 *
 *
 */
namespace Ui {
class Window;
}

class Window: public QMainWindow{
Q_OBJECT

private:
QTimer timer/*!the timer for displaying the result of the answer*/;
QMenu fileMenu/*!the menu of the main window*/;
QWidget all/*!the widget displaying the questions*/,options/*!the widget for the option window*/;
//Editor editor;
QTranslator m_translator; // contains the translations for this application
QTranslator m_translatorQt; // contains the translations for qt
QString m_currLang; // contains the currently loaded language
QString m_langPath; // Path of language files. This is always fixed to /languages.
QTranslator translator;
QDesktopWidget* d/*!a desktop widget for getting the desktop height/width for centering the main window*/;
QLabel lab/*!the label displaying the current question*/,lab2/*!the label displaying the current answer possibilities*/,lab3/*!the label including the pixmap*/,optlab/*!the label included ín the options window*/;
QPixmap pix/*!the pixmap for displaying the image*/;
QPushButton *b1/*!the A button*/,*b2/*!the B button*/,*b3/*!the C button*/,*b4/*!the D button*/,ok/*!the ok button for the free question type*/,optok/*!the ok button in the options window*/;
QLineEdit edit/*!the edit line for the free question type*/,optedit/*!the edit line for the options window*/;
QCheckBox f0/*!Checkbox in the options window representing the log option*/,f1/*!Checkbox in the options window representing the multchoice questions*/,f2/*!Checkbox in the options window representing the image questions*/,f3/*!Checkbox in the options window representing the free questions*/;
QAction exitAct/*!the action the exit selection*/,opt/*!the action the options selection*/,newgame/*!the action the new game selection*/,newgame2/*!the action 2p-Game selection*/,aboutAct/*!the action the about window*/,manualAct/*!the action the manual selection*/;
QDialogButtonBox bgroup/*!the button group for grouping the buttons for multchoice questions*/;
QGridLayout grid/*!the layout for the main window*/,optgrid/*!the layout for the options window*/;
bool player/*!indicates which player is active*/,b[3]/*!check array for the 3 question types*/,cons/*!indicates if a function is called from the constructor*/;
int game/*!stores the amount of questions to be played*/;
Steuerung s/*!an object of the class Steuerung for controlling the values of the game*/;
protected:
//void changeEvent(QEvent*);
private slots:
void ngame(bool b);
void slotLanguageChanged(QAction* action);
void ngame2();
void about();
void manual();
void option();
void abutton();
void bbutton();
void cbutton();
void dbutton();
void exit();
void okay();
void optokay();
void acttimer();
public:
Window()/*!checks the availability of the questions and calls the build function*/;
virtual~Window()/*!deletes the dynamically built buttons and calls the class*/;
void visibility(bool end);
void createActions();
void createMenus();
void createGui();
void loadLanguage(const QString& rLanguage);
void createLanguageMenu();
void keyPressEvent(QKeyEvent *e);
void rightanzeige(QString s);
void build();
};
#endif // WINDOW_HPP_INCLUDED
