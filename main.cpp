#include "utils.hpp"
#include <algorithm>

int main()
{
    try
      {
        //ввод данных
          std::vector<IpAddress> ipPoolInt;

          std::ifstream file("ip_filter.tsv");
          if(!file.is_open())
          {
              std::cout<<"FileNotfound"<<std::endl;
              return 0;
          }
          std::cout<<"FileOpened"<<std::endl;

          //разбор
          for(std::string line; std::getline(file, line);)
          {
              const auto& primeryString =split(line, '\t');
              const auto& ipString      =split(primeryString.at(0),'.');
              const auto& ipNum         =ipParser(ipString);
              if(ipNum)
              {
                  ipPoolInt.push_back(ipNum.value());
              }
          }

          //сортировка

          auto compareRuleReverse=[](auto a, auto b)
          {
              auto ai=a.cbegin();
              auto bi=b.cbegin();
              bool ret;

              for(;ai!=a.cend();++ai, ++bi)
              {
                  ret = ((*ai)>(*bi));

                  if( (*ai==*bi) && (ai!=(a.cend()-1))  ){continue;}
                  return ret;
              }
              return ret;
          };

          std::sort(ipPoolInt.begin(), ipPoolInt.end(), compareRuleReverse);
          printIpList(ipPoolInt);

          //фильтры

          auto firstByteCompare =   [cmp=1]             (auto v){return (v[0]==cmp);};
          auto twoBytesCompare  =   [cmp1=46, cmp2=70]  (auto v){return (v[0]==cmp1)&&(v[1]==cmp2);};
          auto anyBytesCompare  =   [cmp=46]            (auto v)
          {
              for(const auto& el:v)
              {
                  if(el==cmp){return true;}
              }
              return false;
          };

          ipFilter(ipPoolInt, firstByteCompare);
          ipFilter(ipPoolInt, twoBytesCompare);
          ipFilter(ipPoolInt, anyBytesCompare);

      }
      catch(const std::exception &e)
      {
          std::cerr << e.what() << std::endl;
      }
    return 0;
}
