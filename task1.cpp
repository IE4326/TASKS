#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cmath>

void fill(char* filepath, std::vector<int64_t> &arr);
void sort(std::vector<int64_t> &arr);
int64_t findmiddle(std::vector<int64_t> &arr);
int64_t findpercentile(std::vector<int64_t> &arr);
std::vector<int64_t> getnewset(std::vector<int64_t> &old, int64_t mid, int64_t per);
int countdigits(std::vector<int64_t> &arr);

int main(int argc, char** argv){
	if (argc != 2){
		std::cout << "Usage: <infile>";
		return 1;
	}
	std::vector<int64_t>fund;
	fill(argv[1], fund);
	sort(fund);
	int64_t middle = findmiddle(fund);
	int64_t percentile90 = findpercentile(fund);
	std::vector<int64_t> newset = getnewset(fund, middle, percentile90);
	int digitsum = countdigits(newset);
	std::cout << digitsum << std::endl; 
	return 0;
}

// Считывает данные из файла и заполняет ими массив
void fill(char* filepath, std::vector<int64_t> &arr){
	std::ifstream file;
	file.open(filepath);
	if (!file){
		std::cout << "Could not open the file!";
		return;
	}
	std::string line;
	std::getline(file, line, (char)10);
	int dropcount = 0;
	while (file){
		try{
			arr.push_back(stoi(line));
		}
		catch (std::out_of_range exception){
			std::cout << "Numbers longer than 8 bytes are not allowed! Dropping..\n";
			dropcount++;
		}
		std::getline(file, line, (char)10);
	}
	if (dropcount){
		std::cout << "Dropped " << dropcount << " numbers while parsing!\n";
	}
	return;
}

// Простая пузырьковая сортировка
void sort(std::vector<int64_t> &arr){
	bool unsorted = true;
	std::vector<int64_t>::iterator left;
	while (unsorted){
		left = arr.begin();
		unsorted = false;
		for (std::vector<int64_t>::iterator i = arr.begin()+1; i < arr.end(); i++, left++){
			if (*left > *i) {
				std::iter_swap(left, i);
				unsorted = true;
			}
		}
	}
}

// Получает на вход массив отсортированных значений и возвращает среднее
int64_t findmiddle(std::vector<int64_t> &arr){
	int64_t sum = 0;
	for (std::vector<int64_t>::iterator i = arr.begin(); i < arr.end(); i++){
		sum += *i;
	}
	return sum/(arr.size());
}

// Найти перцентиль в отсортированном массиве
int64_t findpercentile(std::vector<int64_t> &arr){
	int index = ((float)arr.size() * 0.9) + 0.5;
	return arr.at(index);
}

// Создаёт новый массив по условиям задачи. Получает на вход весь массив, среднее и перцентиль
std::vector<int64_t> getnewset(std::vector<int64_t> &old, int64_t mid, int64_t per){
	std::vector<int64_t> ns;
	for (std::vector<int64_t>::iterator i = old.begin(); i < old.end(); i++){
		if (*i > mid && *i < per) ns.push_back(*i);
	}
	return ns;
}

// Получает на вход новый массив. Разбивает значения на цифры и суммирует
int countdigits(std::vector<int64_t> &arr){
	int64_t wrn;
	int sum = 0;
	for (std::vector<int64_t>::iterator i = arr.begin(); i < arr.end(); i++){
		wrn = *i;
		while (wrn != 0){
			sum += wrn % 10;
			wrn /= 10;
		}
	}
	return sum;
}
