# Shortest_path_algorithm

  Data Structure that has been utilized in the program includes breadth-first search algorithm and queue. Breadth-first search algorithm is utilized to traverse through the graph. For every node that has been visited, it will be ‘colored’ which is represented by making it negative. Once a node is colored, it will not be visited again. As the program traverses through the graph, it labels the minimum number of turns it requires to get to that particular node. Basically, all nodes on the graph will be visited and it takes O(N) run-time to complete it. But now the number of turns is not minimal yet. That is why the program need to repeat the whole process for every row and it eventually takes O(NM) run-time to finish computing the minimum number of turns.
Run-time Complexity:
Construction of data structure to represent input
A 2D string is first used to store the characters, then a matrix is deployed to convert the characters into integers. Therefore, O(NM) run-time is required for loading the input.
Computing the number of turns
	As mentioned above, it takes O(NM) run-time to compute the data.
