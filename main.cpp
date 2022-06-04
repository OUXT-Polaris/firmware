/**
 * @file main.cpp
 * @author T.nishimura (hbvcg00@gmail.com)
 * @brief
 * data protocol
 * |header1|header2|length|data...|end|
 *
 * @version 0.1
 * @date 2022-06-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "mbed.h"
#include "EthernetInterface.h"
#include <vector>
#include "config.hpp"

enum class receiveStatus
{
    header1 = 0,
    header2 = 1,
    length = 2,
    data = 3,
};

int main(void)
{
    const uint8_t header1 = 0xFF;
    const uint8_t header2 = 0xFE;
    const uint8_t end = 0xFD;

    EthernetInterface net;
    TCPSocket sock;
    TCPSocket *client;
    PwmOut led(A0);
    uint8_t rxBuf[32] = {0};
    std::vector<uint8_t> data;
    receiveStatus status = receiveStatus::header1;
    uint8_t length = 0;
    uint8_t count = 0;

    net.set_network(myIp, netmask, gateway);
    if (net.connect() != 0)
    {
        printf("connection failed\r\n");
    }
    else
    {
        printf("connection success\r\n");
    }

    sock.open(&net);
    sock.bind(myPort);
    sock.listen(1);

    while (1)
    {
        nsapi_error_t error = 0;
        client = sock.accept(&error);
        if (error == NSAPI_ERROR_OK)
        {
            while (client->recv(rxBuf, sizeof(rxBuf)) > 0)
            {
                for (int i = 0; i < sizeof(rxBuf); i++)
                {
                    switch (status)
                    {
                    case receiveStatus::header1:
                        if (rxBuf[i] == header1)
                        {
                            status = receiveStatus::header2;
                            data.push_back(rxBuf[i]);
                            count++;
                        }
                        break;
                    case receiveStatus::header2:
                        // header1読み込み後
                        // header2が読み込まれたらdata受け取り開始
                        if (rxBuf[i] == header2)
                        {
                            status = receiveStatus::length;
                            data.clear();
                            count = 0;
                        }
                        else
                        // header2以外が読み込まれたらdata受け取り続行
                        {
                            data.push_back(rxBuf[i]);
                            count++;
                            status = receiveStatus::data;
                        }
                        break;
                    case receiveStatus::length:
                        // 長さを保存
                        length = rxBuf[i];
                        // data.resize(length);
                        status = receiveStatus::data;
                        break;
                    case receiveStatus::data:
                        // length == countになるまでdataを保存
                        if (count < length)
                        {
                            data.push_back(rxBuf[i]);

                            count++;
                        }
                        else
                        {
                            status = receiveStatus::header1;
                            if (rxBuf[i] == end)
                            {
                                uint8_t temp1[4] = {data[3], data[2], data[1], data[0]};
                                uint8_t temp2[4] = {data[7], data[6], data[5], data[4]};
                                const float period = *reinterpret_cast<float *>(&temp1[0]);
                                const float value = *reinterpret_cast<float *>(&temp2[0]);
                                printf("period : %f value : %f\r\n", period, value);
                                led.period(period);
                                led.write(value);
                            }
                        }
                        break;
                    }
                }
            }
            client->close();
        }
    }
    sock.close();
    net.disconnect();
    return 0;
}