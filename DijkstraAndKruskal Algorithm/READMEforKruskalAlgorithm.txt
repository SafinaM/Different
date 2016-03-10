//Task: to write Kruskal's algoriphm. The program consist of 3 classes. One of them class Vertex . The second class is Graph consists of the vector which included the first class as argument.
The Kruskul's algorithm is the separate class. It was done because of many reasons. One of them is to add new code to the existing one
is more easy. All edges of input graph are sorted with the help of multimap Edge. When we begin to form paths in Vec.vecPath by
adding of the cheapest edge. The vertices of the graph we add to the vertex vector Vec.vecV. They must be non-repeating.
When the number of edges and vertices are equal && >= 3 the cycle exists. In this case the last edge is deleting. 
We continue to add edges while they are not finished. On the exit we'll get one vecPath which will include the MST - minimum
spanning tree.
Besides in this variant I added the way of reading matrix from the file. I placed all simple functions in the Class Graph and
overloaded operator << for class The Vertex. 
I will be grateful to you for the noticed errors and sensible comments. I'm not a wizard, I'm just studying. Please, put
input_data_file in the root folder.
You also can find exit file in the root folder (folder with the project).