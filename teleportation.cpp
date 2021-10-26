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
        outputStream << node.getId();
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

        AdjacentNode<V, W> otherAdjacentNode(edge.getStart(), edge.getWeight());
        m_nodes[edge.getEndId()].addAdjacentNode(otherAdjacentNode);

    }

    std::vector<Node<V>> breadthFirstSearch(int startingNode)
    {
        std::unordered_map<V, bool> visited;

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
    int N, Q;
    std::cin >> N >> Q;

    std::vector<Edge<int, int>> edges;
    for(int i = 1; i < N; i++)
    {
        int u, v, r;
        std::cin >> u >> v >> r;
        Edge<int, int> edge(Node(0, u), Node(1, v), r);
        edges.push_back(edge);
    }
    EdgeList<int, int> edge_list(edges);

    Graph g(edge_list);
    std::cout << g;
    for(int i = 0; i < Q; i++)
    {
        int x, y;
        std::cin >> x >> y;
    }
}
