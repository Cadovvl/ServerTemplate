#include "MessagesQueue.h"

uint64_t nextId() {
    static uint64_t id = 0;
    return id++;
}

Message::Message(const std::string &dest_, const std::string &message_) : dest_(dest_), message_(message_), id_(nextId()) {}

std::string Message::dest() const {
    return dest_;
}

std::string Message::message() const {
    return message_;
}

uint64_t Message::id() const {
    return id_;
}


void MessagesQueue::addMessage(const Message & m) {
    messagesContainer_[m.dest()].push(m);
}

bool MessagesQueue::hasNext(const std::string &user) const {
    return !messagesContainer_.at(user).empty();
}

Message MessagesQueue::getNext(const std::string &user) {
    Message res(messagesContainer_[user].front());
    messagesContainer_[user].pop();
    return res;
}

MessagesQueue::MessagesQueue() { }

template<>
MessagesQueue& singleton() {
    MessagesQueue mq;
    return mq;
}
