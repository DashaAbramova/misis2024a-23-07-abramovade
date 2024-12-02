#include <iostream>
#include "laba3.cpp"
#include <memory>
#include <string>

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->someMethod();
    std::cout << std::endl;

    // Создание фабрики для консольного логгера
    std::unique_ptr<LoggerFactory> consoleFactory = std::make_unique<ConsoleLoggerFactory>();
    consoleFactory->logMessage("Hello, console!");

    // Создание фабрики для файлового логгера
    std::unique_ptr<LoggerFactory> fileFactory = std::make_unique<FileLoggerFactory>();
    fileFactory->logMessage("Hello, file!");
    std::cout << std::endl;


    WindowsFactory windowsFactory;
    Application app1(&windowsFactory);
    app1.paint();

    MacFactory macFactory;
    Application app2(&macFactory);
    app2.paint();
    std::cout << std::endl;

    HawaiianPizzaBuilder builder;
    PizzaDirector director(&builder);

    director.constructPizza();
    Pizza pizza = builder.getResult();

    std::cout << pizza << std::endl;

    return 0;
}