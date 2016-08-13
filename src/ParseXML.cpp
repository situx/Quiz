#include "../include/ParseXML.hpp"
#include <iostream>
#include "../include/Frageimg.hpp"
#include "../include/Fragefrei.hpp"
template <typename A>
ParseXML<A>::ParseXML(){
    mul=false;
    free=false;
    image=false;
    zeile=0;
    error = new QFile("error.log");
    errorfile=true;
    if (!error->open(QFile::WriteOnly|QFile::Text|QFile::Append)){
        std::cerr<<"Errorlog could not be created"<<std::endl;
        errorfile=false;
    }
}
template <typename A>
ParseXML<A>::~ParseXML(){
}
/*! \fn bool ParseXML<A>::parse(QString parsefile)
 *  \brief calls the parse function for the given XML-File and handles errors
 *  \param parsefile a QString: the filename of the file to be parsed
 *  \return a bool: success indicator
 */
template <typename A>
bool ParseXML<A>::parse(QString parsefile){
    file= new QFile(parsefile);
    if(!file->open(QFile::ReadOnly | QFile::Text)){/*Checks if the XML-File can be opened*/
        std::cerr<<"File "<<qPrintable(parsefile)<<" could not be opened"<<std::endl;
        if(errorfile){
            error->write("File ");
            error->write(qPrintable(parsefile));
            error->write(" could not be opened\n\n");
            error->close();
        }
        delete(error);/*deleting the error and xml file objects - they are no longer needed if the file could not be opened*/
        delete(file);
        return false;
    }
    std::cout<<"File "<<qPrintable(parsefile)<<" opened"<<std::endl;
    i=0;
    QXmlInputSource qi (file);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);/*Setting the this object as content and default handler*/
    reader.setErrorHandler(this);
    reader.parse(&qi,false);
    std::cout<<hash.count()<<" questions added"<<std::endl;
    file->close();
    error->close();
    delete(error);/*deleting the error and xml file objects - they are no longer needed after the first parse*/
    delete(file);
    return true;
}
/*! \fn bool ParseXML<A>::startElement(const QString &namespaceURI, const QString &localName, const QString &qname, const QXmlAttributes &qattributes)
 *  \brief an event handler called when a new XML Element begins: parses the data in the tags
 *  \param namespaceURI a const QString: the namespace of the XML document
 *  \param localName a const QString: the tagname of the element
 *  \param qname a const QString: the qname of the element
 *  \param qattributes a QXmlAttributes: the attributes list of the element
 *  \return a bool: success indicator
 */
template <typename A>
bool ParseXML<A>::startElement(const QString &namespaceURI, const QString &localName, const QString &qname, const QXmlAttributes &qattributes){
zeile++;
if (localName=="Multchoice" || localName=="Image" || localName=="Fragefrei"){/*decides which question type is read and saves the appropriate values*/
    r=qattributes.value("Right");
    if(localName=="Fragefrei")
        return(free=true);
    a=qattributes.value("A");
    b=qattributes.value("B");
    c=qattributes.value("C");
    d=qattributes.value("D");
    if (localName=="Image"){
        img=qattributes.value("Img");
        return(image=true);
    }
    return (mul=true);
}
return true;
}
/*! \fn bool ParseXML<A>::endElement(const QString &namespaceURI, const QString &localName, const QString &qname)
 *  \brief an event handler called when a new XML Element ends: parses the data in the tags
 *  \param namespaceURI a const QString: the namespace of the XML document
 *  \param localName a const QString: the tagname of the element
 *  \param qname a const QString: the qname of the element
 *  \return a bool: success indicator
 */
template <typename A>
bool ParseXML<A>::endElement(const QString &namespaceURI, const QString &localName, const QString &qname){
    return true;
}
/*! \fn bool ParseXML<A>::characters(const QString &str)
 *  \brief an event handler called when the character section of the tag is reached
 *  \param str a const QString: includes the text of the tag
 *  \return a bool: success indicator
 */
