#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

enum class SeatAvailability {
	FREE,
	RESERVED, 
	PAID
};

static char* deepCopy(const char* original) {
	char* result = new char[strlen(original) + 1];
	strcpy(result, original);

	return result;
}

class Seat {
public:
	Seat(short seatId):seatId(seatId) {
		this->availability = SeatAvailability::FREE;
	}

	Seat(const Seat& seat):seatId(seat.seatId) {
		this->availability = seat.availability;
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
		default:
				return "unkown";
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

	Room(const Room& room): roomId(room.roomId) {
		this->numberOfSeats = room.numberOfSeats;
		this->seats = new Seat * [numberOfSeats];

		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(room.seats[i]->getSeatId());
			this->seats[i]->setAvailability(room.seats[i]->getAvailability());
		}
	}

	short getRoomId() const {
		return this->roomId;
	}

	Room& operator=(const Room& room) {
		if (this == &room) {
			return *this;
		}

		for (int i = 0; i < numberOfSeats; ++i) {
			delete this->seats[i];
		}
		delete[] this->seats;

		this->roomId = room.roomId;
		this->numberOfSeats = room.numberOfSeats;

		this->seats = new Seat * [numberOfSeats];
		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(*room.seats[i]);
		}

		return *this;
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
	short roomId;
	int numberOfSeats;
	Seat** seats;
};

class Event {
public:
	Event(): room(0, 1) {
		this->name = nullptr;
		this->startTime = nullptr;
		
		this->runtime = -1;
	}

	Event(const char* name, int runtime, const char* startTime, Room room) : room(room) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->runtime = runtime;

		this->startTime = new char[strlen(startTime) + 1];
		strcpy(this->startTime, startTime);
	}

	Event(const Event& event) : room(event.room) {
		this->runtime = event.runtime;

		this->name = new char[strlen(event.name) + 1];
		strcpy(this->name, event.name);

		this->startTime = new char[strlen(event.startTime) + 1];
		strcpy(this->startTime, event.startTime);
	}

	Event& operator=(const Event& anotherEvent) {
		if (this == &anotherEvent) {
			return *this;
		}

		this->runtime = anotherEvent.runtime;

		delete[] this->name;
		this->name = deepCopy(anotherEvent.name);

		delete[] this->startTime;
		this->startTime = deepCopy(anotherEvent.startTime);

		this->room = anotherEvent.room;

		return *this;
	}

	void print() {
		cout << "Event " << name << " runs at " << startTime << " in room "
			<< room.getRoomId() << " and lasts " << runtime << endl;
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

		this->events = new Event[NO_EVENTS];

		this->runningEvents = 0;
	}

	Cinema& operator=(const Cinema& anotherCinema) {
		if (this == &anotherCinema) {
			return *this;
		}

		delete[] this->name;
		this->name = deepCopy(anotherCinema.name);

		delete[] this->address;
		this->address = deepCopy(anotherCinema.address);
		this->runningEvents = anotherCinema.runningEvents;

		delete[] this->events;
		this->events = new Event[NO_EVENTS];
		for (int i = 0; i < runningEvents; ++i) {
			this->events[i] = anotherCinema.events[i];
		}

		return *this;
	}

	~Cinema() {
		delete[] name;
		delete[] address;
		delete[] events;
	}

	void addEvent(Event& event) {
		this->events[runningEvents] = event;
		++runningEvents;
	}

	void print() {
		cout << "Cinema " << name << " is located at " << address << endl;
		if (runningEvents == 0) {
			cout << "No running events!" << endl;

			return;
		}

		for (int i = 0; i < runningEvents; ++i) {
			events[i].print();
		}
		cout << endl;
	}

private:
	char* name;
	char* address;
	Event* events;
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

	Event event("event1", 120, "10:20", room);
	event.print();

	event = event;

	Cinema cinema("cinema1", "address1");
	cinema.print();

	cout << "************************************" << endl;

	cinema.addEvent(event);
	cinema.print();

	cout << "************************************" << endl;

	Cinema cinema2("", "");
	cinema2 = cinema;
	cinema2.print();

	return 0;
}