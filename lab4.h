#pragma once
#include <iostream>
#include <Windows.h>
const int ValChPlacesAmount = 2;//���������� ��������� ��� ����������� ������ �������� ������ �� ������
const int OutSpaceChPlacesAmount = 2;//���������� ��������� ��� ����������� ����� ��������� ������� ������
const int InSpaceChPlacesAmount = 1;//���������� ��������� ��� ����������� ����� ���������� ������ ����� �������
//������ ������ ������ ��������� ������
template <class Type>
class BSTree
{
	//��������� ����� ������� ������
	class Node
	{
		//������ �������
		Type Data;
		//��������� �� ������� ������ ���������
		Node *Left;
		//��������� �� ������� ������� ���������
		Node *Right;
	public:
		Node(const Type &);
		Node(const Node &);
		Type GetData();//��������� ������ � ������� ������� ������
		void SetData(const Type &);//������ ������ � ������� ������� ������
		Node * GetLeft();//��������� ��������� �� ������� ������ ��������� ������� ������� ������
		void SetLeft(Node *);//������ ��������� �� ������� ������ ��������� � ������� ������� ������
		Node * GetRight();//��������� ��������� �� ������� ������� ��������� ������� ������� ������
		void SetRight(Node *);//������ ��������� �� ������� ������� ��������� � ������� ������� ������
	};
	//��������� �� ������ ������
	Node *Root;
	//���������� ������ ������
	int Count;
public:
	//����������� �� ���������
	BSTree();
	~BSTree();//����������
	Node* ClearAll(Node*);//�������� ������
	Node * Paste(Node *, const Type &);//������� ������� ������
	Node * Delete(Node *, const Type &);//�������� ������� ������
	int GetCount();//��������� ���������� ������ ������
	Node *GetRoot();//��������� ��������� �� ������ ������
	int TreeHeight(Node * LocalRoot);//��������� ������ ������ � ������ ����� � ������� ��������
	void Show(Node * LocalRoot);//����� ������ �� �����
	void ShowLevel(Node * LocalRoot, int ReqLevel, int Height, int TempLevel);//����� ������ ������ ������ �� �����
};
//����������� � ����������
template<class Type>
BSTree<Type>::Node::Node(const Type &T) : Data(T), Left(NULL), Right(NULL)
{
}
//����������� �����������. typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
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
typename BSTree<Type>::Node * BSTree<Type>::Node::GetLeft()//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Left;
}
template<class Type>
void BSTree<Type>::Node::SetLeft(typename BSTree<Type>::Node *T)
{
	Left = T;
}
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Node::GetRight()//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Right;
}
template<class Type>
void BSTree<Type>::Node::SetRight(typename BSTree<Type>::Node *T)
{
	Right = T;
}
//����������� �� ���������
template<class Type>
BSTree<Type>::BSTree() : Root(NULL), Count(0)
{
}
//����������
template<class Type>
BSTree<Type>::~BSTree()
{
	ClearAll(Root);//������� ��� ������� ������
	std::cout << std::endl << "�������� " << GetCount() << " ������" << std::endl;
}
//�������� ���� ������ ������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::ClearAll(typename BSTree<Type>::Node *LocalRoot)
{
	if (LocalRoot == NULL)//����� �� ����� �����
	{
		return NULL;
	}
	BSTree<Type>::Node *LocalLeft, *LocalRight;
	LocalLeft = ClearAll(LocalRoot->GetLeft());//���� � ����� ����� �����
	LocalRight= ClearAll(LocalRoot->GetRight());//���� � ����� ������ �����
	//����� �� ����� ����� �����
	delete LocalRoot;
	Count--;
	return NULL;
}
//������� ������� ������
//���� ����� ������� ������� �� �������� ��������������� (����� ��������� ������ ����� �������� ������
//������ ������ �������� ������ ��������, � ������ ��������� ������ ����� �������� ������ ������,
//���� ������ �������� ������ ��������), ������������� ������ �� ��������������� �������.
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
//T - �������� ������ �������
//���������� ��������� �� ������ ������
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Paste(typename BSTree<Type>::Node *LocalRoot, const Type &T)//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	if (Count == 0)//������ ������
	{
		Root = new Node(T);//�������� ������� �� ��������� ������ � � ����������� �� �������� NULL
		Count = 1;
		return Root;
	}
	else//������ �� ������
	{
		if (LocalRoot == NULL)//������� ������� ������
		{
			Count++;
			return new Node(T);//�������� ������� �� ��������� ������ � � ����������� �� �������� NULL
		}
		else//������� ������� ������. ���������� ���� ���������� ��������� �������
		{
			if (LocalRoot->GetData() > T)//���� ������ � ������� ������� ������ ������ ������ ������������ ��������
			{
				//���� � ����� ��������� ���������� ������ �������
				LocalRoot->SetLeft(Paste(LocalRoot->GetLeft(), T));
			}
			else
				if(LocalRoot->GetData() < T)//������ � ������� ������� ������ ������ ������������ ��������
				{
					//���� � ������ ��������� ���������� ������ �������
					LocalRoot->SetRight(Paste(LocalRoot->GetRight(), T));
				}
				else//������ � ������� ������� ������ ����� ������������ ��������
				{
					throw std::exception("������ ������� (����) ������ ���� ���������!!!");
				}
			return LocalRoot;
		}
	}
}
//�������� ������� ������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
//Del - ��������� �������� ������ �������
//���������� ��������� �� ������ ������
template<class Type>
typename BSTree<Type>::Node * BSTree<Type>::Delete(typename BSTree<Type>::Node *LocalRoot, const Type &DelData)
{
	if (LocalRoot == NULL)//����� �� ����� �����
	{
		return NULL;
	}
	else
	{
		Type TData = LocalRoot->GetData();//������ ������� �������
		typename BSTree<Type>::Node *TLeft= LocalRoot->GetLeft();//��������� �� ������ �������
		typename BSTree<Type>::Node *TRight = LocalRoot->GetRight();//��������� �� ������� �������
		if (TData > DelData)//������ ������� ������ ���������� ��������
		{
			LocalRoot->SetLeft(Delete(TLeft, DelData));//������ �����
		}
		if (TData < DelData)//������ ������� ������ ���������� ��������
		{
			LocalRoot->SetRight(Delete(TRight, DelData));//������ ������
		}
		if (TData == DelData)//������ ������� ����� ���������� ��������
		{
			Count--;//��������� ������� ������
			if (TLeft == NULL && TRight == NULL)//����� �� �������� �������
			{
				if (Root == LocalRoot)//���� ������� ������ ������
				{
					Root= NULL;
				}
				delete LocalRoot;//�����������  ������ ��-��� ��������� �������
				return NULL;//�������� �������� NULL ��������� ������ ��������� �� ���������� �������
			}
			if (TLeft != NULL && TRight == NULL)//����� ���� �������, ������ - ���
			{
				if (Root == LocalRoot)//���� ������� ������ ������
				{
					Root = TLeft;
				}
				delete LocalRoot;//�����������  ������ ��-��� ��������� �������
				return TLeft;//�������� �������� ��������� �� ������ ������ ��������� �� ���������� �������
			}
			if (TLeft == NULL && TRight != NULL)//������ ���� �������, ����� - ���
			{
				if (Root == LocalRoot)//���� ������� ������ ������
				{
					Root = TRight;
				}
				delete LocalRoot;//�����������  ������ ��-��� ��������� �������
				return TRight;//�������� �������� ��������� �� ������� ������ ��������� �� ���������� �������
			}
			if (TLeft != NULL && TRight != NULL)//������ ���� �������, � ����� - ����
			{
				Node *T1 = TRight;//������ � ������ ���������
				if (T1->GetLeft() != NULL)//���� � ������ ��������� ���� ����� �������
				{
					Node *T2 = T1->GetLeft();//������ � ����� ��������� ������� ���������
					while (T2->GetLeft() != NULL)//���������� �� ����� �������� ������� ��������� �� ����� �����
					{
						T1 = T2;
						T2 = T2->GetLeft();
					}
					//T2 - ����� ����� ������� ������� ��������� ��������� �������
					//T1 - �������� T2
					T1->SetLeft(NULL);//������� ������ ������� � T1
					T2->SetLeft(TLeft);//������������� ������ ������� ��������� �������
					T2->SetRight(TRight);//������������� ������� ������� ��������� �������
					if (Root == LocalRoot)//���� ������� ������ ������
					{
						Root = T2;
					}
					delete LocalRoot;//�����������  ������ ��-��� ��������� �������
					return T2;//�������� �������� ��������� ������� ��������� �� ������ ������ ������� ������� ���������
				}
				else//� ������ ��������� ��� ������ �������
				{
					T1->SetLeft(TLeft);//������������� ������ ������� ��������� �������
					if (Root == LocalRoot)//���� ������� ������ ������
					{
						Root = T1;
					}
					delete LocalRoot;//�����������  ������ ��-��� ��������� �������
					return T1;//�������� �������� ��������� �� ������� ������ ��������� �� ���������� �������
				}
			}
		}
	}
	return LocalRoot;//���� �������� DelData ��� � ������
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
//������� ��������� ������ ������ � ������ ����� � ������� ��������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
template<class Type>
int BSTree<Type>::TreeHeight(typename BSTree<Type>::Node * LocalRoot)
{
	if (LocalRoot == NULL)//����� �� ����� �����
	{
		return 0;
	}
	int LeftHeight, RightHeight;//������ �����������
	LeftHeight = TreeHeight(LocalRoot->GetLeft());//������ ������ ���������
	RightHeight = TreeHeight(LocalRoot->GetRight());//������ ������� ���������
	return ((LeftHeight>RightHeight) ? LeftHeight : RightHeight) + 1;//������������+1(�������)
}
//������� ���������� ������
//LocalRoot - ��������� �� ������ ������
template<class Type>
void BSTree<Type>::Show(typename BSTree<Type>::Node * LocalRoot)
{
	int Height = TreeHeight(LocalRoot);//������ ������ � ������ ������� �����
	printf("\n");
	for (int i = 0; i < Height; i++)
	{
		ShowLevel(LocalRoot, i, Height, 0);//���������� ���� ������� ������
		printf("\n");
	}
}
//������� ���������� ���� ������� ������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
//ReqLevel - ����� ����������� ������
//Height - ������ ������, ���������� ����� � ������� ��������
//TempLevel - ������� ������� (��� ������ ������ ����������� ������)
template<class Type>
void BSTree<Type>::ShowLevel(typename BSTree<Type>::Node * LocalRoot, int ReqLevel, int Height, int TempLevel)
{
	char FormatS[5];
	FormatS[0] = '%';
	FormatS[1] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount / 10 : '0' + ValChPlacesAmount;
	FormatS[2] = (ValChPlacesAmount>9) ? '0' + ValChPlacesAmount % 10 : 's';
	FormatS[3] = (ValChPlacesAmount>9) ? 's' : '\0';
	FormatS[4] = '\0';
	int Temp1 = OutSpaceChPlacesAmount / 2,//��������� ���������� 1
		Temp2 = OutSpaceChPlacesAmount - Temp1,//��������� ���������� 2
		SpacesBeforeNode = Temp1,//���������� ��������, ������� ����� ���������� ����� �������� �������� ������
		SpacesAfterNode = Temp2,//���������� ��������, ������� ����� ���������� ����� ������� �������� ������
		W = ValChPlacesAmount;//���������� ���������, ���������� ����� �������� ������
	if (TempLevel < ReqLevel)//���� �� �������� ���������� ������
	{
		if (LocalRoot != NULL)//�� �������� ����� �����
		{
			ShowLevel(LocalRoot->GetLeft(), ReqLevel, Height, TempLevel + 1);//������� � ���������� ������ � ����� ���������
			ShowLevel(LocalRoot->GetRight(), ReqLevel, Height, TempLevel + 1);//������� � ���������� ������ � ������ ���������
		}
		else//�������� ����� �����. ���������� ���������� ������� � ������������� ������ (��������� ������ ��������� � ������������� ������), ����� ���������� ������������� �������� ��-�� ������� ������ � ������� ������ � ��������� ��������� ������
		{
			for (int i = Height - 2; i >= TempLevel; i--)
			{
				Temp1 = SpacesBeforeNode;//�������� �� ���������� ������
				Temp2 = SpacesAfterNode;//�������� �� ���������� ������
										//���������� ��������, ������� ����� ���������� ����� ��������
				SpacesBeforeNode = 2 * (W + Temp1 + Temp2) / 2 - W / 2;
				//���������� ��������, ������� ����� ���������� ����� �������
				SpacesAfterNode = SpacesBeforeNode + W / 2 - (W - W / 2);//�.�. W �.�. �������� � W/2 < �������� W
			}
			//������ �������� ����� ��������
			for (int i = 0; i < SpacesBeforeNode; i++)
			{
				printf(" ");
			}
			printf(FormatS, " ");//������ �������� ������ ������������� ������, ����� ��������� ���������
								 //������ �������� ����� �������
			for (int i = 0; i < SpacesAfterNode; i++)
			{
				printf(" ");
			}
		}
	}
	else//�������� ���������� ������
	{
		for (int i = Height - 2; i >= TempLevel; i--)
		{
			Temp1 = SpacesBeforeNode;
			Temp2 = SpacesAfterNode;
			//���������� ��������, ������� ����� ���������� ����� ��������
			SpacesBeforeNode = 2 * (W + Temp1 + Temp2) / 2 - W / 2;
			//���������� ��������, ������� ����� ���������� ����� �������
			SpacesAfterNode = SpacesBeforeNode + W / 2 - (W - W / 2);//�.�. W �.�. �������� � W/2 < �������� W
		}
		//������ �������� ����� ��������
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
		//������ �������� �������
		if (LocalRoot != NULL)//������� ������� (�� ����� �����)
		{
			printf(Format, LocalRoot->GetData());
		}
		else//������� ������� (����� �����)
		{
			printf(FormatS, "*");
		}
		//������ �������� ����� �������
		for (int i = 0; i < SpacesAfterNode; i++)
		{
			printf(" ");
		}
	}
}
//������� ����
void Menu();
