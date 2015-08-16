#ifndef PLOTTERMAINWINDOW_H
#define PLOTTERMAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"


namespace Ui {
class PlotterMainWindow;


}

class PlotterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotterMainWindow(QWidget *parent = 0);
    ~PlotterMainWindow();

public slots:
    void getData();


private:
    Ui::PlotterMainWindow *ui;



    QCustomPlot *customPlot;
};

#endif // PLOTTERMAINWINDOW_H
