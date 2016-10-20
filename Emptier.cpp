#include "Emptier.h"



Emptier::Emptier()
{
	to_empty = new int[volume];
	serving = new HeavyCar*[volume];
	queue = new HeavyCar*[S];
	for (size_t i = 0; i < volume; ++i)
	{
		to_empty[i] = -1;
		serving[i] = NULL;
	}
	for (size_t i = 0; i < S; ++i)
		queue[i] = NULL;
}

Emptier::~Emptier()
{
	delete[]to_empty;
	delete[]serving;
	delete[]queue;
}

void Emptier::Complete(int i)
{
	serving[i]->state = Empty_Move;
	serving[i]->to_pempty = (int)(get_normal(serving[i]->back_ave,
		serving[i]->back_disp, 0.001) * 60);
	if (qLenght() == 0)
	{
		to_empty[i] = -1;
		serving[i] = NULL;
	}
	else
	{
		to_empty[i] = border1 + rand() % (border2 - border1 + 1);
		serving[i] = queue[0];
		serving[i]->state = Empty;
		for (size_t j = 0; j < (S - 1); ++j)
			queue[j] = queue[j + 1];
		queue[S - 1] = NULL;
	}
	
}

void Emptier::Arrival(HeavyCar * h)
{
	int k, p;
	k = FirstArrival();
	if (k == -1)
	{
		p = qLenght();
		queue[p] = h;
		queue[p]->state = Que_Emptier;
	}
	else
	{
		to_empty[k] = border1 + rand() % (border2 - border1 + 1);
		serving[k] = h;
		serving[k]->state = Empty;
	}
}

void Emptier::Print()
{
	cout << "In queue on loading - trucks " << qLenght();
	for (size_t i = 0; i < S; ++i)
	{
		if (queue[i] == NULL)break;
		cout << "In queue truck # " << i + 1 << queue[i]->id;
	}
	for (size_t i = 0; i < volume; ++i)
	{
		if (to_empty[i] > 0)
			cout << "Loader working. It serving truck # " << i + 1 <<
			"Before the end of the loading remaine " << serving[i]->id << to_empty[i] / 60;
		else
			cout << "The loader is downtime " << i + 1;
	}
	return;
}

int Emptier::qLenght()
{
	for (size_t i = 0; i < S; ++i)
		if (queue[i] == NULL)return(i);
	return (S);
}

int Emptier::Busy()
{
	int k = 0;
	for (size_t i = 0; i < volume; ++i)
		if (to_empty[i] > 0)k++;
	return k;
}

int Emptier::FirstArrival()
{
	for (size_t i = 0; i < volume; ++i)
		if (to_empty[i] == -1)return(i);
	return (-1);
}

void Emptier::run()
{
	for (size_t i = 0; i < volume; ++i)
	{
		if (to_empty[i] > 0)to_empty--;
		if (to_empty[i] == 0)
		{
			Complete(i);
			completed++;
		}
	}
	cout << qu2<<" " << qLenght();
	que2_ave = que2_ave*(1 - 1.0 / (total + 1)) + ((float)qLenght()) / (total + 1);
}
