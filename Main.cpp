#include<iostream>
#include<ctime>
#include<fstream>
#include<iomanip>
#include"HeavyCar.h"
#include"Fuller.h"
#include"Emptier.h"
using namespace std;
int main(int argc, char**argv)
{
	HeavyCar**truckMas;  //array trucks
	truckMas = new HeavyCar*[S];

	srand((unsigned)time(0));

	ofstream qu1 ("que1.txt", ios_base::out);  //open file to collect statics for queue lenght
	ofstream qu2("que2.txt", ios_base::out);
	return 0;
}