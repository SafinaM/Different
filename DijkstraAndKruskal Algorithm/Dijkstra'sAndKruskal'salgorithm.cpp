//Task: to write Kruskal's algoriphm. The program consist of 3 classes. One of them class Vertex . The second class is Graph 
//consists of the vector which included the first class as argument.
//The Kruskul's algorithm is the separate class. It was done because of many reasons. One of them is to add new code to the existing one
// is more easy. All edges of input graph are sorted with the help of multimap Edge. When we begin to form paths in Vec.vecPath by
//adding of the cheapest edge. The vertices of the graph we add to the vertex vector Vec.vecV. They must be non-repeating.
//When the number of edges and vertices are equal && >= 3 the cycle exists. In this case the last edge is deleting. 
//We continue to add edges while they are not finished. On the exit we'll get one vecPath which will include the MST - minimum
//spanning tree.
//Besides in this variant I added the way of reading matrix from the file. I placed all simple functions in the Class Graph and
//overloaded operator << for class The Vertex. 
//I will be grateful to you for the noticed errors and sensible comments. I'm not a wizard, I'm just studying. Please, put
//input_data_file in the root folder.
//You also can find exit file in the root folder (folder with the project).

#pragma warning(disable:4018)
#pragma warning(disable:4244)
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;
float density = 0.2;      
const int nTries = 2;
const int n = 7;

class Vertex             //class of graph vertex
{
public:
	bool visit;          //show visite or not visited vertex
	float mark;          //the mark of the vertex
	vector <float> v;    // the vector for strings in the graph matrix
	int x, y, weight;
	int V;
	vector <Vertex> vecPath; //the vector for possible paths
	vector <int> vecV;       //the vector for vertex of graph

	Vertex()             //default constructor, initialization by zero for default case
	{
		visit = false;
		mark = FLT_MAX;
	}
	Vertex(int i, int j, int w)            //default constructor, initialization by zero for default case
	{
		x = i;
		y = j;
		weight = w;
	}
	bool verifV(int x)
	{
		for (int i = 0; i < vecV.size(); ++i)
		{
			if (x == vecV[i])
				return true;
		}
		return false;
	}

	bool verifOnCoin(int inputValue)
	{
		for (auto i = 0; i < vecPath.size(); i++)
		{
			if (vecPath[i].x == inputValue || vecPath[i].y == inputValue)
			{
				return true;
			}
		}
		return false;
	}
	friend ostream& operator<<(ostream &out, Vertex a);

};
ostream& operator <<(ostream &out, Vertex a)
{
	out  << "(" << a.x << "; " << a.y << ")"<<"  " <<"\t" << "weight = " << a.weight;
	return     out;
}

class Graph : public Vertex   //class of the graph
{
public:
	multimap <float, Vertex> Edge; //vector of the Vertex, which consist of strings of graph matrix
	vector <Vertex> Vec;    //vector of the Vertex, which consist of strings of graph matrix
	Graph()                 //empty constructor
	{
	}
	Graph(int x)            //empty constructor
	{
		Vertex *A = new Vertex;
		Vec.push_back(*A);
	}

