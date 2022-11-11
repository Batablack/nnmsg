/*
    Copyright (c) 2012 Martin Sustrik  All rights reserved.
    Copyright (c) 2013 GoPivotal, Inc.  All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "nn.h"
#include "pipeline.h"
#include "nnmsg.h"
#include <unistd.h>

string SOCKET_ADDRESS("tcp://127.0.0.1:5560");

int main ()
{
    int push1;
    int push2;
    /*  nnmsg fan-out. */
    push1 = nnmsg_socket (AF_SP, NN_PUSH);
    nnmsg_bind (push1, SOCKET_ADDRESS);
    cout << "bind" << endl;
    /*  Wait till both connections are established to get messages spread
        evenly between the two pull sockets. */
    nn_sleep (10);

    nnmsg_send (push1, "ABC");
    sleep(5);
    nnmsg_send (push1, "DEF");
    cout << "nnmsg_send" << endl;
    nnmsg_close (push1);


    return 0;
}

