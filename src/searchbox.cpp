#include "searchbox.h"
#include "familycompletion.h"

SearchBox::SearchBox(QWidget *parent)
    : QLineEdit(parent)
{
    completer = new FamilyCompletion(this);

    connect(this, SIGNAL(returnPressed()),
            this, SLOT(doSearch()));
    //connect(completer, SIGNAL(doneCompletion(QString, QString)),
    //        this, SLOT(completed(QString, QString)));
    //setFocus();
}

void SearchBox::doSearch()
{
    //qDebug() << "---- Return ----";
    if( !completer->completed ) {
        //qDebug() << "---- Not completed! ----";
        return;
    }
    completer->preventSuggest();
    //setWindowTitle(text());
    clear();
    //QDesktopServices::openUrl(QUrl(url));
}

//void SearchBox::completed(QString family, QString familyId)
//{
//    emit completed(family, familyId);
//}
