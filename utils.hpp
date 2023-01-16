#ifndef UTILS_HPP
#define UTILS_HPP
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <array>
#include <optional>

enum Ipinfo
{
    len=4,
    ipMax=255,
    ipMin=0
};


void printIpList(const std::vector<std::array<uint8_t,Ipinfo::len>>& ipPoolInt)
{
    for(const auto& ip:ipPoolInt)
    {
        bool isFirst=true;
        for(const auto& byte:ip)
        {
            if(isFirst)   {   std::cout<<std::to_string(byte);  isFirst=false;    }
            else          {   std::cout<<'.'<<std::to_string(byte);               }
        }
        std::cout<<std::endl;
    }
}

auto ipParser(const  std::vector<std::string>& ipStr)
{
    std::array<uint8_t,Ipinfo::len> numIp{192,168,0,1};
    std::optional<decltype(numIp)> ret{std::nullopt};

    if(ipStr.size()!=Ipinfo::len)       {       return ret; }

    auto ipD=numIp.begin();
    for(const auto& ipPartStr:ipStr)
    {
        try
        {
            auto ipPartInt=std::stoul(ipPartStr);
            if(ipPartInt>Ipinfo::ipMax) {       return ret; }
            *ipD =ipPartInt;
            ipD++;
        }
        catch(const std::exception &e)  {       return ret; }
    }

    ret=numIp;
    return ret;
}

auto split(const std::string& str, char d)
{
    auto r=new std::vector<std::string>;

    auto stop = str.find_first_of(d);
    decltype(stop) start = 0;

    while(stop != std::string::npos)
    {
        r->push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r->push_back(str.substr(start));

    return std::move(*r);
}
#endif // UTILS_HPP
