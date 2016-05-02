#pragma once
#include<vector>
#include"Individual.h"
using namespace std;
template<int numofbit>
class Group
{
public:
	typedef double(*FitnessFunc) (Individual<numofbit>);
	Group(FitnessFunc fitnessFunc, double fitness_threshold, int p, double cross_rate, double mutate_rate);
	~Group();
	vector<Individual<numofbit> > getIndividuals() { return _individuals; }
	double getFitness_threshold() { return _fitness_threshold };
	//Ⱥ���ʼ��
	void init(vector<Individual<numofbit> >);
	//Ⱥ������,�����������Ӧ�ȸ���
	Individual<numofbit> evaluate();
	//Ⱥ���ݻ�
	void evolution();
private:
	FitnessFunc _fitnessFunc;
	vector<Individual<numofbit> > _individuals;
	int _num_of_individuals;
	double _cross_rate;
	double _mutate_rate;
	double _fitness_threshold;
	//���ݸ������Ӧ�ȼ���ĸ���ѡ��n������
	vector<Individual<numofbit> > select(int n);
};

template<int numofbit>
Group<numofbit>::Group(FitnessFunc fitnessFunc, double fitness_threshold, int p, double cross_rate, double mutate_rate)
	:_num_of_individuals(p), _cross_rate(cross_rate), _mutate_rate(mutate_rate),_fitness_threshold(fitness_threshold)
{
	/*
	fitnessFunc����Ӧ�����ֺ���
	fitness_threshold���ƶ���ֹ�оݵ���ֵ
	p��Ⱥ���а����ļ�������
	cross_rate��ÿһ����ͨ������ȡ��Ⱥ���Ա�ı���
	mutate_rate��������
	*/
	_fitnessFunc = fitnessFunc;
	_individuals = vector<Individual<numofbit> >(p);
}

template<int numofbit>
void Group<numofbit>::init(vector<Individual<numofbit> > individuals)
{
	_individuals = individuals;
}

template<int numofbit>
Individual<numofbit> Group<numofbit>::evaluate()
{
	Individual<numofbit> max_fitness_individual = _individuals[0];
	for (Individual<numofbit> individual : _individuals) {
		//����ÿ���������Ӧ��
		double fitness = _fitnessFunc(individual);
		//�趨�ø������Ӧ��
		individual.setFitness(fitness);
		if (fitness >= max_fitness_individual.getFitness()) {
			//���浱ǰ�����Ӧ�ȸ���
			max_fitness_individual = individual;
		}
	}
	return max_fitness_individual;
}

template<int numofbit>
vector<Individual<numofbit> > Group<numofbit>::select(int n) 
{
	vector<Individual<numofbit>> selection = vector<Individual<numofbit>>(n);
	//���̶��㷨���ȼ�������Ӧ�ȵĴ�С
	double sum = 0;
	for (Individual<numofbit> individual : _individuals) {
		double fitness = _fitnessFunc(individual);
		sum += fitness;
		individual.setFitness(fitness);
	}

	//���̶��㷨���������еĸ������Ӧ��ռ����Ӧ�ȵĴ�С
	double* weights = new double[ _individuals.size() ];
	for (size_t i = 0;i < _individuals.size();i++)
	{
		Individual<numofbit> individual = _individuals[i];
		weights[i] = individual.getFitness() / sum;
	}

	for (int i = 0;i < n;i++) {
		//���ָ���ֵ
		double weight = Individual<numofbit>::getRandomWeight();
		double index = 0;
		for (size_t j = 0;j < _individuals.size();j++)
		{
			if (weight > index && weight <= index + weights[j])
			{
				//ָ��ָ������������ȷ������
				selection.emplace_back(_individuals[j]);
				break;
			}
			else 
			{
				index += weights[j];
			}
		}
	}
	return selection;
}

template<int numofbit>
void Group<numofbit>::evolution()
{
	//��һ��
	vector<Individual<numofbit> > nextGeneration;

	//ѡ�����
	int num_of_selection = int(_num_of_individuals * (1 - _cross_rate));
	vector<Individual<numofbit> > selection = select(num_of_selection);

	//��ѡ����������һ��
	nextGeneration.insert(nextGeneration.end(), selection.begin(), selection.end());

	//�������
	int num_of_cross = int(_cross_rate * _num_of_individuals / 2);
	for (int i = 0;i < num_of_cross;i++) {
		vector<Individual<numofbit> > crosspair = select(2);
		Individual<numofbit> father = crosspair[0];
		Individual<numofbit> mother = crosspair[1];
		//��������
		father.crossover(mother);
		nextGeneration.emplace_back(father);
		nextGeneration.emplace_back(mother);
	}

	//�������
	int num_of_mutate = int(_num_of_individuals * _mutate_rate);
	vector<Individual<numofbit> > mutate_entities = select(num_of_mutate);
	for (Individual<numofbit> individual : mutate_entities)
	{
		individual.mutate();
		nextGeneration.emplace_back(individual);
	}

	//�����һ��
	_individuals = nextGeneration;
}

template<int numofbit>
Group<numofbit>::~Group()
{
}

