
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>
#include <thread>
#include <mutex>



using namespace std;

typedef unordered_map< string, int > wordcount;
typedef unordered_map< string, unordered_set<string> > wordfile;
typedef unordered_map <string, wordcount > filewordcount;


static const int numthreads = 10;
mutex mtx;
/*
* Helper function for individual word vector of every file
*/

void processwords(ifstream &in_fs, wordcount &wordic)
{
	string token;
	while (in_fs.good())
	{
		in_fs >> token;
		if (in_fs.fail())break;
		auto it = wordic.find(token);
		if (it == wordic.end())
		{
			wordic[token] = 0;
		}
		wordic[token]++;
	}
}



/*
* This function creates individual word vector of every file
*/

int processfile(string filename, wordcount &wordic)
{
	ifstream finstream(filename);

	if (finstream.is_open() && !finstream.eof())
	{
		processwords(finstream, wordic);
		//cout << "\n Successfully processed file: " << filename << endl;
	}
	else
	{
		cerr << "\nPlease check your argument file.\nCannot open file: " << filename << endl;
		return -1;
	}

	return 0;

}

/*
* This function Aggregates the information after individual files are processed
*/

void createwordmap(filewordcount &mp, wordfile &wordmap, wordcount &wordcount)
{
	for (auto it : mp)
	{
		for (auto lit : it.second)
		{
			auto rit = wordmap.find(lit.first);
			//cout << lit.first << endl;
			wordmap[lit.first].insert(it.first);
			wordcount[lit.first] += lit.second;
		}
	}
}

/*
* Bonus implementation : This function prints additional details about each word in the list
*/

void tokeninfo(string token, wordfile &wordmap, wordcount &wordcount, filewordcount &filedic)
{
	auto it = wordmap.find(token);
	if (it != wordmap.end())
	{
		cout << "**************************************************" << endl;
		cout << "Selected word: " << it->first << endl;
		for (auto lit : it->second)
		{
			cout << "\n" << lit << "\tCount: " << (filedic[lit])[token];
		}
		cout << endl;
		cout << "Total word count:" << wordcount[token] << endl;
	}
	else
	{
		cerr << "Couldn't find this token :" << token << endl;
	}

}

void printwordmap(wordfile &wordmap)
{
	for (auto it : wordmap)
	{
		cout << it.first << endl;
		for (auto lit : it.second)
		{
			cout << "\t" << lit;
		}
		cout << endl;
	}
}

void printwordcount(wordcount &wordcount)
{
	ofstream ofs("result.txt");
	for (auto it : wordcount)
	{
		ofs << it.first << "\t\t" << it.second << endl;
	}
	ofs.close();
}


/*
* This function creates a vector of filespaths from the input command line file argument
*/

int getinputpaths(string filename, vector <string> &filvec)
{
	ifstream in_fs(filename);
	string token;
	if (in_fs.is_open())
	{
		while (!in_fs.eof())
		{
			in_fs >> token;
			if (in_fs.fail()) break;
			filvec.push_back(token);
		}
		//cout << "\n Successfully processed file: " << filename << endl;
	}
	else
	{
		cerr << "\nPlease check your argument file.\nCannot open file: " << filename << endl;
		return -1;
	}
	in_fs.close();
	return 0;
}






void threadfunction(int threadnum, int start, int end, filewordcount &filedic, vector<string> &fname)
{
	//cout << "Entered in thread: " << threadnum << endl;

	for (int i = start; i < end; i++) {
		wordcount wordic;
		int ret = processfile(fname[i], wordic);
		if (ret == 0) {
			auto it = filedic.find(fname[i]);
			if (it == filedic.end())
			{
				mtx.lock();
				filedic[fname[i]] = wordic;
				mtx.unlock();
			}
			else
			{
				cout << "Repeated/Duplicate file entry : " << fname[i] << endl;
			}
		}
		else cout << "\tContinuing with other files: " << threadnum << "\n\n" << endl;
	}
	//cout << "Finished thread: " << threadnum << endl;
}




int solver(int argc, const char *argv[])
{

	/*for (int i = 1; i < argc; i++)
	{
		printf("\nArg: %d --> %s", i, argv[i]);
	}*/

	cout << "**************************************************" << endl;
	if (argc < 2)
	{
		cerr << "Please try ./wordvec inp.txt" << endl;
		exit(0);
	}
	string input_filename(argv[1]);
	filewordcount filedic;
	wordfile wordmap;
	wordcount wordcount;
	vector<string> fname;
	string token;
	int ret = 0;
	ret = getinputpaths(input_filename, fname);
	if (ret == -1)
	{
		cerr << "Problem with the input filepath" << endl;
		exit(0);
	}
	ret = 0;
	/*
	fname[0] = "/gpfs/home/ksampathkuma/sampath/test.txt";
	fname[1] = "/gpfs/home/ksampathkuma/sampath/test1.txt";
	*/

	if (numthreads < 1)
	{
		cerr << "number of threads cannot be less than 1 " << endl;

		cout << "\n**************************************************" << endl;

		exit(0);
	}
	int blocksize = fname.size() / numthreads; // 2/3
	vector <thread> threads;


	if (blocksize > 0) {
		for (int i = 0; i < numthreads - 1; i++)
		{
			threads.push_back(thread(threadfunction, i, i*blocksize, (i + 1)*blocksize, ref(filedic), ref(fname)));
		}
		threads.push_back(thread(threadfunction, numthreads - 1, (numthreads - 1)*blocksize, fname.size(), ref(filedic), ref(fname)));
	}
	else
	{
		for (int i = 0; i < fname.size(); i++)
		{
			threads.push_back(thread(threadfunction, i, i, i + 1, ref(filedic), ref(fname)));
		}
	}



	//cout << "Syncing threads" << endl;
	for (auto& th : threads)
	{
		th.join();
	}

	createwordmap(filedic, wordmap, wordcount);

	//printwordmap(wordmap);
	cout << "**************************************************" << endl;
	cout << "\nOutput written to result.txt file\n" << endl;
	cout << "**************************************************" << endl;
	printwordcount(wordcount);

	while (1) {
		cout << "\nBonus component\n Select a word of your choice from the list(from result.txt): " << endl;
		cin >> token;
		if (token.find("exit()") != string::npos) { break; }
		tokeninfo(token, wordmap, wordcount, filedic);
	}
	cout << "Exiting" << endl;

	return 0;

}
