
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <iostream>


namespace Graph {

	void computePathsFrom(int source, int nextVertexTo[15][15], int totalDistanceTo[15][15], int paths[15][15], const std::vector<std::vector<int>> & selectedEdgesByVertices) {
		std::queue<int> nextVertices;
		bool visited[15] = {false};

		nextVertices.push(source);
		visited[source] = true;

		

		while (!nextVertices.empty()) {
			int nextVertex = nextVertices.front();
			nextVertices.pop();

			

			for (int adjVertex : selectedEdgesByVertices[nextVertex]) {
				if (totalDistanceTo[source][adjVertex] == 0) {
					if (!visited[adjVertex]) {
						nextVertexTo[source][adjVertex] = (source == nextVertex) ? adjVertex : nextVertexTo[source][nextVertex];
						totalDistanceTo[source][adjVertex] = totalDistanceTo[source][nextVertex] + paths[nextVertex][adjVertex] + 1;
						nextVertices.push(adjVertex); 
						visited[adjVertex] = true;
					}
				}
			}

		}
	}
	
	void computeShortestPathWithMaxNbVertices(int paths[15][15], int nextVertexTo[15][15], int totalDistanceTo[15][15], int nb_paths, int nb_vertices) {
		std::vector<std::tuple<int, int, int>> edges(nb_paths);
		for (int i = 0; i < nb_vertices; ++i) {
			for (int j = 0; j < nb_vertices; ++j) {
				edges.push_back(std::make_tuple(i, j, paths[i][j]));
			}
		}

		std::sort(edges.begin(), edges.end(), [](std::tuple<int, int, int> t, std::tuple<int, int, int> t2) { return std::get<2>(t) < std::get<2>(t2); });


		std::vector<std::vector<int>> selectedEdgesByVertices;
		for (int i = 0; i < nb_vertices; ++i) {
			selectedEdgesByVertices.push_back(std::vector<int>());
		}

		bool visited[15] = {false};
		visited[0] = true;
		int nb_connected = 1;

		while (nb_connected < nb_vertices) {
			for (const std::tuple<int, int, int> & edge : edges) {

				int from = std::get<0>(edge);
				int to = std::get<1>(edge);

				if ((from != to) && ((visited[from] && !visited[to]) || (visited[to] && !visited[from]))) {
					selectedEdgesByVertices[from].push_back(to);
					selectedEdgesByVertices[to].push_back(from);

					++nb_connected;
					visited[from] = true;
					visited[to] = true;
					break;
				}
			}
		}
		
		for (int source = 0; source < nb_vertices; ++source) {
			computePathsFrom(source, nextVertexTo, totalDistanceTo, paths, selectedEdgesByVertices);
		}

		
	}
}