template <typename A>
bool ParseXML<A>::characters(const QString &str){
    if (image || free || mul){
        if(free){
            if(str!=NULL && r!=NULL)/*Checks if all parameters are valid*/
                hash.insert(i++,A(str,r));
            else{
                std::cerr<<"A parameter of the freequestion in line "<<zeile<<" could not be parsed correctly!"<<std::endl;
                if(errorfile){
                    error->write("A parameter of the freequestion in line ");
                    error->write(qPrintable(QString::number(zeile)));
                    error->write("could not be parsed correctly!");
                }
            }
            free=false;
        }
        else if (image){
            if(str!=NULL && r!=NULL && r.length()==1  && r.toUtf8()>="A" && r.toUtf8()<="D" && a!=NULL && b!=NULL && c!=NULL && d!=NULL && img!=NULL){/*Checks if all parameters are valid*/
                QFile test(img);
                if(test.exists())/*Checking if the image file exists*/
                    hash.insert(i++,A(str,r,a,b,c,d,img));
                else{
                    std::cerr<<"Image "<<qPrintable(img)<<" could not be found"<<std::endl;
                    if(errorfile){
                        error->write("Image ");
                        error->write(qPrintable(img));
                        error->write(" could not be found\n\n");
                    }
                }
            }
            else{
                std::cerr<<"A parameter of the imagequestion in line "<<zeile<<" could not be parsed correctly!"<<std::endl;
                if(errorfile){
                    error->write("A parameter of the imagequestion in line ");
                    error->write(qPrintable(QString::number(zeile)));
                    error->write("could not be parsed correctly!");
                }
            }
            image=false;
        }
        else if(mul){
            if(str!=NULL && r!=NULL && r.length()==1 && r.toUtf8()>="A" && r.toUtf8()<="D" && a!=NULL && b!=NULL && c!=NULL && d!=NULL)/*Checks if all parameters are valid*/
                hash.insert(i++,A(str,r,a,b,c,d));
            else{
                std::cerr<<"A parameter of the multiple choice question in line "<<zeile<<" could not be parsed correctly!"<<std::endl;
                if(errorfile){
                    error->write("A parameter of the multiple choice question in line ");
                    error->write(qPrintable(QString::number(zeile)));
                    error->write("could not be parsed correctly!");
                }
            }
            mul=false;
        }
    }
    return true;
}
/*! \fn bool ParseXML<A>::fatalError(const QXmlParseException &exception)
 *  \brief prints out an error message if a fatal parse error occurs
 *  \param exception a const QString: the namespace of the XML documen
 *  \return a bool: success indicator
 */
template <typename A>
bool ParseXML<A>::fatalError(const QXmlParseException &exception){
    QString w="";/*String to collect the error information*/
    w.append("Parsing Error in File ");
    w.append(file->fileName());
    w.append("\nLine: ");
    w.append(QString::number(exception.lineNumber()));
    w.append(" Column: ");
    w.append(QString::number(exception.columnNumber()));
    w.append("\nError Message: ");
    w.append(exception.message());
    w.append("\n");
    std::cerr<<qPrintable(w);
    w.append("\n");
    error->write(qPrintable(w));
    return true;
}
/*! \fn QHash<int,A> ParseXML<A>::getHash()
 *  \brief returns the hash including its questions
 *  \return a QHash<int,A>
 */
template <typename A>
QHash<int,A> ParseXML<A>::getHash(){
    QHash<int,A>& refhash = hash;
    return refhash;
}
/*! \fn QList<int> ParseXML<A>::getState()
 *  \brief returns the log list
 *  \return a QList<int>
 */
template <typename A>
QList<int> ParseXML<A>::getState(){
    QList<int>& refstate = state;
    return refstate;
}
/*! \fn void ParseXML<A>::insertState(int i)
 *  \brief inserts a value in the status list
 *  \param i an int: the value to insert
 *  \return void
 */
template <typename A>
void ParseXML<A>::insertState(int i){
   state.append(i);
}
/*! \fn void ParseXML<A>::clearState()
 *  \brief clears the status list
 *  \return void
 */
template <typename A>
void ParseXML<A>::clearState(){
   state.clear();
}
/*! \fn bool ParseXML<A>::full()
 *  \brief checks if the list contains as much elements as the hash does
 *  \return a bool: true or false
 */
template <typename A>
bool ParseXML<A>::full(){
   return (state.size()>=hash.size());
}
/*! \fn int ParseXML<A>::getCapacity()
 *  \brief returns the hashs capacity
 *  \return a int
 */
template <typename A>
int ParseXML<A>::getCapacity(){
    return hash.capacity();
}
