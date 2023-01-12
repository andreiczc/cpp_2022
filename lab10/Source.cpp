#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

class Cinema {
public:
		Cinema(const char* name) {
				this->id = Cinema::CURRENT_ROOM++;
				this->name = deepCopyString(name);
				this->rooms = new int[Cinema:: DEFAULT_NO_ROOMS];
				this->noRooms = Cinema::DEFAULT_NO_ROOMS;

				for (int i = 0; i < this->noRooms; ++i) {
						this->rooms[i] = 0;
				}
		}

		~Cinema() {
				delete[] this->name;
				delete[] this->rooms;
		}

		Cinema& operator=(const Cinema& other) {
				if (this == &other) {
						return *this;
				}

				this->id = other.id;

				delete[] this->name;
				this->name = deepCopyString(other.name);

				this->noRooms = other.noRooms;

				delete[] this->rooms;
				this->rooms = deepCopyInt(other.rooms, other.noRooms);

				return *this;
		}

		Cinema(const Cinema& other) {
				this->id = other.id;
				this->name = deepCopyString(other.name);
				this->noRooms = other.noRooms;
				this->rooms = deepCopyInt(other.rooms, other.noRooms);
		}

		int operator[](int idx) {
				if (idx >= this->noRooms) {
						throw std::exception();
				}

				return this->rooms[idx];
		}

		Cinema& operator+=(const Cinema& other) {
				if (this->noRooms != other.noRooms) {
						throw std::exception();
				}

				for (int i = 0; i < this->noRooms; ++i) {
						this->rooms[i] += other.rooms[i];
				}

				return *this;
		}

		void buyTicket(int idx) {
				if (idx >= this->noRooms) {
						throw std::exception();
				}

				++this->rooms[idx];
		}

		Cinema operator++(int) {
				Cinema copy = *this;

				int* newArr = new int[this->noRooms + 1];
				memcpy(newArr, this->rooms, this->noRooms * sizeof(int));
				newArr[this->noRooms] = 0;

				++this->noRooms;
				delete[] this->rooms;
				this->rooms = newArr;

				return copy;
		}

		Cinema& operator++() {
			int* newArr = new int[this->noRooms + 1];
			memcpy(newArr, this->rooms, this->noRooms * sizeof(int));
			newArr[this->noRooms] = 0;

			++this->noRooms;
			delete[] this->rooms;
			this->rooms = newArr;

			return *this;
		}

		Cinema operator+(const Cinema& other) {
			// add the ids, concatenate the name, use the min amount of rooms and add up the capacity
			Cinema result("");

			result.id = this->id + other.id;
			
			delete[] result.name;
			char* buffer = new char[strlen(this->name) + strlen(other.name) + 2];
			strcpy(buffer, this->name);
			strcat(buffer, " ");
			strcat(buffer, other.name);
			result.name = buffer;

			result.noRooms = this->noRooms < other.noRooms ? this->noRooms : other.noRooms;

			delete[] result.rooms;
			result.rooms = new int[result.noRooms];
			for (int i = 0; i < result.noRooms; ++i) {
				result.rooms[i] = this->rooms[i] + other.rooms[i];
			}

			return result;
		}

		bool operator==(const Cinema& other) {
			if (this == &other) {
				return true;
			}

			if (strcmp(this->name, other.name) != 0) {
				return false;
			}

			if (this->noRooms != other.noRooms) {
				return false;
			}

			for (int i = 0; i < this->noRooms; ++i) {
				if (this->rooms[i] != other.rooms[i]) {
					return false;
				}
			}

			return true;
		}

		bool operator!=(const Cinema& other) {
			return !(*this == other);
		}

private:
		static char* deepCopyString(const char* original) {
				char* result = new char[strlen(original) + 1];
				strcpy(result, original);

				return result;
		}

		static int* deepCopyInt(const int* original, int size) {
				int* result = new int[size];
				memcpy(result, original, size * sizeof(int));

				return result;
		}

		int id;
		char* name;
		int* rooms;
		int noRooms;


		static const int DEFAULT_NO_ROOMS = 5;
		static int CURRENT_ROOM;

		friend ostream& operator<<(ostream& out, const Cinema& cinema);
		friend istream& operator>>(istream& in, Cinema& cinema);
};

int Cinema::CURRENT_ROOM = 1;

ostream& operator<<(ostream& out, const Cinema& cinema) {
		out << "Cinema " << cinema.name << " with id " 
				<< cinema.id << " has " << cinema.noRooms << " rooms" << ":";

		for (int i = 0; i < cinema.noRooms; ++i) {
				out << cinema.rooms[i] << ", ";
		}

		out << endl;

		return out;
}

istream& operator>>(istream& in, Cinema& cinema) {
		// id,name,noRooms,rooms
		char buffer[128];
		in.getline(buffer, sizeof(buffer));

		char* occurence = strtok(buffer, ",");
		cinema.id = atoi(occurence);

		delete[] cinema.name;
		occurence = strtok(nullptr, ",");
		cinema.name = Cinema::deepCopyString(occurence);

		occurence = strtok(nullptr, ",");
		cinema.noRooms = atoi(occurence);

		delete[] cinema.rooms;
		cinema.rooms = new int[cinema.noRooms];
		for (int i = 0; i < cinema.noRooms; ++i) {
				occurence = strtok(nullptr, ",");
				cinema.rooms[i] = atoi(occurence);
		}

		return in;
}

int main() {
		Cinema cinema("test1");
		cout << cinema;

		/*cin >> cinema;
		cout << cinema;*/

		Cinema cinema3("test3");
		cinema3 = cinema3;

		cout << cinema3;

		Cinema cinema4 = cinema3;
		cout << cinema4;

		cout << "*********************" << endl;
		cinema4.buyTicket(0);
		cinema3.buyTicket(0);
		cinema4 += cinema3;
		cout << cinema4[0];
		cout << endl;

		Cinema old = cinema4++;
		cout << old;
		cout << cinema4;

		Cinema cinema5 = cinema4 + old;
		cout << cinema5;

		Cinema cinema6 = cinema5;
		cout << (cinema5 == cinema5 ? "The instances are equal" : "The instances are NOT equal") << endl;

		++cinema6;
		cout << cinema6;

		return 0;
}