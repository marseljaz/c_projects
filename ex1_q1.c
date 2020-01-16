#include "ex1_q1.h"
struct List* polygonList;
struct command currentAnalyzedCommand;
void(*functionsArr[5])(struct polygon*);
int main() {
	 
	long long int currentCommandInput;
	functionsArr[ADD_POLYGON] = &add_polygon;
	functionsArr[PRINT_PERIMETER] = &print_perimeter;
	functionsArr[PRINT_DIAGONALS] = &print_diagonals;
	functionsArr[PRINT_AREA]= &print_area;
	functionsArr[PRINT_POLYGON] = &print_polygon;
	polygonList = (struct List*)calloc(1, sizeof(struct List));

	while (true)
	{
		scanf("%llx", &currentCommandInput); // getting a long long int command
		commandAnalayzer(currentCommandInput); // analayze it and update the currentAnalyzedCommand global varible
		if (currentAnalyzedCommand.newPolygon) // check if it's new or not
		{
			(*functionsArr[ADD_POLYGON])(createNewPolygon()); // creating a new polygon
		}
		printingFunction(); // output
		if (currentAnalyzedCommand.lastCommand == true) // if it was the last command 
		{
			deleteList();
			break;
		}
	}

	return 0;
}

void commandAnalayzer(long long int currentCommand)
{
	long long int mask = 1;
	long long int mask2 = 60;
	currentAnalyzedCommand.lastCommand = currentCommand&mask; // last command or not
	currentAnalyzedCommand.newPolygon = currentCommand&(mask << 1); // new polygon or not
	int polygonTypeBit = (currentCommand&mask2)>>2; // getting polygon type
	currentAnalyzedCommand.polygonType = (enum POLYGON_TYPE)polygonTypeBit;
	currentAnalyzedCommand.printTypeAndVertices = currentCommand&(mask << 6);
	currentAnalyzedCommand.printPerimeter = currentCommand&(mask << 7);
	currentAnalyzedCommand.printArea = currentCommand&(mask << 8);
	currentAnalyzedCommand.printDiagonals = currentCommand&(mask << 9);
	mask = 15360;	//  binary 11110000000000 == 15360 (decimal) for bits 10-13
	mask = currentCommand&mask;
	mask >>= 10;
	currentAnalyzedCommand.onWho = (enum PRINTING_CHOICE)mask;
}

void add_polygon(struct polygon* Polygon)
{
	struct node* polyNode = (struct node*)calloc(1,sizeof(struct node));
	polyNode->polygonPointer = Polygon;
	polyNode->next = NULL;

	if (polygonList->head == NULL) // if the list is empty
	{
		polygonList->head = polyNode;
		polygonList->tail = polyNode;
	}
	else // the list is not empty then we need to add it to the end of list
	{
		polygonList->tail->next = polyNode;
		polygonList->tail = polyNode;
	}
}

void print_perimeter(struct polygon* polygon)
{
	printf("perimeter = %.1f\n", polygon->perimeter);
}

void print_diagonals(struct polygon* polygon)
{
	printf("diagonals = %.1f\n", polygon->diagonal);
}

void print_area(struct polygon* polygon)
{
	printf("area = %.1f\n", polygon->area);
}

void print_polygon(struct polygon* polygon)
// print the type of polygon and its vertices
{
	unsigned int verticesCount;

	switch (polygon->polygonType)
	{
	case HEXAGON:
		printf("HEXAGON ");
		verticesCount = 6;
		break;
	case HEPTAGON:
		printf("HEPTAGON ");
		verticesCount = 7;
		break;
	case OCTAGON:
		printf("OCTAGON ");
		verticesCount = 8;
		break;
	}
	int i;
	for (i = 0; i < verticesCount; i++)
	{
		printf("{%d, %d} ", polygon->vertices[i].x, polygon->vertices[i].y);
	}

	printf("\n");
}

struct polygon* createNewPolygon()
{
	struct polygon* polygon = (struct polygon*)calloc(1,sizeof(struct polygon));
	polygon->polygonType = currentAnalyzedCommand.polygonType;
	getVertices(polygon);
	calcPolygonArea(polygon);
	calcPolygonPerimeter(polygon);
	calcPolygonDiagonals(polygon);

	return polygon;
}

