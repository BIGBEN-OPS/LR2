#include <iostream>
#include <string>
#include "LinkedList.h" // Подключаем вашу реализацию связного списка

class Stack {
public:
    // Конструктор по умолчанию, создает пустой стек
    Stack();

    // Деструктор, освобождает память, занятую элементами стека
    ~Stack();

    // Проверяет, является ли стек пустым
    bool isEmpty();

    // Добавляет элемент на вершину стека
    void push(int value);

    // Удаляет и возвращает элемент с вершины стека
    int pop();

    // Возвращает элемент с вершины стека без удаления
    int peek();

private:
    LinkedList list; // Используем вашу реализацию связного списка для хранения элементов стека
};

// Конструктор по умолчанию, создает пустой стек
Stack::Stack() {}

// Деструктор, освобождает память, занятую элементами стека
Stack::~Stack() {}

// Проверяет, является ли стек пустым
bool Stack::isEmpty() {
    return list.size == 0;
}

// Добавляет элемент на вершину стека
void Stack::push(int value) {
    list.prepend(value); // Добавляем новый элемент в начало списка
}

// Удаляет и возвращает элемент с вершины стека
int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    int value = list.get(0); // Получаем значение элемента с вершины стека
    list.removeAt(0); // Удаляем элемент с вершины стека
    return value;
}

// Возвращает элемент с вершины стека без удаления
int Stack::peek() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    return list.get(0); // Возвращаем значение элемента с вершины стека
}

// Функция для проверки, является ли символ оператором
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Функция для вычисления значения постфиксного выражения
int evaluatePostfixExpression(const std::string& expression) {
    Stack stack;

    for (char c : expression) {
        if (isspace(c)) {
            continue; // Пропускаем пробелы
        } else if (isdigit(c)) {
            int operand = c - '0'; // Преобразуем символ-цифру в целое число
            stack.push(operand); // Добавляем операнд в стек
        } else if (isOperator(c)) {
            if (stack.isEmpty()) {
                throw std::runtime_error("Invalid expression");
            }

            int operand2 = stack.pop(); // Извлекаем второй операнд
            if (stack.isEmpty()) {
                throw std::runtime_error("Invalid expression");
            }

            int operand1 = stack.pop(); // Извлекаем первый операнд

            int result;
            switch (c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
            }

            stack.push(result); // Добавляем результат вычисления в стек
        } else {
            throw std::runtime_error("Invalid expression");
        }
    }

    if (stack.isEmpty()) {
        throw std::runtime_error("Invalid expression");
    }

    int finalResult = stack.pop(); // Получаем окончательный результат
    if (!stack.isEmpty()) {
        throw std::runtime_error("Invalid expression");
    }

    return finalResult;
}

int main() {
    std::string expression;
    std::cout << "Enter a postfix expression: ";
    std::getline(std::cin, expression);

    try {
        int result = evaluatePostfixExpression(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

