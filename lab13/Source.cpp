#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum class Color {
		WHITE,
		YELLOW,
		BLACK
};

class Animal {
public:
		virtual string emitSound() const = 0;

		Animal(const string& name, int height, float weight, Color color): name(name), height(height), weight(weight), color(color) { }

		vector<string> getPreferences() const { return preferences; }

		void addPreference(const string& preference) { preferences.emplace_back(preference); }

		virtual ~Animal() noexcept = default;

protected:
		string name;
		int height;
		float weight;
		Color color;
		vector<string> preferences;
};

class Lion : public Animal {
public:
		Lion(const string& name, int height, float weight, Color color): Animal(name, height, weight, color) {}

		string emitSound() const override {
				return "lion";
		}

		~Lion() {
				cout << "Destroying lion" << endl;
		}
};

class Dog : public Animal {
public:
		Dog(const string& name, int height, float weight, Color color) : Animal(name, height, weight, color) {}

		string emitSound() const override {
				return "dog";
		}

		~Dog() {
				cout << "Destroying dog" << endl;
		}
};

class CageAlreadyFilledException : public exception {
public:
		CageAlreadyFilledException(): exception() {}
};

class Zoo {
public:
		Zoo(const string& name): name(name) {}

		void addAnimal(const string& cageNumber, Animal* animal) {
				if (animals.find(cageNumber) != animals.end()) {
						throw CageAlreadyFilledException();
				}

				animals[cageNumber] = animal;
		}

		void printAllSoundAndCageNumbers() const {
				for (auto& cage : animals) {
						cout << "Cage " << cage.first << " emits sound " << cage.second->emitSound() << endl;
				}
		}

		vector<Animal*> filterByPreference(const string& preference) const {
				vector<Animal*> result;

				for (auto& cage : animals) {
						auto preferences = cage.second->getPreferences();
						for (string& currPreference : preferences) {
								if (currPreference != preference) {
										continue;
								}

								result.push_back(cage.second);
								break;
						}
				}

				return result;
		}

private:
		string name;
		map<string, Animal*> animals;
};

int main() {
		Animal* lion = new Lion("lion", 100, 150.0f, Color::YELLOW);
		cout << lion->emitSound() << endl;
		
		unique_ptr<Animal> lion2(new Lion("lion2", 100, 150.0f, Color::YELLOW));
		cout << "Lion2 does " << lion2->emitSound() << endl;
		
		Animal* dog = new Dog("dog", 50, 10.0f, Color::BLACK);
		cout << "Dog does " << dog->emitSound() << endl;

		vector<Animal*> animals;
		animals.push_back(lion);
		animals.push_back(lion2.get());
		animals.push_back(dog);

		cout << "Using iterators" << endl;
		for (vector<Animal*>::iterator it = animals.begin(); it != animals.end(); ++it) {
				cout << (*it)->emitSound() << endl;
		}
		cout << "*********************" << endl << endl;

		cout << "Using range based for loops" << endl;
		for (auto& animal : animals) {
				cout << animal->emitSound() << endl;
		}
		cout << "*********************" << endl << endl;

		Zoo zoo("zoo1");
		zoo.addAnimal("cage1", dog);
		zoo.addAnimal("cage2", lion);
		zoo.printAllSoundAndCageNumbers();

		cout << "*********************" << endl << endl;
		dog->addPreference("food");
		auto filteredResult = zoo.filterByPreference("food");
		for (auto& animal : filteredResult) {
				cout << "Animal does " << animal->emitSound() << endl;
		}
		cout << "*********************" << endl << endl;

		cout << "*********************" << endl << endl;
		try {
				zoo.addAnimal("cage2", lion);
		}
		catch (CageAlreadyFilledException& ex) {
				cout << "Exception has occured when adding animal" << endl;
		}
		cout << "*********************" << endl << endl;

		delete dog;
		delete lion;

		int arr[] = {10, 10, 20, 20, 20, 30};
		set<int> set1;
		for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
				set1.insert(arr[i]);
		}

		for (auto& value : set1) {
				cout << "value " << value << endl;
		}

		return 0;
}