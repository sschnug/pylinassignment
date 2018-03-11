#ifndef LA_HPP
#define LA_HPP

#include <pybind11/stl.h>
#include <iostream>
#include <chrono>
#include <lemon/smart_graph.h>
#include <lemon/network_simplex.h>

using namespace lemon;
typedef SmartDigraph Graph;
typedef int LimitValueType;

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

std::pair<int, double> linear_assignment(std::vector<std::vector<double> >& cost_matrix)
{
    // TODO check if it's valid input

    auto t0 = Time::now();

    unsigned int M = cost_matrix.size();
    unsigned int N = cost_matrix[0].size();

    Graph g;
    Graph::ArcMap<LimitValueType> u_i(g), c_i(g);
    Graph::NodeMap<LimitValueType> s_i(g);
    g.reserveNode(M + N + 1);
    g.reserveArc(M*N + N);

    // sink node (only needed because of potential rectangular / asymmetric prob)
    Graph::Node sink_node = g.addNode();
    s_i[sink_node] = -cost_matrix.size();

    // other nodes
    std::vector<Graph::Node> workers(M);
    std::vector<Graph::Node> tasks(N);

    for(int m=0; m<M; ++m)
    {
      workers[m] = g.addNode();
      s_i[workers[m]] = 1;
    }

    for(int n=0; n<N; ++n)
      tasks[n] = g.addNode();

    // arcs
    for(int n=0; n<N; ++n)
    {
      Graph::Arc arc = g.addArc(tasks[n], sink_node);
      u_i[arc] = 1;
      c_i[arc] = 0;
    }

    for(int m=0; m<M; ++m)
      for(int n=0; n<N; ++n)
      {
        Graph::Arc arc = g.addArc(workers[m], tasks[n]);
        u_i[arc] = 1;
        c_i[arc] = cost_matrix[m][n];
      }

    // NetworkSimplex
    NetworkSimplex<Graph> ns(g);
    ns.upperMap(u_i).costMap(c_i).supplyMap(s_i);
    auto t1 = Time::now();
    int status = ns.run(NetworkSimplex<Graph>::FIRST_ELIGIBLE);
    auto t2 = Time::now();

    long time_build_network = std::chrono::duration_cast<ms>(t1 - t0).count();
    long time_ns = std::chrono::duration_cast<ms>(t2 - t1).count();

    std::cout << "Time (ns): network setup: " << time_build_network << std::endl;
    std::cout << "Time (ns): network simplex: " <<  time_ns << std::endl;

    return std::make_pair(status, ns.totalCost());
}

#endif
