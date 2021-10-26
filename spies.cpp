#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

template <class T>
class Node
{
public:
    Node(int id) : m_id(id) {}
    Node(int id, T data) : m_id(id), m_data(data) {}
    int getId() const { return m_id; }
    T getData() const { return m_data; }
    friend std::ostream& operator<<(std::ostream& outputStream, const Node<T>& node)
    {
        outputStream << node.getData();
        return outputStream;
    }
private:
    int m_id;
    T m_data;
};

template <class V, class W>
class AdjacentNode
{
public:
    AdjacentNode(Node<V> node) : m_node(node), m_weight(1) {}
    AdjacentNode(Node<V> node, W weight) : m_node(node), m_weight(weight) {}
    friend std::ostream& operator<<(std::ostream& outputStream, AdjacentNode<V, W>& adjacentNode)
    {
        outputStream << adjacentNode.getNode().getData();
        return outputStream;
    }
    Node<V> getNode() const { return m_node; }
    W getWeight() const { return m_weight; }
private:
    Node<V> m_node;
    W m_weight;
};

template<class V, class W>
class AdjacencyList
{
public:
    AdjacencyList() : m_neighbors({}) {}
    AdjacencyList(std::vector<AdjacentNode<V, W>> neighbors) : m_neighbors(neighbors) {}
    void addAdjacentNode(const AdjacentNode<V, W>& neighbor)
    {
        m_neighbors.push_back(neighbor);
    }
    void clear()
    {
        m_neighbors.clear();
    }
    std::vector<AdjacentNode<V, W>> getNeighbors() const { return m_neighbors; }
    friend std::ostream& operator<<(std::ostream& outputStream, const AdjacencyList<V, W>& adjacencyList)
    {
        for (auto adjacentNode : adjacencyList.getNeighbors())
        {
            outputStream << adjacentNode << ", ";
        }
        return outputStream;
    }
private:
    std::vector<AdjacentNode<V, W>> m_neighbors;
};

template<class V, class W>
class Edge
{
public:
    Edge(Node<V> start, Node<V> end, W weight) : m_start(start), m_end(end), m_weight(weight) {}
    V getStartId() const { return m_start.getData(); }
    V getEndId() const { return m_end.getData(); }
    Node<V> getStart() const { return m_start; }
    Node<V> getEnd() const { return m_end; }
    W getWeight() const { return m_weight; }
private:
    Node<V> m_start;
    Node<V> m_end;
    W m_weight;
};

template<class V, class W>
class EdgeList
{
public:
    EdgeList(std::vector<Edge<V, W>> edges) : m_edges(edges) {}
    std::vector<Edge<V, W>> getEdges() const { return m_edges; }
private:
    std::vector<Edge<V, W>> m_edges;
};

template<class V, class W>
class Graph
{
public:
    Graph(std::vector<AdjacencyList<V, W>> nodes) : m_nodes(nodes) {}
    Graph(EdgeList<V, W> edges)
    {
        for (auto edge : edges.getEdges())
        {
            addEdge(edge);
        }
    }

    void addEdge(const Edge<V, W>& edge)
    {
        AdjacentNode<V, W> adjacentNode(edge.getEnd(), edge.getWeight());
        m_nodes[edge.getStartId()].addAdjacentNode(adjacentNode);
    }

    std::vector<V> breadthFirstSearch(V startingNode, V endingNode)
    {
        std::unordered_map<V, bool> visited;
        std::vector<V> path;
        path.push_back(startingNode);
        for(auto kv : m_nodes)
        {
            visited[kv.first] = false;
        }
        std::queue<V> q;
        q.push(startingNode);
        while(!q.empty())
        {
            auto topValue = q.front();
            q.pop();

            if(topValue == endingNode)
            {
                return path;
            }

            for(auto neighbor : m_nodes[topValue].getNeighbors())
            {
                V data = neighbor.getNode().getData();
                if(!visited[data])
                {
                    visited[data] = true;
                    path.push_back(data);
                    q.push(data);
                }
            }
        }
        return {};

    }
    AdjacencyList<V, W> changeNeighbors(V from, V to) {
        m_nodes[from].clear();
        m_nodes[from].addAdjacentNode(Node(0, to));
        return m_nodes[from];
    }

    friend std::ostream& operator<<(std::ostream& outputStream, const Graph<V, W>& graph)
    {
        for (auto kv : graph.getNodes())
        {
            outputStream << kv.first << " -> " << kv.second << '\n';
        }
        return outputStream;
    }
    AdjacencyList<V, W> getNeighbors(V index) const { return m_nodes[index]; }
    std::unordered_map<V, AdjacencyList<V, W>> getNodes() const { return m_nodes; }
    unsigned int size() const { return m_nodes.size(); }
private:
    std::unordered_map<V, AdjacencyList<V, W>> m_nodes;
};
int main() {
    std::ios::sync_with_stdio(false);
    int testcases;
    std::cin >> testcases;
    for(int t = 0; t < testcases; t++)
    {
        int num_red, num_blue, E;
        std::cin >> num_red >> num_blue >> E;

        std::vector<Edge<std::string, int>> edge_list;
        for(int i = 0; i < num_red - 1; i++)
        {
            std::string senior;
            std::cin >> senior;

            edge_list.emplace_back(Node<std::string>(i + 1, "R" + std::to_string(i + 2)), Node<std::string>(i, senior), 1);
        }

        std::vector<Edge<std::string, int>> blue_edge_list;
        for (int i = num_red - 1; i < num_red + num_blue - 2; i++)
        {
            std::string senior;
            std::cin >> senior;

            edge_list.emplace_back(Node<std::string>(i + 1, "B" + std::to_string(i + 3 - num_red)), Node<std::string>(i, senior), 1);
        }

        EdgeList<std::string, int> el(edge_list);
        Graph<std::string, int> g(el);
        for(int e = 0; e < E; e++)
        {
            char event;
            std::string startR, startB;
            std::cin >> event >> startR >> startB;
            if(event == 'w')
            {
                if(startR[0] == 'B')
                {
                    auto temp = startR;
                    startR = startB;
                    startB = temp;
                }
                std::vector<std::string> path = g.breadthFirstSearch(startR, "R1");
                std::vector<std::string> path2 = g.breadthFirstSearch(startR, "B1");
                int redPath1 = path.size() - 1;
                int redPath2 = path2.size() - 1;


                int bluePath1 = g.breadthFirstSearch(startB, "B1").size() - 1;
                int bluePath2 = g.breadthFirstSearch(startB, "R1").size() - 1;
                int redPath, bluePath;
                if(redPath2 > redPath1)
                {
                    bluePath = redPath2;
                }
                else
                {
                    redPath = redPath1;
                }

                if(bluePath2 > bluePath1)
                {
                    redPath = bluePath2;
                }
                else
                {
                    bluePath = bluePath1;
                }

                if(redPath == -1 && bluePath == -1)
                {
                    std::cout << "NONE" << '\n';
                }
                else
                {
                    if(redPath == bluePath)
                    {
                        std::cout << "TIE " << redPath << '\n';
                    }
                    else if(bluePath == -1 || (redPath != -1 && redPath < bluePath))
                    {
                        std::cout << "RED " << redPath << '\n';
                    }
                    else if(redPath == -1 || (bluePath != -1 && redPath > bluePath))
                    {
                        std::cout << "BLUE " << bluePath << '\n';
                    }
                }
            }
            else if(event == 'c')
            {
                g.changeNeighbors(startR, startB);
            }
        }
    }

    return 0;
}
