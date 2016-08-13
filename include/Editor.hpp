#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED
#include <QLineEdit>
#include <QLabel>
#include <QObject>
#include <QTranslator>
#include <QPushButton>
#include <QGridLayout>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QWidget>

class Editor : public QWidget
{
    Q_OBJECT
    public:
        Editor();
        virtual ~Editor();
    protected:
    private:
    QLineEdit Frage,A,B,C,D,R;
    QLabel fragelab,alab,blab,clab,dlab,rlab;
    QPushButton ok,cancel,apply;
    QTranslator translator;
    QGridLayout g;
};

#endif // EDITOR_HPP_INCLUDED
