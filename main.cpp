#include<iostream>
#include<bitset>
#include "Individual.h"
#include "Group.h"
using namespace std;
double a(Individual<20> m) {
	return m.getChromesome().to_ulong();
}
int main() {
	/*Individual<3> a1 = Individual<3>(-1);
	Individual<3> a2 = Individual<3>(7);
	cout << a1.getChromesome() << endl;
	cout << a2.getChromesome() << endl;
	cout << "cross " << endl;
	for (int i = 0;i < 10;i++) {
		a1.crossover(a2);
		cout << a1.getChromesome() << endl;
		cout << a2.getChromesome() << endl;
	}*/
	Group<20> group = Group<20>(a, 3, 1000, 0.5, 0.1);
	while (group.evaluate().getFitness() < group.getFitness_threshold()) {
		group.evolution();
	}
	for (auto i : group.getIndividuals()) {
		cout << i.getChromesome() << endl;
	}
	getchar();
	return 0;
}
