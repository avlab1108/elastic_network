#include "result_observer.h"

result_observer::result_observer(std::ostream& out) :
  out_(out)
{
}

void result_observer::operator()(const state_type& x, const double t) const
{
  out_ << t << " ";
  for(std::size_t i = 0; i < x.size(); ++i)
  {
    out_  << x[i];
    if(i != x.size() - 1)
    {
      out_ << " ";
    }
  }
  out_ << std::endl;
}
