#include "lab4.h"
//����������� � ����������
template<class Type, int Size>
BSTree<Type, Size>::Node::Node(const Type &T) : Data(T), Left(NULL), Right(NULL)
{
}
//����������� �����������. typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
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
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Node::GetLeft()//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Left;
}
template<class Type, int Size>
void BSTree<Type, Size>::Node::SetLeft(typename BSTree<Type, Size>::Node *T)
{
	Left = T;
}
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Node::GetRight()//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	return Right;
}
template<class Type, int Size>
void BSTree<Type, Size>::Node::SetRight(typename BSTree<Type, Size>::Node *T)
{
	Right = T;
}
//����������� �� ���������
template<class Type, int Size>
BSTree<Type, Size>::BSTree(): Root(NULL), Count(0)
{
}
//������� ������� ������
//���� ���� ����� � ������� Arr - ���������� ������ � ������ ��������� ������� ������� Arr,
//���� ����� ������� ������� �� �������� ��������������� (����� ��������� ������ ����� �������� ������
//������ ������ �������� ������ ��������, � ������ ��������� ������ ����� �������� ������ ������,
//���� ������ �������� ������ ��������), ������������� ������ �� ��������������� �������.
//���� ������ Arr �������� - ����������� ����������.
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
//T - �������� ������ �������
//���������� ��������� �� ������ ������
template<class Type, int Size>
typename BSTree<Type, Size>::Node * BSTree<Type, Size>::Paste(typename BSTree<Type, Size>::Node *LocalRoot, const Type &T)//typename ���������� (��. https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=RU-RU&k=k(C4346)&rd=true)
{
	if (Count == 0)//������ ������
	{
		Arr[0].SetData(T);
		Arr[0].SetLeft(NULL);
		Arr[0].SetRight(NULL);
		Root = &(Arr[0]);
		Count = 1;
		return Root;
	}
	else//������ �� ������
	{
		if (Count < Size)//��� ���� ����� � �������
		{
			Arr[Count].SetData(T);//��������� T � ������ ��������� ������� ������� Arr
			//�������� ��������� �� ��������
			Arr[Count].SetLeft(NULL);
			Arr[Count].SetRight(NULL);
			Count++;
			if (LocalRoot == NULL)//������� ������� ������
			{
				return &(Arr[Count]);
			}
			else//������� ������� ������. ���������� ���� ���������� ��������� �������
			{
				if (LocalRoot->GetData() > T)//���� ������ � ������� ������� ������ ������ ������ ������������ ��������
				{
					//���� � ����� ��������� ���������� ������ �������
					LocalRoot->SetLeft(Paste(LocalRoot->GetLeft(), T));
				}
				else//������ � ������� ������� ������ �� ������ ������������ ��������
				{
					//���� � ������ ��������� ���������� ������ �������
					LocalRoot->SetRight(Paste(LocalRoot->GetRight(), T));
				}
				return LocalRoot;
			}
		}
		else//� ������� ��� �����
		{
			throw std::exception("\n������ ��������");
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
//������� ��������� ������ ������ � ������ ����� � ������� ��������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
template<class Type, int Size>
int BSTree<Type, Size>::TreeHeight(typename BSTree<Type, Size>::Node * LocalRoot)
{
	if (LocalRoot == NULL)//����� �� ����� �����
	{
		return 0;
	}
	int LeftHeight, RightHeight;//������ �����������
	LeftHeight = TreeHeight(LocalRoot->GetLeft());//������ ������ ���������
	RightHeight = TreeHeight(LocalRoot->GetRight());//������ ������� ���������
	return ((LeftHeight>RightHeight)? LeftHeight: RightHeight) + 1;//������������+1(�������)
}
//������� ���������� ������
//LocalRoot - ��������� �� ������ ������
template<class Type, int Size>
void BSTree<Type, Size>::Show(typename BSTree<Type, Size>::Node * LocalRoot)
{
	int Height = TreeHeight(LocalRoot);//������ ������ � ������ ������� �����
	printf("\n");
	for (int i = 0; i < Height; i++)
	{
		ShowLevel(LocalRoot, i, Height);//���������� ���� ������� ������
		printf("\n");
	}
}
//������� ���������� ���� ������� ������
//LocalRoot - ��������� �� ������� ������� ������, � ��� ������� ������ - ��������� �� ������ ������
//ReqLevel - ����� ����������� ������
//Height - ������ ������, ���������� ����� � ������� ��������
//TempLevel - ������� ������� (��� ������ ������ ����������� ������)
template<class Type, int Size>
void BSTree<Type, Size>::ShowLevel(typename BSTree<Type, Size>::Node * LocalRoot, int ReqLevel, int Height, int TempLevel)
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
				SpacesBeforeNode = 2*(W + Temp1 + Temp2) / 2 - W / 2;
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
			SpacesBeforeNode = 2*(W + Temp1 + Temp2) / 2 - W / 2;
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
