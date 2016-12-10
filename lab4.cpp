#include "lab4.h"
//Конструктор с параметром
template<class Type, int Size>
BSTree<Type, Size>::Node::Node(const Type &T) : Data(T), Left(NULL), Right(NULL)
{
}
//Конструктор копирования. typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
template<class Type, int Size>
BSTree<Type, Size>::Node::Node(const typename BSTree<Type, Size>::Node &T): Data(T.Data), Left(T.Left), Right(T.Right)
{
}
template<class Type, int Size>
Type BSTree<Type, Size>::Node::GetData()
{
	return Data;
}
template<class Type, int Size>
void BSTree<Type, Size>::Node::SetData(const Type &T)
{
	Data = T;
}
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Node::GetLeft()//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Left;
}
template<class Type, int Size>
void BSTree<Type, Size>::Node::SetLeft(typename BSTree<Type, Size>::Node *T)
{
	Left = T;
}
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Node::GetRight()//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Right;
}
template<class Type, int Size>
void BSTree<Type, Size>::Node::SetRight(typename BSTree<Type, Size>::Node *T)
{
	Right = T;
}
//Конструктор по умолчанию
template<class Type, int Size>
BSTree<Type, Size>::BSTree(): Root(NULL), Count(0)
{
}
//Вставка вершины дерева
//Если есть место в массиве Arr - записывает данные в первый свободный элемент массива Arr,
//ищет место вставки вершины по критерию упорядоченности (левое поддерево должно иметь значения данных
//строго меньше значения данных родителя, а правое поддерево должно иметь значения данных больше,
//либо равные значению данных родителя), устанавливает ссылки на соответствующие вершины.
//Если массив Arr заполнен - выбрасывает исключение.
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
//T - значение данных вершины
//Возвращает указатель на корень дерева
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Paste(typename BSTree<Type, Size>::Node *LocalRoot, const Type &T)//typename необходимо (см. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	if (Count == 0)//Дерево пустое
	{
		Arr[0].SetData(T);
		Arr[0].SetLeft(NULL);
		Arr[0].SetRight(NULL);
		Root = &(Arr[0]);
		Count = 1;
		return Root;
	}
	else//Дерево не пустое
	{
		if (Count < Size)//Еще есть место в массиве
		{
			Arr[Count].SetData(T);//Поместить T в первый свободный элемент массива Arr
			//Обнулить указатели на потомков
			Arr[Count].SetLeft(NULL);
			Arr[Count].SetRight(NULL);
			Count++;
			if (LocalRoot == NULL)//Текущая вершина пустая
			{
				return &(Arr[Count]);
			}
			else//Текущая вершина занята. Рекурсивно ищем подходящую свободную вершину
			{
				if (LocalRoot->GetData() > T)//Если данные в текущей вершине дерева строго больше вставляемого значения
				{
					//Ищем в левом поддереве подходящую пустую вершину
					LocalRoot->SetLeft(Paste(LocalRoot->GetLeft(), T));
				}
				else//Данные в текущей вершине дерева не больше вставляемого значения
				{
					//Ищем в правом поддереве подходящую пустую вершину
					LocalRoot->SetRight(Paste(LocalRoot->GetRight(), T));
				}
				return LocalRoot;
			}
		}
		else//В массиве нет места
		{
			throw std::exception("\nМассив заполнен");
		}
	}
}
template<class Type, int Size>
int BSTree<Type, Size>::GetCount()
{
	return Count;
}
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::GetRoot()
{
	return Root;
}
//Функция вычисляет высоту дерева с учетом веток к нулевым вершинам
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
template<class Type, int Size>
int BSTree<Type, Size>::TreeHeight(typename BSTree<Type, Size>::Node * LocalRoot)
{
	if (LocalRoot == NULL)//Дошли до конца ветви
	{
		return 0;
	}
	int LeftHeight, RightHeight;//Высоты поддеревьев
	LeftHeight = TreeHeight(LocalRoot->GetLeft());//Высота левого поддерева
	RightHeight = TreeHeight(LocalRoot->GetRight());//Высота правого поддерева
	return ((LeftHeight>RightHeight)? LeftHeight: RightHeight) + 1;//Максимальная+1(текущая)
}
//Функция отображает дерево
//LocalRoot - указатель на корень дерева
template<class Type, int Size>
void BSTree<Type, Size>::Show(typename BSTree<Type, Size>::Node * LocalRoot)
{
	int Height = TreeHeight(LocalRoot);//Высота дерева с учетом нулевых веток
	printf("\n");
	for (int i = 0; i < Height; i++)
	{
		ShowLevel(LocalRoot, i, Height);//Отображает один уровень дерева
		printf("\n");
	}
}
//Функция отображает один уровень дерева
//LocalRoot - указатель на текущую вершину дерева, а для первого вызова - указатель на корень дерева
//ReqLevel - номер печатаемого уровня
//Height - высота дерева, включающая ветки к нулевым вершинам
//TempLevel - текущий уровень (для поиска вершин печатаемого уровня)
template<class Type, int Size>
void BSTree<Type, Size>::ShowLevel(typename BSTree<Type, Size>::Node * LocalRoot, int ReqLevel, int Height, int TempLevel)
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
				SpacesBeforeNode = 2*(W + Temp1 + Temp2) / 2 - W / 2;
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
			SpacesBeforeNode = 2*(W + Temp1 + Temp2) / 2 - W / 2;
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
