#include <iostream>
#include <fstream>	
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 24

using namespace std;
struct tree_elm // Структура элемента бинарного дерева
{
    struct tree_elm* left; //Указатель на левый узел
    int data; //Ключ в узле дерева
    struct tree_elm* right; //Указатель на правый узел
};
tree_elm* create(tree_elm* );
void bypass(tree_elm* );
int search_min(tree_elm* );
tree_elm* search_elem(int , tree_elm* );
tree_elm* add_elem(int , tree_elm* );
void delete_elem(int, tree_elm*);
void printTree(tree_elm*, int);
int main()
{
    setlocale(LC_ALL, "Russian");
    int key, action;
    tree_elm* root = NULL;
    do
    {
        if (root == NULL)
            cout << "Дерево не было создано\n";
        cout << "Выберите действие:\n 1. Создать дерево\n 2. Найти элемент\n 3. Добавить элемент\n 4. Обход\n 5. Найти минимальный элемент\n 6. Удалить элемент из дерева\n 7. Напечатать дерево\n 8. Выход\n";
        cin >> action;
        switch (action)
        {
        case 1:
        {
            root = create(root);
            cout << "Дерево создано\n";
            break;
        }
        case 2:
        {
            if (root == NULL)
                cout << "Дерева не существует\n";
            else
            {
                cout << "Введите элемент, который хотите найти\n";
                cin >> key;
                tree_elm* tmp = search_elem(key, root);
                if (tmp != NULL)
                    cout << "Элемент найден: " << tmp->data << endl;
                else
                    cout << "Элемент не найден\n";
            }
            break;
        }
        case 3:
        {
            cout << "Введите новый элемент\n";
            cin >> key;
            if(root == NULL)
                root = add_elem(key, root);
            else
                add_elem(key, root);
            break;
        }
        case 4:
        {
            if (root == NULL)
                cout << "Дерева не существует\n";
            else
            {
                bypass(root);
                cout << endl;
            }
            break;
        }
        case 5:
        {
            if (root == NULL)
                cout << "Дерева не существует\n";
            else
            {
                key = search_min(root);
                cout << "Минимальный элемент - " << key << endl;
            }
            break;
        }
        case 6:
        {
            if (root == NULL)
                cout << "Дерева не существует\n";
            else
            {
                cout << "Введите элемент, который хотите удалить\n";
                cin >> key;
                delete_elem(key, root);
            }
            break;
        }
        case 7:
        {
            int p = 0;
            printf("\n\n\n\n\n\nДерево:\n");
            printTree(root, p);
            break;
        }
        case 8:
            break;
        default:
            cout << "Вы вввели что-то не то\n";
        }
    } while (action != 8);
}
tree_elm* create(tree_elm* root)
{
    int value;
    ifstream input("input.txt");
    input >> value;
    root = add_elem(value, root);
    for (int i = 0; i < SIZE; i++)
    {
        input >> value;
        add_elem(value, root);
    }
    return root;
}
void bypass(tree_elm* elem)
{
    cout << elem->data << "  ";
    if (elem->left != NULL)
        bypass(elem->left);
    if (elem->right != NULL)
        bypass(elem->right);
}
int search_min(tree_elm* elem)
{
    while (elem->left != NULL)
    {
        elem = elem->left;
    }
    return elem->data;
}
tree_elm* search_elem(int key, tree_elm* root)
{
    while (root->data != key)
    {
        if (key > root->data)
            root = root->right;
        else root = root->left;
        if ((key > root->data&& root->right == NULL) || (key < root->data && root->left == NULL))
            return NULL;
    }
    return root;
}
tree_elm* add_elem(int key, tree_elm* root)
{
    if (root == NULL) { // Если дерева нет, то формируем корень
        root = new tree_elm; // память под узел
        root->data = key;   // поле данных
        root->left = NULL;
        root->right = NULL; // ветви инициализируем пустотой
    }
    else  if (key < root->data)   // условие добавление левого потомка
        root->left = add_elem(key, root->left);
    else
        root->right = add_elem(key, root->right);
    return(root);
}
void delete_elem(int key, tree_elm* root)
{
    tree_elm* tmp;
    while (root->data != key)
    {
        if (key > root->data)
        {
            tmp = root->right; //tmp - узел, который надо удалить
            if (tmp->data == key)
            {
                if (tmp->right != NULL)
                    root->right = tmp->right;
                else if (tmp->left != NULL)
                    root->right = tmp->left;
                else
                    root->right = NULL; //Если лист то удаляем лист
                delete(tmp);
                break;
            }
            else
                root = root->right;

        }
        else
        {
            tmp = root->left;
            if (tmp->data == key)
            {
                if (tmp->right != NULL)
                    root->left = tmp->right;
                else if (tmp->left != NULL)
                    root->left = tmp->left;
                else
                    root->left = NULL;  //Если лист то удаляем лист
                delete(tmp);
                break;
            }
            else
                root = root->left;
        }
        if ((key > root->data && root->right == NULL) || (key < root->data && root->left == NULL))
        {
            cout << "Такого элемента нет\n";
            break;
        }
    }
}
void printTree(tree_elm* elem, int p)
{
    int i;
    if (elem != NULL)
    {
        printTree(elem->right, p + 3);
        for (i = 0; i < p; i++)
        {
            printf(" ");
        }
        printf("%3d\n", elem->data);
        printTree(elem->left, p + 3);
    }
}
