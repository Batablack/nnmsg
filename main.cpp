#include <unistd.h>
#include "json.hpp"
#include "nnmsg.h"
#include <string>

using std::string;
using json = nlohmann::json;
std::string SocketAddress = "tcp://127.0.0.1:5560";
string log_path = "/home/sgb/mnt/json/msg.log";
int data;

void * sub_handler(void * arg) {
    pthread_detach(pthread_self());
    nnmsg SubMsgger(SocketAddress);
    SubMsgger.logger_init("subtest",log_path,1024*1024*1,1);
    SubMsgger.linkSubSocket();
    json j;
    while (1)
    {
        SubMsgger.nnRecv();
        try{
            cout << SubMsgger.data <<endl;
        }
        catch (json::type_error& e)
        {
            std::cout << e.what() << '\n';
            continue;
        }

    }

}

int main ()
{

    pthread_t sub_tid;
    pthread_create(&sub_tid, NULL, sub_handler, NULL);
    while(1)
    {
//        cout << data << endl;
        sleep (2);
    }

    return 0;
}

