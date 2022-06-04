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

int main(void)
{
    const char *myIp = "192.168.0.2";
    const char *netmask = "255.255.255.0";
    const char *gateway = "192.168.0.1";
    const int myPort = 2008;
    // const char *pcIp = "192.168.0.12";
    // const int pcPort = 6005;

    const uint8_t header1 = 0xFF;
    const uint8_t header2 = 0xFE;
    const uint8_t end = 0xFD;
    EthernetInterface net;
    TCPSocket sock;
    TCPSocket *client;
    PwmOut led(A0);
    // SocketAddress pc(pcIp, pcPort);
    uint8_t rxBuf[32] = {0};
    std::vector<uint8_t> data;
    uint8_t status = 0;
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
                printf("received\r\n");
                for (int i = 0; i < sizeof(rxBuf); i++)
                {
                    // printf("received : %x\r\n", rxBuf[i]);
                    switch (status)
                    {
                    case 0:
                        printf("case 0\r\n");
                        if (rxBuf[i] == header1)
                        {
                            status = 1;
                            data.push_back(rxBuf[i]);
                            count++;
                        }
                        break;
                    case 1:
                        printf("case 1\r\n");
                        // header1読み込み後
                        // header2が読み込まれたらdata受け取り開始
                        if (rxBuf[i] == header2)
                        {
                            status = 2;
                            data.clear();
                            count = 0;
                        }
                        else
                        // header2以外が読み込まれたらdata受け取り続行
                        {
                            data.push_back(rxBuf[i]);
                            count++;
                            status = 3;
                        }
                        break;
                    case 2:
                        printf("case 2");
                        // 長さを保存
                        length = rxBuf[i];
                        printf("length = %d\r\n", length);
                        // data.resize(length);
                        status = 3;
                        break;
                    case 3:
                        printf("case 3 ");
                        // length == countになるまでdataを保存
                        if (count < length)
                        {
                            data.push_back(rxBuf[i]);
                            printf("%x \r\n", data[count]);

                            count++;
                        }
                        else
                        {
                            status = 0;
                            if (rxBuf[i] == end)
                            {
                                for (int j = 0; j < length; j++)
                                {
                                    printf("%x ", data[j]);
                                }
                                printf("\r\n");

                                // クソコーディング
                                uint8_t temp1[4] = {data[3], data[2], data[1], data[0]};
                                uint8_t temp2[4] = {data[7], data[6], data[5], data[4]};
                                float period = *reinterpret_cast<float *>(&temp1[0]);
                                float value = *reinterpret_cast<float *>(&temp2[0]);
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