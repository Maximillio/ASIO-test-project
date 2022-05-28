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
#include <array>
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

void timerExample()
{
    asio::io_context io;
    int count {};

    asio::steady_timer t(io, asio::chrono::seconds(5));

    functor func;
    func.count = &count;
    func.timer = &t;

    t.async_wait(func);

    io.run();

    std::cout << "Hello, after world!" << std::endl;
}

int main(int argc, char* argv[])
{
    using asio::ip::tcp;

    try
    {
        asio::io_context io;
        tcp::resolver resolver {io};

        tcp::resolver::results_type endpoints =
              resolver.resolve("localhost", "daytime");

        tcp::socket socket(io);
        asio::connect(socket, endpoints);

        while (true)
        {
            std::array<char, 128> buf;
            asio::error_code error;

            size_t len = socket.read_some(asio::buffer(buf), error);
            if (error == asio::error::eof)
                break; // Connection closed cleanly by peer.
            /*else if (error)
                throw asio::system_error(error); // Some other error.*/

            std::cout.write(buf.data(), len);
        }
        io.run();

        std::cout << "Hello, after world!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout<< e.what() <<std::endl;
    }

    return 0;
}
