#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define NMax 105
using namespace std;
ifstream fin("LFA3.in");
ifstream fin2("LFA3_ex.in");
ofstream fout("LFA3.out");
map<string, vector<char> > Map;
vector<char> V[NMax][NMax];
vector<char> Produs(int x1, int y1, int x2, int y2)
{
	int i, j, k;
	set<char>v;
	vector<char>v2;
	string s1, s2, s;
	char c;
	for (i = 0; i < V[x1][y1].size(); i++)
	{
		for (j = 0; j < V[x2][y2].size(); j++)
		{
			s1 = V[x1][y1][i];
			s2 = V[x2][y2][j];
			s = s1 + s2;
			for (k = 0; k < Map[s].size(); k++)
			{
				c = Map[s][k];
				if (c != 0) v.insert(c);
			}
		}
	}
	for (set<char>::iterator it=v.begin(); it!=v.end(); ++it)
		v2.push_back(*it);
	return v2;
}
vector <char> Reuniune(int x, int y)
{
	int i, j, ct = 0;
	set<char> s;
	vector<char> s2;
	vector<char> c;
	for (i = 1; i < y; i++)
	{
		c = Produs(x, i, x + i, y - i);
		for (j = 0; j < c.size(); j++)
			s.insert(c[j]);
	}
	for (set<char>::iterator it=s.begin(); it!=s.end(); ++it)
		s2.push_back(*it);
	return s2;
}
bool Verificare(string s)
{
	int W, i, j, k;
	string c;
	W = s.size();
	for (i = 1; i <= W; i++)
	{
		c = s[i - 1];

		for (j = 0; j < Map[c].size(); j++)
			V[i][1].push_back(Map[c][j]);
	}
	for (j = 2; j <= W; j++)
		for (i = 1; i <= W - j + 1; i++)
		   V[i][j] = Reuniune(i, j);

	for (k = 0; k < V[1][W].size(); k++)
		if (V[1][W][k] == 'S') return 1;
	return 0;
}
int main()
{
	int N, i, ct = 0;

	char s, c, q[NMax];
	string x;
	while (fin >> s)
	{
		fin >> c >> c >> x;
		for (i = 0; x[i] != 0; i++)
		{
			q[ct] = x[i];
			ct++;
			if (x[i] == '/') {
				q[ct - 1] = 0;
				Map[q].push_back(s);
				ct = 0;
			}
		}
		q[ct] = 0;
		ct = 0;
		Map[q].push_back(s);
	}
	fin2 >> N;
	for (i = 1; i <= N; i++)
	{
		fin2 >> x;
		if (Verificare(x) == 1) fout << "DA\n";
		else fout << "NU\n";

	}
}

