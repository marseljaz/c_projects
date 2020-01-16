#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>	
#include<math.h>

#define ADD_POLYGON 0
#define PRINT_PERIMETER 1
#define PRINT_DIAGONALS 2
#define PRINT_AREA 3
#define PRINT_POLYGON 4

enum POLYGON_TYPE {HEXAGON = 6, HEPTAGON = 7, OCTAGON = 8 };
enum PRINTING_CHOICE {CURRENT_POLYGON = 0, ALL_HEXAGONS = 6, ALL_HEPTAGONS = 7, ALL_OCTAGONS = 8 , ALL_POLYGONS = 15};

struct point {
	int x;
	int y;
};

struct polygon {
	enum POLYGON_TYPE polygonType;
	double perimeter;
	double diagonal;
	double area;
	struct point* vertices;
};

struct node {
	struct polygon* polygonPointer;
	struct node* next;
};

struct List {
	struct node* head;
	struct node* tail;
};

struct command {
	bool lastCommand;
	bool newPolygon;
	enum POLYGON_TYPE polygonType;
	bool printTypeAndVertices;
	bool printPerimeter;
	bool printArea;
	bool printDiagonals;
	enum PRINTING_CHOICE onWho;
};

void deleteList();
void add_polygon(struct polygon* polygon);
void printingFunction();
void getVertices(struct polygon* polygon);
void calcPolygonArea(struct polygon* polygon);
void calcPolygonPerimeter(struct polygon* polygon);
void calcPolygonDiagonals(struct polygon* polygon);
struct polygon* createNewPolygon();
double calcTriangleArea(struct point A, struct point B, struct point C);
double calcDistance(struct point A, struct point B);
void printByPolygonConditions(struct polygon* polygon);
void print_polygon(struct polygon*);
void print_perimeter(struct polygon*);
void print_diagonals(struct polygon*);
void print_area(struct polygon*);
void commandAnalayzer(long long int currentCommand);