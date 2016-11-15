#include "Fuller.h"



Fuller::Fuller(HeavyCar**h)
//at the beginning all loaders downtime,all trucks wait in queue,bulldozers get to work
{
	//to_bulldozer = (int)(get_erland(mu, volume, 0.001) * 60);
	to_full = new int[volume];
	to_rest = new int[volume];
	perf = new float[volume];
	isHeap = new int[volume];
	serving = new HeavyCar*[volume];
	queue = new HeavyCar*[S];
	perf[0] = 0.0714;     //capacity loader number 1 - 1/14 truck in minute
	perf[1] = 0.0833;   //perfomance loader number 2 - 1/12 truck in minute
	for (size_t i = 0; i < volume; ++i)
	{
		to_full[i] = -1;
		to_rest[i] = -1;
		isHeap[i] = 0;
		serving[i] = nullptr;
	}
	for (size_t i = 0; i < S; ++i)
		queue[i] = h[i];
}


Fuller::~Fuller()
{
	delete[] to_full;
	delete[]to_rest;
	delete[]isHeap;
	delete[]serving;
	delete[]perf;
	delete[]serving;
	delete[]queue;
}

void Fuller::GroundReady()
{
	int mi,k;
	for (size_t i = 0; i < volume; ++i)
		isHeap[i] = 1;
	to_bulldozer = -1;
	if (qLentgh() < volume)mi = qLentgh();
	else
		mi = volume;
	for (size_t j = 0; j < mi; ++j)
	{
		k = BestAvail();
		if (k == -1)return;
		//to_full[k] = (int)(get_exp(perf[k] * 60));  //random number generator
		serving[k] = queue[0];

		queue[0]->state=Full;

		for (size_t i = 0; i < (S - 1); ++i)
			queue[i] = queue[i + 1];
		queue[S - 1] = NULL;
	}
}

void Fuller::Complete(int i)
{
	to_rest[i] = rest;
	isHeap[i] = 0;
	to_full[i] = -1;
	serving[i]->state = Full_Move;
	serving[i]->to_pfull = (int)(get_normal(serving[i]->direct_ave, serving[i]->direct_disp, 0.001) * 60);
	serving[i] = NULL;
	for (int j = 0; j < volume; ++j) {
		if (isHeap[j] == 1)break;
		if (j == volume)         //starting bulldozer if loader free
			to_bulldozer = (int)(get_erlang(mu, volume, 0.001) * 60);
	}
}

void Fuller::RestComplete(int i)
{
	to_rest[i] = -1;
	if (qLentgh() == 0)return;
	if (isHeap[i] == 0)return;
	to_full = (int)(get_exp(perf[i]) * 60);
	serving[i] = queue[0];
	queue[0]->state = Full;
	for (size_t k = 0; k < (S - 1); ++k)
		queue[k] = queue[k + 1];
	queue[S - 1] = NULL;
}

void Fuller::Arrival(HeavyCar * h)  //arrived empty truck
{
	int k, p;
	k = BestAvail();
	if (k == -1)
	{
		p = qLentgh();
		queue[p] = h;
		queue[p]->state = Que_Fuller;
	}
	else
	{
		to_full[p] = (int)(get_exp(perf[k] * 60));
		serving[k] = h;
		serving[k]->state = Full;
	}
}

int Fuller::BestAvail()
{
	float max = 0;
	int k = -1;
	for (size_t i = 0; i < volume; ++i)
	{
		if ((State(i) == 3) && (perf[i] > max) && (isHeap[i] == 1))
		{
			max = perf[i];
			k = i;
		}
	}
	return(k);
}

void Fuller::Print()
{
	if (to_bulldozer > 0)
		cout << "The bulldozer is work. Prepare heap ground throw minutes: " <<
		to_bulldozer / 60;
	else
		cout << "The bulldozer dont work\n" << "In queue on load truck " << qLentgh();
	for (size_t i = 0; i < S; ++i)
	{
		if (!queue[i])break;
		cout << "The truck is queue " << i + 1 << queue[i]->id;
	}
	for (size_t i = 0; i < volume; ++i)
	{
		switch (State(i))
		{
		case 1:
			cout << "The loader working. It is serving truck ... " << i + 1 << serving[i]->id << to_full[i] / 60;
		case 2:
			cout << "The loader is rest " << i + 1 << to_rest[i] / 60;
		case 3:
			cout << "The loader is downtime " << i + 1;
		}
	}
	return;
}

int Fuller::qLentgh()
{
	for (size_t i = 0; i < S; ++i)
		if (queue[i] == NULL)return(1);
	return (S);
}

int Fuller::State(int i)
{
	if (serving[i] != NULL)return 1;
	if(to_rest[i]>0)return 2;
	return(3);
}

int Fuller::Busy()
{
	int k = 0;
	for (size_t i = 0; i < volume; ++i)
		if (State(i) == 1)k++;
	return (k);
}

void Fuller::run()
{
	if (to_bulldozer > 0)to_bulldozer--;
	if (to_bulldozer == 0)GroundReady();
	for (size_t i = 0; i < volume; ++i)
	{
		if (to_full[i] > 0)to_full[i]--;
		if (to_full[i] == 0)Complete(i);
		if (to_rest[i] > 0)to_rest[i]--;
		if (to_rest[i] == 0)RestComplete(i);
	}
	cout << qu1 << " " << qLentgh();
	que1_ave = que1_ave*(1 - 1.0 / (total + 1)) + ((float)qLentgh()) / (total + 1);
	ro_fuller = ro_fuller*(1 - 1.0 / (total + 1)) + (((float)Busy()) / volume) / (total + 1);
	if (to_bulldozer > 0)ro_buld++;
}
