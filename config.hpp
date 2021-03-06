#pragma once

#ifdef LEFT
static constexpr char myIp[] = "192.168.0.2";
static constexpr char netmask[] = "255.255.255.0";
static constexpr char gateway[] = "192.168.0.1";
static constexpr int myPort = 2008;
#elif RIGHT
static constexpr char myIp[] = "192.168.0.3";
static constexpr char netmask[] = "255.255.255.0";
static constexpr char gateway[] = "192.168.0.1";
static constexpr int myPort = 2008;
#endif