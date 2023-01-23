#include "utils.hpp"
#include <algorithm>

int main()
{
    try
      {
        //ввод данных
          std::vector<IpAddress> ipPoolInt;

          auto file=std::ifstream{"ip_filter.tsv"};

          if(!file.is_open())
          {
              parseStream(ipPoolInt, std::cin);
          }
          else
          {
              parseStream(ipPoolInt, file);
          }

           //сортировка

          std::sort(ipPoolInt.begin(), ipPoolInt.end(),std::greater{});
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
