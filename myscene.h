#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QList>
#include <QSignalMapper>
#include "marker.h"
#include "interpolation_model.h"
class QGraphicsSceneWheelEvent;
class myScene : public QGraphicsScene
{
    Q_OBJECT

public:
    myScene(QObject *parent = 0);
    void setCoreData(InterpolationModel *core);
    void setZoomScale(double scale);
private slots:
    void onMarkerMoved(QObject *markerFormMapper);
private:
    void updateData();
    void removeMarker(int id);
    void resizeMarkers();
    void resizeMarker(int id);
    Marker *appendMarker(double x,double y);
    QList<Marker *> markerList;
    InterpolationModel *coreData;
    QSignalMapper *mapper;
    double currentZoomScale;
    QGraphicsItemGroup* curves;
};



#endif // MYSCENE_H
