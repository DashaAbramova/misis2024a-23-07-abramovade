#include <iostream>
#include "laba4.cpp"

int main() {
    Sorter sorter;

    // Использование стратегии сортировки пузырьком
    BubbleSortStrategy bubbleSort;
    sorter.setStrategy(&bubbleSort);
    std::vector<int> array1 = {5, 3, 8, 4, 2};
    sorter.sortArray(array1);

    // Использование стратегии быстрой сортировки
    QuickSortStrategy quickSort;
    sorter.setStrategy(&quickSort);
    std::vector<int> array2 = {5, 3, 8, 4, 2};
    sorter.sortArray(array2);

    //Responsibility chain
    std::shared_ptr<Handler> handlerA = std::make_shared<ConcreteHandlerA>();
    std::shared_ptr<Handler> handlerB = std::make_shared<ConcreteHandlerB>();

    handlerA->setNextHandler(handlerB);

    Request requestA(RequestType::TYPE_A);
    Request requestB(RequestType::TYPE_B);

    handlerA->handleRequest(requestA); // Вывод: ConcreteHandlerA handled the request.
    handlerA->handleRequest(requestB); // Вывод: ConcreteHandlerB handled the request.

    //Итератор
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    ArrayIterator<int> iterator(numbers);

    while (iterator.hasNext()) {
        std::cout << iterator.next() << std::endl; // Выводит элементы массива
    }

    return 0;
}