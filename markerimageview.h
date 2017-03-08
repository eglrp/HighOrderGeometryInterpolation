#ifndef MARKERIMAGEVIEW_H
#define MARKERIMAGEVIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QList>
#include <cmath>
#include "myscene.h"
#include "marker.h"
#include "interpolation_model.h"
class QModelIndex;
class QAbstractItemModel;
class QItemSelectionModel;
class QSignalMapper;
class QImage;
class QItemSelection;
class QMatrix;
class MarkerImageView : public QGraphicsView
{
    Q_OBJECT

public:
    enum ViewMode {
        InsertItem, MoveItem
    };
    MarkerImageView(QWidget *parent = 0);
    void setCoreData(InterpolationModel* core);
    void loadImage(const QImage &image);
protected:
    void wheelEvent(QWheelEvent *event);
public slots:
    void scrollWithPixels(const QPoint &pixel);
    void scrollWithDegrees(const QPoint &step);
    void zoom(double z);
    void zoomRestore();
private:
    myScene *scene;
};

#endif // MARKERIMAGEVIEW_H
