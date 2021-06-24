#include "../include/Subject.h"

void Subject::attach(Observer* observer) {
    this->observer = observer;
}

void Subject::detach(Observer* observer) {
    this->observer = nullptr;
}

void Subject::notify() {
    if(this->observer != nullptr) {
        this->observer->update();
    }
}