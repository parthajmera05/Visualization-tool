#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int RADIUS = 20;

class Edge {
public:
    int to;
    float weight;

    Edge(int to, float weight) : to(to), weight(weight) {}
};

class Node {
public:
    float x, y;
    vector<Edge> edges;

    Node(float x, float y) : x(x), y(y) {}
};

class State {
public:
    int node;
    float distance;

    State(int node, float distance) : node(node), distance(distance) {}

    bool operator>(const State& other) const {
        return distance > other.distance;
    }
};

void dijkstra(const vector<Node>& graph, int start, vector<float>& distances, vector<int>& previous) {
    priority_queue<State, vector<State>, greater<State>> pq;
    distances[start] = 0;
    pq.push(State(start, 0));

    while (!pq.empty()) {
        int u = pq.top().node;
        float dist = pq.top().distance;
        pq.pop();

        if (dist > distances[u]) continue;

        for (const auto& edge : graph[u].edges) {
            int v = edge.to;
            float weight = edge.weight;
            float new_dist = dist + weight;
            if (new_dist < distances[v]) {
                distances[v] = new_dist;
                previous[v] = u;
                pq.push(State(v, new_dist));
            }
        }
    }
}

void drawGraph(sf::RenderWindow& window, const vector<Node>& graph, const vector<int>& path) {
    window.clear(sf::Color::White);

    for (const auto& node : graph) {
        for (const auto& edge : node.edges) {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(node.x, node.y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(graph[edge.to].x, graph[edge.to].y), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    for (int i = 0; i < path.size() - 1; ++i) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(graph[path[i]].x, graph[path[i]].y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(graph[path[i + 1]].x, graph[path[i + 1]].y), sf::Color::Red)
        };
        window.draw(line, 2, sf::Lines);
    }

    for (const auto& node : graph) {
        sf::CircleShape circle(RADIUS);
        circle.setFillColor(sf::Color::Blue);
        circle.setOrigin(RADIUS, RADIUS);
        circle.setPosition(node.x, node.y);
        window.draw(circle);
    }

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dijkstra's Algorithm Visualization");

    vector<Node> graph = {
        Node(100, 100),
        Node(300, 100),
        Node(100, 300),
        Node(300, 300)
    };

    graph[0].edges.push_back(Edge(1, 1));
    graph[0].edges.push_back(Edge(2, 4));
    graph[1].edges.push_back(Edge(2, 2));
    graph[1].edges.push_back(Edge(3, 5));
    graph[2].edges.push_back(Edge(3, 1));

    vector<float> distances(graph.size(), numeric_limits<float>::infinity());
    vector<int> previous(graph.size(), -1);

    int start = 0;
    dijkstra(graph, start, distances, previous);

    vector<int> path;
    for (int at = 3; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        drawGraph(window, graph, path);
    }

    return 0;
}
