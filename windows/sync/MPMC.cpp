#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>

void print(std::ostream& s)
{
  std::cout << s.rdbuf();
  std::cout.flush();
  s.clear();
}

const int num_producers = 5;
const int num_consumers = 10;
const int producer_delay_to_produce = 10;
const int consumer_delay_to_consume = 30;

const int consumer_max_wait_time = 200;

const int max_production = 10;
const int max_products = 10;

std::atomic<int> num_producers_working(0);
std::stack<int> products;
std::mutex xmutex;

std::condition_variable NOT_FULL;
std::condition_variable NOT_EMPTY;

void produce(int producer_id)
{
  std::unique_lock<std::mutex> lock(xmutex);
  int product;

  NOT_FULL.wait(lock, [] { return products.size() != max_products; });
  product = products.size();
  products.push(product);

  std::stringstream sin;
  print(sin << "Producer " << producer_id << " produced " << product << "\n");
  NOT_EMPTY.notify_all();
}

void consume(int consumer_id)
{
  std::unique_lock<std::mutex> lock(xmutex);
  int product;

  if(NOT_EMPTY.wait_for(lock, std::chrono::milliseconds(consumer_max_wait_time),
                        [] { return products.size() > 0; }))
  {
    product = products.top();
    products.pop();

    std::stringstream sin;
    print(sin << "Consumer " << consumer_id << " consumed " << product << "\n");
    NOT_FULL.notify_all();
  }
}

void producer(int id)
{
  ++num_producers_working;
  for(int i = 0; i < max_production; ++i)
  {
    produce(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(producer_delay_to_produce));
  }

  std::stringstream sin;
  print(sin << "Producer " << id << " has exited\n");
  --num_producers_working;
}

void consumer(int id)
{
  while(num_producers_working == 0)
  {
    std::this_thread::yield();
  }

  while(num_producers_working != 0 || products.size() > 0)
  {
    consume(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(consumer_delay_to_consume));
  }

  std::stringstream sin;
  print(sin << "Consumer " << id << " has exited\n");
}


int main()
{
  std::vector<std::thread> producers_and_consumers;

  for(int i = 0; i < num_producers; ++i)
  {
    producers_and_consumers.push_back(std::thread(producer, i));
  }

  for(int i = 0; i < num_consumers; ++i)
  {
    producers_and_consumers.push_back(std::thread(consumer, i));
  }

  for(auto& t : producers_and_consumers)
  {
    t.join();
  }
}