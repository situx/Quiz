#ifndef FRAGE_HPP_INCLUDED
#define FRAGE_HPP_INCLUDED
#include <QtCore/QString>
/*! \class Frage Frage.hpp "Quiz/Frage.hpp"
 *  \brief A class representing the multchoice questions
 */
class Frage{
protected:
QString Fragen/*!the question*/;
QString r/*!the right answer*/;
QString A/*!the first answer*/;
QString B/*!the second answer*/;
QString C/*!the third answer*/;
QString D/*!the fourth answer*/;
public:
Frage()/*!the default constructor*/;
Frage(QString Fragen,QString r,QString A=0, QString B=0,QString C=0,QString D=0,QString Img=0);
virtual ~Frage()/*!the default destructor*/;
virtual bool right(QString t);
virtual QString getFrage();
virtual QString getAnswerText();
virtual QString answerString();
virtual QString toXML() const;
};
#endif // FRAGE_HPP_INCLUDED
