#pragma once

class excitor
{
public:
  excitor(const network& net, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes = std::vector<std::size_t>());

  virtual void run();

private:
  network net_;
  const double fs_;
  const std::size_t time_;
  const std::vector<std::size_t> nodes_;
};
