//
// http_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <ASIO/asio.hpp>
#include <functional>

struct functor
{
    asio::steady_timer* timer;
    int* count;
    void operator()(const asio::error_code& e)
    {
        std::cout << "Hello, world #" << *count <<"!" << std::endl;
        std::cout << "The error code is:" << e << std::endl;
        if ((*count) < 6)
        {
            ++(*count);
            timer->expires_at(timer->expiry() + std::chrono::seconds(5));
            timer->async_wait(*this);
        }
    }
};

void print(const asio::error_code& e, asio::steady_timer& timer, int& count)
{
    std::cout << "Hello, world #" << count <<"!" << std::endl;
    std::cout << "The error code is:" << e << std::endl;
    ++count;
    if (count < 6)
    {
        timer.expires_at(timer.expiry() + std::chrono::seconds(5));
    }
}

void print_2(const asio::error_code& e)
{
    std::cout << "Another Hello, world!" << std::endl;
    std::cout << "The error code is:" << e << std::endl;
}

int main(int argc, char* argv[])
{
    asio::io_context io;
    int count {};

    asio::steady_timer t(io, asio::chrono::seconds(5));
    asio::steady_timer ti(io, asio::chrono::seconds(3));

    functor func;
    func.count = &count;
    func.timer = &t;

    t.async_wait(func);
    ti.async_wait(&print_2);

    io.run();

    std::cout << "Hello, after world!" << std::endl;

    return 0;
}
