#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct Rectangles {
	double w;
	double h;
};

typedef struct Squares {
	double a;
};

typedef struct Circles {
	double r;
};

enum Type {
	RectangleShape = 0,
	SquareShape = 1,
	CircleShape = 2
};

// Read data from file
void inputShapes(string filename, int& n, string inputData[100]) {
	ifstream reader;
	reader.open(filename, ios::in);

	if (reader.good()) {
		reader >> n;
		reader.ignore();

		for (int i = 0; i < n; i++) {
			string buffer;
			getline(reader, inputData[i]);
		}
	}

	reader.close();
}

// Split each line to specific data
void splitShapes(int n, string inputData[100], void**& a, Type types[100]) {
	for (int i = 0; i < n; i++) {
		string val = inputData[i];
		string token = ":";
		int pos = val.find_first_of(token, 0);
		
		string type = val.substr(0, pos);
		
		// Split data Rectangle
		if (type == "Rectangle") {
			string token = ",";
			int pos1 = val.find_first_of(token, pos + 1);
			string width = val.substr(pos + 4, pos1 - pos - 4);
			double w = stod(width);
			string height = val.substr(pos1 + 4, val.length() - pos1 - 4);
			double h = stod(height);

			Rectangles* rec = new Rectangles;
			rec->w = w;
			rec->h = h;

			a[i] = (void*) rec;
			types[i] = Type::RectangleShape;
		}
		// Split data Square
		else if (type == "Square") {
			string edge = val.substr(pos + 4, val.length() - pos - 2);
			double ed = stod(edge);

			Squares* sqr = new Squares;
			sqr->a = ed;
			
			a[i] = (void*) sqr;
			types[i] = Type::SquareShape;
		}
		// Split data Circle
		else {
			string radius = val.substr(pos + 4, val.length() - pos - 2);
			double r = stod(radius);

			Circles* cir = new Circles;
			cir->r = r;

			a[i] = (void*) cir;
			types[i] = Type::CircleShape;
		}
	}
}

void printRectangle(Rectangles* rec) {
	cout << "Rectangle: w=" << rec->w << ", h=" << rec->h << endl;
}

void printSquare(Squares* sqr) {
	cout << "Square: a=" << sqr->a << endl;
}

void printCircle(Circles* cir) {
	cout << "Circle: r=" << cir->r << endl;
}

void outputShape(void* value, Type type) {
	if (Type::RectangleShape == type) {
		printRectangle((Rectangles*) value);
	}
	else if (Type::SquareShape == type) {
		printSquare((Squares*) value);
	}
	else {
		printCircle((Circles*) value);
	}
}

int main() {
	const int MAX = 100;
	int n;
	string inputData[MAX]; // Store data in each line of text file
	inputShapes("Shapes.txt", n, inputData);

	void** a = new void*[MAX]; // Store struct
	Type* types = new Type[MAX];
	splitShapes(n, inputData, a, types);
	/*Squares s1;
	s1.a = 10.01;
	a[0] = (void*)&s1;

	Squares* test = (Squares*) a[0];
	cout << test->a << endl;
	printSquare(test);
	cout << "After pass to function: " << endl;
	cout << test->a << endl;*/

	for (int i = 0; i < n; i++) {
		outputShape(a[i], types[i]);
	}
	return 0;
}