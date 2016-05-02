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
	//群体初始化
	void init(vector<Individual<numofbit> >);
	//群体评估,并返回最大适应度个体
	Individual<numofbit> evaluate();
	//群体演化
	void evolution();
private:
	FitnessFunc _fitnessFunc;
	vector<Individual<numofbit> > _individuals;
	int _num_of_individuals;
	double _cross_rate;
	double _mutate_rate;
	double _fitness_threshold;
	//根据个体的适应度计算的概率选出n个个体
	vector<Individual<numofbit> > select(int n);
};

template<int numofbit>
Group<numofbit>::Group(FitnessFunc fitnessFunc, double fitness_threshold, int p, double cross_rate, double mutate_rate)
	:_num_of_individuals(p), _cross_rate(cross_rate), _mutate_rate(mutate_rate),_fitness_threshold(fitness_threshold)
{
	/*
	fitnessFunc：适应度评分函数
	fitness_threshold：制定终止判据的阈值
	p：群体中包含的假设数量
	cross_rate：每一步中通过交叉取代群体成员的比例
	mutate_rate：变异率
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
		//计算每个个体的适应度
		double fitness = _fitnessFunc(individual);
		//设定该个体的适应度
		individual.setFitness(fitness);
		if (fitness >= max_fitness_individual.getFitness()) {
			//保存当前最大适应度个体
			max_fitness_individual = individual;
		}
	}
	return max_fitness_individual;
}

template<int numofbit>
vector<Individual<numofbit> > Group<numofbit>::select(int n) 
{
	vector<Individual<numofbit>> selection = vector<Individual<numofbit>>(n);
	//轮盘赌算法，先计算总适应度的大小
	double sum = 0;
	for (Individual<numofbit> individual : _individuals) {
		double fitness = _fitnessFunc(individual);
		sum += fitness;
		individual.setFitness(fitness);
	}

	//轮盘赌算法，计算所有的个体的适应度占总适应度的大小
	double* weights = new double[ _individuals.size() ];
	for (size_t i = 0;i < _individuals.size();i++)
	{
		Individual<numofbit> individual = _individuals[i];
		weights[i] = individual.getFitness() / sum;
	}

	for (int i = 0;i < n;i++) {
		//获得指针的值
		double weight = Individual<numofbit>::getRandomWeight();
		double index = 0;
		for (size_t j = 0;j < _individuals.size();j++)
		{
			if (weight > index && weight <= index + weights[j])
			{
				//指针指向了轮盘上正确的区域
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
	//下一代
	vector<Individual<numofbit> > nextGeneration;

	//选择过程
	int num_of_selection = int(_num_of_individuals * (1 - _cross_rate));
	vector<Individual<numofbit> > selection = select(num_of_selection);

	//将选择结果加入下一代
	nextGeneration.insert(nextGeneration.end(), selection.begin(), selection.end());

	//交叉过程
	int num_of_cross = int(_cross_rate * _num_of_individuals / 2);
	for (int i = 0;i < num_of_cross;i++) {
		vector<Individual<numofbit> > crosspair = select(2);
		Individual<numofbit> father = crosspair[0];
		Individual<numofbit> mother = crosspair[1];
		//基因重组
		father.crossover(mother);
		nextGeneration.emplace_back(father);
		nextGeneration.emplace_back(mother);
	}

	//变异过程
	int num_of_mutate = int(_num_of_individuals * _mutate_rate);
	vector<Individual<numofbit> > mutate_entities = select(num_of_mutate);
	for (Individual<numofbit> individual : mutate_entities)
	{
		individual.mutate();
		nextGeneration.emplace_back(individual);
	}

	//组成下一代
	_individuals = nextGeneration;
}

template<int numofbit>
Group<numofbit>::~Group()
{
}

