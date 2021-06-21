#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>       

using namespace std;


struct point {
    float m_x;
    float m_y;
    float m_t;
    friend std::istream& operator>>(std::istream& is, point& info)
    {
        char skip ;
        is >> info.m_x;
        is >> skip;
        is >> info.m_y;
        is >> skip;
        is >> info.m_t;
        return is;
    }
};
struct info_type
{
    vector<point> linfo;
    int  m_id;
    friend std::istream& operator>>(std::istream& is, info_type& info)
    {
        is >> info.m_id;
		char skip;
        for(point infor; (is >> skip) && (skip == '/' || skip == '|' || skip == '*') && (is >> infor);) 
        {  
           info.linfo.push_back(infor);
        }
        return is;
    }
};

float vitesse(point a, point b ) {
    return sqrt(pow((a.m_x - b.m_x),2) +  pow((a.m_y - b.m_y),2))/(a.m_t - b.m_t);
}
int main()
{
	auto file = std::ifstream("file.txt");
    std::vector<info_type> v;
    std::vector<int> cars; // cars with average speed  more than 5 m / s

    for(info_type info; file >> info;) // keep reading until we run out
    {  
        v.push_back(info);
    }

  
    for(int i =0; i<v.size() ; i++) {
        float s;
        for(int j =1; j<v[i].linfo.size() ; j++) {
            s += vitesse(v[i].linfo[j], v[i].linfo[j-1]);
        }
        if (s/v[i].linfo.size() > 5 ) {
            cars.push_back(v[i].m_id);
        }
    }
  
    file.close();
}
