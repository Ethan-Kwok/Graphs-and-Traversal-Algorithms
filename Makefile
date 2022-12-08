all : UndirectedGraphRepresentation

UndirectedGraphRepresentation : UndirectedGraphRepresentation.c
	gcc -Wall -Werror -fsanitize=address -std=c11 UndirectedGraphRepresentation.c -o UndirectedGraphRepresentation 

WeightedDirectedGraphRepresentation : WeightedDirectedGraphRepresentation.c
	gcc -Wall -Werror -fsanitize=address -std=c11 WeightedDirectedGraphRepresentation.c -o WeightedDirectedGraphRepresentation 

BreadthFirstSearch : BreadthFirstSearch.c
	gcc -Wall -Werror -fsanitize=address -std=c11 BreadthFirstSearch.c -o fBreadthFirstSearchirst 

DepthFirstSearch : DepthFirstSearch.c
	gcc -Wall -Werror -fsanitize=address -std=c11 DepthFirstSearch.c -o DepthFirstSearch 

ShortestPathDAG : ShortestPathDAG.c
	gcc -Wall -Werror -fsanitize=address -std=c11 ShortestPathDAG.c -o ShortestPathDAG 

DijkstrasAlgorithm : DijkstrasAlgorithm.c
	gcc -Wall -Werror -fsanitize=address -std=c11 DijkstrasAlgorithm.c -o DijkstrasAlgorithm 