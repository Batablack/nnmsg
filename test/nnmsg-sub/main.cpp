#include "nnmsg.h"
#include <unistd.h>
#include "json.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
using json = nlohmann::json;
string SOCKET_ADDRESS("tcp://127.0.0.1:5560");

int data;

void * sub_handler(void * arg) {
    pthread_detach(pthread_self());
    int sub;
    string _data;
    sub = nnmsg_socket (AF_SP, NN_SUB);
    nnmsg_connect (sub, SOCKET_ADDRESS);
    cout << "nnmsg_connect" << endl;

    nnmsg_setsockopt(sub, NN_SUB, NN_SUB_SUBSCRIBE, "abc", 0);

    /*  Wait till both connections are established to get messages spread
        evenly between the two pull sockets. */
    nn_sleep(10);
    json j;
    while (1)
    {
        nnmsg_recv(sub,_data);
        cout << _data << endl;
        try{
            j = json::parse(_data);
            cout << j.dump() << endl;
            data = j.at("num");
        }
        catch (json::type_error& e)
        {
            std::cout << e.what() << '\n';
            continue;
        }

    }

    nnmsg_close (sub);
}

int main ()
{

    pthread_t sub_tid;
    pthread_create(&sub_tid, NULL, sub_handler, NULL);
    while(1)
    {
        cout << data << endl;
        sleep (2);
    }

    return 0;
}

