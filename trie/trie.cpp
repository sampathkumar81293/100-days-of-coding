#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

 struct Node {
	bool isend;
	int prefixes;
	map <char, Node*> child;
	Node()
	{
		prefixes = 0;
		isend = false;
	}
 };

 void insert(Node *root, string word)
 {
	 Node *cur = root;
	 for (int i = 0; i < word.length(); i++)
	 {
		 char ch = word[i];
		 Node *tmp = cur->child[ch];
		 if (tmp == NULL)
		 {
			 tmp = new Node();
			 cur->child[ch] = tmp;
		 }
		 cur = tmp;
		 cur->prefixes += 1;
	 }
	 cur->isend = true;
 }


 bool search(Node *root, string word)
 {
	 Node *cur = root;
	 for (int i = 0; i < word.length(); i++)
	 {
		 char ch = word[i];
		 Node *tmp = cur->child[ch];
		 if (tmp == NULL)
		 {
			 return false;
		 }
		 cur = tmp;
	 }
	 return cur->isend;
 }

 int no_of_prefixes(Node * root, string word)
 {
	 Node *cur = root;
	 for (int i = 0; i < word.length(); i++)
	 {
		 char ch = word[i];
		 Node *tmp = cur->child[ch];
		 if (tmp == NULL)
		 {
			 return 0;
		 }
		 cur = tmp;
	 }
	 return cur->prefixes;
 }

 int main()
 {
	 Node *root = new Node();
	 insert(root, "sampath");
	 insert(root, "samantha");
	 insert(root, "samosa");
	 string p;
	 cin >> p;
	 cout << search(root, p)  << no_of_prefixes(root, p) << endl;
	 return 0;
 }
