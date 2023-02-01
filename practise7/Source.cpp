#include <iostream>
#include <string>
#include <vector>

using namespace std;

int greedyAlgorithm(vector<string> medNames, vector<string> vitNames, vector<vector<int>> vitamins, vector<int> deficit);
int dumbAlgorithm(vector<string> medNames, vector<string> vitNames, vector<vector<int>> vitamins, vector<int> deficit);

const int k = 5;

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	short problem;
	bool flag = true;
	vector <string> medNames = { "Лекарство-1", "Лекарство-2", "Лекарство-3", "Лукарство-4", "Лекарство-5" };
	vector <string> vitNames = { "A", "B", "C", "D", "E" };
	vector <vector<int>> vitamins =
	{ {5, 15, 10, 35, 0}, //65
	  {30, 5, 20, 10, 15}, //80
	  {0, 15, 10, 30, 45}, // 100
	  {15, 0, 30, 0, 15}, // 60
	  {0, 20, 10, 25, 30} }; // 85
	vector <int> deficit;
	deficit.resize(5);
	while (flag)
	{
		system("cls");
		cout <<
			"Меню\n"
			"0) Ввод дефицита витаминов у пациента.\n"
			"1) Жадный алгоритм.\n"
			"2) Решение в лоб.\n";
		cout << "Ваш выбор: ";
		cin >> problem;
		switch (problem) {
		case 0:
		{
			cout << "Введитее неддостающее количество витаминов:\n";
			cout << "Витамин A:";
			cin >> deficit[0];
			cout << "Витамин B: ";
			cin >> deficit[1];
			cout << "Витамин C: ";
			cin >> deficit[2];
			cout << "Витамин D: ";
			cin >> deficit[3];
			cout << "Витамин E: ";
			cin >> deficit[4];
			system("pause");
			break;
		}
		case 1:
		{
			cout << "Количество переборов = " << greedyAlgorithm(medNames, vitNames, vitamins, deficit) << '\n';
			system("pause");
			break;
		}
		case 2:
		{
			cout << "Количество переборов = " << dumbAlgorithm(medNames, vitNames, vitamins, deficit) << '\n';
			system("pause");
			break;
		}
		default:
			cout << "Извините, я не совсем понимаю, что вы хотите сделать. Попробуйте в другой раз.\n";
			continue;
			system("pause");
			break;
		}
	}
	return 0;
}

int greedyAlgorithm(vector<string> medNames, vector<string> vitNames, vector<vector<int>> vitamins, vector<int> deficit) {
	int sum = 0;
	for (int i = 0; i < 4; i++) { // сортировка по убыванию нехватки витаминов
		for (int j = i + 1; j < 5; j++) {
			if (deficit[j] > deficit[i]) {
				swap(deficit[i], deficit[j]);
				swap(vitNames[i], vitNames[j]);
				for (int k = 0; k < 5; k++) swap(vitamins[k][i], vitamins[k][j]);
			}
		}
	}
	int value[5] = { 0 };
	for (int i = 0; i < 5; i++) { // составление массива ценности витаминов
		for (int j = 0; j < 5; j++) {
			value[i] += vitamins[i][j];
		}
	}
	for (int i = 0; i < 4; i++) { // сортировака двумерного масссива по ценности
		for (int j = i + 1; j < 5; j++) {
			if (value[j] > value[i]) {
				swap(medNames[i], medNames[j]);
				for (int k = 0; k < 5; k++) swap(vitamins[i][k], vitamins[j][k]);
			}
		}
	}
	int count[5] = { 0 };
	int max = 0;
	for (int i = 0; i < 5; i++) { // сам алгоритм
		while (count[i] < deficit[i]) {
			max = 0;
			for (int j = 0; j < 5; j++) {
				sum++;
				if (vitamins[j][i] > vitamins[max][i]) max = j;
				if (count[i] + vitamins[j][i] >= deficit[i]) {
					for (int k = 0; k < 5; k++) {
						count[k] += vitamins[j][k];
						sum++;
					}
					cout << medNames[j] << '\n';
					break;
				}
			}
			if (count[i] < deficit[i]) {
				for (int k = 0; k < 5; k++) {
					count[k] += vitamins[max][k];
					sum++;
				}
				cout << medNames[max] << '\n';
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << vitNames[i] << ": " << count[i] << '\n';
	}
	return sum;
}

int dumbAlgorithm(vector<string> medNames, vector<string> vitNames, vector<vector<int>> vitamins, vector<int> deficit) {
	int sum = 0;
	int count[5] = { 0 };
	for (int i = 0; i < 5; i++) {
		int j = 0;
		while (count[i] < deficit[i]) {
			sum++;
			for (int k = 0; k < 5; k++) count[k] += vitamins[j][k];
			sum += 5;
			cout << medNames[j] << '\n';
			j++;
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << vitNames[i] << ": " << count[i] << '\n';
	}
	return sum;
}