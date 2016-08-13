#ifndef FRAGEIMG_HPP_INCLUDED
#define FRAGEIMG_HPP_INCLUDED
#include "Frage.hpp"
/*! \class Frageimg Frageimg.hpp "Quiz/Frageimg.hpp"
 *  \brief A class representing the image questions
 *
 *
 */
class Frageimg : public Frage{
private:
QString pix;/*!the string containing the path to the image*/
public:
Frageimg(QString Fragen,QString right,QString A=0, QString B=0, QString C=0, QString D=0,QString pix=0);
Frageimg()/*!the default constructor*/;
~Frageimg()/*!the default destructor*/;
QString getImg();
QString toXML() const;
};
#endif // FRAGEIMG_HPP_INCLUDED
