#include "plottermainwindow.h"
#include "ui_plottermainwindow.h"
#include "qcustomplot.h"



PlotterMainWindow::PlotterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotterMainWindow)
{
    //dataUi->setupUi(Ui::Data);
    ui->setupUi(this);

    customPlot = new QCustomPlot(this);


}

void PlotterMainWindow::getData()
{

}

PlotterMainWindow::~PlotterMainWindow()
{
    delete ui;
}
