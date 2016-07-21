#include <config.h>

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE IO_UNIT_TEST
#include <boost/test/unit_test.hpp>

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS

BOOST_AUTO_TEST_SUITE(io_suite)

BOOST_AUTO_TEST_CASE(user_settings_case)
{
  boost::filesystem::path current = boost::filesystem::system_complete(boost::unit_test::framework::master_test_suite().argv[0]);
  const std::string& current_dir = current.remove_filename().make_preferred().string();
  config c(current_dir + "/../config.yaml", current_dir + "/../global_config.yaml");
  const user_settings& us = c.get_user_settings();

  BOOST_CHECK(us.get_fs() == 2);
  BOOST_CHECK(us.get_simulations_count() == 100);
  BOOST_CHECK(us.get_excitation_time() == 10000);
  std::vector<std::size_t> fan = {1, 3};
  BOOST_CHECK(us.get_force_application_nodes() == fan);
  std::vector<std::size_t> vn = {0, 2};
  BOOST_CHECK(us.get_visualization_nodes() == vn);
  BOOST_CHECK(us.get_network().get_size() == 4);
  BOOST_CHECK(us.get_network().are_connected(3, 1));
  BOOST_CHECK(us.get_network().are_connected(1, 2));
  BOOST_CHECK(!us.get_forces_dynamic());
}

BOOST_AUTO_TEST_CASE(global_settings_case)
{
  boost::filesystem::path current = boost::filesystem::system_complete(boost::unit_test::framework::master_test_suite().argv[0]);
  const std::string& current_dir = current.remove_filename().make_preferred().string();
  config c(current_dir + "/../config.yaml", current_dir + "/../global_config.yaml");
  const global_settings& gs = c.get_global_settings();
  BOOST_CHECK(gs.get_results_dir() == "results");
  BOOST_CHECK(gs.get_relaxation_file_name() == "relaxation.txt");
  BOOST_CHECK(!gs.get_dump_data());
  BOOST_CHECK(gs.get_dump_step() == 10);
}

BOOST_AUTO_TEST_SUITE_END()
