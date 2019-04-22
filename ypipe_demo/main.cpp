#include <iostream>
#include <stddef.h>
#include <thread>
#include <condition_variable>
#include "ypipe.hpp"


using namespace std;
using namespace zmq;
condition_variable cv;

template <typename T, int N, template <typename T, int N> typename yp_t = zmq::ypipe_t>
void read(yp_t<T, N> &pipe)
{
    while (1)
    {
        int t = -999;
        if ( pipe.read(&t))
        {
            std::cout << t << std::endl;
        }   
    }
}

template <typename T, int N, template <typename T, int N> typename yp_t = zmq::ypipe_t>
void write(yp_t<T, N> &pipe)
{
    while (1)
    {
        size_t count = 50;
        for (size_t i = 0; i < count; i++)
        {
            pipe.write(i, i%6);
        }
    }
}

int main(int argc, char const *argv[])
{
    zmq::ypipe_t<int, 20> pipe;

    thread t1(read<int, 20>, pipe);

    thread t2(read<int, 20>, pipe);

    t1.join();
    t2.join();
    return 0;
}
