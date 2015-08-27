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
#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))
#define TRUE 1

typedef QVector <double> array;


void swap_row(double *a, double *b, int r1, int r2, int n)
{
    double tmp, *p1, *p2;
    int i;

    if (r1 == r2) return;
    for (i = 0; i < n; i++) {
        p1 = mat_elem(a, r1, i, n);
        p2 = mat_elem(a, r2, i, n);
        tmp = *p1, *p1 = *p2, *p2 = tmp;
    }
    tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}

void gauss_eliminate(double *a, double *b, double *x, int n)
{
#define A(y, x) (*mat_elem(a, y, x, n))
    int i, j, col, row, max_row,dia;
    double max, tmp;

    for (dia = 0; dia < n; dia++) {
        max_row = dia, max = A(dia, dia);

        for (row = dia + 1; row < n; row++)
            if ((tmp = fabs(A(row, dia))) > max)
                max_row = row, max = tmp;

        swap_row(a, b, dia, max_row, n);

        for (row = dia + 1; row < n; row++) {
            tmp = A(row, dia) / A(dia, dia);
            for (col = dia+1; col < n; col++)
                A(row, col) -= tmp * A(dia, col);
            A(row, dia) = 0;
            b[row] -= tmp * b[dia];
        }
    }
    for (row = n - 1; row >= 0; row--) {
        tmp = b[row];
        for (j = n - 1; j > row; j--)
            tmp -= x[j] * A(row, j);
        x[row] = tmp / A(row, row);
    }
#undef A
}

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
    return top / bottom;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //Creating array
//    array x(43), y(43), new_y(43);

//    // Inserting value
//    for (int i = 0 ; i < 43; i++){
//        x[i] = i;
//        y[i] =  x[i] * 0.5 - x[i] * .1;
//    }

//    //Showing data in console
//    qDebug() << "x:\n";
//    for (int i = 0; i < x.size(); i++) {
//        qDebug() << x[i];
//    }

//    qDebug() << "y:\n";
//    for(int j = 0; j < y.size(); j++){
//        qDebug() << y[j];
//    }

//    double slope = calculateSlope(x, y);
//    double b = average(y) - slope * average(x);

//    //inserting new values to an array for plotting
//    for (int i = 0; i < x.size(); i++) new_y[i] =  (slope * x[i] + b);

//    QFont font("Consolas", 20);
//    QFont font2("Consolas", 16);
//    QPen pen(QColor(100, 255, 150), 5);
//    QCustomPlot *plotter = new QCustomPlot;
//    plotter->addGraph();
//    plotter->graph(0)->setData(x, new_y);
//    plotter->graph(0)->rescaleAxes();
//    plotter->graph(0)->setPen(pen);

//    QCPScatterStyle scatter(QCPScatterStyle::ssCircle, Qt::black, 10);

//    plotter->addGraph();
//    plotter->graph(1)->setScatterStyle(scatter);
//    plotter->graph(1)->setLineStyle(QCPGraph::lsNone);
//    plotter->graph(1)->setData(x, y);
//    plotter->graph(1)->rescaleAxes();
//    plotter->yAxis->setRange(-70, 100);
//    plotter->xAxis->setLabel("x value");
//    plotter->yAxis->setLabel("y value");
//    plotter->xAxis->setLabelFont(font);
//    plotter->yAxis->setLabelFont(font);
//    plotter->xAxis->setTickLabelFont(font2);
//    plotter->yAxis->setTickLabelFont(font2);
//    plotter->plotLayout()->insertRow(0);
//    plotter->plotLayout()->addElement(0, 0, new QCPPlotTitle(plotter, "Linear Fitting"));

//    plotter->replot();
//    plotter->show();

//    //Polynomial Curve fitting begins here

//    array polynomial_y(43);
//    for (int i = 0; i < 43; i++){
//        polynomial_y[i] = 1.52 * x[i] + 0.49 * pow(x[i], 2);
//    }

//    QCustomPlot *poly_plotter = new QCustomPlot;
//    poly_plotter->addGraph();
//    poly_plotter->graph(0)->setData(x, polynomial_y);
//    poly_plotter->rescaleAxes();
//    poly_plotter->xAxis->setAutoTicks(TRUE);
//    poly_plotter->yAxis->setAutoTicks(TRUE);
//    poly_plotter->xAxis->setLabelFont(font);
//    poly_plotter->yAxis->setLabelFont(font);
//    poly_plotter->xAxis->setTickLabelFont(font2);
//    poly_plotter->yAxis->setTickLabelFont(font2);
//    poly_plotter->addGraph();
//    poly_plotter->graph(1)->setData(x, y);
//    poly_plotter->graph(1)->setScatterStyle(scatter);
//    poly_plotter->xAxis->setAutoTickStep(TRUE);
//    poly_plotter->yAxis->setAutoTickStep(TRUE);
//    poly_plotter->graph(1)->setLineStyle(QCPGraph::lsNone);
//    poly_plotter->xAxis->setLabel("x");
//    poly_plotter->yAxis->setLabel("y");
//    poly_plotter->graph(0)->setPen(pen);
//    poly_plotter->plotLayout()->insertRow(0);
//    poly_plotter->plotLayout()->addElement(0, 0, new QCPPlotTitle(poly_plotter, "Polynomial Curve Fitting"));
//    poly_plotter->replot();
//    poly_plotter->show();

//    //Calculating Rank
//    qDebug() << "Rank: " << calculateRank(x, y);

//    double SpeedN[] = {3000, 2997, 2984, 2973, 2957, 2945, 2928, 2908};
//    double TorqueT[] = {.19, .24, .299, .32, .36, .39, .44, .48};
//    double OutputVoltageV[] = {47, 46, 45, 44, 43.5, 43, 42.5, 42};
//    double InputCurrentI[] = {3, 3.1, 3.25, 3.4, 3.5, 3.7, 3.85, 4.00};
//    double InputVoltageV[] = {40, 40.9, 40.6, 40.4, 40.2, 40.0, 39.7, 39.6};
//    double OutputCurrentI[] = {0, 0.2, 0.37, 0.52, 0.7, 0.86, 1.00, 1.1};

//    array speed(8), torque(8), input_current(8), output_current(8), output_voltage(8);

//    for (int i = 0; i < 8; i++){
//        speed[i] = SpeedN[i];
//        torque[i] = TorqueT[i];
//        input_current[i] = InputCurrentI[i];
//        output_current[i] = OutputCurrentI[i];
//        output_voltage[i] = OutputVoltageV[i];
//    }

//    QCustomPlot *plotter = new QCustomPlot;
//    plotter->addGraph();
//    plotter->graph(0)->setData(input_current, torque);
//    plotter->addGraph();
//    plotter->graph(1)->setPen(QPen(Qt::red));
//    plotter->graph(1)->setData(input_current, speed);

//    plotter->yAxis->rescale();
//    plotter->xAxis->rescale();
//    plotter->show();

    return a.exec();
}
