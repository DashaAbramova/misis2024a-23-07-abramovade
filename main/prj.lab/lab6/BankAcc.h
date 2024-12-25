#include <stdexcept>
#include <string>

class BankAccount {
private:
  std::string accountNumber;
  float balance;

public:
  BankAccount(const std::string &accountNumber, float balance = 0.0) {
    if (balance < 0) {
      throw std::invalid_argument("ValueError");
    }
    this->accountNumber = accountNumber;
    this->balance = balance;
  }

  void Deposit(float amount) {
    if (amount <= 0) {
      throw std::invalid_argument("ValueError");
    } else {
      balance += amount;
    }
  }

  void Withdraw(float amount) {
    if (amount <= 0) {
      throw std::invalid_argument("ValueError");
    } else if (amount > balance) {
      throw std::invalid_argument("ValueError. Insufficient funds");
    }
    balance -= amount;
  }

  float GetBalance() { return balance; }
};
