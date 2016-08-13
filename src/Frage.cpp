#include "../include/Frage.hpp"
Frage::Frage(){
}
/*! \fn Frage::Frage(QString Fragen,QString right,QString A, QString B, QString C, QString D,QString Img)
 *  \brief Constructor for creating a Frage object
 *  \param Fragen a QString
 *  \param right a QString
 *  \param A a QString
 *  \param B a QString
 *  \param C a QString
 *  \param D a QString
 *  \param Img a QString
 */
Frage::Frage(QString Fragen,QString right,QString A, QString B, QString C, QString D,QString Img):Fragen(Fragen),r(right),A(A),B(B),C(C),D(D){
}
Frage::~Frage(){
}
/*! \fn bool Frage::right(QString t)
 *  \brief Checks if the given answer is correct
 *  \param t a QString
 *  \return a bool
 */
bool Frage::right(QString t){
    if(t==r)
        return true;
    return false;
}
/*! \fn QString Frage::getFrage()
 *  \brief Getter Function for returning the current question
 *  \return a QString
 */
QString Frage::getFrage(){
    return Fragen;
}
/*! \fn QString Frage::getAnswerText()
 *  \brief Creates the appropriate String including the right answer
 *  \return a QString
 */
QString Frage::getAnswerText(){
QString answertext;
    if(right("A")){
        answertext.append("A: ");
        answertext.append(A);
    }
    if(right("B")){
        answertext.append("B: ");
        answertext.append(B);
    }
    if (right("C")){
        answertext.append("C: ");
        answertext.append(C);
    }
    if (right("D")){
        answertext.append("D: ");
        answertext.append(D);
    }
    return answertext;
}
/*! \fn QString Frage::answerString()
 *  \brief Creates the string including the 4 different answers
 *  \return a QString
 */
QString Frage::answerString(){
QString answer="A: ";
    answer.append(A);
    answer.append("\nB: ");
    answer.append(B);
    answer.append("\nC: ");
    answer.append(C);
    answer.append("\nD: ");
    answer.append(D);
    return answer;
}
/*! \fn QString Frage::toXML()
 *  \brief Formats the question for writing it to the xml file
 *  \return a QString
 */
QString Frage::toXML() const {
QString mults="<Multchoice";
    mults.append(" A=\""+A+"\"");
    mults.append(" B=\""+B+"\"");
    mults.append(" C=\""+C+"\"");
    mults.append(" D=\""+D+"\"");
    mults.append(" right=\""+r+"\"");
    mults.append(">"+Fragen);
    mults.append("</Multchoice>");
return mults;
}

