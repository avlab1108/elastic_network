#pragma once

#include <network.h>

class node_chooser
{
public:
  typedef std::vector<std::size_t> node_numbers_type;

public:
  node_chooser(const network& net);
  const node_numbers_type& choose() const;

private:
  const network& net_;
  node_numbers_type node_numbers_;
};
