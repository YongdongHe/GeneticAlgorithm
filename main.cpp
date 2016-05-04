#include<iostream>
#include<bitset>
#include "Individual.h"
#include "Group.h"
#include <cmath>
using namespace std;
double func(Individual<20> m) {
	double x = (double(m.getChromesome().to_ulong()) / (pow(2.0,20.0)-1) )* 9.0;
	return x + 10 * sin(5 * x) + 7 * cos(4 * x);
}
double func2(Individual<8> m) {
	return m.getChromesome().to_ulong();
}
int main() {
	/*Individual<20> a1 = Individual<20>(-1);
	Individual<20> a2 = Individual<20>(7);
	cout << a1.getChromesome() << endl;
	cout << a2.getChromesome() << endl;
	cout << "cross " << endl;
	for (int i = 0;i < 10;i++) {
		a1.crossover(a2);
		cout << a1.getChromesome() << endl;
		cout << a2.getChromesome() << endl;
	}
	cout << "mutate " << endl;
	for (int i = 0;i < 100;i++) {
		a1.mutate();
		cout << a1.getChromesome() << endl;
	}*/
	/*Group<20> group = Group<20>(func, 0, 1000, 0.8, 0.1);
	for(int i = 0;i<100;i++){
		group.evolution();
		cout << "i " << group.evaluate().getFitness() << endl;
		cout << group.evaluate().getChromesome() << endl;
		double x = group.evaluate().getChromesome().to_ulong() / (pow(2.0, 20.0) - 1) * 3;
		cout << x << endl;
		cout << sin(x) << endl;

	}*/
	Group<20> group = Group<20>(func, 0, 100, 0.8, 0.1);
	for (int i = 0;i<100;i++) {
		
		Individual<20> m = group.evaluate();
		cout << "第"<<i<<"次演化\n" << endl;
		double x = (double(m.getChromesome().to_ulong()) / (pow(2.0, 20.0) - 1))* 9.0;
		cout << "最高适应度 ：" << m.getChromesome() << " " << x <<" "<< m.getFitness() << endl;
		/*for (auto item : group.getIndividuals())
		{
			double x = (double(item.getChromesome().to_ulong()) / (pow(2.0, 20.0) - 1))* 9.0;
			cout << item.getChromesome() << " " << x <<" "<< item.getFitness() << endl;
		}*/
		group.evolution();
		
	}
	cout << (pow(2.0, 20.0) - 1.0);
	getchar();
	return 0;
}