	void Add(float a, Vertex *V)
	{
		Edge.insert(make_pair(a, *V));
	}
	void setEdges(float **A, int n)     //multimap Edge is initializing by the graph matrix elements
	{                                   //edges in multimap are sorting with their weights
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (A[i][j] != 0 && j > i)
				{
					int w = A[i][j];
					Vertex *p = new Vertex(i, j, w);
						Add(A[i][j], p);
				}
			}
		}
		for (auto it = Edge.begin(); it != Edge.end(); ++it)
		{
			cout << it->first << " " << it->second << " " << endl;
		}
	}
	void printGraphToFile()
	{
		ofstream out;
		out.open("MST.txt");
		out << "Graph: " << endl;
		for (auto it = Edge.begin(); it != Edge.end(); ++it)
		{
			out << it->first << " " << it->second << " " << endl;
		}
	}

	int verifVecOfV(int value, int k)  //returns the number of Vec where was found the value
	{
		for (int i = k; i < Vec.size(); ++i)
		{
			for (int j = 0; j < Vec[i].vecV.size(); ++j)
			{
				if (Vec[i].vecV[j] == value)
					return i;
			}
		}
		return -1;
	}

	void delLastPathElem(int i)  //deletes of the last element vecPath in Vec[i]
	{
		Vec[i].vecPath.pop_back();
	}

	bool verifSizes(int i)       //compares the vecPath and vecV sizes, if they are aqual and >=3 the cycle is existing
	{
		if (Vec[i].vecV.size() == Vec[i].vecPath.size() && Vec[i].vecV.size() >= 3 && Vec[i].vecPath.size() >= 3)
			return true;
		return false;
	}

	void AddVertex(const Vertex &vertex)
	{
		Vec.push_back(vertex);
	}
	void Show()      // show graph matrix on the display
	{
		int size = Vec.size();
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << setw(4) << Vec[i].v[j] << " ";
			}
			cout << endl;
		}
	}

	void ShowMark()     //show marks on the display
	{
		int size = Vec.size();
		for (int i = 0; i < size; ++i)
		{
			cout << setw(4) << "mark[" << i + 1 << "] = " << Vec[i].mark << endl;
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
			AddVertex(*p);
		}
	}

	void initMark()
	{
		int size = Vec.size();
		for (int i = 0; i < size; ++i)      //initialization of the array mark
		{
			if (i == 0)
				Vec[i].mark = 0;             //the weight of the first vertex is ZERO
			else
				Vec[i].mark = FLT_MAX;       //maximum integer number, the weigth of other vertices is infinity
		}
	}
	void initFirstVertex()
	{
		int size = Vec.size();
		for (int j = 0; j < size; ++j)     //set the values of the marks for verticies
		{
			if (Vec[0].v[j] != 0)
			{
				Vec[j].mark = Vec[0].v[j] + Vec[0].mark;
			}
		}
		Vec[0].visit = true;
	}

	bool verifyingVisit()
	{
		int size = Vec.size();
		for (int i = 0; i < size; ++i)
		{
			if (Vec[i].visit == false)
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

		int size = Vec.size();
		while (tumb == false)
		{
			tumb = verifyingVisit();
			for (int i = 0; i < size; ++i)   //choice of the minimum weight
			{
				if (Vec[i].visit == false)
				{
					if (temp < Vec[i].mark)
					{
						temp = temp;
						k = k;
					}
					else
					{
						temp = Vec[i].mark;
						k = i;
					}
				}
			}

			for (int i = 0; i < size; ++i)
	//		cout << "mark[" << i + 1 << "] = " << G[i].mark << endl;
	//		cout << "Vertex number = " << k + 1 << "; Min_mark = " << temp << endl;

			for (int j = 0; j < size; ++j)     //set the values of the marks for verticies
			{
				if (Vec[k].v[j] != 0)
				{
					prevMark = Vec[j].mark;
					Vec[j].mark = Vec[k].v[j] + Vec[k].mark;
					if (prevMark < Vec[j].mark)
						Vec[j].mark = prevMark;
					else
						Vec[j].mark = Vec[j].mark;
				}
			}
			Vec[k].visit = true;
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
		for (int i = 0; i < Vec.size(); ++i)
			sum += Vec[i].mark;
		return sum;
	}
	void setGraphMatrixRandom(float **A, int nVertex)
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
						A[i][j] = float(rand() % 10 + 1);
					else
						A[i][j] = 0.0;
				}
				else
					A[i][j] = A[j][i];
			}
		}
	}
	void setGraphMatrix(float **A, int nVertex)
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


	void setGraphMatrix(float **A)
	{
		float V[n][n] =               //first matrix for verification by default
		{
			{ 0, 7, 0, 5, 0, 0, 0 },
			{ 7, 0, 8, 9, 7, 0, 0 },
			{ 0, 8, 0, 0, 5, 0, 0 },
			{ 5, 9, 0, 0, 15, 6, 0 },
			{ 0, 7, 5, 15, 0, 8, 9 },
			{ 0, 0, 0, 6, 8, 0, 11 },
			{ 0, 0, 0, 0, 9, 11, 0 },
		};

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				A[i][j] = V[i][j];
			}
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << A[i][j] << " ";
			}
			cout << endl;
		}
	}
	void setGraphMatrixFromFile(float **A, int nVertex)
	{
		for (int i = 0; i < nVertex; ++i)
		{
			for (int j = 0; j < nVertex; ++j)
			{
					A[i][j] = 0;
			}
		}
		ifstream in;
		in.open("input.txt", ios_base::in);
		in >> nVertex;
		int i = 0, j = 0;
		while (!in.eof())
		{
			in >> i;
			in >> j;
			in >> A[i][j];
		}
		in.close();

		for (int i = 0; i < nVertex; ++i)
		{
			for (int j = 0; j < nVertex; ++j)
			{
				cout << setw(3) << A[i][j] << " ";
			}
			cout << endl;
		}
	}
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
		cout << "Enter the number of vertices for Graph: ";
		nVertex = verificationInputNoneZero(nVertex);
		return nVertex;
	}
	int getVertexFromFile()
	{
		int nVertex = 0;
		fstream in;
		in.open("input.txt", ios_base :: in);
		if (!in.is_open()) // 
			cout << "File could not be opened!\n"; // 
		in >> nVertex;

		return nVertex;
	}
};

