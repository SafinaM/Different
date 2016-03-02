
//Task: to write Dijkstra's algoriphm. The program consist of 2 classes. One of them class Vertex with 2 parameteres and with the vector. The second class is Graph consist of the vector which included
// the first class as argument.

#pragma warning(disable:4018)
#pragma warning(disable:4244)
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;
float density = 0.2; //you can change the density of edges
const int nTries = 2; 

class Vertex  //class of graph vertex
{
public:
	bool visit;          //show visite or not visited vertex
	float mark;          //the mark of the vertex
	vector <float> v;    // the vector for strings in the graph matrix

	Vertex()             //default constructor, initialization by zero for default case
	{
		visit = false;
		mark = FLT_MAX;
	}

	void Show()      //show of the vector on the display
	{
		int size = v.size();
		for (int i = 0; i < size; ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
};

class Graph : Vertex   //class of the graph
{
public:
	vector <Vertex> G;  //vector of the Vertex, which consist of strings of graph matrix
	Graph()            //empty constructor
	{
	}
	void Add(const Vertex &V)
	{
		G.push_back(V);
	}
	void Show()      // show graph matrix on the display
	{
		int size = G.size();
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << setw(4) << G[i].v[j] << " ";
			}
			cout << endl;
		}
	}

	void ShowMark()     //show marks on the display
	{
		int size = G.size();
		for (int i = 0; i < size; ++i)
		{
			cout << setw(4) << "mark[" << i + 1 << "] = " << G[i].mark << endl;
		}
	}

	void setVerticies(float **A, int nVertex)
	{
		for (int i = 0; i < nVertex; ++i)
		{
			Vertex *p = new Vertex;
			for (int j = 0; j < nVertex; ++j)
			{
				p->v.push_back(A[i][j]);
			}
			Add(*p);
		}
	}

	void initMark()
	{
		int size = G.size();
		for (int i = 0; i < size; ++i)      //initialization of the array mark
		{
			if (i == 0)
				G[i].mark = 0;             //the weight of the first vertex is ZERO
			else
				G[i].mark = FLT_MAX;       //maximum integer number, the weigth of other vertices is infinity
		}
	}
	void initFirstVertex()
	{
		int size = G.size();
		for (int j = 0; j < size; ++j)     //set the values of the marks for verticies
		{
			if (G[0].v[j] != 0)
			{
				G[j].mark = G[0].v[j] + G[0].mark;
			}
		}
		G[0].visit = true;
	}

	bool verifyingVisit()
	{
		int size = G.size();
		for (int i = 0; i < size; ++i)
		{
			if (G[i].visit == false)
				return false;
		}
		return true;
	}

	void Dijkstra()
	{
		float temp = FLT_MAX;
		int k = 0;
		bool tumb = false;
		float prevMark = FLT_MAX;

		int size = G.size();
		while (tumb == false)
		{
			tumb = verifyingVisit();
			for (int i = 0; i < size; ++i)   //choice of the minimum weight
			{
				if (G[i].visit == false)
				{
					if (temp < G[i].mark)
					{
						temp = temp;
						k = k;
					}
					else
					{
						temp = G[i].mark;
						k = i;
					}
				}
			}

			for (int i = 0; i < size; ++i)
	//			cout << "mark[" << i + 1 << "] = " << G[i].mark << endl;
	//		cout << "Vertex number = " << k + 1 << "; Min_mark = " << temp << endl;

			for (int j = 0; j < size; ++j)     //set the values of the marks for verticies
			{
				if (G[k].v[j] != 0)
				{
					prevMark = G[j].mark;
					G[j].mark = G[k].v[j] + G[k].mark;
					if (prevMark < G[j].mark)
						G[j].mark = prevMark;
					else
						G[j].mark = G[j].mark;
				}
			}
			G[k].visit = true;
			k = 0;
			temp = FLT_MAX;
		}
	}

	void baseProcess()
	{
		initMark();
		initFirstVertex();
		Dijkstra();
		//Show();
		//ShowMark();
	}
	float getSumMark()
	{
		float sum = 0;
		for (int i = 0; i < G.size(); ++i)
			sum += G[i].mark;
		return sum;
	}
};
float verificationInputNoneZero(float inpNumber)
{
	string temp_str = "";
	do
	{
		cin >> temp_str;                   //try to avoid of incorrect input data with the help of atof function
		inpNumber = atof(temp_str.c_str());
		if (inpNumber == 0)
			cout << "Please, re-enter the number: ";
	} while (inpNumber == 0);
	return inpNumber;
}

float verificationInputWithZero(float inpNumber)
{
	string temp_str = "";
	cin >> temp_str;                   //try to avoid of incorrect input data with the help of atof function
	inpNumber = atof(temp_str.c_str());
	return inpNumber;
}

int getVertex()
{
	int nVertex = 0;
	cout << "Enter the number of vertecies for Graph: ";
	nVertex = verificationInputNoneZero(nVertex);
	return nVertex;
}

void getGraphMatrix(float **A, int nVertex)
{
	for (int i = 0; i < nVertex; ++i)
	{
		for (int j = 0; j < nVertex; ++j)
		{
			if (i == j)
				A[i][j] = 0;
			else if (j > i)
			{
				cout << "Please, enter the element of matrix with the indexes [" << i << "]" << "[" << j << "]:";
				A[i][j] = verificationInputWithZero(A[i][j]);
			}
			else
				A[i][j] = A[j][i];
		}
	}
	//for (int i = 0; i < nVertex; ++i)
	//{
	//	for (int j = 0; j < nVertex; ++j)
	//	{
	//		cout << A[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}
float probe()
{
	srand(time(NULL));
	float weight = float(rand() % 100) / 100.0;
	return weight;
}

void getGraphMatrixRandom(float **A, int nVertex)
{
	float  weight = 0;
	srand(time(NULL));
	for (int i = 0; i < nVertex; ++i)
	{
		for (int j = 0; j < nVertex; ++j)
		{
			
			if (i == j)
				A[i][j] = 0;
			else if (j > i || j < i)
			{
				
				weight = float(rand() % 1000) / float(1000);
				if (weight < density)
					A[i][j] = float(rand() % 10+1);
				else
					A[i][j] = 0.0;
			}
			else
				A[i][j] = A[j][i];
		}
	}
	//for (int i = 0; i < nVertex; ++i)
	//{
	//	for (int j = 0; j < nVertex; ++j)
	//	{
	//		cout<<setprecision(5) << setw(8) << A[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}

int main()
{
	float fullSum = 0;
	int nVertex = 0;
	
	nVertex = getVertex();
	for (int i = 0; i < nTries; ++i)    //Monte-Carlo simulation as I understand).
	{
		if (i == 1)
			density = 0.4;
		Graph *G = new Graph;           //pointer on the class Graph
		
		float **A = new float *[nVertex];  //temporary graph matrix
		for (int i = 0; i < nVertex; ++i)
			A[i] = new float[nVertex];

		getGraphMatrixRandom(A, nVertex);
		G->setVerticies(A, nVertex);

		G->baseProcess();
		float sum = G->getSumMark();
		
		delete G;
		if (density <= 0.201)
		{
			cout << "The sum of marks of shortest average path is, density = 0.2: " << sum / nVertex << endl;
			sum = 0;
		}
		else
			cout << "The sum of marks of shortest average path is, density = 0.4: " << sum / nVertex << endl;
	}

	cin.ignore();
	cin.get();
	return 0;
}




