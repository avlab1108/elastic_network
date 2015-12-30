#include "user_settings.h"

user_settings::user_settings() :
  excitation_time_(0),
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

void user_settings::set_visualization_nodes(const std::vector<std::size_t>& nodes)
{
  visualization_nodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::get_visualization_nodes() const
{
  return visualization_nodes_;
}

void user_settings::set_time_step(const double step)
{
  time_step_ = step;
}

const double user_settings::get_time_step() const
{
  return time_step_;
}

void user_settings::set_force_application_nodes(const std::vector<std::size_t>& nodes)
{
  force_application_nodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::get_force_application_nodes() const
{
  return force_application_nodes_;
}

void user_settings::set_node_positions(const node_positions_type& node_positions)
{
  node_positions_ = node_positions;
}

const boost::optional<node_positions_type>& user_settings::get_node_positions() const
{
  return node_positions_;
}

void user_settings::set_links(const links_type& links)
{
  links_ = links;
}

const boost::optional<links_type>& user_settings::get_links() const
{
  return links_;
}

void user_settings::set_cutoff_distance(const double l0)
{
  cutoff_distance_ = l0;
}

const boost::optional<double>& user_settings::get_cutoff_distance() const
{
  return cutoff_distance_;
}

void user_settings::set_network_file_path(const std::string& path)
{
  network_file_path_ = path;
}

const boost::optional<std::string>& user_settings::get_network_file_path() const
{
  return network_file_path_;
}

std::ostream& operator<<(std::ostream& out, const user_settings& s)
{
  out << "Network size: " << s.get_network().get_size() << std::endl;
  out << "Network link count: " << s.get_network().get_links().size() << std::endl;
  out << "Fs: " << s.get_fs() << std::endl;
  out << "Sim count: " << s.get_simulations_count() << std::endl;
  out << "Excitation time: " << s.get_excitation_time() << std::endl;
  return out;
}
