#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include <QLineEdit>
#include "familycompletion.h"

class SearchBox : public QLineEdit
{
    Q_OBJECT

public:
    SearchBox(QWidget *parent = 0);
    FamilyCompletion *completer;
//signals:
    //void completed(QString, QString);
public slots:
    void doSearch();
    //void completed(QString family, QString familyId);
};

#endif // SEARCHBOX_H
