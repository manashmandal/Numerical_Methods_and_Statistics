/*
 *  Manash Kumar Mandal
 *  1203043
 *
 *
 * Qt Framework, QCustomPlot Library for Qt C++
 *
 * Verification Link: https://github.com/manashmndl/Numerical_Methods_and_Statistics/tree/master/Lab04
 *
 * */
#include <QApplication>
#include "qcustomplot.h"
#include <QVector>
#include <QDebug>
#include "math.h"
#include <QPen>
#define endl "\n"
#define TRUE 1

#define TRUEVALUE_FUNC1 15.41261

using namespace std;

typedef QVector <double> array;

double function(double x)
{
    double out = 10 * exp(-x) * sin(2 * x * M_PI );
    double res = pow(out, 2);
    return res;
}

//Trapezoidal Method
double trapezoidalRule(double down, double up, double segments)
{
    double h = (up - down) / segments;
    double total = 0.0000000;
    array dataset(segments + 1);
    dataset[0] = down;
    double xi = 0.0;
    for (int i = 1; i < segments + 1; i++){
        xi += h;
        dataset[i] = xi;
    }
    double fx0 = function(dataset[0]);
    double fxn = function(dataset[dataset.size() - 1]);

    for (int i = 1; i < dataset.size() - 1; i++) total += function(dataset[i]);
    double result = h / 2 * ( fx0 + 2 * total + fxn);
    return result;
}

//Simpsone 1/3 Rule Function
double simpsonOneThird(double lo, double hi, double segments)
{
    array dataset(segments + 1);
    double h = (hi - lo) / segments;
    double xi = 0;
    dataset[0] = lo;
    //Generate Data
    for (int i = 1; i < segments + 1; i++){
        xi += h;
        dataset[i] = xi;
    }
    double fx0 = function(dataset[0]);
    double fxn = function(dataset[dataset.size()-1]);
    double odd, even;
    odd = even = 0;
    //Calculation for odd and even parts
    for (int i = 1; i < dataset.size() - 1; i++){
        if (i % 2 != 0) {
            odd += function(dataset[i]);
        } else {
            even += function(dataset[i]);
        }
    }
    return h / 3 * (fx0 + fxn + 4 * odd + 2 * even);
}

//Calculates Relative error in %
double error(double input, double real)
{
    return ((real - input) / real ) * 100;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCustomPlot *plotter = new QCustomPlot;
    array error_values(8);
    array segment_values(8);
    array error_values_simpson(8);
    array segment_values_simpson(8);
    QFont font("Consolas", 20);
    QFont font2("Consolas", 16);
    QPen pen(QColor(100, 255, 150), 5);
    QPen pen2(QColor(255, 0, 0), 5);
    qDebug() << "TRAPEZOIDAL RULE" << endl;
    qDebug() << "================" << endl;
    qDebug() << "Segments\tIntegral\t\terror(%)" << endl;
    for (int i = 0; i < 8; i++){
        int segments = pow(2, i);
        segment_values[i] = segments;
        double integral = trapezoidalRule(0, 0.5, segments);
        double err = error(integral, TRUEVALUE_FUNC1);
        error_values[i] = err;
        qDebug() << segments << "\t\t" << integral << "\t\t" << err << "\t";
        endl;
    }
    qDebug() << "SIMPSON 1/3 RULE" << endl;
    qDebug() << "================" << endl;
    qDebug() << "Segments\tIntegral\t\terror(%)" << endl;
    for (int i = 0; i < 8; i++){
        int segments = pow(2, i);
        segment_values_simpson[i] = segments;
        double integral = simpsonOneThird(0, 0.5, segments);
        double err = error(integral, TRUEVALUE_FUNC1);
        error_values_simpson[i] = err;
        qDebug() << segments << "\t\t" << integral << "\t\t" << err << "\t";
        endl;
    }
    plotter->legend->setVisible(true);
    plotter->legend->setFont(font);
    plotter->addGraph();
    plotter->graph(0)->setData(segment_values, error_values);
    plotter->graph(0)->setPen(pen);
    plotter->yAxis->rescale();
    plotter->xAxis->setLabelFont(font);
    plotter->graph(0)->setName("Trapezoidal Method");
    plotter->yAxis->setLabelFont(font);
    plotter->xAxis->setTickLabelFont(font2);
    plotter->yAxis->setTickLabelFont(font2);
    plotter->xAxis->setLabel("Number of segments");
    plotter->yAxis->setLabel("Error (%)");
    plotter->plotLayout()->insertRow(0);
    plotter->plotLayout()->addElement(0, 0, new QCPPlotTitle(plotter, "Error vs Segment Graph using Trapezoidal & Simpson 1/3 Method"));
    plotter->addGraph();
    plotter->graph(1)->setData(segment_values_simpson, error_values_simpson);
    plotter->graph(1)->setPen(pen2);
    plotter->graph(1)->setName("Simpson 1/3 Method");
    plotter->xAxis->setRange(0, 8);
    plotter->yAxis->setRange(-35,100);
    plotter->replot();
    plotter->show();
    return a.exec();
}
