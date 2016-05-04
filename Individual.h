#pragma once
#include<iostream>
#include<bitset>
#include<windows.h>
#include<cmath>
using namespace std;

template<int numofbit>
class Individual
{
public:
	//��ȡ�����bit
	static unsigned getRandomBit();
	static double getRandomWeight();
	static unsigned getRandomNum(int);
	//��ȡ�����Ⱦɫ��
	bitset<numofbit> getRandomChromosome();
	//Ĭ�Ϲ��캯�������������Ⱦɫ������Ⱦɫ��
	Individual();
	//���ݴ���ֵ����Ⱦɫ��
	Individual(int);
	//�������캯��
	Individual(const Individual&);
	//���ض�������л��򽻲�
	void crossover(Individual<numofbit>& ,int=1);
	//����
	void mutate(int=1);
	double getFitness() { return _fitness; }
	void setFitness(double fitness) { _fitness = fitness; }
	~Individual();
	bitset<numofbit> getChromesome();
private:
	bitset<numofbit> _chromosome;
	//������Ӧ��
	double _fitness;
};
template<int numofbit>
unsigned Individual<numofbit>::getRandomBit()
{
	return Individual<numofbit>::getRandomNum(2);
}

template<int numofbit>
double Individual<numofbit>::getRandomWeight()
{
	return Individual<numofbit>::getRandomNum(10000000)/10000000;
}

template<int numofbit>
unsigned Individual<numofbit>::getRandomNum(int x)
{
	//���ø߾���ʱ���ȡ�����
	LARGE_INTEGER nFrequency;
	if (::QueryPerformanceFrequency(&nFrequency))

	{

		LARGE_INTEGER nStartCounter;
		
		::QueryPerformanceCounter(&nStartCounter);

		::srand((unsigned)nStartCounter.LowPart);

	}
	return double(rand())/RAND_MAX * x;
}


template<int numofbit>
bitset<numofbit> Individual<numofbit>::getRandomChromosome()
{

	double max = pow(2, numofbit) -1;
	bitset<numofbit> randomChromosome;
	double randnum = getRandomNum(max);
	randomChromosome = bitset<numofbit>(randnum);
	return randomChromosome;
}



template<int numofbit>
bitset<numofbit> Individual<numofbit>::getChromesome()
{
	return _chromosome;
}

template<int numofbit>
Individual<numofbit>::Individual()
{
	_chromosome = Individual::getRandomChromosome();
	_fitness = 0;
}

template<int numofbit>
Individual<numofbit>::Individual(int val)
{
	_chromosome = bitset<numofbit>(val);
	_fitness = 0;
}

template<int numofbit>
Individual<numofbit>::Individual(const Individual& copy)
{
	_chromosome = copy._chromosome;
	_fitness = copy._fitness;
}
template<int numofbit>
void Individual<numofbit>::crossover(Individual<numofbit>& mate, int numOfTagBit) {
	for (int i = 0;i < numOfTagBit;i++) {
		int index = getRandomNum(numofbit);
		bool bit1 = getChromesome()[index];
		bool bit2 = mate.getChromesome()[index];
		_chromosome[index] = bit2;
		mate._chromosome[index] = bit1;
	}
}

template<int numofbit>
void Individual<numofbit>::mutate(int numOfTagBit) {
	for (int i = 0;i < numOfTagBit;i++) {
		int index = getRandomNum(numofbit);
		//cout << numofbit << "  rand  " << index << endl;
		_chromosome[index] = !_chromosome[index];
	}
}

template<int numofbit>
Individual<numofbit>::~Individual()
{

}
