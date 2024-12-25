#include "BankAcc.h"
#include <gtest/gtest.h>

TEST(BankAccTest, CreateAccountWithValidBalance) {
  BankAccount account("1", 100.0);
  EXPECT_DOUBLE_EQ(account.GetBalance(), 100.0);
}

TEST(BankAccTest, CreateAccountWithInvalidBalance) {
  EXPECT_THROW(BankAccount account("1", -50.0), std::invalid_argument);
}

TEST(BankAccTest, DepositValidAmount) {
  BankAccount account("1", 100.0);
  account.Deposit(50.0);
  EXPECT_DOUBLE_EQ(account.GetBalance(), 150.0);
}

TEST(BankAccTest, DepositZeroAmount) {
  BankAccount account("1", 100.0);
  EXPECT_THROW(account.Deposit(0), std::invalid_argument);
}

TEST(BankAccTest, DepositNegativeAmount) {
  BankAccount account("1", 100.0);
  EXPECT_THROW(account.Deposit(-20.0), std::invalid_argument);
}

TEST(BankAccTest, WithdrawValidAmount) {
  BankAccount account("1", 100.0);
  account.Withdraw(50.0);
  EXPECT_DOUBLE_EQ(account.GetBalance(), 50.0);
}

TEST(BankAccTest, WithdrawMoreThanBalance) {
  BankAccount account("1", 100.0);
  EXPECT_THROW(account.Withdraw(150.0), std::invalid_argument);
}

TEST(BankAccTest, WithdrawZeroAmount) {
  BankAccount account("1", 100.0);
  EXPECT_THROW(account.Withdraw(0), std::invalid_argument);
}

TEST(BankAccTest, WithdrawNegativeAmount) {
  BankAccount account("1", 100.0);
  EXPECT_THROW(account.Withdraw(-20.0), std::invalid_argument);
}

TEST(BankAccTest, BalanceAfterMultipleOperations) {
  BankAccount account("1", 100.0);
  account.Deposit(50.0);
  account.Withdraw(30.0);
  EXPECT_DOUBLE_EQ(account.GetBalance(), 120.0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}