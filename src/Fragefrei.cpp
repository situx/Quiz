#include "../include/Fragefrei.hpp"
/*! \fn Fragefrei::Fragefrei(QString Fragen,QString right,QString A, QString B, QString C, QString D,QString Img)
 *  \brief Constructor for creating a Fragefrei object
 *  \param Fragen a QString
 *  \param right a QString
 *  \param A a QString
 *  \param B a QString
 *  \param C a QString
 *  \param D a QString
 *  \param Img a QString
 */
Fragefrei::Fragefrei(QString Fragen,QString Antwort,QString A, QString B,QString C,QString D,QString Img):Frage(Fragen,Antwort,"","","","",""){
}
Fragefrei::Fragefrei(){
}
Fragefrei::~Fragefrei(){
}
/*! \fn Fragefrei::right(QString eingabe)
*   \brief checks if the given answer ist correct
*   \param eingabe a QString
*   \return a bool
*/
bool Fragefrei::right(QString eingabe){
    if (eingabe.toLower()==r.toLower())
        return true;
    return false;
}
/*! \fn Fragefrei::getAnswerText()
*   \brief Gets the text of the right answer
*   \return a QString
*/
QString Fragefrei::getAnswerText(){
    return r;
}

/*! \fn QString Frage::toXML()
 *  \brief Formats the question for writing it to the xml file
 *  \return a QString
 */
QString Fragefrei::toXML() const{
QString frees="<Fragefrei";
    frees.append(" answer=\""+r+"\"");
    frees.append(">"+Fragen);
    frees.append("</Fragefrei>");
return frees;
}
