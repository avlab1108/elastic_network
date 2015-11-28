#include "user_settings.h"

user_settings::user_settings() :
  excitation_time_(0),
  time_limit_(0),
  fs_(0),
  simulations_count_(0)
{
}

void user_settings::set_network(const network& net)
{
  net_ = net;
}

const network& user_settings::get_network() const
{
  return net_;
}

void user_settings::set_excitation_time(const std::size_t time)
{
  excitation_time_ = time;
}

const std::size_t user_settings::get_excitation_time() const
{
  return excitation_time_;
}

void user_settings::set_time_limit(const std::size_t limit)
{
  time_limit_ = limit;
}

const std::size_t user_settings::get_time_limit() const
{
  return time_limit_;
}

void user_settings::set_time_step(const double step)
{
  time_step_ = step;
}

const double user_settings::get_time_step() const
{
  return time_step_;
}

void user_settings::set_fs(const double fs)
{
  fs_ = fs;
}

const double user_settings::get_fs() const
{
  return fs_;
}

void user_settings::set_simulations_count(const std::size_t sim_count)
{
  simulations_count_ = sim_count;
}

const std::size_t user_settings::get_simulations_count() const
{
  return simulations_count_;
}

void user_settings::set_force_application_nodes(const std::vector<std::size_t>& nodes)
{
  force_application_nodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::get_force_application_nodes() const
{
  return force_application_nodes_;
}

void user_settings::set_visualization_nodes(const std::vector<std::size_t>& nodes)
{
  visualization_nodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::get_visualization_nodes() const
{
  return visualization_nodes_;
}

std::ostream& operator<<(std::ostream& out, const user_settings& s)
{
  out << "Network size: " << s.get_network().get_size() << std::endl;
  out << "Network link count: " << s.get_network().get_links().size() << std::endl;
  out << "Fs: " << s.get_fs() << std::endl;
  out << "Sim count: " << s.get_simulations_count() << std::endl;
  out << "Excitation time: " << s.get_excitation_time() << std::endl;
  out << "Time limit: " << s.get_time_limit() << std::endl;
  out << "Time step: " << s.get_time_step() << std::endl;
  return out;
}
