#include "./09_Graph.h"
#include "./Person.h"
using namespace std;
using namespace app;

int main(int argc, char const* argv[])
{
	tuple<Person*, Person*, double> array[] = {
		make_tuple(new Person(0), new Person(2), 2),
		make_tuple(new Person(0), new Person(4), 7),
		make_tuple(new Person(1), new Person(2), 3),
		make_tuple(new Person(1), new Person(5), 1),
		make_tuple(new Person(1), new Person(6), 7),
		make_tuple(new Person(2), new Person(4), 4),
		make_tuple(new Person(2), new Person(5), 3),
		make_tuple(new Person(2), new Person(6), 6),
		make_tuple(new Person(3), new Person(7), 9),
		make_tuple(new Person(4), new Person(6), 8),
		make_tuple(new Person(5), new Person(6), 4),
		make_tuple(new Person(5), new Person(7), 5)
	};
	Graph<Person> graph = Graph<Person>(false, 12, array);
	graph.print();
	return 0;
}

/*
delete 0x63ef30[0, unnamed]
delete 0x63eff0[2, unnamed]
delete 0x63eff0[4, unnamed]
delete 0x63ef30[1, unnamed]
delete 0x63eff0[5, unnamed]
delete 0x63eff0[6, unnamed]
delete 0x63ef30[3, unnamed]
delete 0x63eff0[7, unnamed]
----------vertex_map----------
[7, unnamed]
delete 0x63f190[7, unnamed]
[3, unnamed]
delete 0x63f190[3, unnamed]
[2, unnamed]
delete 0x63f190[2, unnamed]
[5, unnamed]
delete 0x63f190[5, unnamed]
[0, unnamed]
delete 0x63f190[0, unnamed]
[4, unnamed]
delete 0x63f190[4, unnamed]
[1, unnamed]
delete 0x63f190[1, unnamed]
[6, unnamed]
delete 0x63f190[6, unnamed]
----------edge_set----------
Edge [[6, unnamed], [5, unnamed], 4]
Edge [[5, unnamed], [6, unnamed], 4]
Edge [[2, unnamed], [1, unnamed], 3]
Edge [[1, unnamed], [2, unnamed], 3]
Edge [[7, unnamed], [3, unnamed], 9]
Edge [[3, unnamed], [7, unnamed], 9]
Edge [[4, unnamed], [0, unnamed], 7]
Edge [[0, unnamed], [4, unnamed], 7]
Edge [[1, unnamed], [5, unnamed], 1]
Edge [[5, unnamed], [1, unnamed], 1]
Edge [[2, unnamed], [6, unnamed], 6]
Edge [[6, unnamed], [2, unnamed], 6]
Edge [[7, unnamed], [5, unnamed], 5]
Edge [[5, unnamed], [7, unnamed], 5]
Edge [[6, unnamed], [4, unnamed], 8]
Edge [[4, unnamed], [6, unnamed], 8]
Edge [[0, unnamed], [2, unnamed], 2]
Edge [[2, unnamed], [0, unnamed], 2]
Edge [[1, unnamed], [6, unnamed], 7]
Edge [[6, unnamed], [1, unnamed], 7]
Edge [[2, unnamed], [5, unnamed], 3]
Edge [[5, unnamed], [2, unnamed], 3]
Edge [[2, unnamed], [4, unnamed], 4]
Edge [[4, unnamed], [2, unnamed], 4]
delete 0xdf8278[7, unnamed]
delete 0xdf80a8[3, unnamed]
delete 0x25b2528[2, unnamed]
delete 0xdf7178[5, unnamed]
delete 0xdf6ee8[0, unnamed]
delete 0x25b2868[4, unnamed]
delete 0x25b2ef8[1, unnamed]
delete 0xdf7758[6, unnamed]
*/
