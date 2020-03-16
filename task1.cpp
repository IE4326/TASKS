#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cmath>

typedef std::vector<int64_t> int_vector;
typedef int64_t longt;

void fill(char* filepath, int_vector& arr);
void sort(int_vector& arr);
longt findmiddle(int_vector& arr);
longt findpercentile(int_vector& arr);
int_vector getnewset(int_vector& old, longt mid, longt per);
int countdigits(int_vector& arr);

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: <infile>";
		return 1;
	}
	int_vector fund;
	fill(argv[1], fund);
	sort(fund);
	longt middle = findmiddle(fund);
	longt percentile90 = findpercentile(fund);
	int_vector newset = getnewset(fund, middle, percentile90);
	int digitsum = countdigits(newset);
	std::cout << digitsum << std::endl;
	return 0;
}

// Считывает данные из файла и заполняет ими массив
void fill(char* filepath, int_vector& arr) {
	std::ifstream file;
	file.open(filepath);
	if (!file) {
		std::cout << "Could not open the file!";
		return;
	}
	std::string line;
	std::getline(file, line, (char)10);
	int dropcount = 0;
	while (file) {
		try {
			arr.push_back(stoi(line));
		}
		catch (std::out_of_range exception) {
			std::cout << "Numbers longer than 8 bytes are not allowed! Dropping..\n";
			dropcount++;
		}
		std::getline(file, line, (char)10);
	}
	if (dropcount) {
		std::cout << "Dropped " << dropcount << " numbers while parsing!\n";
	}
	return;
}

// Простая пузырьковая сортировка
void sort(int_vector& arr) {
	bool unsorted = true;
	int_vector::iterator left;
	while (unsorted) {
		left = arr.begin();
		unsorted = false;
		for (int_vector::iterator i = arr.begin() + 1; i < arr.end(); i++, left++) {
			if (*left > * i) {
				std::iter_swap(left, i);
				unsorted = true;
			}
		}
	}
}

// Получает на вход массив отсортированных значений и возвращает среднее
longt findmiddle(int_vector& arr) {
	longt sum = 0;
	for (int_vector::iterator i = arr.begin(); i < arr.end(); i++) {
		sum += *i;
	}
	return sum / (arr.size());
}

// Найти перцентиль в отсортированном массиве
longt findpercentile(int_vector& arr) {
	int index = ((float)arr.size() * 0.9) + 0.5;
	return arr.at(index);
}

// Создаёт новый массив по условиям задачи. Получает на вход весь массив, среднее и перцентиль
int_vector getnewset(int_vector& old, longt mid, longt per) {
	int_vector ns;
	for (int_vector::iterator i = old.begin(); i < old.end(); i++) {
		if (*i > mid&&* i < per) ns.push_back(*i);
	}
	return ns;
}

// Получает на вход новый массив. Разбивает значения на цифры и суммирует
int countdigits(int_vector& arr) {
	longt wrn;
	int sum = 0;
	for (int_vector::iterator i = arr.begin(); i < arr.end(); i++) {
		wrn = *i;
		while (wrn != 0) {
			sum += wrn % 10;
			wrn /= 10;
		}
	}
	return sum;
}
