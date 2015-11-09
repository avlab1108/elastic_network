#include "result_observer.h"

#include <iomanip>

stream_dumper::stream_dumper(format_type format, std::ostream* out) :
  format_(format),
  out_(out)
{
}

void stream_dumper::process(const state_type& r, const double t)
{
  switch(format_)
  {
    case format_type::gnuplot:
      format_for_gnuplot(r, t);
      break;
    case format_type::raw:
      format_for_raw(r, t);
      break;
    default:
      break;
  }
}

void stream_dumper::format_for_raw(const state_type& r, const double t)
{
  *out_ << t << " ";
  for(std::size_t i = 0; i < r.size(); ++i)
  {
    *out_ << r[i];
    if(i != r.size() - 1)
    {
      *out_ << " ; ";
    }
  }
  *out_ << std::endl;
}

void stream_dumper::format_for_gnuplot(const state_type& r, const double t)
{
  for(std::size_t i = 0; i < r.size(); ++i)
  {
    std::cout << std::setw(15) << std::left << r[i][0] << std::setw(15) << std::left << r[i][1] << std::setw(15) << r[i][2];
    *out_ << std::endl;
  }
  *out_ << '\n' << std::endl;
}

result_observer_wrapper::result_observer_wrapper(const network_dynamics_wrapper& dynamics) :
  dynamics_(dynamics)
{
}

void result_observer_wrapper::operator()(const state_type& r, const double t)
{
  dynamics_.prepare_for_step();
  if(observer_)
  {
    observer_->process(r, t);
  }
}

void result_observer_wrapper::set_result_observer(const std::shared_ptr<result_observer>& observer)
{
  observer_ = observer;
}
