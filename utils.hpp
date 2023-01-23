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

using IpAddress = std::array<uint8_t,Ipinfo::len>;

auto split(const std::string& str, char d)
{
//    auto r=new std::vector<std::string>;
    auto r=std::vector<std::string>();

    auto stop = str.find_first_of(d);
    decltype(stop) start = 0;

    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return std::move(r);
}


auto ipParser(const  std::vector<std::string>& ipStr)
{
    IpAddress numIp{192,168,0,1};
    std::optional<decltype(numIp)> ret{std::nullopt};

    if(ipStr.size()!=Ipinfo::len)
    {
        std::cout<<"Faild IP address string"<<std::endl;
        return ret;
    }

    auto ipD=numIp.begin();
    for(const auto& ipPartStr:ipStr)
    {
        try
        {
            auto ipPartInt=std::stoul(ipPartStr);
            if(ipPartInt>Ipinfo::ipMax)
            {
                std::cout<<"Faild IP address part"<<ipPartInt<<std::endl;
                return ret;
            }
            *ipD =ipPartInt;
            ipD++;
        }
        catch(const std::exception &e)
        {
            std::cout<<"Faild IP address part: "<<ipPartStr<<std::endl;
            return ret;
        }
    }

    ret=numIp;
    return ret;
}

template <typename T, typename S>
void parseStream(T& ipArray, S& stream)
{
    for(std::string line; std::getline(stream, line);)
    {
        const auto primeryString =split(line, '\t');                //попробовал поиграться с move.
        const auto ipString      =split(primeryString.at(0),'.');
        const auto ipNum         =ipParser(ipString);
        if(ipNum)
        {
            ipArray.push_back(ipNum.value());
        }
    }
}

inline void printIP(const IpAddress& ip)
{
    bool isFirst=true;
    for(const auto& byte:ip)
    {
        if(isFirst)   {   std::cout<<std::to_string(byte);  isFirst=false;    }
        else          {   std::cout<<'.'<<std::to_string(byte);               }
    }
}

void printIpList(const std::vector<IpAddress>& ipPoolInt)
{
    for(const auto& ip:ipPoolInt)
    {
        printIP(ip);
        std::cout<<std::endl;
    }
}

template <class List, class Compare>
void ipFilter(const List& list, Compare comp)
{
     for(const auto& item:list)
     {
        if(comp(item))
        {
            printIP(item);
            std::cout<<std::endl;
        }

     }
}






#endif // UTILS_HPP
