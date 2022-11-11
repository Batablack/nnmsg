#include "nnmsg.h"
#include <unistd.h>
#include "json.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
using json = nlohmann::json;
string SOCKET_ADDRESS("tcp://127.0.0.1:5560");

string data;


int main ()
{
    int pub;
    pub = nnmsg_socket (AF_SP, NN_PUB);
    nnmsg_bind (pub, SOCKET_ADDRESS);
    cout << "nnmsg_bind" << endl;


    /*  Wait till both connections are established to get messages spread
        evenly between the two pull sockets. */
    nn_sleep(10);
    int i = 0;
    json j;
    while (1)
    {   i ++;
        j["num"] = i;
        data = j.dump();
        nnmsg_send(pub,data);
        sleep(2);
    }

    nnmsg_close (pub);

    return 0;
}

