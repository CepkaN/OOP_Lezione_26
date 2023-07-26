#include<iostream>
#include<vector>

#include<set>
#include<map>
#include<algorithm>
#include<unordered_set>

struct Record {
	int id;
	std::string name;
	double vage;


	// фу-фу это моветон (- ~ -)
	bool operator<(const Record& ob)const {
		return id < ob.id; 
	}
	//size_t hash()const;
	bool operator==(const Record& ob)const {
		return id == ob.id && name == ob.name && vage == ob.vage;
	}
};

namespace std {
	template<>
	struct hash<Record> {
		size_t operator()(const Record& ob) const {
			// взять хэш-функцию от первого поля, сдвинуть результат на один элемент,
			// взять хэш-функцию от второго поля ; побитовое исключающее или между результатом последней хэш-функцией
			using std::size_t;
			using std::hash;

			return (hash<int>()(ob.id) ^ (hash<std::string>()(ob.name) << 1) ^ (hash<double>()(ob.vage) << 1));
		}
	};
}

void foo(){
	//std::set<Record>coll;
	std::unordered_set<Record>coll;
	coll.insert(Record());
	std::map<int, Record>coll2;
	Record a(1,"Ivan",2324.3);
	coll2.insert(/*std::pair<int, Record>*/{a.id, a});
}

int main() {
	setlocale(LC_ALL, "Russian");
	std::vector<int>data;
	data.reserve(10'000);
	
	std::cout << data.size() << ' ' << data.capacity()<<'\n';

	for (size_t i = 0; i < data.capacity(); ++i) {
		data.emplace_back(::rand() % 10000);
	}

	// цикл прохода по массиву
	// цикл поиска повторений
	// измменение счётчика уникальных элементов

	std::set<int>uniq_element;
	for (size_t i = 0; i < data.size(); ++i) {
		uniq_element.insert(data[i]);
	}
	//for (auto& it : data)uniq_element.insert(it);

	std::cout << data.size() << " всё вектор \n" << uniq_element.size() << " это сет \n";
	std::vector<int>uniq_data;
	for (auto& it : data) {
		auto find = std::find(uniq_data.begin(), uniq_data.end(), it);
		if (find == uniq_data.end()) {
			uniq_data.push_back(it);
		}
	}
	std::cout << "\n";
	std::cout << data.size() << " всё вектор \n" << uniq_data.size() << " это сет \n";

	std::vector<int>data_altre;
	data_altre.reserve(10'000);
	for (size_t i = 0; i < data_altre.capacity(); ++i) {
		data_altre.emplace_back(-5000 + ::rand() % 10000);
	}
	std::set<int>uniq_element_altre;
	for (size_t i = 0; i < data_altre.size(); ++i) {
		uniq_element_altre.insert(data_altre[i]);
	}
	std::cout << "\n";
	std::cout << data_altre.size() << " всё вектор \n" << uniq_element_altre.size() << " это сет \n";

	std::vector<int>result;
	std::set_intersection(uniq_element.begin(), uniq_element.end(), uniq_element_altre.begin(), uniq_element_altre.end(), std::back_inserter(result));

	std::cout << "\n\n";
	std::cout << result.size() << " размер \n";


	return 0;
}