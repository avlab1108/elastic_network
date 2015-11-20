#include <from_article.h>
#include <hierarchical_potential.h>

#include <utils.h>
#include <excitor.h>
#include <relaxer.h>
#include <result_observer.h>
#include <node_chooser.h>

#include <fstream>
#include <cstdlib>
#include <memory>

class comparer : public result_observer
{
public:
  comparer(const state_type& r) :
    previous_(r)
  {
  }

  virtual void process(const state_type& r, const double t) override
  {
    for(std::size_t i = 0; i < r.size(); ++i)
    {
      std::cout << utils::distance(r[i], previous_[i]) << " ";
    }
    std::cout << "\n";
    previous_ = r;
  }
 
  void reset(const state_type& r)
  {
    previous_ = r;
  }

private:
  state_type previous_;
};

void test_from_article()
{
  network net(fa::node_positions, fa::links);
  std::vector<std::size_t> nodes;
  nodes.push_back(32);
  nodes.push_back(40);
  nodes.push_back(41);
  network::node_positions_type initial = net.get_node_positions();
  //std::shared_ptr<result_observer> obs(new stream_dumper(stream_dumper::format_type::gnuplot));
  std::shared_ptr<comparer> obs(new comparer(initial));
  excitor x(net, initial, 0.01, 100000, 0.2, nodes);
  x.set_result_observer(obs);
  x.run();
  std::cout << "relaxing" << std::endl;
  //obs->reset(net.node_positions());
  //relaxer r(net, initial, 0.01, 10000000);
  //r.set_result_observer(obs);
  //r.run();
}

void test_hierarchical_potential()
{
  network net(hp::node_positions, 3);
  std::vector<std::size_t> nodes;
  for(std::size_t i = 0; i < hp::node_positions.size(); ++i)
  {
    nodes.push_back(i);
  }
  network::node_positions_type initial = net.get_node_positions();
  //std::shared_ptr<result_observer> obs(new stream_dumper(stream_dumper::format_type::gnuplot));
  std::ofstream tout("./trajectory.txt");
  if(!tout.is_open())
  {
    return;
  }
  node_chooser chooser(net);
  std::shared_ptr<trajectory_dumper> traj_obs(new trajectory_dumper(tout, initial, chooser.choose(), 10));
  const double dt = 0.002;
  //std::shared_ptr<comparer> obs(new comparer(initial));
  excitor x(net, initial, dt, 10000, 0.2, nodes);
  //x.set_result_observer(obs);
  clock_t t1 = clock();
  x.run();
  //std::cout << "relaxing" << std::endl;
  //obs->reset(net.node_positions());
  relaxer r(net, initial, dt, 100000);
  r.set_result_observer(traj_obs);
  r.run();
  clock_t t2 = clock();
  std::cout << (double)(t2-t1)/CLOCKS_PER_SEC << std::endl;
}

int main()
{
  //test_from_article();
  test_hierarchical_potential();
  return 0;
}
