#include <iostream>
#include <stdlib.h>
#include <string>
#include <random>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <sstream>


using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

vector<string> Questions;


string itostr(int i)
{
    stringstream ss;
    ss << i;

    string str;
    ss >> str;

    return str;
}

string curTime()
{
    time_t now = time(0);
    tm* now2=localtime(&now);
    string strtime=itostr(now2->tm_year+1900)+"_"+itostr(now2->tm_mon+1)+"_"+itostr(now2->tm_mday)+"_"+itostr(now2->tm_sec);
    return strtime;
}

int main()
{
    ifstream qq("D:\\Future\\C++ Practice\\_Questions Shower\\questions\\questions.txt");
    while(!qq.eof()){
        string ele;
        getline(qq, ele, '@');
        Questions.push_back(ele);
    }

    qq.close();


    string strDate = curTime();
    string filename = "Test "+strDate+".txt";

    ofstream NewFile(filename);

    int n = Questions.size();
    int i=1;

    srand(time(0));

    while(1)
    {
        int qnum = rand()%n;
        string qnum2;
        qnum2+=itostr(i++);
        string q = qnum2+". "+Questions.at(qnum);

        cout<<endl<<endl<<q<<endl;
        NewFile<<q<<endl;

        string answer;
        cin.sync(); // 清空cin
        getline(cin, answer, '@'); // 结束符为 @， 不为回车 。 只有getline 能够办到这一点。 getline 在 string.h 里面。
        NewFile<<answer<<endl<<endl;

        char contn=0;
        cout<<endl<<"Continue?? Y or N";
        cin>>contn;

        if(contn=='y' || contn =='Y') continue;
        else break;
    }

    NewFile.close();
}
