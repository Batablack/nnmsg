/*
    Copyright (c) 2013 Insollo Entertainment, LLC. All rights reserved.
    Copyright 2015 Garrett D'Amore <garrett@damore.org>
    Copyright 2016 Franklin "Snaipe" Mathieu <franklinmathieu@gmail.com>

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

#ifndef TESTUTIL_H_INCLUDED
#define TESTUTIL_H_INCLUDED

#include "utils/attr.h"
#include "utils/err.c"
#include "utils/sleep.c"
#include <string>
#include <iostream>
#ifdef __cplusplus
extern "C" {
#endif
using std::cout;
using std::endl;
using std::string;
#define MAX_SIZE 1024


static int test_socket_impl (string file, int line, int family, int protocol);
static int test_connect_impl (string file, int line, int sock, string address);
static int test_bind_impl (string file, int line, int sock, string address);
static void test_close_impl (string file, int line, int sock);
static void test_send_impl (string file, int line, int sock, string data);
static void test_recv_impl (string file, int line, int sock, string &data);
static void test_drop_impl (string file, int line, int sock, int err);
static int  test_setsockopt_impl (string file, int line, int sock, int level,
    int option, const void *optval, size_t optlen);

#define test_socket(f, p) test_socket_impl (__FILE__, __LINE__, (f), (p))
#define test_connect(s, a) test_connect_impl (__FILE__, __LINE__, (s), (a))
#define test_bind(s, a) test_bind_impl (__FILE__, __LINE__, (s), (a))
#define test_send(s, d) test_send_impl (__FILE__, __LINE__, (s), (d))
#define test_recv(s, d) test_recv_impl (__FILE__, __LINE__, (s), (d))
#define test_drop(s, e) test_drop_impl (__FILE__, __LINE__, (s), (e))
#define test_close(s) test_close_impl (__FILE__, __LINE__, (s))
#define test_setsockopt(s, l, o, v, z) test_setsockopt_impl (__FILE__, \
    __LINE__, (s), (l), (o), (v), (z))

static int NN_UNUSED test_socket_impl (string file, int line, int family,
    int protocol)
{
    int sock;

    sock = nn_socket (family, protocol);
    if (sock == -1) {
        fprintf (stderr, "Failed create socket: %s [%d] (%s:%d)\n",
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }

    return sock;
}

static int NN_UNUSED test_connect_impl (string file, int line,
    int sock, string address)
{
    int rc;
    char * _address = new char[64];
    strcpy(_address, address.c_str());
    rc = nn_connect (sock, _address);
    if(rc < 0) {
        fprintf (stderr, "Failed connect to \"%s\": %s [%d] (%s:%d)\n",
            _address,
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
    if (_address != NULL)
    {
        delete[] _address;
        _address = NULL;
    }
    return rc;
}

static int NN_UNUSED test_bind_impl (string file, int line,
    int sock, string address)
{
    int rc;
    char * _address = new char[64];
    strcpy(_address, address.c_str());
    rc = nn_bind (sock, _address);
    if(rc < 0) {
        fprintf (stderr, "Failed bind to \"%s\": %s [%d] (%s:%d)\n",
                 _address,
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
    if (_address != NULL)
    {
        delete[] _address;
        _address = NULL;
    }
    return rc;
}

static int NN_UNUSED test_setsockopt_impl (string file, int line,
    int sock, int level, int option, const void *optval, size_t optlen)
{
    int rc;

    rc = nn_setsockopt (sock, level, option, optval, optlen);
    if(rc < 0) {
        fprintf (stderr, "Failed set option \"%d\": %s [%d] (%s:%d)\n",
            option,
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
    return rc;
}

static void NN_UNUSED test_close_impl (string file, int line, int sock)
{
    int rc;

    rc = nn_close (sock);
    if ((rc != 0) && (errno != EBADF && errno != ETERM)) {
        fprintf (stderr, "Failed to close socket: %s [%d] (%s:%d)\n",
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
}

static void NN_UNUSED test_send_impl (string file, int line,
    int sock, string data)
{
    size_t data_len;
    int rc;
    char * _data = new char[MAX_SIZE];
    strcpy(_data,data.c_str());
    data_len = strlen (_data);

    rc = nn_send (sock, _data, data_len, 0);
    if (rc < 0) {
        fprintf (stderr, "Failed to send: %s [%d] (%s:%d)\n",
            nn_err_strerror (errno),
            (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
    if (rc != (int)data_len) {
        fprintf (stderr, "Data to send is truncated: %d != %d (%s:%d)\n",
            rc, (int) data_len,
            file.c_str(), line);
        nn_err_abort ();
    }
    delete[] _data;
}

static void NN_UNUSED test_recv_impl (string file, int line, int sock, string &data)
{
    size_t data_len;
    int rc;
    char *buf = new char[MAX_SIZE];

    alloc_assert (buf);
    rc = nn_recv (sock, buf, MAX_SIZE+1, 0);
    if (rc < 0) {
        fprintf (stderr, "Failed to recv: %s [%d] (%s:%d)\n",
                 nn_err_strerror (errno),
                 (int) errno, file.c_str(), line);
        nn_err_abort ();
    }
    data = buf;
    delete[] buf;
}

//static void NN_UNUSED test_recv_impl (string file, int line, int sock, string data)
//{
//    size_t data_len;
//    int rc;
//    char *buf;
//    char * _data = new char[MAX_SIZE];
//    strcpy(_data,data.c_str());
//
//    data_len = strlen (_data);
//    /*  We allocate plus one byte so that we are sure that message received
//        has correct length and not truncated  */
//    buf = (char *)malloc (data_len+1);
//    alloc_assert (buf);
//
//    rc = nn_recv (sock, buf, data_len+1, 0);
//    if (rc < 0) {
//        fprintf (stderr, "Failed to recv: %s [%d] (%s:%d)\n",
//            nn_err_strerror (errno),
//            (int) errno, file.c_str(), line);
//        nn_err_abort ();
//    }
//    if (rc != (int)data_len) {
//        fprintf (stderr, "Received data has wrong length: %d != %d (%s:%d)\n",
//            rc, (int) data_len,
//            file.c_str(), line);
//        nn_err_abort ();
//    }
//    if (memcmp (_data, buf, data_len) != 0) {
//        /*  We don't print the data as it may have binary garbage  */
//        fprintf (stderr, "Received data is wrong (%s:%d)\n", file.c_str(), line);
//        nn_err_abort ();
//    }
//    free (buf);
//    delete[] _data;
//}

static void NN_UNUSED test_drop_impl (string file, int line, int sock, int err)
{
    int rc;
    char buf[MAX_SIZE];

    rc = nn_recv (sock, buf, sizeof (buf), 0);
    if (rc < 0 && err != errno) {
        fprintf (stderr, "Got wrong err to recv: %s [%d != %d] (%s:%d)\n",
            nn_err_strerror (errno),
            (int) errno, err, file.c_str(), line);
        nn_err_abort ();
    } else if (rc >= 0) {
        fprintf (stderr, "Did not drop message: [%d bytes] (%s:%d)\n",
            rc, file.c_str(), line);
        nn_err_abort ();
    }
}

static int NN_UNUSED get_test_port (int argc, const char *argv[])
{
    return atoi(argc < 2 ? "5555" : argv[1]);
}

static void NN_UNUSED test_addr_from (char *out, const char *proto,
        const char *ip, int port)
{
    sprintf(out, "%s://%s:%d", proto, ip, port);
}
#ifdef __cplusplus
}
#endif
#endif
