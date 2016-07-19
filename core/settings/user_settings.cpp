#include "user_settings.h"

user_settings::user_settings() :
  excitation_time_(0),
  fs_(0),
  simulations_count_(0),
  forces_dynamic_(false)
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

std::size_t user_settings::get_excitation_time() const
{
  return excitation_time_;
}

void user_settings::set_fs(const double fs)
{
  fs_ = fs;
}

double user_settings::get_fs() const
{
  return fs_;
}

void user_settings::set_simulations_count(const std::size_t sim_count)
{
  simulations_count_ = sim_count;
}

std::size_t user_settings::get_simulations_count() const
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

void user_settings::set_excitation_time_step(const double step)
{
  excitation_time_step_ = step;
}

double user_settings::get_excitation_time_step() const
{
  return excitation_time_step_;
}

void user_settings::set_relaxation_time_step_spec(const relaxation_time_step_spec& step_spec)
{
  relaxation_time_step_spec_ = step_spec;
}

const relaxation_time_step_spec& user_settings::get_relaxation_time_step_spec() const
{
  return relaxation_time_step_spec_;
}

void user_settings::set_force_application_nodes(const std::vector<std::size_t>& nodes)
{
  force_application_nodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::get_force_application_nodes() const
{
  return force_application_nodes_;
}

void user_settings::set_forces_dynamic(const bool dynamic)
{
  forces_dynamic_ = dynamic;
}

bool user_settings::get_forces_dynamic() const
{
  return forces_dynamic_;
}

void user_settings::set_network_file_path(const std::string& path)
{
  network_file_path_ = path;
}

const std::string& user_settings::get_network_file_path() const
{
  return network_file_path_;
}

void user_settings::set_equilibrium_state_spec(const equilibrium_state_spec& state)
{
	equilibrium_state_spec_ = state;
}

const boost::optional<equilibrium_state_spec>& user_settings::get_equilibrium_state_spec() const
{
	return equilibrium_state_spec_;
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
