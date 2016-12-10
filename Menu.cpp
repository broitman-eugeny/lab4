#include "lab4.h"
//Функция отображения меню
void ShowMenu()
{
	std::cout << std::endl << "Лабораторная работа №4 (ООП)" << std::endl << "Контейнер - двоичное дерево";
	std::cout << std::endl << "[1]. Добавить вершину в дерево";
	std::cout << std::endl << "[2]. Показать дерево";
	std::cout << std::endl << "[3]. Выход";
	std::cout << std::endl << "Введите номер требуемого пункта меню: ";
}
//Функция проверки ввода из потока std::cin целочисленного значения
//Value - ссылка на переменную в которую осуществляется ввод
//LeftBorder - левая граница области определения вводимой переменной
//LeftIncluded - признак включения в область определения переменной левой границы
//RightBorder - правая граница области определения вводимой переменной
//RightIncluded - признак включения в область определения переменной правой границы
void CheckCinInt(int &Value, const int LeftBorder, const bool LeftIncluded, const int RightBorder, const bool RightIncluded)
{
	while ((LeftIncluded == true) ? (Value<LeftBorder) : (Value <= LeftBorder) || (RightIncluded == true) ? (Value>RightBorder) : (Value >= RightBorder) || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());//Очистка буфера
		std::cout << std::endl << "Значение введено неверно, введите еще раз: ";
		std::cin >> Value;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());//Очистка буфера если введено вещественное число попадающее в заданный диапазон
}
//Функция меню
void Menu()
{
	BSTree<int> TreeInt10;//Котейнер-дерево для целых чисел на 10 вершин
	int T;
	int C = -1;
	while (C != 3)//3 - выход
	{
		ShowMenu();
		std::cin >> C;
		CheckCinInt(C, 1, true, 3, true);//проверка корректности ввода
		switch (C)
		{
		case 1://Добавить вершину в дерево
			std::cout << "Введите целое число (1-2 знака): ";
			std::cin >> T;
			CheckCinInt(T, -9, true, 99, true);//проверка корректности ввода
			try//Попытка добавления вершины дерева
			{
				TreeInt10.Paste(TreeInt10.GetRoot(), T);
				std::cout << "Добавлено";
			}
			catch (std::exception Ex)//Если массив заполнен
			{
				std::cerr << Ex.what() << std::endl << "Не добавлено";
			}
			break;
		case 2://Показать дерево
			std::cout << std::endl << "Количество вершин дерева: "<< TreeInt10.GetCount();
			TreeInt10.Show(TreeInt10.GetRoot());//Вывод дерева на экран
			break;
		case 3://Выход
			break;
		}//switch (C)
	}//while (C != 3)//3 - выход
}