#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <vector>

// Интерфейс стратегии сортировки
class SortingStrategy {
public:
    virtual void sort(std::vector<int>& array) = 0; // Чисто виртуальная функция
};

// Реализация сортировки пузырьком
class BubbleSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& array) override {
        std::cout << "Sorting using Bubble Sort" << std::endl;
        for (size_t i = 0; i < array.size() - 1; ++i) {
            for (size_t j = 0; j < array.size() - i - 1; ++j) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }
};

// Реализация быстрой сортировки
class QuickSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& array) override {
        std::cout << "Sorting using Quick Sort" << std::endl;
        quickSort(array, 0, array.size() - 1);
    }

private:
    void quickSort(std::vector<int>& array, int low, int high) {
        if (low < high) {
            int pi = partition(array, low, high);
            quickSort(array, low, pi - 1);
            quickSort(array, pi + 1, high);
        }
    }

    int partition(std::vector<int>& array, int low, int high) {
        int pivot = array[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                i++;
                std::swap(array[i], array[j]);
            }
        }
        std::swap(array[i + 1], array[high]);
        return (i + 1);
    }
};

// Класс сортировщика
class Sorter {
private:
    SortingStrategy* strategy;

public:
    void setStrategy(SortingStrategy* strategy) {
        this->strategy = strategy;
    }

    void sortArray(std::vector<int>& array) {
        strategy->sort(array);
    }
};



//Responsibility chain
// Перечисление типов запросов
enum class RequestType {
    TYPE_A,
    TYPE_B
};

// Класс запроса
class Request {
private:
    RequestType type;

public:
    Request(RequestType type) : type(type) {}

    RequestType getType() const {
        return type;
    }
};

// Интерфейс обработчика
class Handler {
public:
    virtual ~Handler() = default; // Виртуальный деструктор для корректного удаления производных классов
    virtual void handleRequest(const Request& request) = 0;
    virtual void setNextHandler(std::shared_ptr<Handler> nextHandler) = 0;
};

// Конкретный обработчик A
class ConcreteHandlerA : public Handler {
private:
    std::shared_ptr<Handler> nextHandler;

public:
    void handleRequest(const Request& request) override {
        if (request.getType() == RequestType::TYPE_A) {
            std::cout << "ConcreteHandlerA handled the request." << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        }
    }

    void setNextHandler(std::shared_ptr<Handler> nextHandler) override {
        this->nextHandler = nextHandler;
    }
};

// Конкретный обработчик B
class ConcreteHandlerB : public Handler {
private:
    std::shared_ptr<Handler> nextHandler;

public:
    void handleRequest(const Request& request) override {
        if (request.getType() == RequestType::TYPE_B) {
            std::cout << "ConcreteHandlerB handled the request." << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        }
    }

    void setNextHandler(std::shared_ptr<Handler> nextHandler) override {
        this->nextHandler = nextHandler;
    }
};

//Итератор
// Интерфейс итератора
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default; // Виртуальный деструктор
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// Конкретный итератор
template <typename T>
class ArrayIterator : public Iterator<T> {
private:
    std::vector<T> items; // Используем вектор для хранения элементов
    size_t position;

public:
    ArrayIterator(const std::vector<T>& items) : items(items), position(0) {}

    bool hasNext() override {
        return position < items.size();
    }

    T next() override {
        if (this->hasNext()) {
            return items[position++];
        }
        throw std::out_of_range("No more elements in the iterator."); // Генерируем исключение, если элементов больше нет
    }
};





