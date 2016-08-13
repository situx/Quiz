#ifndef FRAGEFREI_HPP_INCLUDED
#define FRAGEFREI_HPP_INCLUDED
#include "Frage.hpp"
/*! \class Fragefrei Fragefrei.hpp "Quiz/Fragefrei.hpp"
 *  \brief A class representing the freetext questions
 *
 *
 */
class Fragefrei : public Frage{
public:
Fragefrei(QString Frage,QString r,QString A=0, QString B=0,QString C=0,QString D=0,QString Img=0);
Fragefrei()/*!the default constructor*/;
~Fragefrei()/*!the default destructor*/;
bool right(QString eingabe);
QString getAnswerText();
QString toXML() const;
};
#endif // FRAGEFREI_HPP_INCLUDED
