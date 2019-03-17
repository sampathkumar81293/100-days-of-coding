
#include "wordvec.h"
#include <assert.h>


void test1()
{
	string input_filename("unit_test_input.txt");
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

	assert(fname[0].compare("/gpfs/home/ksampathkuma/sampath/files/unit1.txt") == 0);
	assert(fname[1].compare("/gpfs/home/ksampathkuma/sampath/files/unit2.txt") == 0);

	cout << "**************************************************" << endl;
	cout << "getinputpaths() Test passed" << endl;
	cout << "**************************************************" << endl;


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

	assert((threads.size() == 2));

	cout << "Number of threads Test passed" << endl;
	cout << "**************************************************" << endl;
	//cout << "Syncing threads" << endl;
	for (auto& th : threads)
	{
		th.join();
	}

	createwordmap(filedic, wordmap, wordcount);
	assert(wordcount["sampath"] == 3);
	assert(wordcount["sam"] == 3);
	assert(wordcount["path"] == 3);
	assert(wordcount["premsai"] == 3);
	assert(wordcount["prem"] == 3);
	assert(wordcount["sai"] == 3);

	cout << "Word count Integrity Test passed" << endl;
	cout << "**************************************************" << endl;



}
int main()
{
	test1();
return 0;

}
