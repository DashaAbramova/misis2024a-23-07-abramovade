#include <iostream>
#include <memory>
#include <string>

// Интерфейс базы данных
class Database {
public:
    virtual ~Database() = default; // Виртуальный деструктор
    virtual void query(const std::string& sql) = 0;
};

// Реальная база данных
class RealDatabase : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << std::endl;
    }
};

// Прокси для базы данных
class DatabaseProxy : public Database {
private:
    std::shared_ptr<RealDatabase> realDatabase;
    bool hasAccess;

public:
    DatabaseProxy(bool hasAccess) : realDatabase(std::make_shared<RealDatabase>()), hasAccess(hasAccess) {}

    void query(const std::string& sql) override {
        if (hasAccess) {
            realDatabase->query(sql);
        } else {
            std::cout << "Access denied. Query cannot be executed." << std::endl;
        }
    }
};

//Адаптер
// Внешний логгер
class ExternalLogger {
public:
    void logMessage(const std::string& msg) {
        std::cout << "External log: " << msg << std::endl;
    }
};

// Интерфейс логгера
class Logger {
public:
    virtual ~Logger() = default; // Виртуальный деструктор
    virtual void log(const std::string& message) = 0;
};

// Адаптер для логгера
class LoggerAdapter : public Logger {
private:
    ExternalLogger* externalLogger; // Указатель на внешний логгер

public:
    LoggerAdapter(ExternalLogger* externalLogger) : externalLogger(externalLogger) {}

    void log(const std::string& message) override {
        externalLogger->logMessage(message); // Адаптируем метод
    }
};

//Мост
// Интерфейс устройства
class Device {
public:
    virtual ~Device() = default; // Виртуальный деструктор
    virtual void print(const std::string& data) = 0;
};

// Класс Монитор
class Monitor : public Device {
public:
    void print(const std::string& data) override {
        std::cout << "Displaying on monitor: " << data << std::endl;
    }
};

// Класс Принтер
class Printer : public Device {
public:
    void print(const std::string& data) override {
        std::cout << "Printing to paper: " << data << std::endl;
    }
};

// Абстрактный класс Выхода
class Output {
protected:
    std::shared_ptr<Device> device;

public:
    Output(std::shared_ptr<Device> device) : device(device) {}
    virtual ~Output() = default; // Виртуальный деструктор
    virtual void render(const std::string& data) = 0;
};

// Класс Текстового Выхода
class TextOutput : public Output {
public:
    TextOutput(std::shared_ptr<Device> device) : Output(device) {}

    void render(const std::string& data) override {
        device->print("Text: " + data);
    }
};

// Класс Выхода Изображения
class ImageOutput : public Output {
public:
    ImageOutput(std::shared_ptr<Device> device) : Output(device) {}

    void render(const std::string& data) override {
        device->print("Image: [Binary data: " + data + "]");
    }
};




