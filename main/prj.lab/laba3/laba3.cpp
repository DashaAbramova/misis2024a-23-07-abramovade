#include <iostream>
#include <memory>
#include <string>

class Singleton {
private:
    // Приватное статическое поле для хранения единственного экземпляра
    static Singleton* instance;

    // Приватный конструктор, чтобы предотвратить создание экземпляров извне
    Singleton() {
        // Инициализация, если необходимо
    }

    // Удаляем копирующий конструктор и оператор присваивания
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Статический метод для получения единственного экземпляра
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    // Другие методы класса
    void someMethod() {
        std::cout << "Метод Singleton вызван" << std::endl;
    }
};

// Определение статического члена класса
Singleton* Singleton::instance = nullptr;

// Factory method // Интерфейс для продукта (логгера)
class Logger {
public:
    virtual void log(const std::string& message) = 0; // Чисто виртуальный метод
    virtual ~Logger() = default; // Виртуальный деструктор
};

// Конкретный продукт: Файловый логгер
class FileLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Logging to file: " << message << std::endl;
    }
};

// Конкретный продукт: Консольный логгер
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Logging to console: " << message << std::endl;
    }
};

// Создатель (фабрика)
class LoggerFactory {
public:
    virtual std::unique_ptr<Logger> createLogger() = 0; // Фабричный метод
    virtual ~LoggerFactory() = default;

    // Метод, использующий фабричный метод
    void logMessage(const std::string& message) {
        std::unique_ptr<Logger> logger = createLogger();
        logger->log(message);
    }
};

// Конкретный создатель: Фабрика для файлового логгера
class FileLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<FileLogger>();
    }
};

// Конкретный создатель: Фабрика для консольного логгера
class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<ConsoleLogger>();
    }
};


// Abstract factory Интерфейс для продукта A
class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

// Конкретный продукт A1
class WindowsButton : public Button {
public:
    void paint() override {
        std::cout << "You have created a Windows button." << std::endl;
    }
};

// Конкретный продукт A2
class MacButton : public Button {
public:
    void paint() override {
        std::cout << "You have created a Mac button." << std::endl;
    }
};

// Интерфейс для продукта B
class Checkbox {
public:
    virtual void paint() = 0;
    virtual ~Checkbox() = default;
};

// Конкретный продукт B1
class WindowsCheckbox : public Checkbox {
public:
    void paint() override {
        std::cout << "You have created a Windows checkbox." << std::endl;
    }
};

// Конкретный продукт B2
class MacCheckbox : public Checkbox {
public:
    void paint() override {
        std::cout << "You have created a Mac checkbox." << std::endl;
    }
};

// Интерфейс абстрактной фабрики
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

// Конкретная фабрика 1
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// Конкретная фабрика 2
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

// Клиентский код
class Application {
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;

public:
    Application(GUIFactory* factory) {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void paint() {
        button->paint();
        checkbox->paint();
    }
};


// Продукт
class Pizza {
private:
    std::string dough;
    std::string sauce;
    std::string topping;

public:
    void setDough(const std::string& dough) {
        this->dough = dough;
    }

    void setSauce(const std::string& sauce) {
        this->sauce = sauce;
    }

    void setTopping(const std::string& topping) {
        this->topping = topping;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pizza& pizza) {
        os << "Pizza{" 
           << "dough='" << pizza.dough << '\'' 
           << ", sauce='" << pizza.sauce << '\'' 
           << ", topping='" << pizza.topping << '\'' 
           << '}';
        return os;
    }
};

// Интерфейс строителя
class PizzaBuilder {
public:
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual Pizza getResult() = 0;
    virtual ~PizzaBuilder() = default;
};

// Конкретный строитель
class HawaiianPizzaBuilder : public PizzaBuilder {
private:
    Pizza pizza;

public:
    HawaiianPizzaBuilder() = default;

    void buildDough() override {
        pizza.setDough("cross");
    }

    void buildSauce() override {
        pizza.setSauce("mild");
    }

    void buildTopping() override {
        pizza.setTopping("ham+pineapple");
    }

    Pizza getResult() override {
        return pizza;
    }
};

// Директор
class PizzaDirector {
private:
    PizzaBuilder* builder;

public:
    PizzaDirector(PizzaBuilder* builder) : builder(builder) {}

    void constructPizza() {
        builder->buildDough();
        builder->buildSauce();
        builder->buildTopping();
    }
};