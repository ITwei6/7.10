#include "test.h"
using namespace std;
#include <iostream>
void test1()
{
	tao::string s1("xiaotao");
	cout << s1.c_str() << endl;
	tao::string s2;
	cout << s2.c_str() << endl;
	for (int i = 0; i < s1.size(); i++)
	{
		s1[i]++;
		cout << s1[i];
	}
	const tao::string s3("taoenwei");
	cout << s3[3] << endl;
	//s3[2] = '1';

	tao::string::iterator it = s1.begin();
	tao::string::const_iterator cit = s3.begin();
	while (cit != s3.end())
	{
	
		cout << (*cit);
		cit++;
	}
	while (it != s1.end())
	{
		cout << (*it);
		it++;
	}

	for (auto ch : s1)//范围for底层其实就是迭代器
	{
		cout << ch << endl;
	}
}
void test2()
{
	tao::string s1("xiao");
	s1.push_back('#');
	cout << s1.c_str() << endl;
	s1.append("ssssssss");
	cout << s1.c_str() << endl;
	
}
void test3()
{
	tao::string s1("helloxiaotao");
	s1.insert(0, 3, '6');
	cout << s1.c_str() << endl;
	s1.insert(0, "nb");
	cout << s1.c_str() << endl;
}
void test4()
{
	tao::string s1("helloxiaotao");
	s1.erase(2, 3);
	cout << s1.c_str() << endl;
	tao::string s2("helloxiaotao");
	s2.erase(1,100);
	cout << s2.c_str() << endl;
	tao::string s3("helloxiaotao");
	s3.erase(2);
	cout << s3.c_str() << endl;
}
void test5()
{
	tao::string s1("helloxiaotao");
	s1.resize(8);

	cout << s1.c_str() << endl;
	
	//cout << s1 << endl;
	
}

int main()
{
	test5();
}