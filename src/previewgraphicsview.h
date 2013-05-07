#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
 
#include <QGraphicsView>
#include <QGraphicsRectItem>
 
class PreviewGraphicsView : public QGraphicsView
{
    Q_OBJECT;
public:
    PreviewGraphicsView(QWidget* parent = NULL);
public slots:
    void setPicture(QString filename);
signals:
    void visibilityChanged(bool);
 
protected:
    //Holds the current centerpoint for the view, used for panning and zooming
    QPointF CurrentCenterPoint;
 
    //From panning the view
    QPoint LastPanPoint;
 
    //Set the current centerpoint in the
    void SetCenter(const QPointF& centerPoint);
    QPointF GetCenter() { return CurrentCenterPoint; }
 
    //Take over the interaction
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent * ce);
    QGraphicsPixmapItem *item;
    bool itemFit;
};
 
#endif // MYGRAPHICSVIEW_H
