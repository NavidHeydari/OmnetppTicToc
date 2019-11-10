#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc3: public cSimpleModule {

private:
    int counter; // counting how long we should bounce the message

protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc3);

void Txc3::initialize() {

    // Initialize counter to ten. We'll decrement it every time and delete
    // the message when it reaches zero.
    counter = 10;

    // The WATCH() statement below will let you examine the variable under
    // Tkenv. After doing a few steps in the simulation, double-click either
    // `tic' or `toc', select the Contents tab in the dialog that pops up,
    // and you'll find "counter" in the list.
    WATCH(counter);

    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        cMessage *msg = new cMessage("tictocMsg");
//        cMessage *msg; //for testing this line will throw error. because of not allocated reference. the variables doesn't have any
        // value and it's null.
        /*
         *Adding further logging here
         */
        EV << "Sending initial message \n";
        send(msg, "out");
    }
}

void Txc3::handleMessage(cMessage *msg) {

    // Increment counter and check value.
    counter--;
    if (counter == 0) {

        //find the name of the sender
        const char* receiverName = msg->getArrivalModule()->getFullName();
        const char* senderName = msg->getSenderModule()->getFullName();

        printf("Message received in Module: [%s] From Module: [%s]\n",
                receiverName, senderName);

        // If counter is zero, delete message. If you run the model, you'll
        // find that the simulation will stop at this point with the message
        // "no more events".
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    } else {
        EV << getName() << "'s counter is " << counter
                  << ", sending back message\n";
        send(msg, "out");
    }
}
