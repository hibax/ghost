
namespace Graph {

	void computePathsFrom(int source, int** nextVertexTo, int** totalDistanceTo, int** paths, const std::vector<std::vector<int>> & selectedEdgesByVertices);
	
	void computeShortestPathWithMaxNbVertices(int paths[15][15], int nextVertexTo[15][15], int totalDistanceTo[15][15], int nb_paths, int nb_vertices);
}