#include "result_observer.h"

result_observer::result_observer(std::ostream& out) :
  out_(out)
{
}

void result_observer::operator()(const state_type& x, const double t)
{
  format_state(x, t);
}

void result_observer::format_state(const state_type& state, const double t)
{
  out_ << t << " ";
  for(std::size_t i = 0; i < state.size(); ++i)
  {
    out_ << state[i];
    if(i != state.size() - 1)
    {
      out_ << " ; ";
    }
  }
  out_ << std::endl;
}
