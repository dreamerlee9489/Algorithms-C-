#include "./05_Deque.h"
#include "./Person.h"

int main(int argc, char const *argv[])
{
    Deque<Person> deque = Deque<Person>();
    deque.en_queue(std::make_shared<Person>(10, "Alice10"));
    deque.en_queue(std::make_shared<Person>(11, "Alice11"));
    deque.en_queue(std::make_shared<Person>(12, "Alice12"));
    deque.en_queue_front(std::make_shared<Person>(13, "Alice13"));
    deque.en_queue_front(std::make_shared<Person>(14, "Alice14"));
    deque.en_queue_front(std::make_shared<Person>(15, "Alice15"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;
    size_t size = deque.size();
    std::cout << "size=" << size << "\n";
    std::cout << "----------Test de_queue()----------\n";
    for(size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.de_queue();
    std::cout << "----------Test de_queue_rear()----------\n";
    for (size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.de_queue_rear();
    std::cout << "size=" << deque.size() << "\n";
    return 0;
}
