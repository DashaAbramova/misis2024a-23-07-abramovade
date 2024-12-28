#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>
#include <map>
#include <optional>
#include <memory>

// Базовый класс репозитория
class UserRepository {
public:
    virtual ~UserRepository() = default;
    virtual std::optional<std::map<std::string, std::string>> getUserById(int userId) = 0;
};

// Mock-класс для репозитория
class MockUserRepository : public UserRepository {
public:
    MOCK_METHOD((std::optional<std::map<std::string, std::string>>), getUserById, (int userId), (override));
};

// Сервисный класс
class UserService {
public:
    explicit UserService(std::shared_ptr<UserRepository> repository) : repository_(std::move(repository)) {}

    std::string getUserName(int userId) {
        auto user = repository_->getUserById(userId);
        if (user.has_value()) {
            return user.value().at("name");
        } else {
            throw std::runtime_error("User not found");
        }
    }

private:
    std::shared_ptr<UserRepository> repository_;
};

// Тесты
TEST(UserServiceTest, GetUserNameSuccess) {
    // Arrange
    auto mockRepository = std::make_shared<MockUserRepository>();
    UserService service(mockRepository);

    // Act
    EXPECT_CALL(*mockRepository, getUserById(1))
        .WillOnce(testing::Return(std::map<std::string, std::string>{{"id", "1"}, {"name", "Alice"}}));

    // Assert
    std::string userName = service.getUserName(1);
    EXPECT_EQ(userName, "Alice");
}

TEST(UserServiceTest, GetUserNameNotFound) {
    // Arrange
    auto mockRepository = std::make_shared<MockUserRepository>();
    UserService service(mockRepository);

    // Act + Assert
    EXPECT_CALL(*mockRepository, getUserById(1))
        .WillOnce(testing::Return(std::nullopt));

    EXPECT_THROW({
        try {
            service.getUserName(1);
        } catch (const std::runtime_error &e) {
            EXPECT_STREQ("User not found", e.what());
            throw;
        }
    }, std::runtime_error);
}