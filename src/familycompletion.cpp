#include "familycompletion.h"
#include "qjson/parser.h"
#include <QSslError>
#include "cookiejar.h"

#define AUTOCOMPLETE_URL "https://www.jafrench.com/autocomplete/?contains=%1"


FamilyCompletion::FamilyCompletion(QLineEdit *parent) : QObject(parent), editor(parent)
{
    completed = false;
    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);

    popup->setColumnCount(2);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Box | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();

    popup->installEventFilter(this);

    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            SLOT(doneCompletion()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), SLOT(autoSuggest()));
    connect(editor, SIGNAL(textEdited(QString)), timer, SLOT(start()));

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
    networkManager.setCookieJar(new CookieJar(&networkManager));

}

FamilyCompletion::~FamilyCompletion()
{
    delete popup;
}

bool FamilyCompletion::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != popup)
        return false;

    if (ev->type() == QEvent::MouseButtonPress) {
        completed = true;
        popup->hide();
        editor->setFocus();
        return true;
    }

    if (ev->type() == QEvent::KeyPress) {

        bool consumed = false;
        int key = static_cast<QKeyEvent*>(ev)->key();
        switch (key) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            // ONLY IF AN ACTUAL SELECTION HAS BEEN MADE!!!?
            completed = true;
            doneCompletion();
            consumed = true;
        case Qt::Key_Escape:
            editor->setFocus();
            popup->hide();
            consumed = true;

        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;

        default:
            editor->setFocus();
            editor->event(ev);
            popup->hide();
            break;
        }

        return consumed;
    }

    return false;
}

void FamilyCompletion::showCompletion(const QStringList &choices, const QStringList &hits)
{

    if (choices.isEmpty() || choices.count() != hits.count())
        return;

    const QPalette &pal = editor->palette();
    QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

    popup->setUpdatesEnabled(false);
    popup->clear();
    for (int i = 0; i < choices.count(); ++i) {
        QTreeWidgetItem * item;
        item = new QTreeWidgetItem(popup);
        item->setText(0, choices[i]);
        item->setText(1, hits[i]);
        item->setTextAlignment(1, Qt::AlignRight);
        item->setTextColor(1, color);
    }
    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->resizeColumnToContents(1);
    popup->adjustSize();
    popup->setUpdatesEnabled(true);

    int h = popup->sizeHintForRow(0) * qMin(7, choices.count()) + 3;
    popup->resize(popup->width(), h);

    popup->move(editor->mapToGlobal(QPoint(0, editor->height())));
    popup->setFocus();
    popup->show();
}

void FamilyCompletion::doneCompletion()
{
    timer->stop();
    popup->hide();
    editor->setFocus();
    QTreeWidgetItem *item = popup->currentItem();
    if (item) {
        emit doneCompletion(item->text(0), item->text(1));
        //editor->setText(item->text(1));
        QMetaObject::invokeMethod(editor, "returnPressed");
    }
}

void FamilyCompletion::autoSuggest()
{
    completed = false;
    QString str = editor->text();
    QString url = QString(AUTOCOMPLETE_URL).arg(str);
    networkManager.get(QNetworkRequest(QString(url)));
    connect(&networkManager, SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError> &)),
            this, SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> &)));
}

void FamilyCompletion::sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist)
{
    qDebug() << "SSL ERRORS!!";
    foreach (QSslError err, errlist)
        qDebug() << "ssl error: " << err;
    qnr->ignoreSslErrors();
}

void FamilyCompletion::preventSuggest()
{
    timer->stop();
}

void FamilyCompletion::handleNetworkData(QNetworkReply *networkReply)
{
    //qDebug("got network reply");
    QUrl url = networkReply->url();
    QByteArray data(networkReply->readAll());

    if (!networkReply->error()) {
        //qDebug("No errors");
        QStringList choices;
        QStringList hits;
        bool ok;
        QVariantMap res = this->parser.parse(data, &ok).toMap();
        if (!ok) {
            qDebug("An error occurred during parsing");
            networkReply->deleteLater();
            return;
        }
        foreach (QVariant family, res["families"].toList()) {
            choices << QString(family.toMap()["firstNames"].toString() + " " + family.toMap()["lastName"].toString());
            //qDebug("row");
            hits << QString::number(family.toMap()["pk"].toInt());
        }

        showCompletion(choices, hits);
    } else {
        qDebug() << "Network Error! " << networkReply->errorString();
    }
    //qDebug("deleteLater()");
    networkReply->deleteLater();
}
