#ifndef NNMSG_PULL_NNMSG_H
#define NNMSG_PULL_NNMSG_H






using std::cout;
using std::endl;
using std::string;
#define MAX_SIZE 1024




static int nnmsg_socket_impl (const char * file, int line, int family, int protocol);
static int nnmsg_socket_impl (string file, int line, int family, int protocol);

static int nnmsg_connect_impl (string file, int line, int sock, string address);
static int nnmsg_connect_impl (const char * file, int line, int sock, string address);

static int nnmsg_bind_impl (string file, int line, int sock, string address);
static int nnmsg_bind_impl (const char* file, int line, int sock, string address);

static void nnmsg_close_impl (const char *file, int line, int sock);

static void nnmsg_send_impl (string file, int line, int sock, string data);
static void nnmsg_send_impl (const char* file, int line, int sock, string data);

static void nnmsg_recv_impl (string file, int line, int sock, string &data);
static void nnmsg_recv_impl (const char* file, int line, int sock, string &data);

static void nnmsg_drop_impl (string file, int line, int sock, int err);

static int  nnmsg_setsockopt_impl (string file, int line, int sock, int level,
                                  int option, const void *optval, size_t optlen);
static int  nnmsg_setsockopt_impl (const char* file, int line, int sock, int level,
                                   int option, const void *optval, size_t optlen);


#define nnmsg_socket(f, p) nnmsg_socket_impl (__FILE__, __LINE__, (f), (p))
#define nnmsg_connect(s, a) nnmsg_connect_impl (__FILE__, __LINE__, (s), (a))
#define nnmsg_bind(s, a) nnmsg_bind_impl (__FILE__, __LINE__, (s), (a))
#define nnmsg_send(s, d) nnmsg_send_impl (__FILE__, __LINE__, (s), (d))
#define nnmsg_recv(s, d) nnmsg_recv_impl (__FILE__, __LINE__, (s), (d))
#define nnmsg_drop(s, e) nnmsg_drop_impl (__FILE__, __LINE__, (s), (e))
#define nnmsg_close(s) nnmsg_close_impl (__FILE__, __LINE__, (s))
#define nnmsg_setsockopt(s, l, o, v, z) nnmsg_setsockopt_impl (__FILE__, \
    __LINE__, (s), (l), (o), (v), (z))

static int NN_UNUSED nnmsg_socket_impl (const char * file, int line, int family,
                                       int protocol)
{
    int sock;

    sock = nn_socket (family, protocol);
    if (sock == -1) {
        fprintf (stderr, "Failed create socket: %s [%d] (%s:%d)\n",
                 nn_err_strerror (errno),
                 (int) errno, file, line);
        nn_err_abort ();
    }

    return sock;
}

static int NN_UNUSED nnmsg_socket_impl (string file, int line, int family,
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

static int NN_UNUSED nnmsg_connect_impl (string file, int line,
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



static int NN_UNUSED nnmsg_connect_impl (const char *file, int line,
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
                 (int) errno, file, line);
        nn_err_abort ();
    }
    if (_address != NULL)
    {
        delete[] _address;
        _address = NULL;
    }
    return rc;
}

static int NN_UNUSED nnmsg_bind_impl (string file, int line,
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

static int NN_UNUSED nnmsg_bind_impl (const char* file, int line,
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
                 (int) errno, file, line);
        nn_err_abort ();
    }
    if (_address != NULL)
    {
        delete[] _address;
        _address = NULL;
    }
    return rc;
}

static int NN_UNUSED nnmsg_setsockopt_impl (string file, int line,
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

static int NN_UNUSED nnmsg_setsockopt_impl (const char* file, int line,
                                            int sock, int level, int option, const void *optval, size_t optlen)
{
    int rc;

    rc = nn_setsockopt (sock, level, option, optval, optlen);
    if(rc < 0) {
        fprintf (stderr, "Failed set option \"%d\": %s [%d] (%s:%d)\n",
                 option,
                 nn_err_strerror (errno),
                 (int) errno, file, line);
        nn_err_abort ();
    }
    return rc;
}

static void NN_UNUSED nnmsg_close_impl (const char *file, int line, int sock)
{
    int rc;

    rc = nn_close (sock);
    if ((rc != 0) && (errno != EBADF && errno != ETERM)) {
        fprintf (stderr, "Failed to close socket: %s [%d] (%s:%d)\n",
                 nn_err_strerror (errno),
                 (int) errno, file, line);
        nn_err_abort ();
    }
}

static void NN_UNUSED nnmsg_send_impl (string file, int line,
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

static void NN_UNUSED nnmsg_send_impl (const char* file, int line,
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
                 (int) errno, file, line);
        nn_err_abort ();
    }
    if (rc != (int)data_len) {
        fprintf (stderr, "Data to send is truncated: %d != %d (%s:%d)\n",
                 rc, (int) data_len,
                 file, line);
        nn_err_abort ();
    }
    delete[] _data;
}

static void NN_UNUSED nnmsg_recv_impl (string file, int line, int sock, string &data)
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

static void NN_UNUSED nnmsg_recv_impl (const char* file, int line, int sock, string &data)
{
    size_t data_len;
    int rc;
    char *buf = new char[MAX_SIZE];

    alloc_assert (buf);
    rc = nn_recv (sock, buf, MAX_SIZE+1, 0);
    if (rc < 0) {
        fprintf (stderr, "Failed to recv: %s [%d] (%s:%d)\n",
                 nn_err_strerror (errno),
                 (int) errno, file, line);
        nn_err_abort ();
    }
    data = buf;
    delete[] buf;
}

static void NN_UNUSED nnmsg_drop_impl (string file, int line, int sock, int err)
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

static int NN_UNUSED get_nnmsg_port (int argc, const char *argv[])
{
    return atoi(argc < 2 ? "5555" : argv[1]);
}

static void NN_UNUSED nnmsg_addr_from (char *out, const char *proto,
                                      const char *ip, int port)
{
    sprintf(out, "%s://%s:%d", proto, ip, port);
}



#endif //NNMSG_PULL_NNMSG_H
