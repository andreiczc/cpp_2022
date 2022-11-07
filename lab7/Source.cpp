#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

enum class SeatAvailability {
	FREE,
	RESERVED, 
	PAID
};

class Seat {
public:
	Seat(short seatId):seatId(seatId) {
		this->availability = SeatAvailability::FREE;
	}

	void setAvailability(SeatAvailability availability) {
		this->availability = availability;
	}

	short getSeatId() {
		return this->seatId;
	}

	SeatAvailability getAvailability() {
		return this->availability;
	}

	void print() {
		cout << "Seat " << this->seatId << " is " << enumToString(this->availability) << endl;
	}

private:
	string enumToString(SeatAvailability availability) {
		switch (availability) {
		case SeatAvailability::FREE:
			return "free";
		case SeatAvailability::RESERVED:
			return "reserved";
		case SeatAvailability::PAID:
			return "paid";
		}
	}

	const short seatId;
	SeatAvailability availability;
};

class Room {
public:
	Room(short roomId, int numberOfSeats): roomId(roomId) {
		this->numberOfSeats = numberOfSeats;
		this->seats = new Seat*[numberOfSeats];

		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(i + 1);
		}
	}

	Room(Room& room): roomId(room.roomId) {
		this->numberOfSeats = room.numberOfSeats;
		this->seats = new Seat * [numberOfSeats];

		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(room.seats[i]->getSeatId());
			this->seats[i]->setAvailability(room.seats[i]->getAvailability());
		}
	}

	~Room() {
		for (int i = 0; i < numberOfSeats; ++i) {
			delete this->seats[i];
		}

		delete[] this->seats;
	}

	void print() {
		cout << "Room " << this->roomId << " has capacity of " << numberOfSeats << " seats." << endl;
		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i]->print();
		}
	}

private:
	const short roomId;
	int numberOfSeats;
	Seat** seats;
};

class Event {
	Event(const char* name, int runtime, const char* startTime, Room room) : room(room) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->runtime = runtime;

		this->startTime = new char[strlen(startTime) + 1];
		strcpy(this->startTime, startTime);
	}

	~Event() {
		delete[] this->name;
		delete[] this->startTime;
	}

private:
	char* name;
	int runtime;
	char* startTime;
	Room room;
};

class Cinema {
public:
	Cinema(const char* name, const char* address) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);

		this->events = new Event*[NO_EVENTS];

		this->runningEvents = 0;
	}

private:
	char* name;
	char* address;
	Event** events;
	int runningEvents;

	static const int NO_EVENTS = 10;
};

int main() {
	Seat seat1(1);
	Seat seat2(2);

	seat1.print();
	seat2.print();

	Room room(1, 10);
	room.print();

	return 0;
}