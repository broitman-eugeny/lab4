#pragma once
#include <iostream>
#include <Windows.h>
const int ValChPlacesAmount = 2;//Количество знакомест для отображения одного значения данных на экране
const int OutSpaceChPlacesAmount = 2;//Количество знакомест для разделителя между вершинами нижнего уровня
const int InSpaceChPlacesAmount = 1;//Количество знакомест для разделителя между значениями данных одной вершины
//Шаблон класса дерева двоичного поиска
template <class Type>
class BSTree
{
	//Вложенный класс вершины дерева
	class Node
	{
		//Данные вершины
		Type Data;
		//Указатель на вершину левого поддерева
		Node *Left;
		//Указатель на вершину правого поддерева
		Node *Right;
	public:
		Node(const Type &);
		Node(const Node &);
		Type GetData();//Получение данных в текущей вершине дерева
		void SetData(const Type &);//Запись данных в текущую вершину дерева
		Node * GetLeft();//Получение указателя на вершину левого поддерева текущей вершины дерева
		void SetLeft(Node *);//Запись указателя на вершину левого поддерева в текущую вершину дерева
		Node * GetRight();//Получение указателя на вершину правого поддерева текущей вершины дерева
		void SetRight(Node *);//Запись указателя на вершину правого поддерева в текущую вершину дерева
	};
	//Указатель на корень дерева
	Node *Root;
	//Количество вершин дерева
	int Count;
public:
	//Конструктор по умолчанию
	BSTree();
	~BSTree();//Деструктор
	Node* ClearAll(Node*);//Удаление дерева
	Node * Paste(Node *, const Type &);//Вставка вершины дерева
	Node * Delete(Node *, const Type &);//Удаление вершины дерева
	int GetCount();//Получение количества вершин дерева
	Node *GetRoot();//Получение указателя на корень дерева
	int TreeHeight(Node * LocalRoot);//Вычисляет высоту дерева с учетом веток к нулевым вершинам
	void Show(Node * LocalRoot);//Вывод дерева на экран
	void ShowLevel(Node * LocalRoot, int ReqLevel, int Height, int TempLevel);//Вывод одного уровня дерева на экран
};
//Конструктор с параметром
template<class Type>
BSTree<Type>::Node::Node(const Type &T) : Data(T), Left(NULL), Right(NULL)
{
}
//Конструктор копирования. typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
template<class Type>
BSTree<Type>::Node::Node(const typename BSTree<Type>::Node &T) : Data(T.Data), Left(T.Left), Right(T.Right)
{
}
template<class Type>
Type BSTree<Type>::Node::GetData()
{
	return Data;
}
template<class Type>
void BSTree<Type>::Node::SetData(const Type &T)
{
	Data = T;
}
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Node::GetLeft()//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Left;
}
template<class Type>
void BSTree<Type>::Node::SetLeft(typename BSTree<Type>::Node *T)
{
	Left = T;
}
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Node::GetRight()//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Right;
}
template<class Type>
void BSTree<Type>::Node::SetRight(typename BSTree<Type>::Node *T)
{
	Right = T;
}
//Конструктор по умолчанию
template<class Type>
BSTree<Type>::BSTree() : Root(NULL), Count(0)
{
}
//Деструктор
template<class Type>
BSTree<Type>::~BSTree()
{
	ClearAll(Root);//Удалить все вершины дерева
	std::cout << std::endl << "Осталось " << GetCount() << " вершин" << std::endl;
}
//Удаление всех вершин дерева
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::ClearAll(typename BSTree<Type>::Node *LocalRoot)
{
	if (LocalRoot == NULL)//Дошли до конца ветки
	{
		return NULL;
	}
	BSTree<Type>::Node *LocalLeft, *LocalRight;
	LocalLeft = ClearAll(LocalRoot->GetLeft());//Идем в конец левой ветки
	LocalRight= ClearAll(LocalRoot->GetRight());//Идем в конец правой ветки
	//Дошли до конца обеих веток
	delete LocalRoot;
	Count--;
	return NULL;
}
//Вставка вершины дерева
//Ищет место вставки вершины по критерию упорядоченности (левое поддерево должно иметь значения данных
//строго меньше значения данных родителя, а правое поддерево должно иметь значения данных больше,
//либо равные значению данных родителя), устанавливает ссылки на соответствующие вершины.
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
//T - значение данных вершины
//Возвращает указатель на корень дерева
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Paste(typename BSTree<Type>::Node *LocalRoot, const Type &T)//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	if (Count == 0)//Дерево пустое
	{
		Root = new Node(T);//Создание вершины со значением данных Т и указателями на потомков NULL
		Count = 1;
		return Root;
	}
	else//Дерево не пустое
	{
		if (LocalRoot == NULL)//Текущая вершина пустая
		{
			Count++;
			return new Node(T);//Создание вершины со значением данных Т и указателями на потомков NULL
		}
		else//Текущая вершина занята. Рекурсивно ищем подходящую свободную вершину
		{
			if (LocalRoot->GetData() > T)//Если данные в текущей вершине дерева строго больше вставляемого значения
			{
				//Ищем в левом поддереве подходящую пустую вершину
				LocalRoot->SetLeft(Paste(LocalRoot->GetLeft(), T));
			}
			else
				if(LocalRoot->GetData() < T)//Данные в текущей вершине дерева меньше вставляемого значения
				{
					//Ищем в правом поддереве подходящую пустую вершину
					LocalRoot->SetRight(Paste(LocalRoot->GetRight(), T));
				}
				else//Данные в текущей вершине дерева равны вставляемому значению
				{
					throw std::exception("Данные вершины (ключ) должны быть уникальны!!!");
				}
			return LocalRoot;
		}
	}
}
//Удаление вершины дерева
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
//Del - удаляемое значение данных вершины
//Возвращает указатель на корень дерева
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Delete(typename BSTree<Type>::Node *LocalRoot, const Type &DelData)
{
	if (LocalRoot == NULL)//Дошли до конца ветки
	{
		return NULL;
	}
	else
	{
		Type TData = LocalRoot->GetData();//данные текущей вершины
		typename BSTree<Type>::Node *TLeft= LocalRoot->GetLeft();//указатель на левого потомка
		typename BSTree<Type>::Node *TRight = LocalRoot->GetRight();//указатель на правого потомка
		if (TData > DelData)//Данные вершины больше удаляемого значения
		{
			LocalRoot->SetLeft(Delete(TLeft, DelData));//Уходим влево
		}
		if (TData < DelData)//Данные вершины меньше удаляемого значения
		{
			LocalRoot->SetRight(Delete(TRight, DelData));//Уходим вправо
		}
		if (TData == DelData)//Данные вершины равны удаляемому значению
		{
			Count--;//Уменьшаем счетчик вершин
			if (TLeft == NULL && TRight == NULL)//Дошли до конечной вершины
			{
				if (Root == LocalRoot)//Если удаляем корень дерева
				{
					Root= NULL;
				}
				delete LocalRoot;//Освобождаем  память из-под удаляемой вершины
				return NULL;//Передаем родителю NULL указатель вместо указателя на удаленного потомка
			}
			if (TLeft != NULL && TRight == NULL)//Слева есть потомок, справа - нет
			{
				if (Root == LocalRoot)//Если удаляем корень дерева
				{
					Root = TLeft;
				}
				delete LocalRoot;//Освобождаем  память из-под удаляемой вершины
				return TLeft;//Передаем родителю указатель на левого вместо указателя на удаленного потомка
			}
			if (TLeft == NULL && TRight != NULL)//Справа есть потомок, слева - нет
			{
				if (Root == LocalRoot)//Если удаляем корень дерева
				{
					Root = TRight;
				}
				delete LocalRoot;//Освобождаем  память из-под удаляемой вершины
				return TRight;//Передаем родителю указатель на правого вместо указателя на удаленного потомка
			}
			if (TLeft != NULL && TRight != NULL)//Справа есть потомок, и слева - есть
			{
				Node *T1 = TRight;//Уходим в правое поддерево
				if (T1->GetLeft() != NULL)//Если в правом поддереве есть левый потомок
				{
					Node *T2 = T1->GetLeft();//Уходим в левое поддерево правого поддерева
					while (T2->GetLeft() != NULL)//Спускаемся по левым потомкам правого поддерева до конца ветки
					{
						T1 = T2;
						T2 = T2->GetLeft();
					}
					//T2 - самый левый потомок правого поддерева удаляемой вершины
					//T1 - родитель T2
					T1->SetLeft(NULL);//Убираем левого потомка у T1
					T2->SetLeft(TLeft);//Переназначаем левого потомка удаляемой вершины
					T2->SetRight(TRight);//Переназначаем правого потомка удаляемой вершины
					if (Root == LocalRoot)//Если удаляем корень дерева
					{
						Root = T2;
					}
					delete LocalRoot;//Освобождаем  память из-под удаляемой вершины
					return T2;//Передаем родителю удаленной вершины указатель на самого левого потомка правого поддерева
				}
				else//В правом поддереве нет левого потомка
				{
					T1->SetLeft(TLeft);//Переназначаем левого потомка удаляемой вершины
					if (Root == LocalRoot)//Если удаляем корень дерева
					{
						Root = T1;
					}
					delete LocalRoot;//Освобождаем  память из-под удаляемой вершины
					return T1;//Передаем родителю указатель на правого вместо указателя на удаленного потомка
				}
			}
		}
	}
	return LocalRoot;//Если значения DelData нет в дереве
}
template<class Type>
int BSTree<Type>::GetCount()
{
	return Count;
}
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::GetRoot()
{
	return Root;
}
//Функция вычисляет высоту дерева с учетом веток к нулевым вершинам
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
template<class Type>
int BSTree<Type>::TreeHeight(typename BSTree<Type>::Node * LocalRoot)
{
	if (LocalRoot == NULL)//Дошли до конца ветви
	{
		return 0;
	}
	int LeftHeight, RightHeight;//Высоты поддеревьев
	LeftHeight = TreeHeight(LocalRoot->GetLeft());//Высота левого поддерева
	RightHeight = TreeHeight(LocalRoot->GetRight());//Высота правого поддерева
	return ((LeftHeight>RightHeight) ? LeftHeight : RightHeight) + 1;//Максимальная+1(текущая)
}
//Функция отображает дерево
//LocalRoot - указатель на корень дерева
template<class Type>
void BSTree<Type>::Show(typename BSTree<Type>::Node * LocalRoot)
{
	int Height = TreeHeight(LocalRoot);//Высота дерева с учетом нулевых веток
	printf("\n");
	for (int i = 0; i < Height; i++)
	{
		ShowLevel(LocalRoot, i, Height, 0);//Отображает один уровень дерева
		printf("\n");
	}
}
//Функция отображает один уровень дерева
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
//ReqLevel - номер печатаемого уровня
//Height - высота дерева, включающая ветки к нулевым вершинам
//TempLevel - текущий уровень (для поиска вершин печатаемого уровня)
template<class Type>
void BSTree<Type>::ShowLevel(typename BSTree<Type>::Node * LocalRoot, int ReqLevel, int Height, int TempLevel)
{
	char FormatS[5];
	FormatS[0] = '%';
	FormatS[1] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount / 10 : '0' + ValChPlacesAmount;
	FormatS[2] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount % 10 : 's';
	FormatS[3] = (ValChPlacesAmount>9) ? 's' : '\0';
	FormatS[4] = '\0';
	int Temp1 = OutSpaceChPlacesAmount / 2,//Временная переменная 1
		Temp2 = OutSpaceChPlacesAmount - Temp1,//Временная переменная 2
		SpacesBeforeNode = Temp1,//Количество пробелов, которые нужно напечатать перед вершиной текущего уровня
		SpacesAfterNode = Temp2,//Количество пробелов, которые нужно напечатать после вершины текущего уровня
		W = ValChPlacesAmount;//Количество знакомест, занимаемых одной вершиной дерева
	if (TempLevel < ReqLevel)//Пока не достигли требуемого уровня
	{
		if (LocalRoot != NULL)//Не достигли конца ветви
		{
			ShowLevel(LocalRoot->GetLeft(), ReqLevel, Height, TempLevel + 1);//Переход к следующему уровню в левом поддереве
			ShowLevel(LocalRoot->GetRight(), ReqLevel, Height, TempLevel + 1);//Переход к следующему уровню в правом поддереве
		}
		else//достигли конца ветви. Необходимо напечатать пробелы в запрашиваемом уровне (текстовый курсор находится в запрашиваемом уровне), чтобы восполнить отсутствующие элементы из-за нулевых вершин в текущем уровне и сохранить симметрию дерева
		{
			for (int i = Height - 2; i >= TempLevel; i--)
			{
				Temp1 = SpacesBeforeNode;//Значение со следующего уровня
				Temp2 = SpacesAfterNode;//Значение со следующего уровня
										//Количество пробелов, которые нужно напечатать перед вершиной
				SpacesBeforeNode = 2 * (W + Temp1 + Temp2) / 2 - W / 2;
				//Количество пробелов, которые нужно напечатать после вершины
				SpacesAfterNode = SpacesBeforeNode + W / 2 - (W - W / 2);//Т.к. W м.б. нечетным и W/2 < половины W
			}
			//Печать пробелов перед вершиной
			for (int i = 0; i < SpacesBeforeNode; i++)
			{
				printf(" ");
			}
			printf(FormatS, " ");//Печать пробелов вместо отсутствующих вершин, чтобы сохранить симметрию
								 //Печать пробелов после вершины
			for (int i = 0; i < SpacesAfterNode; i++)
			{
				printf(" ");
			}
		}
	}
	else//Достигли требуемого уровня
	{
		for (int i = Height - 2; i >= TempLevel; i--)
		{
			Temp1 = SpacesBeforeNode;
			Temp2 = SpacesAfterNode;
			//Количество пробелов, которые нужно напечатать перед вершиной
			SpacesBeforeNode = 2 * (W + Temp1 + Temp2) / 2 - W / 2;
			//Количество пробелов, которые нужно напечатать после вершины
			SpacesAfterNode = SpacesBeforeNode + W / 2 - (W - W / 2);//Т.к. W м.б. нечетным и W/2 < половины W
		}
		//Печать пробелов перед вершиной
		for (int i = 0; i < SpacesBeforeNode; i++)
		{
			printf(" ");
		}
		char Format[5];
		Format[0] = '%';
		Format[1] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount / 10 : '0' + ValChPlacesAmount;
		Format[2] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount % 10 : 'd';
		Format[3] = (ValChPlacesAmount>9) ? 'd' : '\0';
		Format[4] = '\0';
		//Печать значений вершины
		if (LocalRoot != NULL)//Вершина имеется (не конец ветви)
		{
			printf(Format, LocalRoot->GetData());
		}
		else//Нулевая вершина (конец ветви)
		{
			printf(FormatS, "*");
		}
		//Печать пробелов после вершины
		for (int i = 0; i < SpacesAfterNode; i++)
		{
			printf(" ");
		}
	}
}
//Функция меню
void Menu();