void getVertices(struct polygon* polygon)
{
	long long int polygonVertices1, polygonVertices2;
	char mask;
	int unsigned verticesCount = polygon->polygonType;
	int i;

	scanf("%llx", &polygonVertices1); // 4 vertices
	scanf("%llx", &polygonVertices2); // 4 vertices

	polygon->vertices = (struct point*)calloc(verticesCount, sizeof(struct point));
	mask = 0xFF;
	for (i = 0; i < 4; i++)
	{
		polygon->vertices[i].x = (int)((char)polygonVertices1&mask);
		polygonVertices1 >>= 8;
		polygon->vertices[i].y = (int)((char)polygonVertices1&mask);
		polygonVertices1 >>= 8;
	}
	mask = 0xFF;
	for (i = 4; i < verticesCount; i++)
	{
		polygon->vertices[i].x = (int)((char)polygonVertices2&mask);
		polygonVertices2 >>= 8;
		polygon->vertices[i].y = (int)((char)polygonVertices2&mask);
		polygonVertices2 >>= 8;
	}
}

void calcPolygonPerimeter(struct polygon* polygon) {
	double perimeterCalc = 0;
	unsigned int edgeCount = polygon->polygonType;
	int i;
	for (i = 0; i < edgeCount; i++)
	{
		perimeterCalc += sqrt(((double)pow((polygon->vertices[i%edgeCount].x - polygon->vertices[(i + 1) % edgeCount].x), 2) + (double)pow((polygon->vertices[i%edgeCount].y - polygon->vertices[(i + 1) % edgeCount].y), 2)));
	}
	polygon->perimeter = perimeterCalc;
}

void calcPolygonArea(struct polygon* polygon) {
	struct point A, B, C;
	double areaCalc;
	int i;
	for (i = 1; i < (polygon-> polygonType) - 1; i++)
	{
		A = polygon->vertices[0];
		B = polygon->vertices[i];
		C = polygon->vertices[i+1];
		areaCalc += calcTriangleArea(A, B, C);
	}

	polygon->area = areaCalc;
}

double calcTriangleArea(struct point A, struct point B, struct point C)
{
	//Hermon formula
	double a, b, c, s, area;
	a = calcDistance(A, B);
	b = calcDistance(B, C);
	c = calcDistance(A, C);
	s = (a + b + c) / 2;
	area = sqrt(s*(s - a)*(s - b)*(s - c));
	return area;
}

void calcPolygonDiagonals(struct polygon* polygon)
{
	double calcDiagonals = 0;
	int i,j;
	for (i = 0; i < (polygon->polygonType) - 2; i++)
	{
		for (j = i + 2; j < polygon->polygonType; j++)
		{
			if ((i != 0) || (j != (polygon->polygonType) - 1))
			{
				calcDiagonals += calcDistance(polygon->vertices[i], polygon->vertices[j]);
			}
		}
	}
	polygon->diagonal = calcDiagonals;
}

double calcDistance(struct point A, struct point B)
{
	return sqrt(((double)pow((A.x - B.x), 2) + (double)pow((A.y - B.y), 2)));
}

void printingFunction()
{
	struct node* polyNode;
	if (currentAnalyzedCommand.onWho == CURRENT_POLYGON)
	{
		if (polygonList->tail != NULL)
		{
			printByPolygonConditions(polygonList->tail->polygonPointer);
		}
		else
		{
			printf("Polygon list is empty \n");
		}
	}
	else 
	{
		polyNode = polygonList->head;
		while (polyNode != NULL)
		{
			switch (currentAnalyzedCommand.onWho)
			{
			case ALL_HEXAGONS:
				if (polyNode->polygonPointer->polygonType == HEXAGON)
				{
					printByPolygonConditions(polyNode->polygonPointer);
				}
				break;
			case ALL_HEPTAGONS:
				if (polyNode->polygonPointer->polygonType == HEPTAGON)
				{
					printByPolygonConditions(polyNode->polygonPointer);
				}
				break;
			case ALL_OCTAGONS:
				if (polyNode->polygonPointer->polygonType == OCTAGON)
				{
					printByPolygonConditions(polyNode->polygonPointer);
				}
				break;
			case ALL_POLYGONS:
				printByPolygonConditions(polyNode->polygonPointer);
				break;
			default:
				break;
			}

			polyNode = polyNode->next;
		}
	}
}

void printByPolygonConditions(struct polygon* polygon)
{
	if (currentAnalyzedCommand.printTypeAndVertices)
	{
		(*functionsArr[PRINT_POLYGON])(polygon);
		//print type and vertices
	}

	if (currentAnalyzedCommand.printPerimeter)
	{
		(*functionsArr[PRINT_PERIMETER])(polygon);
		//print perimeter
	}

	if (currentAnalyzedCommand.printArea)
	{
		(*functionsArr[PRINT_AREA])(polygon);
		//print area
	}

	if (currentAnalyzedCommand.printDiagonals)
	{
		(*functionsArr[PRINT_DIAGONALS])(polygon);
		//print diagonals length sum
	}
}

void deleteList()
{
	struct node* current = polygonList->head;
	struct node* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(polygonList);
}