class Kruskal : public Graph
{
public:
	int sum;
	Kruskal()
	{
		sum = 0;
	}
	Kruskal(int x)            //empty constructor
	{
		Vertex *A = new Vertex;
		Vec.push_back(*A);
		sum = 0;
	}
	void findingMST()
	{
		for (auto it = Edge.begin(); it != Edge.end(); ++it)
		{
			int xV = it->second.x;                  //temporary value x of current V(x, y)
			int yV = it->second.y;                  //temporary value y of current V(x, y)
			Vertex edge = it->second;
			if (it == Edge.begin())             //if the it is the beginner
			{
				setStartVecElem(xV, yV, edge);
			}
			else if (it != Edge.begin())
			{
				int i = 0;
				for (i = 0; i < Vec.size(); ++i)
				{
					bool stateX = Vec[i].verifOnCoin(xV);   //class Vertex: temp value, if x is already existing vertex of another edge
					bool stateY = Vec[i].verifOnCoin(yV);   //class Vertex: temp value, if y is already existing vertex of another edge

					if ((stateX && !stateY) || (!stateX && stateY) || (stateX && stateY)) //if x is found and y not found or x is not found and y -is found
					{
						Vec[i].vecPath.push_back(edge);  //adding of the edge to the path's vector
						bool add = false;
						if (!stateX)  //x is not found and y can be found in another path
						{
							int iVertex = verifVecOfV(xV, i + 1);  // class Graph: verifying on coinsidence in the vector of vertexies
							int jVertex = verifVecOfV(yV, i + 1);
							if (iVertex == -1 && jVertex == -1)
							{
								Vec[i].vecV.push_back(xV);
								add = true;
							}
								       //if y is not found
						}

						if (!stateY)  //y is not found and x is found in another path
						{
							int iVertex = verifVecOfV(yV, i + 1);
							int jVertex = verifVecOfV(xV, i + 1);
							if (iVertex == -1 && jVertex == -1)
							{
								Vec[i].vecV.push_back(yV);
								add = true;
							}
						}

						if (add == true || (stateX && stateY))
						{
							if (verifSizes(i))     //if path's and vertex's vectors sizes are equal the last edge is erasing
								delLastPathElem(i);
						}
						
						if (verifVecOfV(xV, i + 1) != -1 && verifVecOfV(yV, i + 1) == -1)
						{
							int k = verifVecOfV(xV, i + 1);
							copyingPathAndVertexToCurrentVec(i, k);
							Vec.erase(Vec.begin() + k);
						}
						if (verifVecOfV(xV, i + 1) == -1 && verifVecOfV(yV, i + 1) != -1)
						{
							int k = verifVecOfV(yV, i + 1); //returns the i of Vec where was found vertex number

							copyingPathAndVertexToCurrentVec(i, k);
							Vec.erase(Vec.begin() + k);    //after coping the k-th element of Vec is erasing
						}
						break;
					}
				}
				if (i == Vec.size())  //the case when V(x, y) is not found in exasting paths, new path is creating, x and y are new!!!
				{
					setNewVecElem(xV, yV, edge);

					if (verifSizes(Vec.size() - 1))         //if path's and vertex's vectors sizes are equal the last edge is erasing
						delLastPathElem(Vec.size() - 1);
				}
			}
		}
		fullPriceOfMST();
	}
	void setNewVecElem(int xV, int yV, Vertex edge)
	{
		Vertex *A = new Vertex;                           //pointer on new Vertex object
		Vec.push_back(*A);                                //new element of Vec is pushed
		Vec[Vec.size() - 1].vecPath.push_back(edge);      //current edge is new first element of new path of last element of Vec
		Vec[Vec.size() - 1].vecV.push_back(xV);           // xV is new first element of new vecV of last element of Vec
		Vec[Vec.size() - 1].vecV.push_back(yV);           // yV is new first element of new vecV of last element of Vec
	}
	void setStartVecElem(int xV, int yV, Vertex edge)
	{
		Vec[0].vecPath.push_back(edge); // the first path is the first edge of Vec[0] int V[0].vecPath[0]
		Vec[0].vecV.push_back(xV);      // the first and the second verteces are x and y of V(x, y)
		Vec[0].vecV.push_back(yV);
	}

