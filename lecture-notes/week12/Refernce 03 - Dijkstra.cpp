#include <fstream>
#include <sstream>

template <typename T>
auto read_graph_from_file() {
	ifstream infile("USA-road-d.NY.gr.txt");
	unsigned num_vertices, num_edges;
	string line;
	while (getline(infile, line)) {
		if (line[0] == 'p') {
			istringstream iss(line);
			char p;
			string sp;
			iss >> p >> sp >> num_vertices >> num_edges;
			cout << "Number of vertices: " << num_vertices << endl;
			cout << "Number of edges: " << num_edges << endl;
			break;
		}
	}
	Graph<T> G(num_vertices + 1);
	while (getline(infile, line)) {
		if (line[0] == 'a') {
			istringstream iss(line);
			char p;
			unsigned source_vertex, dest_vertex;
			T weight;
			iss >> p >> source_vertex >> dest_vertex >> weight;
			G.add_edge(Edge<T>{source_vertex, dest_vertex, weight});
		}
	}
	infile.close();
	return G;
}

int main() {
	using T = unsigned;
	auto G = read_graph_from_file<T>();
	//cout << "Example graph" << endl;
	//cout << G << endl;
	auto shortest_path = CDIJKSTRA<T>(G, 913, 542);
	cout << endl << "The shortest path between the vertex 913 and 542" << endl;
	for (auto v : shortest_path)
		cout << v << ' ';
	cout << endl;
    return 0;
}