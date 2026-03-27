#ifndef OBSERVER_H_

#define OBSERVER_H_

#include <vector>
#include <algorithm>

using std::vector;

class Observer {
private:

public:
	/*
	* Invocat cand observable shchimba.
	* 
	*/
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;

protected:
	//Notifica un obiect observer de schimbare.
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}

public:
	/*
	* Inregistreaza un observer pentru notificare.
	*/
	void adaugaObserver(Observer* obs) {
		observers.push_back(obs);
	}

	/*
	* Stergerea inregistrarii la observare.
	*/
	void stergeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs), observers.end());
	}
};

#endif // !OBSERVER_H_
