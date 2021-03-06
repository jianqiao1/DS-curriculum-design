#include <iostream>
#include <string>
#include <sstream>
#include "CandidateList.h"
#include <vector>
#include <regex>
using namespace std;

bool isPositiveInterger(string s)
{
	//compile a Regex pattern to match the positive intergers
	regex pattern("^(\\+)?(\\d+)$");
	if (regex_match(s, pattern)) {
		return true;
	}
	else
		return false;
}

Candidate IstreamMess(string str)
{
	stringstream ss;
	ss << str;
	vector<string> vect;
	string result;
	while (ss >> result)
	{
		vect.push_back(result);
	}
	string i = vect[0];
	string n = vect[1];
	string g = vect[2];
	int a = stoi(vect[3]);
	string t = vect[4];
	Candidate candi(i, n, g, a, t);
	vect.clear();
	return candi;
}

CandidateList Eastablish()
{
	CandidateList list;
	int loop = 1;
	string n;
	cout << "首先请建立考生信息系统！" << endl;
	while (loop) {
		cout << "请输入考生人数：";
		cin >> n;
		if (isPositiveInterger(n)) {
			loop = 0;
		}
		else
			cout << "人数只能是正整数" << endl << endl;
	}
	int num = stoi(n);
	cout << "请依次输入考生的考号， 姓名， 性别， 年龄及报考类别！" << endl;
	string str;
	getchar();
	for(int i = 0; i < num; i++)
	{
		getline(cin, str);
		Candidate candi = IstreamMess(str);
		list.Insert(candi);
	}
	return list;
}

void SearchOption(CandidateList& list)
{
	cout << "请选择要查找的考生的考号： ";
	string id;
	getchar();
	getline(cin, id);
	if (!list.Exist(id)) {
		cout << "该考生不存在!\n";
	}
	else
	{
		Candidate* candi = list.preSearchById(id);
		candi = candi->next;
		cout << "考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << endl;
		candi->print();
	}
}

void InsertOption(CandidateList& list)
{
	int pos;
	cout << "请选择要插入的考生的位置： ";
	cin >> pos;
	if (pos < 0) {
		cout << "位置必须是正数\n";
	}
	else if (pos > list.getLength()+1 || pos != (int)pos) {
		cout << "位置不符合要求\n";
	}
	else {
		cout << "请依次输入该考生的考号，姓名，性别，年龄以及报考类别！" << endl;
		string mes;
		getchar();
		getline(cin, mes);
		Candidate candi = IstreamMess(mes);
		list.Insert(candi, pos);
	}
}

void DeleteOption(CandidateList& list)
{
	string id;	
	cout << "请选择要删除的考生的考号： ";
	cin >> id;
	if (!list.Exist(id)) {
		cout << "没有该考号考生，无法删除!\n"<<endl;
	}
	else {
		Candidate* candi = list.Delete(id);
		cout << "你删除的考生的考号信息是： ";
		candi->print();
	}
}

void ModifyOption(CandidateList& list)
{
	cout << "请选择要修改的考生的考号： ";
	string id;
	cin >> id;
	if (!list.Exist(id)) {
		cout << "该考号不存在！" << endl;
	}
	else {
		Candidate* candi = list.preSearchById(id);
		candi = candi->next;
		cout << "你要修改的考生的考号信息是： ";
		candi->print();
		cout << "请依次输入新的考号， 姓名， 性别， 年龄及报考类别！" << endl;
		string mes;
		getchar();
		getline(cin, mes);
		Candidate from = IstreamMess(mes);
		candi->id = from.id;
		candi->name = from.name;
		candi->gender = from.gender;
		candi->age = from.age;
		candi->type = from.type;
	}	
}

int main()
{
	CandidateList list = Eastablish();
	list.Traverse();
	int option;
	bool isLoop = 1;
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl << endl;
	while (isLoop)
	{
		cout << "请选择您要进行的操作：";
		cin >> option;
		switch (option)
		{
		case(0):
			cout << "感谢您的使用！";
			isLoop = 0;
			break;
		case(1):
			InsertOption(list);
			list.Traverse();
			break;
		case(2):
			DeleteOption(list);
			list.Traverse();
			break;
		case(3):
			SearchOption(list);
			list.Traverse();
			break;
		case(4):
			ModifyOption(list);
			list.Traverse();
			break;
		case(5):
			list.Traverse();
			break;
		default:
			cout << "输入不符合规范，请重新输入..." << endl << endl;
			break;
		}
	}

}
