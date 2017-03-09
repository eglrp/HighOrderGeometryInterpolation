#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "markerimageview.h"
#include "myscene.h"
#include "interpolation_model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:

    void changeDegree(int degree);
    void resetControlPoints();
	void resetNonVertex();
public:
    MainWindow(QWidget *parent = 0);
    MarkerImageView *markerViewer;
    myScene* scene;
    InterpolationModel* model;
};

#endif // MAINWINDOW_H
