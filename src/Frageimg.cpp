#include "../include/Frageimg.hpp"
/*! \fn Frageimg::Frageimg(QString Fragen,QString right,QString A, QString B, QString C, QString D,QString Img)
 *  \brief Constructor for creating a Frageimg object
 *  \param Fragen a QString
 *  \param right a QString
 *  \param A a QString
 *  \param B a QString
 *  \param C a QString
 *  \param D a QString
 *  \param Img a QString
 */
Frageimg::Frageimg(QString Fragen,QString right,QString A, QString B, QString C, QString D,QString pix):Frage(Fragen,right,A,B,C,D,pix),pix(pix){
}
Frageimg::Frageimg(){
}
Frageimg::~Frageimg(){
}
/*! \fn Frageimg::getImg()
 *  \brief returns the path to the image file
 *  \return a QString: the path
 */
QString Frageimg::getImg(){
    return pix;
}
/*! \fn QString Frage::toXML()
 *  \brief Formats the question for writing it to the xml file
 *  \return a QString
 */
QString Frageimg::toXML() const{
QString images="<Image";
    images.append(" A=\""+A+"\"");
    images.append(" B=\""+B+"\"");
    images.append(" C=\""+C+"\"");
    images.append(" D=\""+D+"\"");
    images.append(" right=\""+r+"\"");
    images.append(" Img=\""+pix+"\"");
    images.append(">"+Fragen);
    images.append("</Image>");
return images;
}
