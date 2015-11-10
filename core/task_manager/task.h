#include <list>
#include <memory>

class process
{
public:
  virtual ~process();
  virtual void execute() = 0; 
};

class task
{
public:
  virtual void run();
  void add_process(const std::shared_ptr<process>& proc);

private:
  std::list<std::shared_ptr<process>> processes_;
};

