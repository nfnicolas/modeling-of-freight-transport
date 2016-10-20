#pragma once
#include"HeavyCar.h"
#include"Fuller.h"
class Emptier
{
	const static int volume = 1;
	const static int border1 = 120;
	const static int border2 = 480;
	int *to_empty; //array time to completion unloading -> -1 in the case downtime
	HeavyCar**serving; //array pointers on unloading trucks
	HeavyCar**queue;  //array pointers on trucks wating queue
public:
	
	Emptier();
	~Emptier();
	void Complete(int i);  // truck to completion unloading
	void Arrival(HeavyCar*h); //arrived truck
	void Print();
	int qLenght();
	int Busy();
	int FirstArrival(); // select first free truck 
	void run();
};

