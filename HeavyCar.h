#pragma once
#include<cstdio>
#include<ctime>
#include<iostream>
#include<fstream>
using namespace std;
FILE*qu1;
FILE*qu2;
int S{ 4 };   // the number of trucks
int completed{ 0 }; // counter of empty trucks
float que1_ave{ 0 };  //counter the average length queue loading
float que2_ave{ 0 };  // counter the average length queue unloading
long int total;      //counter general time modeling
long int ro_buld{0}; //counter the average loading bulldozer
float ro_fuller{ 0 };  //counter the average loading of point loading
float ro_emptier{ 0 };  //counter the average loading of point unloading
long int path_full{ 0 };  //counter time conducted in a way truck (full)
long int path_empty{ 0 };  //counter time conducted in a way truck (empty)
long int take{ 0 };  //counter time conducted in the point loading
long int give{ 0 };  //counter time conducted in the point unloading
class HeavyCar
{
	constexpr static float direct_ave=22.0;
	constexpr static float direct_disp = 3.0;
	constexpr static float back_ave = 18.0;
	constexpr static float back_disp = 3.0 
	int id = 0; // serial number truck
	enum states{Que_Fuller=1,Full,Full_Move,Que_Emptier,Empty,Empty_Move}
	state;  //current position truck
	int to_pfull; //time arrival in point loading
	int to_pempty;  //time arrival in point unloading
	void*f;  //pointer on the point loading
	void*e;  //pointer on the point unloading

public:
	friend class Fuller;
	friend class Emptier;
	HeavyCar(int i);
	void putFuller(Fuller*f1);
	void putEmptier(Emptier*e1);
	void run();
	void print();
	int State() { return (state); }
	~HeavyCar();
};

