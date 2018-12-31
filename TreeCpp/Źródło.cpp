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
		int z; //przechowywana warto��
		item* left = NULL; //lewe dziecko
		item* right = NULL; //prawe dziecko
		item* up = NULL; //rodzic
	};
	

public:
	item* root; //korzen drzewa
	void add(int text);
	void del(int text);
	void treeToString(item* root, int indent);
};

/*
Dodawanie do drzewa
*/
void  tree::add(int text)
{
	//je�li lista jest pusta tworzy now� list�
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
	//je�li lista nie jest pusta
	else
	{
		//nowy li��
		item* i = new item;
		i->z = text;
		i->left = NULL;
		i->right = NULL;

		//przeszukiwanie drzewa w poszukiwaniu miejsca na nowy li��
		//zaczynam od korzenia root
		for (item* x = root; x != NULL;)
		{
			//ga��� nie ma li�ci
			if (x->left == NULL && x->right == NULL)
			{
				//je�li warto�� do dodania jest mniejsza ni� rodzic to na lewo
				if (text < x->z)
				{
					x->left = i;
				}
				//je�li warto�� do dodania jest wi�ksza ni� rodzic to na prawo
				else
				{
					x->right = i;
				}
				//zapisanie rodzica
				i->up = x;
				break;
			} 
			//ga��� ma tylko jeden li�� z prawej strony
			else if (x->left == NULL && x->right != NULL)
			{
				//sprawd� czy warto�� po prawej jest mniejsza
				//je�li tak to dodaj zamie� miejscami i dodaj now�
				if (x->right->z < i->z)
				{
					x->left = x->right;
					x->right = i;
				}
				//je�li warto�� jest wi�ksza to zapisuj z lewej
				else 
				{
					x->left = i;
				}
				//zapisanie rodzica
				i->up = x;
				break;
			}
			//ga��� ma tylko jeden li�� z lewej strony
			//odwrotnie ni� w warunku powy�ej
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
			//ga��� ma dwa li�cie wi�c musz� i�� do kolejnej ga��zi
			else if (x->left != NULL && x->right != NULL)
			{
				//tu ewentualnie mo�na doda� optymalizacje drzewa
				
				//zasada wyboru kierunku drogi po ga��ziach
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
/*
Usuwanie z drzewa
*/
void tree::del(int text)
{
	//usuwam je�li drzewo nie jest puste
	if (!empty)
	{
		//je�li w drzewie jest tylko jeden element
		if (root->left == NULL && root->right == NULL)
		{
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
			//przeszukiwanie drzewa w poszukiwaniu elementu do uzuni�cia
			for (item* x = root; x != NULL;)
			{
				//je�li trafili�my na element
				if (x->z == text)
				{
					//je�li to li�� to usuwam go wraz z odwo�aniami do niego z rodzica (x->up)
					if (x->left == NULL && x->right == NULL)
					{
						//sprawdzam czy dla rodzica znaleziony element jest lewym czy prawym dzieckiem
						if ((x->up)->left->z == text)
						{
							(x->up)->left = NULL;
						}
						else
						{
							(x->up)->right = NULL;
						}
						x = NULL;
					}
					//je�li element to ga��� z jednym li�ciem to usuwam i przesuwam li�� wy�ej
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
					//je�li element to ga��� z jednym li�ciem to usuwam i przesuwam li�� wy�ej
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
					//element to ga��� o dw�ch dzieciach
					else if (x->left != NULL && x->right != NULL)
					{
						//je�li element nie jest korzeniem
						if (x->up != NULL)
						{
							//je�li dla rodzica jest z lewej strony
							if ((x->up)->left->z == text)
							{
								item* i = x->right;
								item* j = x->left;
								//dziecko z lewej przypisz wy�ej
								(x->up)->left = x->left;
								free(x);
								//szukamy gdzie dopisa� dzieci z prawej od usuni�tego elementu
								while (j != NULL)
								{
									if (i->z > j->z)
									{
										if (j->right != NULL)
										{
											j = j->right;
										}
										else
										{
											j->right = i;
											break;
										}
									}
									else
									{
										if (j->left != NULL)
										{
											j = j->left;
										}
										else
										{
											j->left = i;
											break;
										}
									}
								}
							}
							else
							{
								item* i = x->left;
								item* j = x->right;
								//dziecko z prawej przypisz wy�ej
								(x->up)->right = x->right;
								free(x);
								//szukamy gdzie dopisa� dzieci z lewej od usuni�tego elementu
								while (j != NULL)
								{
									if (i->z > j->z)
									{
										if (j->right != NULL)
										{
											j = j->right;
										}
										else
										{
											j->right = i;
											break;
										}
									}
									else
									{
										if (j->left != NULL)
										{
											j = j->left;
										}
										else
										{
											j->left = i;
											break;
										}
									}
								}
							}
						}
						//je�li element jest korzeniem
						else
						{
							root = x->left;
							item* i = x->right;
							item* j = new item;
							j = root;
							while (j != NULL)
							{
								if (i->z > j->z)
								{
									if (j->right != NULL)
									{
										j = j->right;
									}
									else
									{
										j->right = i;
										break;
									}
								}
								else
								{
									if (j->left != NULL)
									{
										j = j->left;
									}
									else
									{
										j->left = i;
										break;
									}
								}
							}
						}
						
					}
					break;
				}
				//je�li nie trafili�my to szukamy dalej
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
/*
Drukowanie drzewa na ekranie od lewej do prawej, korze� na pocz�tku i na �rodku ekranu
*/
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
	cout << "Podaj pierwsza wartosc: " << endl;
	tree *t = new tree; // nowe drzewo
	int x;
	cin >> x;
	t->add(x);
	while (true)
	{
		cout << endl;
		cout << "1. Dodaj do drzewa" << endl;
		cout << "2. Usun z drzewa" << endl;
		cout << "3. Wyjscie" << endl;
		cin >> x;
		int wartosc;
		switch (x)
		{
		case(1):
			cout << "Podaj wartosc: ";
			cin >> wartosc;
			t->add(wartosc);
			t->treeToString(t->root, 1);
			break;
		case(2):
			cout << "Podaj wartosc: ";
			cin >> wartosc;
			t->del(wartosc);
			t->treeToString(t->root, 1);
			break;
		case(3):
			return 0;
		}
	}

}
