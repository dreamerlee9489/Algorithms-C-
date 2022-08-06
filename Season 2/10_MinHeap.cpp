#include "./10_MinHeap.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const *argv[]) {
    Person **array = new Person *[15]
            {
                    new Person(88),
                    new Person(44),
                    new Person(53),
                    new Person(41),
                    new Person(16),
                    new Person(6),
                    new Person(70),
                    new Person(18),
                    new Person(85),
                    new Person(98),
                    new Person(81),
                    new Person(23),
                    new Person(36),
                    new Person(43),
                    new Person(37)
            };
    MinHeap<Person> heap = MinHeap<Person>(array, 15);
    cout << "size=" << heap.size() << ", capacity=" << heap.capacity() << "\n";
    heap.traverse();
    delete[] array;
    return 0;
}
