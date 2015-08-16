/*
 *  Manash Kumar Mandal
 *  1203043
 *
 *
 * Qt Framework, QCustomPlot Library for Qt C++
 *
 * */
#include <QApplication>
#include "qcustomplot.h"
#include <QVector>
#include <QDebug>
#include "math.h"
#include <QPen>

typedef QVector <double> array;

double average(array &input)
{
    double sum = 0;
    for (int i = 0; i < input.size(); i++) sum += input[i];
    if (input.size() != 0) return sum / input.size();
    else return 0;
}

double calculateRank(array &xIn, array &yIn)
{
    double top = 0, bottom_first = 0, bottom_second = 0, bottom = 0;
    for (int i = 0; i < xIn.size(); i++){
        top += (xIn[i] - average(xIn)) * (yIn[i] - average(yIn));
        bottom_first += pow(xIn[i] - average(xIn), 2);
        bottom_second += pow(yIn[i] - average(yIn), 2);
    }

    bottom = sqrt(bottom_first * bottom_second);
    return top / bottom;
}

double calculateSlope(array &x_in, array &y_in)
{
    double top = 0, bottom = 0;
    for (int i = 0; i < x_in.size(); i++){
        top += (x_in[i] - average(x_in)) * (y_in[i] * average(y_in));
        bottom += pow((x_in[i] - average(x_in)), 2);
    }
    qDebug() << "top: " << top;
    qDebug() << "bottom: " << bottom;

    return top / bottom;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Creating array
    array x(43), y(43), new_y(43);

    // Inserting value
    for (int i = 0 ; i < 43; i++){
        x[i] = i;
        y[i] =  x[i] * 0.5 - x[i] * .1;
    }

    //Showing data in console
    qDebug() << "x:\n";
    for (int i = 0; i < x.size(); i++) {
        qDebug() << x[i];
    }

    qDebug() << "y:\n";
    for(int j = 0; j < y.size(); j++){
        qDebug() << y[j];
    }

    //Calculating Rank
    qDebug() << "Rank: " << calculateRank(x, y);

    double slope = calculateSlope(x, y);
    double b = average(y) - slope * average(x);

    //inserting new values to an array for plotting
    for (int i = 0; i < x.size(); i++) new_y[i] =  (slope * x[i] + b);

    QFont font("Consolas", 20);
    QFont font2("Consolas", 16);
    QPen pen(QColor(100, 255, 150), 5);
    QCustomPlot *plotter = new QCustomPlot;
    plotter->addGraph();
    plotter->graph(0)->setData(x, new_y);
    plotter->graph(0)->rescaleAxes();
    plotter->graph(0)->setPen(pen);

    QCPScatterStyle scatter(QCPScatterStyle::ssCircle, Qt::blue, 10);

    plotter->addGraph();
    plotter->graph(1)->setScatterStyle(scatter);
    plotter->graph(1)->setLineStyle(QCPGraph::lsNone);

    plotter->graph(1)->setData(x, y);
    plotter->graph(1)->rescaleAxes();
    plotter->yAxis->setRange(-70, 100);
    plotter->xAxis->setLabel("x value");
    plotter->yAxis->setLabel("y value");

    plotter->xAxis->setLabelFont(font);
    plotter->yAxis->setLabelFont(font);

    plotter->xAxis->setTickLabelFont(font2);
    plotter->yAxis->setTickLabelFont(font2);

    plotter->replot();
    plotter->show();
    return a.exec();
}
