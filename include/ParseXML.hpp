#ifndef PARSEXML_HPP_INCLUDED
#define PARSEXML_HPP_INCLUDED
#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtXml/QtXml>
/*! \class ParseXML ParseXML.hpp "Quiz/ParseXML.hpp"
 *  \brief A class for parsing the questions out of the XML files and storing them
 */
template <typename A> class ParseXML : public QXmlDefaultHandler{
private:
QHash<int,A> hash/*!the hash for including the questions*/;
QList<int> state/*!the list for including the correctly answered questions of this type*/;
QFile *error/*!the file for the error log*/,*file/*!the xml file*/;
QString a/*!parameter for the first answer possibility*/,b/*!parameter for the secónd answer possibility*/,c/*!parameter for the third answer possibility*/,d/*!parameter for the fourth answer possibility*/,r/*!parameter for storing the right answer*/,img/*!parameter for storing an image path*/;
bool mul/*!shows if a mul question is read*/,free/*!shows if a free question is read*/,image/*!shows if an image question is read*/,errorfile/*!shows if the errorfile is available*/;
int i/*!the counter for creating the question index*/,zeile/*!counts the parsed columns for error messages*/;
public:
ParseXML()/*!constructs the class object, initialises the bool variables and prepares the error.log file for writing*/;
~ParseXML()/*!Default Destructor*/;
bool startElement(const QString &namespaceURI, const QString &localName, const QString &qname, const QXmlAttributes &qattributes);
bool endElement(const QString &namespaceURI, const QString &localName, const QString &qname);
bool characters(const QString &str);
bool fatalError(const QXmlParseException &exception);
bool parse(QString parsefile);
QHash<int,A> getHash();
QList<int> getState();
void insertState(int i);
void clearState();
bool full();
int getCapacity();
};
#endif // PARSEXML_HPP_INCLUDED
