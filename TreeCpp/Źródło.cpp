#include <iostream> 
#include <string>
using namespace std;

class tree
{
private:
	bool empty = true; //czy drzewo jest puste
	//do przechowywania "obiektu" w drzewie. Przechowuje string i wskazania na lewy i prawy obiekt oraz wskazanie na rodzica
	struct item
	{
		int z;
		item* left = NULL;
		item* right = NULL;
		item* up = NULL;
	};
	item* root; //korzen drzewa

public:
	//void search() //znajdz
	void add(int text);
	void del(int text);
	string treeToString();
};

//dodawanie do listy (na koñcu)
void  tree::add(int text)
{
	if (empty)
	{
		item* i = new item;
		i->z = text;
		i->left = NULL;
		i->right = NULL;
		i->up = NULL;
		root = i;
		empty = false;
	}
	else
	{
		item* i = new item;
		i->z = text;
		i->left = NULL;
		i->right = NULL;

		for (item* x = root; x != NULL;)
		{
			if (x->left == NULL && x->right == NULL)
			{
				if (text < x->z)
				{
					x->left = i;
				}
				else
				{
					x->right = i;
				}
				i->up = x;
				break;
			} 
			else if (x->left == NULL && x->right != NULL)
			{
				if (x->right->z < i->z)
				{
					x->left = x->right;
					x->right = i;
				}
				else 
				{
					x->left = i;
				}
				i->up = x;
				break;
			}
			else if (x->left != NULL && x->right == NULL)
			{
				if (x->left->z > i->z)
				{
					x->right = x->left;
					x->left = i;
				}
				else
				{
					x->right = i;
				}
				i->up = x;
				break;
			}
			else if (x->left != NULL && x->right != NULL)
			{
				//dodaæ optymalizacje drzewa
				
				if ((abs(x->left->z - text)) > (abs(x->right->z - text)))
				{
					x = x->right;
				}
				else
				{
					x = x->left;
				}
			}
		}
	}
}

void tree::del(int text)
{
	if (!empty)
	{
		if (root->left == NULL && root->right == NULL)
		{
			//jedyny
			if (text == root->z)
			{
				root = NULL;
				empty = true;
			}
			else
			{
				cout << "brak elementu w drzewie" << endl;
			}
		}
		else 
		{
			for (item* x = root; x != NULL;)
			{
				if (x->z == text)
				{
					if (x->left == NULL && x->right == NULL)
					{
						x = NULL;
					}
					else if (x->left == NULL && x->right != NULL)
					{
						x = x->right;
					}
					else if (x->left != NULL && x->right == NULL)
					{
						x = x->left;
					}
					else if (x->left != NULL && x->right != NULL)
					{
						//tego jeszcze nie wiem
					}
					break;
				}
				else
				{
					if ((abs(x->left->z - text)) > (abs(x->right->z - text)))
					{
						x = x->right;
					}
					else
					{
						x = x->left;
					}
				}
			}
		}
	}
	else
	{
		cout << "drzewo jest puste" << endl;
	}
}

string tree::treeToString()
{
	string treeText = "";
	if (!empty)
	{
		treeText = root->z + " \n";
		item* x = root->left;
		item* y = root->right;
		
		// do zrobienia
	}
	return treeText;
}

int main()
{
	tree *t = new tree; // nowa drzewo
	t->add(0); //dodaj do drzewa
	t->add(1); //dodaj do drzewe kolejny
	t->add(2); //dodaj do drzewa kolejny
	t->add(3); //dodaj do drzewa kolejny
	t->add(4); //dodaj do drzewe kolejny
	t->add(5); //dodaj do drzewa kolejny
	t->add(6); //dodaj do drzewa kolejny
	cout << t->treeToString() << endl; //wypisz drzewo
	//t->del("test_1");
	//cout << t->treeToString() << endl; //wypisz drzewo
	getchar();
	return 0;
}
