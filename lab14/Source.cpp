#include <iostream>
#include <map>
#include <vector>

using namespace std;

class InvalidArgumentException : public exception {
public:
		InvalidArgumentException() {}
};

enum class SeatAvailability {
		FREE,
		RESERVED,
		SOLD
};

class Seat {
private:
		const int id;
		SeatAvailability availability;
		int ticketId;
public:
		Seat(int id) : id(id) {
				availability = SeatAvailability::FREE;
				ticketId = -1;
		}

		Seat(): id(-1) {

		}

		Seat(const Seat& seat) : id(seat.id) {
				this->availability = seat.availability;
				this->ticketId = seat.ticketId;
		}

		SeatAvailability getAvailability() const { return this->availability; }

		void setAvailability(SeatAvailability availability) {
				if (this->availability == availability) {
						throw InvalidArgumentException();
				}

				if (this->availability == SeatAvailability::SOLD) {
						throw InvalidArgumentException();
				}

				this->availability = availability;
		}
};

class Event {
private:
		string name;
		int startTime;
		int runTime;
		int noRows;
		int noColumns;
		map<int, Seat> seats;

		void setName(const string& name) {
				if (name.empty()) {
						throw InvalidArgumentException();
				}

				this->name = name;
		}

		void setStartTime(int startTime) {
				if (startTime < 0 || startTime >(24 * 60)) {
						throw InvalidArgumentException();
				}

				this->startTime = startTime;
		}

		void setRunTime(int runTime) {
				if (runTime < 0 || runTime > 200) {
						throw InvalidArgumentException();
				}

				this->runTime = runTime;
		}

		void setNoRows(int noRows) {
				if (noRows < 0 || noRows > 50) {
						throw InvalidArgumentException();
				}

				this->noRows = noRows;
		}

		void setNoColumns(int noColumns) {
				if (noColumns < 0 || noColumns > 50) {
						throw InvalidArgumentException();
				}

				this->noColumns = noColumns;
		}

		void createSeats() {
				int toCreate = noRows * noColumns;
				for (int i = 0; i < toCreate; ++i) {
						seats.emplace(i, Seat(i));
				}
		}

		friend ostream& operator<<(ostream& out, const Event& event);

public:
		Event(const string& name, int startTime, int runTime, int noRows, int noColumns) {
				setName(name);
				setStartTime(startTime);
				setRunTime(runTime);
				setNoRows(noRows);
				setNoColumns(noColumns);
				createSeats();
		}

		void printLayout() {
				for (int i = 0; i < noRows; ++i) {
						for (int j = 0; j < noColumns; ++j) {
								const auto seat = seats.at(i);
								switch (seat.getAvailability()) {
								case SeatAvailability::FREE:
										cout << "- ";
										break;
								case SeatAvailability::RESERVED:
										cout << "/ ";
										break;
								case SeatAvailability::SOLD:
										cout << "X ";
										break;
								}
						}
						cout << endl;
				}
		}

		void changeAvailability(int row, int column, SeatAvailability availability) {
				if (row < 0 || row >= noRows || column < 0 || column >= noColumns) {
						throw InvalidArgumentException();
				}

				const auto idx = row * noColumns + column;
				auto seat = seats.at(idx);
				seat.setAvailability(availability);
		}
};

ostream& operator<<(ostream& out, const Event& event) {
		const auto startHour = event.startTime / 60;
		const auto startMinutes = event.startTime % 60;
		out << "Event " << event.name << " starts at " << startHour << ":" << startMinutes
				<< " and runs for " << event.runTime << " minutes.\n";

		return out;
}

class Room {
private:
		const int id;
		string name;
		vector<Event> events;

public:
		Room(int id, const string& name) : id(id), name(name) {}

		void addEvent(const Event& event) {
				events.push_back(event);
		}

		void printEvents() {
				cout << "Room with " << id << " has " << events.size() << " events running:\n";
				for (const Event& event : events) {
						cout << event;
				}
		}
};

int main() {
		Room room1(1, "room1");
		Event event1("Movie1", 12 * 60, 30, 2, 2);

		room1.addEvent(event1);
		room1.printEvents();

		event1.printLayout();
		event1.changeAvailability(0, 0, SeatAvailability::SOLD);
		event1.printLayout();

		return 0;
}