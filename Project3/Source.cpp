#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Node
{
	double keyNumber;
	string keyWord;
	vector<double> dataArray;
	Node *left, *right;
};

double defendWriteDouble();
unsigned int defendWriteInt();

vector<string> split(string &s, char delim);

void mainMenu()
{
	cout << "'add'	:" << "add new node." << endl;
	cout << "'show'	:" << "show tree." << endl;
	cout << "'del'	:" << "delete node tree." << endl;
	cout << "'clear'	:" << "delete all node of tree." << endl;
	cout << "'search':" << "search node and show: key numb, key word, data." << endl;
	cout << "'exit'	:" << "close programm." << endl;
}
// Добавляем новую ветвь
void addTree(Node *&Tree, double keyNumb, string keyWord, vector<double> dataArray)
{
	if(NULL == Tree)
	{
		Tree = new Node;
		Tree->keyNumber = keyNumb;
		Tree->keyWord = keyWord;
		Tree->dataArray = dataArray;
		Tree->left = NULL;
		Tree->right = NULL;
	}
	else if(keyNumb < Tree->keyNumber)
	{
		if(Tree->left != NULL) addTree(Tree->left,keyNumb, keyWord, dataArray);
		else
		{
			Tree->left = new Node;
			Tree->left->left = NULL;
			Tree->left->right = NULL;
			Tree->left->keyNumber = keyNumb;
			Tree->left->keyWord = keyWord;
			Tree->left->dataArray = dataArray;
		}
	} else
	{
		if(Tree->right != NULL) addTree(Tree->right, keyNumb, keyWord, dataArray);
		else
		{
			Tree->right = new Node;
			Tree->right->right = NULL;
			Tree->right->left = NULL;
			Tree->right->keyNumber = keyNumb;
			Tree->right->keyWord = keyWord;
			Tree->right->dataArray = dataArray;
		}
	}
}

void showTree(Node *&Tree)
{
	if(Tree != NULL)
	{
		showTree(Tree->left);
		cout << Tree->keyNumber << " ";
		showTree(Tree->right);
	}
}

void searchTree(Node *&Tree, double element)
{
	if(NULL == Tree)
	{
		cout << "WRN: No element in tree.";
		return;
	}
	if (element < Tree->keyNumber)
	{
		searchTree(Tree->left, element);
	}
	else if(element == Tree->keyNumber)
	{
		cout << "	Key numb: " << Tree->keyNumber << endl;
		cout << "	Key word: " << Tree->keyWord << endl;
		for(int i = 0; i<Tree->dataArray.size(); i++)
		{
			cout << "	Data[" << i+1 << "] = " << Tree->dataArray[i] << endl;
		}
		cout << "----------------" << endl;
		if(Tree->right != NULL)
		{
			if(element == Tree->right->keyNumber)
			{
				searchTree(Tree->right, element);
			}
		}
	}
	else if(element > Tree->keyNumber)
	{
		searchTree(Tree->right, element);
	}
}

void delAll(Node *&Tree)
{
	if(Tree != NULL)
	{
		delAll(Tree->left);
		delAll(Tree->right);
		delete Tree;
		Tree = NULL;
	}
}
Node *switchNode(Node *&Tree) // поиск узла для замены удаленного
{
	return NULL;
}

void delElem(Node *&Tree, double keyNumb, string keyWord)
{
	if(NULL == Tree)
	{
		cout << "WRN: no element in tree." << endl;
		return;
	}
	if(Tree->keyNumber == keyNumb)
	{
		if(Tree->keyWord == keyWord)
		{
			//Удаление
		} else
		{
			if(Tree->right != NULL)
			{
				if(Tree->right->keyWord == keyWord)
				{
					delElem(Tree->right, keyNumb, keyWord);
				}
			}
			else
			{
				cout << "WRN: no element in tree." << endl;
			}
		}
	}
	else if(Tree->keyNumber < keyNumb)
	{
		delElem(Tree->left, keyNumb, keyWord);
	}
	else 
	{
		delElem(Tree->right, keyNumb, keyWord);
	}
}

int main()
{
	Node *Tree = NULL;
	while(true){
		mainMenu();
		string command;

		/*----------Работа cmd с разделением на аргументы----------*/
		/*std::vector<std::string> args = {};
		string messages;
		getline(cin, messages);
		transform(messages.begin(), messages.end(), messages.begin(), ::tolower);
		args = split(messages, ' ');
		command = args[0];
		args.erase(args.begin());*/
		// На аргументы разделять покачто не вижу смысла оставлю на потом...

		getline(cin, command);
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		system("cls");
		if (command == "add")
		{
			double keyNumb;
			string keyWord;
			vector<double> dataArray = {};
			unsigned int arrN = 0;  
			cout << "Write key NUMBER for node:";
			keyNumb = defendWriteDouble();
			cout << "Write key WORD for node: ";
			getline(cin, keyWord);
			cout << "	Write DATA massive for node..." << endl;
			cout << "		Numder elements of data: ";
			arrN = defendWriteInt();
			cout << "	Data push:\n";
			for(unsigned int i=0; i<arrN; i++)
			{
				cout << "		" << "Data[" << i << "] = ";
				dataArray.push_back(defendWriteDouble());
			}
			addTree(Tree, keyNumb, keyWord, dataArray);
		} else if (command == "show")
		{
			showTree(Tree);
			cout << endl;
		} else if (command == "search")
		{
			cout << "Write key number for search." << endl;
			double sechElem = defendWriteDouble();
			cout << endl << "Result:" << endl;
			searchTree(Tree, sechElem);
			cout << endl;	
		} else if (command == "exit")
		{
			return 0;
		} else if (command == "clear")
		{
			delAll(Tree);
			cout << "Tree is empty." << endl;
		} else if (command == "del")
		{
			cout << "Write search key word: ";
			double sechElem = defendWriteDouble();
			//getline(cin, command);
		}
		else
		{
			cout << "Wrong command. Try again" << endl;
		}
		
		system("pause");
		system("cls");
	}

	return 1;
}

double defendWriteDouble()
{
	double keyNumb;
	bool eror = true;
	while(eror) // ввод keyNumb
	{
		try
		{
			string str;
			getline(cin, str);
			keyNumb = stod(str);
			eror = false;
		}
		catch(const std::exception& e)
		{
			eror = true;
			std::cerr << e.what() << ". Try again: ";
		}
	}
	return keyNumb;
}
unsigned int defendWriteInt()
{
	unsigned int keyNumb;
	bool eror = true;
	while(eror) // ввод keyNumb
	{
		try
		{
			string str;
			getline(cin, str);
			keyNumb = stoi(str);
			eror = false;
		}
		catch(const std::exception& e)
		{
			eror = true;
			std::cerr << e.what() << ". Try again: ";
		}
	}

	return keyNumb;
}

vector<string> split(string &s, char delim) 
{
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

