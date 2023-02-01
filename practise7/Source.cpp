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
	vector <string> medNames = { "���������-1", "���������-2", "���������-3", "���������-4", "���������-5" };
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
			"����\n"
			"0) ���� �������� ��������� � ��������.\n"
			"1) ������ ��������.\n"
			"2) ������� � ���.\n";
		cout << "��� �����: ";
		cin >> problem;
		switch (problem) {
		case 0:
		{
			cout << "�������� ������������ ���������� ���������:\n";
			cout << "������� A:";
			cin >> deficit[0];
			cout << "������� B: ";
			cin >> deficit[1];
			cout << "������� C: ";
			cin >> deficit[2];
			cout << "������� D: ";
			cin >> deficit[3];
			cout << "������� E: ";
			cin >> deficit[4];
			system("pause");
			break;
		}
		case 1:
		{
			cout << "���������� ��������� = " << greedyAlgorithm(medNames, vitNames, vitamins, deficit) << '\n';
			system("pause");
			break;
		}
		case 2:
		{
			cout << "���������� ��������� = " << dumbAlgorithm(medNames, vitNames, vitamins, deficit) << '\n';
			system("pause");
			break;
		}
		default:
			cout << "��������, � �� ������ �������, ��� �� ������ �������. ���������� � ������ ���.\n";
			continue;
			system("pause");
			break;
		}
	}
	return 0;
}

int greedyAlgorithm(vector<string> medNames, vector<string> vitNames, vector<vector<int>> vitamins, vector<int> deficit) {
	int sum = 0;
	for (int i = 0; i < 4; i++) { // ���������� �� �������� �������� ���������
		for (int j = i + 1; j < 5; j++) {
			if (deficit[j] > deficit[i]) {
				swap(deficit[i], deficit[j]);
				swap(vitNames[i], vitNames[j]);
				for (int k = 0; k < 5; k++) swap(vitamins[k][i], vitamins[k][j]);
			}
		}
	}
	int value[5] = { 0 };
	for (int i = 0; i < 5; i++) { // ����������� ������� �������� ���������
		for (int j = 0; j < 5; j++) {
			value[i] += vitamins[i][j];
		}
	}
	for (int i = 0; i < 4; i++) { // ����������� ���������� �������� �� ��������
		for (int j = i + 1; j < 5; j++) {
			if (value[j] > value[i]) {
				swap(medNames[i], medNames[j]);
				for (int k = 0; k < 5; k++) swap(vitamins[i][k], vitamins[j][k]);
			}
		}
	}
	int count[5] = { 0 };
	int max = 0;
	for (int i = 0; i < 5; i++) { // ��� ��������
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