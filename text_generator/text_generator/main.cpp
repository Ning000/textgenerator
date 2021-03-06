#define N 2
#define MAX 10000
#include<iostream>
#include<string>
#include<deque>
#include<vector>
#include<map>
#include<stdlib.h>
#include<ctime>
#include<sstream>
#include<fstream>
using namespace std;
typedef deque<string> Prefix;
typedef vector<string> Postfix;
typedef map<Prefix, Postfix> mapping_table;
char fake_prefix[] = "\n";
void add_post(Prefix &pre, mapping_table &tab, const string &s)
{	
	if (pre.size() == N)
	{
		tab[pre].push_back(s);
		pre.pop_front();
	}
	pre.push_back(s);
}
void build_samp(Prefix &pre, mapping_table &tab, istream &in)
{
	string cur_word;
	while (in >> cur_word)
	{
		add_post(pre, tab, cur_word);
	}
}
void generate_sentence( mapping_table &tab)
{
	srand(time(NULL));
	Prefix prefix;
	for (int i = 0; i < N; i++)
	{
		add_post(prefix,tab,fake_prefix);
	}
	for (int i = 0; i < MAX; i++)
	{
		Postfix cur_post = tab[prefix];
		const string &w = cur_post[rand() % cur_post.size()];
		if (w == "\n") break;
		cout << w<<" ";
		prefix.pop_front();
		prefix.push_back(w);
	}
	cout << endl;
}
void main()
{
	Prefix pre_;
	mapping_table table_;
	for (int i = 0; i < N; i++)
	{
		add_post(pre_, table_, fake_prefix);
	}
	
	string sample_sentence;
	ifstream fin("sample.txt");
	if (fin)
	{
		getline(fin, sample_sentence);
	}	
	else
	{
		cout << "can't find the file";
	}
	istringstream in(sample_sentence);
	build_samp(pre_, table_, in);
	add_post(pre_, table_, fake_prefix);
	generate_sentence(table_);
	system("pause");
}