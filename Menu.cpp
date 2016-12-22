#include "lab4.h"
//������� ����������� ����
void ShowMenu()
{
	std::cout << std::endl << "������������ ������ �4 (���)" << std::endl << "��������� - �������� ������";
	std::cout << std::endl << "[1]. �������� ������� � ������";
	std::cout << std::endl << "[2]. ������� ������� �� ������";
	std::cout << std::endl << "[3]. �������� ������";
	std::cout << std::endl << "[4]. �����";
	std::cout << std::endl << "������� ����� ���������� ������ ����: ";
}
//������� �������� ����� �� ������ std::cin �������������� ��������
//Value - ������ �� ���������� � ������� �������������� ����
//LeftBorder - ����� ������� ������� ����������� �������� ����������
//LeftIncluded - ������� ��������� � ������� ����������� ���������� ����� �������
//RightBorder - ������ ������� ������� ����������� �������� ����������
//RightIncluded - ������� ��������� � ������� ����������� ���������� ������ �������
void CheckCinInt(int &Value, const int LeftBorder, const bool LeftIncluded, const int RightBorder, const bool RightIncluded)
{
	while ((LeftIncluded == true) ? (Value<LeftBorder) : (Value <= LeftBorder) || (RightIncluded == true) ? (Value>RightBorder) : (Value >= RightBorder) || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());//������� ������
		std::cout << std::endl << "�������� ������� �������, ������� ��� ���: ";
		std::cin >> Value;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());//������� ������ ���� ������� ������������ ����� ���������� � �������� ��������
}
//������� ����
void Menu()
{
	BSTree<int> TreeInt10;//��������-������ ��� ����� ����� �� 10 ������
	int T;
	int C = -1;
	while (C != 4)//4 - �����
	{
		ShowMenu();
		std::cin >> C;
		CheckCinInt(C, 1, true, 4, true);//�������� ������������ �����
		switch (C)
		{
		case 1://�������� ������� � ������
			std::cout << "������� ������ ������� (����� �����, 1-2 �����): ";
			std::cin >> T;
			try
			{
				TreeInt10.Paste(TreeInt10.GetRoot(), T);
			}
			catch (std::exception e)
			{
				std::cerr << std::endl << e.what();
				break;
			}
			std::cout << "������ ����� " << TreeInt10.GetCount();
			break;
		case 2://������� ������� �� ������
			std::cout << "������� ������ ������� (����� �����, 1-2 �����): ";
			std::cin >> T;
			TreeInt10.Delete(TreeInt10.GetRoot(), T);
			std::cout << "������ ����� " << TreeInt10.GetCount();
			break;
		case 3://�������� ������
			std::cout << std::endl << "���������� ������ ������: "<< TreeInt10.GetCount();
			TreeInt10.Show(TreeInt10.GetRoot());//����� ������ �� �����
			break;
		case 4://�����
			break;
		}//switch (C)
	}//while (C != 4)//4 - �����
}