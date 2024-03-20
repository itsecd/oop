#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Account {
private:
  int _balance;
  std::mutex _balance_mutex;

public:
  Account(int balance) : _balance(balance) { }
  Account(const Account&) = delete;

  Account& operator=(const Account&) = delete;

  int balance() const noexcept {
    return _balance;
  }

  bool withdraw(int value) {
    std::lock_guard<std::mutex> lg(_balance_mutex);

    if (_balance < value) {
      return false;
    }

    _balance -= value;
    return true;
  }
};

void my_consumer(Account& account, size_t& value) {
  while (account.withdraw(1)) {
    ++value;
  }
}

int main() {
  Account account(1000000);

  const size_t tn = 4;

  std::vector<size_t> cs(tn, 0);
  std::vector<std::thread> ts;
  ts.reserve(tn);
  for (size_t i = 0; i < tn; ++i) {
    std::thread t(my_consumer, std::ref(account), std::ref(cs[i]));
    ts.push_back(std::move(t));
  }

  for (auto& t : ts) {
    t.join();
  }

  std::cout << account.balance() << '\n';
  for (auto c : cs) {
    std::cout << c << '\n';
  }
}
