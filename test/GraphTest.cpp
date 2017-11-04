
#include <gtest/gtest.h>
#include <graph.h>

TEST(Graph, computeShortestPathWithMaxNbVerticesTest) {

	int paths[15][15] = {{0, 2, 5, 5, 8, 128},
					   {2, 0, 4, 5, 6, 8},
					   {5, 4, 0, 2, 3, 5},
					   {5, 5, 2, 0, 128, 4},
					   {8, 6, 3, 128, 0, 3},
					   {128, 8, 5, 4, 3, 0}};

    int nextVertexTo[15][15] = {{0}};
    int totalDistanceTo[15][15] = {{0}};
    int nb_paths = 13;
    int nb_vertices = 6;

	Graph::computeShortestPathWithMaxNbVertices(paths, nextVertexTo, totalDistanceTo, nb_paths, nb_vertices);

	EXPECT_EQ(1, nextVertexTo[0][4]);
	EXPECT_EQ(12, totalDistanceTo[0][4]);
	EXPECT_EQ(4, nextVertexTo[5][3]);
	EXPECT_EQ(11, totalDistanceTo[5][3]);
}
