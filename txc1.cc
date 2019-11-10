//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;
/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Txc1: public cSimpleModule {

protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);

void Txc1::initialize() {
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
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

void Txc1::handleMessage(cMessage *msg) {
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.

    //find the name of the sender
    const char* receiverName = msg->getArrivalModule()->getFullName();
    const char* senderName = msg->getSenderModule()->getFullName();

    printf("Message received in Module: [%s] From Module: [%s]\n", receiverName,
            senderName);
    /*
     * further Logging
     */
    EV << "Received message '" << msg->getName() << "', sending it out again\n";
    send(msg, "out"); // send out the message
//    send(msg, "out"); // at this point message has already been send before, and it will throw run time error.
}