	void copyingPathAndVertexToCurrentVec(int i, int k)
	{
		for (int p = 0; p < Vec[k].vecPath.size(); ++p)        //all path with of Vec[k] element is coping to current V[i]
		{
			Vec[i].vecPath.push_back(Vec[k].vecPath[p]);       //the kth path is adding to the path current V[i]

			if (!Vec[i].verifV(Vec[k].vecPath[p].x))           //if the x is not found at vector of vertices        
				Vec[i].vecV.push_back(Vec[k].vecPath[p].x);    //x is adding to the vector of vertices

			if (!Vec[i].verifV(Vec[k].vecPath[p].y))            //if y is not found at vector of vertices
				Vec[i].vecV.push_back(Vec[k].vecPath[p].y);     //y is adding to the vector of vertices
		}
	}

	void showMST()
	{
		cout << "MST: " << endl;
		for (auto i = 0; i < Vec.size(); i++)
			for (auto j = 0; j < Vec[i].vecPath.size(); j++)
				cout << Vec[i].vecPath[j] << endl;
		cout <<"\n"<< "Full price of MST = " << sum << endl;
	}

	void printMSTtoFile()
	{
		ofstream out;
		out.open("MST.txt", ios_base::app);
		out << "MST: " << endl;
		for (auto i = 0; i < Vec.size(); i++)
			for (auto j = 0; j < Vec[i].vecPath.size(); j++)
				out << Vec[i].vecPath[j] << endl;
		out << "\n" << "Full price of MST = " << sum << endl;
		out.close();
	}

	void fullPriceOfMST()
	{
		for (int i = 0; i < Vec.size(); ++i)
		{
			for (int j = 0; j < Vec[i].vecPath.size(); ++j)
			{
				sum += Vec[i].vecPath[j].weight;
			}
		}
	}
};


float probe()
{
	srand(time(NULL));
	float weight = float(rand() % 100) / 100.0;
	return weight;
}


int main()
{
	string input;                       // temporary string for the input data
	cout << "Please, choose the way of graph forming:\n 1 - by hands, 2 - from file, 3 - random, else - default for verifying: ";
	cin >> input;

	float **A;
	Kruskal C(1);                       //initialization of graph, 1 vertex is creating  
	if (input == "1"|| input == "2" || input =="3")       //if input is 1 you should correctly fill graph matrix
	{
		
		int nVertex = 0;
		if(input == "1" || input == "3")
			nVertex = C.getVertex();
		else
			nVertex = C.getVertexFromFile();
		
		A = new float *[nVertex];         //initialization of A
		for (int i = 0; i < nVertex; ++i)
			A[i] = new float[nVertex];

		if (input == "1")
		{
			C.setGraphMatrix(A, nVertex);          //forming matrix by hands
		}
		else if (input == "2")
		{
			C.setGraphMatrixFromFile(A, nVertex);  //reading matrix from the file
		}
		else if (input == "3")
		{
			C.setGraphMatrixRandom(A, nVertex);   //random matrix
		}
		C.setEdges(A, nVertex);   //multimap Edge is initializing by the graph matrix elements, edges in multimap are sorting with their weights
	}

	else
	{
		A = new float *[n];
		for (int i = 0; i < n; ++i)
			A[i] = new float[n];
		C.setGraphMatrix(A);
		C.setEdges(A, n);   //multimap Edge is initializing by the graph matrix elements, edges in multimap are sorting with their weights
	}
	C.findingMST();
	C.showMST();
	C.printGraphToFile();
	C.printMSTtoFile();

	//Task 2: Dijkstra's algorithm
	//float fullSum = 0;
	//int nVertex = 0;
	//nVertex = getVertex();
	//for (int i = 0; i < nTries; ++i)    
	//{
	//	if (i == 1)
	//		density = 0.4;
	//	Graph *G = new Graph;           //pointer on the class Graph
	//	
	//	float **A = new float *[nVertex];  //temporary graph matrix
	//	for (int i = 0; i < nVertex; ++i)
	//		A[i] = new float[nVertex];

	//	setGraphMatrixRandom(A, nVertex);
	//	G->setVerticies(A, nVertex);

	//	G->baseProcess();
	//	float sum = G->getSumMark();
	//	
	//	delete G;
	//	if (density <= 0.201)
	//	{
	//		cout << "The sum of marks of shortest average path is, density = 0.2: " << sum / nVertex << endl;
	//		sum = 0;
	//	}
	//	else
	//		cout << "The sum of marks of shortest average path is, density = 0.4: " << sum / nVertex << endl;
	//}

	cin.ignore();
	cin.get();
	return 0;
}




