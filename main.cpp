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
//int main() {
//	/*Individual<20> a1 = Individual<20>(-1);
//	Individual<20> a2 = Individual<20>(7);
//	cout << a1.getChromesome() << endl;
//	cout << a2.getChromesome() << endl;
//	cout << "cross " << endl;
//	for (int i = 0;i < 10;i++) {
//		a1.crossover(a2);
//		cout << a1.getChromesome() << endl;
//		cout << a2.getChromesome() << endl;
//	}
//	cout << "mutate " << endl;
//	for (int i = 0;i < 100;i++) {
//		a1.mutate();
//		cout << a1.getChromesome() << endl;
//	}*/
//	/*Group<20> group = Group<20>(func, 0, 1000, 0.8, 0.1);
//	for(int i = 0;i<100;i++){
//		group.evolution();
//		cout << "i " << group.evaluate().getFitness() << endl;
//		cout << group.evaluate().getChromesome() << endl;
//		double x = group.evaluate().getChromesome().to_ulong() / (pow(2.0, 20.0) - 1) * 3;
//		cout << x << endl;
//		cout << sin(x) << endl;
//
//	}*/
//	Group<20> group = Group<20>(func, 0, 50, 0.5, 0.1);
//	for (int i = 0;i<100;i++) {
//		
//		Individual<20> m = group.evaluate();
//		cout << "第"<<i<<"次演化\n" << endl;
//		double x = (double(m.getChromesome().to_ulong()) / (pow(2.0, 20.0) - 1))* 9.0;
//		cout << "最高适应度 ：" << m.getChromesome() << " " << x <<" "<< m.getFitness() << endl;
//		for (auto item : group.getIndividuals())
//		{
//			double x = (double(item.getChromesome().to_ulong()) / (pow(2.0, 20.0) - 1))* 9.0;
//			cout << item.getChromesome() << " " << x <<" "<< item.getFitness() << endl;
//		}
//		group.evolution();
//		
//	}
//	cout << (pow(2.0, 20.0) - 1.0);
//	getchar();
//	return 0;
//}
class A {
public:
	A(int a) { cout << "A ctor!" << endl; }
	A() { cout << "A default ctor!" << endl; }
	~A() { cout << "A dtor!" << endl; }
};
class B :public A{
public:
	B(int a, int b) { cout << "B ctor!" << endl; }
	B() : m(0) { cout << "B default ctor!" << endl; }
	~B() { cout << "B dtor!" << endl; }
private:
	A m;
};
class C : public B {
public:
	C(int a=0, int=0){ cout << "C ctor!" << endl; }
	C(){ cout << "C default ctor!" << endl; }
	~C() { cout << "C dtor!" << endl; }
private:
	A m;
};
int main()
{
	{
		//构造函数调用顺序是：基类 -> 派生类,析构函数反过来
		//对于每一个对象里，初始化顺序是成员变量 > 类构造，
		//对于初始化列表中的对象，初始化顺序跟声明顺序有关
		C obj();
		int a();
	}
	pow(2.0, 3.0);
	//C obj;
	getchar();
	return 0;
}

class Polynomial {
public:
	friend Polynomial& operator+(Polynomial& ,Polynomial& );
	friend Polynomial& operator-(Polynomial& ,Polynomial& );
	Polynomial(double a, double b, double c)
	:_a(a),_b(b),_c(c){
	}
	double getResult(double x) {
		return _a * x * x + _b* x + _c;
	}
	double getRoot1() {
		return -_b + sqrt(_b* _b - 4 * _a * _c);
	}
	double getRoot2() {
		return -_b - sqrt(_b* _b - 4 * _a * _c);
	}
private:
	double _a;
	double _b;
	double _c;
};

Polynomial& operator+(Polynomial& self,Polynomial& arg)
{
	double a = self._a + arg._a;
	double b = self._b + arg._b;
	double c = self._c + arg._c;
	return Polynomial(a, b, c);
	

}
Polynomial& operator-(Polynomial& self,Polynomial& arg)
{
	double a = self._a - arg._a;
	double b = self._b - arg._b;
	double c = self._c - arg._c;
	return Polynomial(a, b, c);
}



