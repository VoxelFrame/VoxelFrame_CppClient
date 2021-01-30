#include "NetSys.h"
#include <iostream>
#include <memory>
#include <thread>
#include "brynet/base/AppStatus.hpp"
#include "brynet/base/Packet.hpp"
#include "brynet/net/EventLoop.hpp"
#include "brynet/net/SocketLibFunction.hpp"
#include "brynet/net/TcpConnection.hpp"

using namespace std;
using namespace brynet;
using namespace brynet::net;
using namespace brynet::base;

namespace NetSys
{
    void netSysThread();
    void start()
    {
        auto th = std::make_shared<thread>(netSysThread); // new thread(netSysThread);
    }
    void netSysThread()
    {
        cout << "NetSys thread started" << endl;

        brynet::net::base::InitSocket();

        auto clientEventLoop = std::make_shared<EventLoop>();
        std::string ip = "127.0.0.1";
        int port = 6666;
        int packetLen = 100;
        auto fd = brynet::net::base::Connect(false, ip, port);
        brynet::net::base::SocketSetSendSize(fd, 32 * 1024);
        brynet::net::base::SocketSetRecvSize(fd, 32 * 1024);
        brynet::net::base::SocketNodelay(fd);

        auto enterCallback = [packetLen](const TcpConnection::Ptr &dataSocket) {
            cout << "NetSys socket enterd" << endl;

            static_assert(sizeof(dataSocket.get()) <= sizeof(int64_t), "ud's size must less int64");

            auto HEAD_LEN = sizeof(uint32_t) + sizeof(uint16_t);

            std::shared_ptr<BigPacket> sp = std::make_shared<BigPacket>(false);
            sp->writeUINT32(HEAD_LEN + sizeof(int64_t) + packetLen);
            sp->writeUINT16(1);
            sp->writeINT64((int64_t)dataSocket.get());
            sp->writeBinary(std::string(packetLen, '_'));

            for (int i = 0; i < 1; ++i)
            {
                dataSocket->send(sp->getData(), sp->getPos());
            }

            dataSocket->setDataCallback([dataSocket](brynet::base::BasePacketReader &reader) {
                while (true)
                {
                    if (!reader.enough(sizeof(uint32_t)))
                    {
                        break;
                    }

                    auto buffer = reader.currentBuffer();
                    auto packetLen = reader.readUINT32();
                    if (!reader.enough(packetLen - sizeof(uint32_t)))
                    {
                        break;
                    }

                    // TotalRecvSize += packetLen;
                    // TotalRecvPacketNum++;

                    reader.readUINT16();
                    int64_t addr = reader.readINT64();

                    if (addr == (int64_t)(dataSocket.get()))
                    {
                        dataSocket->send(buffer, packetLen);
                    }

                    reader.addPos(packetLen - sizeof(uint32_t) - sizeof(uint16_t) - sizeof(int64_t));
                    reader.savePos();
                }
            });

            dataSocket->setDisConnectCallback([](const TcpConnection::Ptr &dataSocket) {
                (void)dataSocket;
                cout << "NetSys disconnected" << endl;
            });
        };
        auto tcpConnection = TcpConnection::Create(TcpSocket::Create(fd, false),
                                                   1024 * 1024,
                                                   enterCallback,
                                                   clientEventLoop);
        while (true)
        {
            clientEventLoop->loop(10);

            if (app_kbhit())
            {
                cout << "NetSys stoped" << endl;
                break;
            }
        }
    }
} // namespace NetSys