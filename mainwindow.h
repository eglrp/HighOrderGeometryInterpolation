#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "markerimageview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    MarkerImageView *markerViewer;
};

#endif // MAINWINDOW_H
