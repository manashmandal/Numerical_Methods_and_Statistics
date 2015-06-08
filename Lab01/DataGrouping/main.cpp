#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct data
{
    int lowerValue;
    int upperValue;
    int value;
    int frequency = 0;
};

struct dataOperationResults
{
    double arithmatic_mean;
    double geometric_mean;
    double harmonic_mean;
    double mode;

    vector <double> median;
};

int main()
{

   int number;
   cout << "Enter the number of data: " << endl;
   cin >> number;

    vector <int> a;
    int sum = 0;
    long long int multiplication = 1;
    double inverse_sum = 0;

    int x;
    for (int i = 0 ; i < number; i++){
        cin >> x;
        a.push_back(x);
    }

    dataOperationResults operated_data;


    int minVal =  *min_element(a.begin(), a.end());
    int maxVal =  *max_element(a.begin(), a.end());

    int classNumber;
    double interVal;

    cout << "Enter number of classes: " << endl;
    cin >> classNumber;

    data * my_data = new data[classNumber];

    interVal = (double) (maxVal - minVal) / classNumber;


    //Calculate total
    for (size_t i = 0; i < a.size(); i++){
        sum += a[i];
    }

    //Calculate multiplication
    for (size_t i = 0; i < a.size(); i++){
        multiplication *= a[i];
    }

    //Calculate Inverse sum
    for (size_t i = 0; i < a.size(); i++){
        inverse_sum += pow(a[i], -1);
    }


    int left = minVal;
    int right = minVal + ceil(interVal);

    int interval = ceil(interVal);

    //Class Creation
    for (int i = 0; i < classNumber; i++){
        my_data[i].lowerValue = left;
        my_data[i].upperValue = right;
        left = right + 1;
        right = left + interval;
    }

    // grouped data with frequency
    for (int i = 0 ; i < a.size(); i++){
        for (int j = 0; j < classNumber; j++){
            if (a[i] >= my_data[j].lowerValue && a[i] <= my_data[j].upperValue){
                my_data[j].frequency++;
            }
        }
    }




    //Printing grouped data
    for (int i = 0; i < classNumber ; i++){

        cout << my_data[i].lowerValue << " - " << my_data[i].upperValue <<" - " << my_data[i].frequency <<endl;
    }


    //Calculate Arithmatic Mean
    operated_data.arithmatic_mean = static_cast<double> ( sum / a.size());

    //Calculate Geometric Mean
    operated_data.geometric_mean = static_cast<double> (pow(multiplication, 1.0 / a.size()));

    //Calculate Harmonic Mean
    operated_data.harmonic_mean = static_cast<double>(a.size() / inverse_sum);

    cout << "Arithmatic mean: " << operated_data.arithmatic_mean << endl;

    cout << "Geometric Mean: " << operated_data.geometric_mean << endl;

    cout << "Harmonic Mean: " << operated_data.harmonic_mean << endl;

//    int size;

//    ifstream file("data.txt");
//    int k[2][2];
//    for (int i = 0; i < 2; i++){
//        for (int j = 0; j < 2; j++){
//            file >> k[j][i];
//        }
//    }


//    int **a;

//    a = new int*[size];

//    for (int i = 0; i < size; ++i){
//        a[i] = new int[size];
//    }


//    ifstream file("data.txt");

//    for (int i = 0; i < size; i++){
//        for (int j = 0; j < size; j++){
//            file >> k[j][i];
//        }
//    }

//    /*
//    //Put data
//    for (int i = 0; i < size; i++){
//        for (int j = 0; j < size; j++){
//            a[i][j] = 5 * i;
//        }
//    }
//
//    //Printing

//    for (int i = 0; i < 2; i++){

//        for (int j = 0; j < 2; j++){
//            cout << "  " << k[j][i] << "  ";
//        }
//        cout << endl;
//    }

    cout << endl;
}

