#include "HeavyCar.h"



HeavyCar::HeavyCar(int i)
{
	id = i;
	state = Que_Fuller;  // all truck stay in queue
	to_pfull = -1;
	to_pempty = -1;
}

void HeavyCar::putFuller(Fuller * f1)
{
	f = f1;
}

void HeavyCar::putEmptier(Emptier * e1)
{
	e = e1;
}

void HeavyCar::run()
{
	if (state == 3)    //the truck load is in way
	{
		to_pfull--;
		if (to_pfull == 0)  //the truck arived in point unloading
		{
			to_pfull = -1;
			((Emptier*)e)->Arrival(this);  //message this in point unloading
		}
	}
	else if (state == Empty_Move)  //the truck empty is in way
	{
		to_pempty--;
		if (to_pempty == 0)    //the truck arrived in point load
		{
			to_pempty = -1;
			((Fuller*)f)->Arrival(this); //message this in point loading
		}
	}
	else
		switch (state)
		{
		case Que_Fuller:take++; break;  //queue on load
		case Full:take++; break;   //load
		case Full_Move:path_full++; break; //way to point unloading
		case Que_Emptier:give++; break;     //queue on unloading
		case Empty: give++; break;     //unloading
		case Empty_Move: path_empty++; break;  //way to point loading
		}
	return;
}

void HeavyCar::print()
{
	switch (state)
	{
	case Que_Fuller: 
		cout << "The truck is in queue on load: " << id; break;
	case Full:
		cout << "The truck loading:  " << id; break;
	case Full_Move:
		cout << "The truck moving with weight. Arrived throw minutes: "<<id << ((float)to_pfull) / 60; break;
	case Que_Emptier:
		cout << "The truck is in queue on unloading: " << id; break;
	case Empty:
		cout << "The truck unloading: " << id; break;
	case Empty_Move:
		cout << "The truck moving is empty. Arrived throw minutes: " << id << ((float)to_pempty) / 60; break;

	}
}


HeavyCar::~HeavyCar()
{
}
