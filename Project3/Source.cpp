#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	double keyNumber;
	string keyWord;
	vector<double> dataArray;
	Node *left, *right;
};

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
		getline(cin, command);
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		system("cls");
		bool eror = true;
		if (command == "add")
		{
			double keyNumb;
			string keyWord;
			vector<double> dataArray = {};
			cout << "Write key number for node:";
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
			cout << "Write key word for node: ";
			getline(cin, keyWord);
			cout << "Write data massive for node:" << endl;
			eror = true;
			while(eror)
			{
				try
				{
					unsigned int arrNumb;
					string str;
					cout << "	Numder elements of massive: ";
					getline(cin, str);
					arrNumb = stoi(str);
					for(int i = 0; i<arrNumb; i++)
					{
						double numb;
						bool numbError = true;
						while(numbError)
						{
							try
							{
								cout << "	";
								string tryStrNumb;
								getline(cin, tryStrNumb);
								dataArray.push_back(stod(tryStrNumb));
								numbError = false;
							}
							catch(const std::exception& e)
							{
								std::cerr << e.what() << ". Try again: ";
								numbError = false;
							}
						}
					}
					eror = false;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << ". Try again: ";
					eror = true;
				}
			}
			addTree(Tree, keyNumb, keyWord, dataArray);

		} else if (command == "show")
		{
			showTree(Tree);
			cout << endl;
		} else if (command == "search")
		{
			double sechElem;
			while(eror)
			{
				cout << "Write search key numb: ";
				try
				{
					getline(cin, command);
					sechElem = stod(command);
					eror = false;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << ". Try again: ";
					eror = true;
				}
			}
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
			double sechElem;
			while(eror)
			{
				cout << "Write search key numb: ";
				try
				{
					getline(cin, command);
					sechElem = stod(command);
					eror = false;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << ". Try again: ";
					eror = true;
				}
			}
			cout << "Write search key word: ";
			getline(cin, command);
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


