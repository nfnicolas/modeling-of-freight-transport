#pragma once
#include"HeavyCar.h"
class Fuller:public HeavyCar
{
	const static int volume = 2;
	const static float mu ;  //0.25
	const static int rest = 300;
	float*perf;   //array perfomance loaders
	int to_bulldozer; // time to completion work bulldozer
	int *to_full;  //array times to completion loading  -> -1 in the case downtime
	HeavyCar**serving;  //array pointers on the loading truck
	HeavyCar**queue;  //array pointers on the trucks,wating in queue
	int*to_rest;  //array time to completion rest -> -1 unless loader is work
	int*isHeap;  // ready the heap ground
public:
	Fuller(HeavyCar**h);
	~Fuller();
	void GroundReady();  //bulldozer prepared heap ground
	void Complete(int i); // loader to completion load
	void RestComplete(int i);  //loader is rest
	void Arrival(HeavyCar*h); //arrived truck
	int BestAvail(); //select free truck
	void Print();
	int qLentgh(); //computation lenght queue
	int State(int i);  //computation position loader
	int Busy(); // computation quantity work loaders
	void run();
};

