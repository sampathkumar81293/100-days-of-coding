#include <iostream>
#include <string>
#include <vector>
using namespace std;

int preprocess(string &p, vector <int> &a)
{
	for (int i = 1, k=0; i < p.length(); i++)
	{
		while (k && p[k] != p[i]) k = a[k-1];
		if (p[k] == p[i]) k++;
		a[i] = k;
	}
}

int kmp(string &t, string &p)
{
	if (p.empty()) return 0;
	vector <int> prep(p.length() , 0);
	preprocess(p, prep);
	for (int i = 0, k = 0; i < t.length(); i++)
	{
		while (k && p[k] != t[i])k = prep[k - 1];
		if (p[k] == t[i])k++;
		if (k == p.length()) return i - k + 1;
	}
	return -1;
}
int main(int argc , char *argv[])
{
	string text, pat;
	if (argc < 3)
	{
		text = "sampathsamanthasathvik";
		pat = "sam";
	}
	else
	{
		text = string(argv[1]);
		pat = string(argv[2]);
	}
	cout << "text: " << text<< endl;
	cout << "pattern: " << pat << endl;
	cout << "index: " << kmp(text, pat) << endl;

	return 0;
}