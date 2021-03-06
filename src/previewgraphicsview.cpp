//Our includes
#include "previewgraphicsview.h"
 
//Qt includes
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTextStream>
#include <QScrollBar>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QGraphicsProxyWidget>
 
/**
* Sets up the subclassed QGraphicsView
*/
PreviewGraphicsView::PreviewGraphicsView(QWidget* parent) : QGraphicsView(parent) {
 
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setCursor(Qt::OpenHandCursor);
 
    QGraphicsScene* Scene = new QGraphicsScene(this);
    setScene(Scene);
    item = NULL;
    Scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
}

void PreviewGraphicsView::closeEvent(QCloseEvent * ce)
{
    emit visibilityChanged(false);
}

void PreviewGraphicsView::setPicture(QString filename) {
    if(item != NULL) {
        //scene()->removeItem(item);
        delete item;
    }
    if( filename == NULL ) {
        item = NULL;
       return;
    }
    item = new QGraphicsPixmapItem(QPixmap(filename));
    item->setTransformationMode(Qt::SmoothTransformation);
    scene()->addItem(item);
    setSceneRect(0, 0, item->pixmap().width(), item->pixmap().height());
    fitInView(item, Qt::KeepAspectRatio);
    itemFit = true;
    centerOn(item);
}
 
/**
  * Sets the current centerpoint.  Also updates the scene's center point.
  * Unlike centerOn, which has no way of getting the floating point center
  * back, SetCenter() stores the center point.  It also handles the special
  * sidebar case.  This function will claim the centerPoint to sceneRec ie.
  * the centerPoint must be within the sceneRec.
  */
//Set the current centerpoint in the
void PreviewGraphicsView::SetCenter(const QPointF& centerPoint) {
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();
 
    //Get the scene area
    QRectF sceneBounds = sceneRect();
 
    double boundX = visibleArea.width() / 2.0;
    double boundY = visibleArea.height() / 2.0;
    double boundWidth = sceneBounds.width() - 2.0 * boundX;
    double boundHeight = sceneBounds.height() - 2.0 * boundY;
 
    //The max boundary that the centerPoint can be to
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);
 
    if(bounds.contains(centerPoint)) {
        //We are within the bounds
        CurrentCenterPoint = centerPoint;
    } else {
        //We need to clamp or use the center of the screen
        if(visibleArea.contains(sceneBounds)) {
            //Use the center of scene ie. we can see the whole scene
            CurrentCenterPoint = sceneBounds.center();
        } else {
 
            CurrentCenterPoint = centerPoint;
 
            //We need to clamp the center. The centerPoint is too large
            if(centerPoint.x() > bounds.x() + bounds.width()) {
                CurrentCenterPoint.setX(bounds.x() + bounds.width());
            } else if(centerPoint.x() < bounds.x()) {
                CurrentCenterPoint.setX(bounds.x());
            }
 
            if(centerPoint.y() > bounds.y() + bounds.height()) {
                CurrentCenterPoint.setY(bounds.y() + bounds.height());
            } else if(centerPoint.y() < bounds.y()) {
                CurrentCenterPoint.setY(bounds.y());
            }
 
        }
    }
 
    //Update the scrollbars
    centerOn(CurrentCenterPoint);
}

void PreviewGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    if(itemFit) {
        //Get the position of the mouse before scaling, in scene coords
        QPointF pointBeforeScale(mapToScene(event->pos()));

        //Get the original screen centerpoint
        QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());

        //Scale the view ie. do the zoom
        double scaleFactor = 1.15*3; //How fast we zoom
        scale(scaleFactor, scaleFactor);
        itemFit = false;

        //Get the position after scaling, in scene coords
        QPointF pointAfterScale(mapToScene(event->pos()));

        //Get the offset of how the screen moved
        QPointF offset = pointBeforeScale - pointAfterScale;

        //Adjust to the new center for correct zooming
        QPointF newCenter = screenCenter + offset;
        SetCenter(newCenter);
    } else {
        itemFit = true;
        if(item)
            fitInView(item, Qt::KeepAspectRatio);
    }
}
 
/**
  * Handles when the mouse button is pressed
  */
void PreviewGraphicsView::mousePressEvent(QMouseEvent* event) {
    //For panning the view
    LastPanPoint = event->pos();
    setCursor(Qt::ClosedHandCursor);
}
 
/**
  * Handles when the mouse button is released
  */
void PreviewGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(Qt::OpenHandCursor);
    LastPanPoint = QPoint();
}
 
/**
*Handles the mouse move event
*/
void PreviewGraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if(!LastPanPoint.isNull()) {
        //Get how much we panned
        QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
        LastPanPoint = event->pos();
 
        //Update the center ie. do the pan
        SetCenter(GetCenter() + delta);
    }
}
 
/**
  * Zoom the view in and out.
  */
void PreviewGraphicsView::wheelEvent(QWheelEvent* event) {
 
    //Get the position of the mouse before scaling, in scene coords
    QPointF pointBeforeScale(mapToScene(event->pos()));
 
    //Get the original screen centerpoint
    QPointF screenCenter = GetCenter(); //CurrentCenterPoint; //(visRect.center());
 
    //Scale the view ie. do the zoom
    double scaleFactor = 1.15; //How fast we zoom
    if(event->delta() > 0) {
        //Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        //Zooming out
        if( mapToScene(rect()).boundingRect().height() > sceneRect().height()
                and mapToScene(rect()).boundingRect().width() > sceneRect().width())
            return;
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
    itemFit = false;
 
    //Get the position after scaling, in scene coords
    QPointF pointAfterScale(mapToScene(event->pos()));
 
    //Get the offset of how the screen moved
    QPointF offset = pointBeforeScale - pointAfterScale;
 
    //Adjust to the new center for correct zooming
    QPointF newCenter = screenCenter + offset;
    SetCenter(newCenter);
}
 
/**
  * Need to update the center so there is no jolt in the
  * interaction after resizing the widget.
  */
void PreviewGraphicsView::resizeEvent(QResizeEvent* event) {
    //qDebug() << "resize";
    if( itemFit && item )
        fitInView(item, Qt::KeepAspectRatio);
    //Get the rectangle of the visible area in scene coords
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    SetCenter(visibleArea.center());
 
    //Call the subclass resize so the scrollbars are updated correctly
    QGraphicsView::resizeEvent(event);
}

