#pragma once

#include <list>
#include <memory>

class config;

class base_task
{
public:
  virtual ~base_task();
  virtual int execute() = 0; 

  const std::shared_ptr<config>& get_config() const;
  std::string get_work_directory() const;
};

class proxy_task : public base_task
{
public:
  proxy_task();
  proxy_task(const std::shared_ptr<base_task>& real_task);

  virtual void pre_execute();
  virtual int execute() override final;
  virtual void post_execute();

protected:
  void assign_task(const std::shared_ptr<base_task>& task);

private:
  std::shared_ptr<base_task> real_task_;
};

class complex_task : public base_task
{
public:
  virtual int execute() override;
  void add_task(const std::shared_ptr<base_task>& task);

private:
  std::list<std::shared_ptr<base_task>> tasks_;
};
