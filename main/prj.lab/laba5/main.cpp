#include <iostream>
#include"laba5.cpp"

int main() {
    std::shared_ptr<Database> userDb = std::make_shared<DatabaseProxy>(false);
    std::shared_ptr<Database> adminDb = std::make_shared<DatabaseProxy>(true);

    userDb->query("SELECT * FROM users"); // Вывод: Access denied. Query cannot be executed.
    adminDb->query("SELECT * FROM users"); // Вывод: Executing query: SELECT * FROM users

    //Адаптер
    ExternalLogger externalLogger;
    LoggerAdapter loggerAdapter(&externalLogger); // Передаем указатель на внешний логгер

    loggerAdapter.log("This is a test message."); // Вывод: External log: This is a test message.

    
    //Мост
    std::shared_ptr<Device> monitor = std::make_shared<Monitor>();
    std::shared_ptr<Device> printer = std::make_shared<Printer>();

    std::shared_ptr<Output> textOnMonitor = std::make_shared<TextOutput>(monitor);
    std::shared_ptr<Output> textOnPrinter = std::make_shared<TextOutput>(printer);

    textOnMonitor->render("Hello, world!"); // Вывод: Displaying on monitor: Text: Hello, world!
    textOnPrinter->render("Hello, world!"); // Вывод: Printing to paper: Text: Hello, world!

    std::shared_ptr<Output> imageOnMonitor = std::make_shared<ImageOutput>(monitor);
    imageOnMonitor->render("101010101"); // Вывод: Displaying on monitor: Image: [Binary data: 101010101]

    return 0;
}