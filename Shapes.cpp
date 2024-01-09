#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits.h>

using namespace std;
// Define Pi constant
const int PI = 3.14; 
// Define struct for 3 shapes
typedef struct Rectangles {
	double w;
	double h;

	double area;
	double perimeter;
};

typedef struct Squares {
	double a;

	double area;
	double perimeter;
};

typedef struct Circles {
	double r;

	double area;
	double perimeter;
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
// Calculate Area for 3 shapes
double areaRectangle(Rectangles* value) {
	return value->w * value->h;
}

double areaSquare(Squares* value) {
	return value->a * value->a;
}

double areaCircle(Circles* value) {
	return PI * (value->r * value->r);
}
// Calculate Perimeter for 3 shapes
double perimeterRectangle(Rectangles* value) {
	return 2 * (value->w + value->h); 
}

double perimeterSquare(Squares* value) {
	return 4 * value->a;
}

double perimeterCircle(Circles* value) {
	return 2 * PI * value->r;
}

void calcAreaPerimeter(void* value, Type type) {
	if (Type::RectangleShape == type) {
		Rectangles* rec = (Rectangles*) value;
		rec->area = areaRectangle(rec);
		rec->perimeter = perimeterRectangle(rec);
	}
	else if (Type::SquareShape == type) {
		Squares* sqr = (Squares*) value;
		sqr->area = areaSquare(sqr);
		sqr->perimeter = perimeterSquare(sqr);
	}
	else {
		Circles* cir = (Circles*) value;
		cir->area = areaCircle(cir);
		cir->perimeter = perimeterCircle(cir);
	}
}
// Print 3 shapes
void printRectangle(Rectangles* rec) {
	cout << "Rectangle: w=" << rec->w << ", h=" << rec->h;
	cout << " => area=" << rec->area << ", perimeter=" << rec->perimeter;
	cout << endl;
}

void printSquare(Squares* sqr) {
	cout << "Square: a=" << sqr->a;
	cout << " => area=" << sqr->area << ", perimeter=" << sqr->perimeter;
	cout << endl;
}

void printCircle(Circles* cir) {
	cout << "Circle: r=" << cir->r;
	cout << " => area=" << cir->area << ", perimeter=" << cir->perimeter;
	cout << endl;
}

void outputMinMax(void**& a, Type types[100], int n) {
	double minPer = INT_MAX, maxPer = INT_MIN;
	double minArea = INT_MAX, maxArea = INT_MIN;
	
	void* minPerShape = a[0]; Type minPerType = Type::RectangleShape;
	void* maxPerShape = a[0]; Type maxPerType = Type::RectangleShape;
	void* minAreaShape = a[0]; Type minAreaType = Type::RectangleShape;
	void* maxAreaShape = a[0]; Type maxAreaType = Type::RectangleShape;

	// find min, max, Area, Perimeter
	for (int i = 0; i < n; i++) {
		if (Type::RectangleShape == types[i]) {
			Rectangles* rec = (Rectangles*)a[i];
			if (rec->perimeter < minPer) {
				minPer = rec->perimeter;
				minPerShape = rec; minPerType = Type::RectangleShape;
			}
			if (rec->perimeter > maxPer) {
				maxPer = rec->perimeter;
				maxPerShape = rec; maxPerType = Type::RectangleShape;
			}

			if (rec->area < minArea) {
				minArea = rec->area;
				minAreaShape = rec; minAreaType = Type::RectangleShape;
			}
			if (rec->area > maxArea) {
				maxArea = rec->area;
				maxAreaShape = rec; maxAreaType = Type::RectangleShape;
			}
		}
		else if (Type::SquareShape == types[i]) {
			Squares* sqr = (Squares*)a[i];
			if (sqr->perimeter < minPer) {
				minPer = sqr->perimeter;
				minPerShape = sqr; minPerType = Type::SquareShape;
			}
			if (sqr->perimeter > maxPer) {
				maxPer = sqr->perimeter;
				maxPerShape = sqr; maxPerType = Type::SquareShape;
			}

			if (sqr->area < minArea) {
				minArea = sqr->area;
				minAreaShape = sqr; minAreaType = Type::SquareShape;
			}
			if (sqr->area > maxArea) {
				maxArea = sqr->area;
				maxAreaShape = sqr; maxAreaType = Type::SquareShape;
			}
		}
		else {
			Circles* cir = (Circles*)a[i];
			if (cir->perimeter < minPer) {
				minPer = cir->perimeter;
				minPerShape = cir; minPerType = Type::CircleShape;
			}
			if (cir->perimeter > maxPer) {
				maxPer = cir->perimeter;
				maxPerShape = cir; maxPerType = Type::CircleShape;
			}

			if (cir->area < minArea) {
				minArea = cir->area;
				minAreaShape = cir; minAreaType = Type::CircleShape;
			}
			if (cir->area > maxArea) {
				maxArea = cir->area;
				maxAreaShape = cir; maxAreaType = Type::CircleShape;
			}
		}
	}

	// Output max Perimeter
	cout << "Hinh co chu vi lon nhat: ";
	if (Type::RectangleShape == maxPerType) {
		Rectangles* rec = (Rectangles*)maxPerShape;
		cout << "Rectangle w=" << rec->w << ", h=" << rec->h << " => perimeter=" << rec->perimeter << endl;
	}
	else if (Type::SquareShape == maxPerType) {
		Squares* sqr = (Squares*)maxPerShape;
		cout << "Square a=" << sqr->a << " => perimeter=" << sqr->perimeter << endl;
	}
	else {
		Circles* cir = (Circles*)maxPerShape;
		cout << "Circle r=" << cir->r << " => perimeter=" << cir->perimeter << endl;
	}
	// Output max Area
	cout << "Hinh co dien tich lon nhat: ";
	if (Type::RectangleShape == maxAreaType) {
		Rectangles* rec = (Rectangles*)maxAreaShape;
		cout << "Rectangle w=" << rec->w << ", h=" << rec->h << " => area=" << rec->area << endl;
	}
	else if (Type::SquareShape == maxAreaType) {
		Squares* sqr = (Squares*)maxAreaShape;
		cout << "Square a=" << sqr->a << " => area=" << sqr->area << endl;
	}
	else {
		Circles* cir = (Circles*)maxAreaShape;
		cout << "Circle r=" << cir->r << " => area=" << cir->area << endl;
	}
	// Output min Perimeter
	cout << "Hinh co chu vi nho nhat: ";
	if (Type::RectangleShape == minPerType) {
		Rectangles* rec = (Rectangles*)minPerShape;
		cout << "Rectangle w=" << rec->w << ", h=" << rec->h << " => perimeter=" << rec->perimeter << endl;
	}
	else if (Type::SquareShape == minPerType) {
		Squares* sqr = (Squares*)minPerShape;
		cout << "Square a=" << sqr->a << " => perimeter=" << sqr->perimeter << endl;
	}
	else {
		Circles* cir = (Circles*)minPerShape;
		cout << "Circle r=" << cir->r << " => perimeter=" << cir->perimeter << endl;
	}
	// Output min Area
	cout << "Hinh co dien tich nho nhat: ";
	if (Type::RectangleShape == minAreaType) {
		Rectangles* rec = (Rectangles*)minAreaShape;
		cout << "Rectangle w=" << rec->w << ", h=" << rec->h << " => area=" << rec->area << endl;
	}
	else if (Type::SquareShape == minAreaType) {
		Squares* sqr = (Squares*)minAreaShape;
		cout << "Square a=" << sqr->a << " => area=" << sqr->area << endl;
	}
	else {
		Circles* cir = (Circles*)minAreaShape;
		cout << "Circle r=" << cir->r << " => area=" << cir->area << endl;
	}
}

void outputShape(void**& a, Type types[100], int n) {
	for (int i = 0; i < n; i++) {
		if (Type::RectangleShape == types[i]) {
			printRectangle((Rectangles*) a[i]);
		}
		else if (Type::SquareShape == types[i]) {
			printSquare((Squares*) a[i]);
		}
		else {
			printCircle((Circles*) a[i]);
		}
	}
	cout << endl;
}

void outputNumber(Type *types, int n) {
	int rec = 0, sqr = 0, cir = 0;
	for (int i = 0; i < n; i++) {
		if (Type::RectangleShape == types[i]) {
			rec++;
		}
		else if (Type::SquareShape == types[i]) {
			sqr++;
		}
		else {
			cir++;
		}
	}
	cout << endl;
	cout << "Thong ke cac hinh da doc" << endl;
	cout << "+ Square: " << sqr << endl;
	cout << "+ Circle: " << cir << endl;
	cout << "+ Rectangle: " << rec << endl;
}

int main() {
	const int MAX = 100;
	int n;
	string inputData[MAX]; // Store data in each line of text file
	inputShapes("Shapes.txt", n, inputData);

	void** a = new void*[MAX]; // Store struct
	Type* types = new Type[MAX];
	splitShapes(n, inputData, a, types);

	// Find area and perimeter for each item
	for (int i = 0; i < n; i++) {
		calcAreaPerimeter(a[i], types[i]);
	}

	int choice = 0;
	do {
		cout << endl;
		cout << "--------------------SHAPES PROJECT---------------------" << endl;
		cout << "=> 0: Exit" << endl;
		cout << "=> 1: Output each item" << endl;
		cout << "=> 2: Output min max of area, perimeter" << endl;
		cout << "=> 3: Output number of each item" << endl;
		cout << "=> 4: Output all infomation" << endl;
		cout << "-------------------------------------------------------" << endl;

		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 0:
			break;
		case 1:
			// Output each item
			outputShape(a, types, n);
			break;
		case 2:
			// Find min max area, perimeter items
			outputMinMax(a, types, n);
			break;
		case 3:
			// Output number of item's type
			outputNumber(types, n);
			break;
		case 4:
			outputShape(a, types, n);
			outputMinMax(a, types, n);
			outputNumber(types, n);
		}
		cout << endl;
		cout << "Press enter to continue your choice..." << endl;
		cout << "=======================================================" << endl;
		cin.ignore();
		getchar();
		system("cls");
	} while (choice != 0);
	
	return 0;
}