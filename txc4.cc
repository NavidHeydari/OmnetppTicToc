#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc4: public cSimpleModule {

private:
    int counter; // counting how long we should bounce the message

protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};


Define_Module(Txc4);

void Txc4::initialize() {

    // Initialize the counter with the "limit" module parameter, declared
    // in the NED file (tictoc4.ned).
    counter = par("limit");

    // we no longer depend on the name of the module to decide
    // whether to send an initial message
    if (par("sendMsgOnInit").boolValue() == true) {

        cMessage *msg = new cMessage("tictocMsg");

        EV << "Sending initial message \n";
        send(msg, "out");
    }
}

void Txc4::handleMessage(cMessage *msg) {

    // Increment counter and check value.
    counter--;
    if (counter == 0) {

        //find the name of the sender
        const char* receiverName = msg->getArrivalModule()->getFullName();
        const char* senderName = msg->getSenderModule()->getFullName();

        printf("Message received in Module: [%s] From Module: [%s]\n",
                receiverName, senderName);

        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    } else {
        EV << getName() << "'s counter is " << counter
                  << ", sending back message\n";
        send(msg, "out");
    }
}
