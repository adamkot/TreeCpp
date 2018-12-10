#include <iostream> 
#include <string>
#include <iomanip> 
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
	

public:
	item* root; //korzen drzewa
	void add(int text);
	void del(int text);
	void treeToString(item* root, int indent);
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
				//tu ewentualnie mo¿na dodaæ optymalizacje drzewa
				
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
						if (x->up->left->z == text)
						{
							(x->up)->left = NULL;
						}
						else
						{
							(x->up)->right = NULL;
						}
						x = NULL;
					}
					else if (x->left == NULL && x->right != NULL)
					{
						if (x->up->left->z == text)
						{
							(x->up)->left = x->right;
						}
						else
						{
							(x->up)->right = x->right;
						}
					}
					else if (x->left != NULL && x->right == NULL)
					{
						if (x->up->left->z == text)
						{
							(x->up)->left = x->left;
						}
						else
						{
							(x->up)->right = x->left;
						}
					}
					else if (x->left != NULL && x->right != NULL)
					{
						//przepisac drzewo
					}
					break;
				}
				else
				{
					if (text > x->z)
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

void tree::treeToString(item* root, int indent)
{
	if (!empty) 
	{
		item* x = root;
		if (x->right) {
			treeToString(x->right, indent + 4);
		}
		if (indent) {
			cout << setw(indent) << ' ';
		}
		if (x->right) cout << " /\n" << setw(indent) << ' ';
		cout << x->z << "\n ";
		if (x->left) {
			cout << setw(indent) << ' ' << " \\\n";
			treeToString(x->left, indent + 4);
		}
	}
}

int main()
{
	tree *t = new tree; // nowe drzewo
	t->add(5); //dodaj do drzewa
	t->add(2);
	t->add(6);
	t->add(3);
	t->add(8); 
	t->add(4);
	t->add(9); 
	t->treeToString(t->root, 1); //wypisz drzewo
	cout << "----------------------------------" << endl;
	t->del(9); //usuñ z drzewa
	t->treeToString(t->root, 1);
	getchar();
	return 0;
}
