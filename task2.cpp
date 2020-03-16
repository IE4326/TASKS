#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <cstring>

enum coords {X, Y, Z};
enum points {A, B, C};
class Triangle{
	float points[3][3];
	float borders[3];
	public:
	Triangle(){
		for (int i = 0; i < 3; i++){
			for (int h = 0; h < 3; h++){
				points[h][i] = 0;
			}
		}
		countborders();
	}
	void setpoint(int point, float x, float y, float z){
		points[point][X] = x;
		points[point][Y] = y;
		points[point][Z] = z;
		countborders();
	}
	float getpoint(int point, int coord){
		if (point >= 0 && point < 3 && coord >= 0 && coord < 3){
			return points[point][coord];
		}
		return 0;
	}
	float getborder(int b){
		if (b >= 0 && b < 3){
			return borders[b];
		}
		return 0;
	}
	void countborders(){
		float c1, c2, c3;
		c1 = pow((points[A][X] - points[B][X]), 2);
		c2 = pow((points[A][Y] - points[B][Y]), 2);
		c3 = pow((points[A][Z] - points[B][Z]), 2);
		borders[0] = sqrt(c1 + c2 + c3);
		c1 = pow((points[B][X] - points[C][X]), 2);
		c2 = pow((points[B][Y] - points[C][Y]), 2);
		c3 = pow((points[B][Z] - points[C][Z]), 2);
		borders[1] = sqrt(c1 + c2 + c3);
		c1 = pow((points[C][X] - points[A][X]), 2);
		c2 = pow((points[C][Y] - points[A][Y]), 2);
		c3 = pow((points[C][Z] - points[A][Z]), 2);
		borders[2] = sqrt(c1 + c2 + c3);
	}
} triangles[2];

bool FileParser(char* filepath);
bool CheckSimilar();

int main(int argc, char** argv){
	if (argc != 2){
		std::cout << "Usage: <filename>";
		return 1;
	}
	FileParser(argv[1]);
	if (CheckSimilar()){
		std::cout << "\nSIMILAR!";
	} else {
		std::cout << "\nNOT SIMILAR!";
	}
	return 0;
}

// Сравнивает треугольники, используя заранее просчитанные стороны 
bool CheckSimilar(){
	float a, b, c;
	a = triangles[0].getborder(0) / triangles[1].getborder(0);
	b = triangles[0].getborder(1) / triangles[1].getborder(1);
	c = triangles[0].getborder(2) / triangles[1].getborder(2);
	if (a == b && b == c){
		return true;
	} else {
		return false;
	}
}

// Считывает данные из файла и записывает их в объекты triangles
bool FileParser(char* filepath){
	std::ifstream file;
	file.open(filepath, std::ios::in);
	if (!file){
		std::cout << "Could not open the file!";
		return false;
	}
	char ch;
	while (ch != '{' && file) {
		file.get(ch);
	}
	if (!file){
		std::cout << "Bad file format!";
		return false;
	}
	std::string line;
	float x, y, z;
	for (int i = 0; i < 2; i++){
		for (int p = 0; p < 3; p++){
			std::getline(file, line, '[');
			std::getline(file, line, ',');
			x = stof(line);
			std::getline(file, line, ',');
			y = stof(line);
			std::getline(file, line, ']');
			z = stof(line);
			triangles[i].setpoint(p, x, y, z);
		}
	}
	return true;
}

