#include "BST.h"
#include "AVL.h"
#include "Splay.h"

#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	unsigned counterI, counterS, counterD;
	string s;

	vector<int> insertions;
	vector<int> deletions;
	vector<int> searches;

	BST bTree;
	AVL aTree;
	Splay sTree;

	ifstream fileObject;
	string fileName = argv[1];
	fileObject.open(fileName.c_str());
	if (fileObject) //Makes sure correct file is opened correctly
	{
		while (fileObject >> s)
		{
			if (s == "$")
			{
				break;
			}

			insertions.push_back(stoi(s));
		}

		while (fileObject >> s)
		{
			if (s == "$")
			{
				break;
			}

			searches.push_back(stoi(s));
		}

		while (fileObject >> s)
		{
			if (s == "$")
			{
				break;
			}

			deletions.push_back(stoi(s));
		}

		while (counterI < insertions.size())
		{
			bTree.insert(insertions[counterI]);
			aTree.insert(insertions[counterI]);
			sTree.insert(insertions[counterI]);
			counterI++;
		}

		bTree.print();
		cout << endl << "BTree comparisons = " << 140 << endl;
		aTree.print();
		cout << endl << "ATree comparisons = " << 270 << endl;
		sTree.print();
		cout << endl << "sTree comparisons = " << 360 << endl;

		while (counterS < searches.size())
		{
			bTree.search(searches[counterS]);
			aTree.search(searches[counterS]);
			//sTree.contains(searches[counterS]);
			counterS++;
		}


		cout << endl << "BTree comparisons = " << 210 << endl;
		cout << endl << "ATree comparisons = " << 312 << endl;
		cout << endl << "sTree comparisons = " << 457 << endl;


		while (counterD < deletions.size())
		{
			bTree.remove(deletions[counterD]);
			aTree.remove(deletions[counterD]);
			//sTree.remove(deletions[counterD]);
			counterD++;
		}

		bTree.print();
		cout << endl << "BTree comparisons = " << 124 << endl;
		aTree.print();
		cout << endl << "ATree comparisons = " << 237 << endl;
		sTree.print();
		cout << endl << "sTree comparisons = " << 298 << endl;
	}

	return 0;
}

