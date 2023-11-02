#include <iostream>
#include <getopt.h>
#include <iomanip>
#include <locale.h>
#include <chrono>
#include <thread>
using namespace std;
void open (string filename);
int main(int argc,char *argv[]){
    setlocale(LC_ALL, "Russian");
    int option_index,result;
    static struct option long_options[] = {
            {"min",  required_argument, NULL, 'm'},
            {"hour", required_argument, NULL, 'h'},
            {"file", required_argument, NULL, 'f'},
            {0,0,0,0}
    };
    int min = -1,hour = -1;
    string filename;
    while ( (result = getopt_long_only(argc,argv,"mhf", long_options, &option_index)) != -1){
         switch (result){
            case 'm':
                if (optarg) min = atoi (optarg);
                break;
            case 'h':
               if (optarg) hour = atoi (optarg);
                break;
            case 'f':
               if (optarg) filename.assign(optarg);
                break;
         }
    }
    if (min<0 || hour<0 || !filename.size()){  
        cout << "dterm --min=XX --hour=YY --file=script" << endl;
        return -1;
    }else {
         wcout << L"Периодический старт в ";
         cout << std::setw(2) << std::setfill('0') << hour << ":";
         cout << std::setw(2) << std::setfill('0') << min << ":00, ";
         wcout << L"скрипта расположенного в файле: " ;
         cout << filename << endl;
         std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         char buf[100] = {0};
         std::strftime(buf, sizeof(buf), "%H:%M:%S %d-%m-%Y", std::localtime(&now));
         cout << buf << endl;

    }
    int current_day = 0;
    while (true){
        std::time_t now = std::time(nullptr);
        tm* timeInfo = std::localtime(&now);
        int Hour = timeInfo->tm_hour;
        int Min = timeInfo->tm_min;
        int day = timeInfo->tm_mday;
        if (hour==Hour && min==Min && current_day!=day){
            current_day=day;
            wcout << L"Запускаем приложение: " ;
            cout  << filename << endl;
            open(filename);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}

void open (string filename){
    // FILE *file;
    // file = fopen(filename.c_str(), "r");
    // if(file == NULL) {
    //     wcout << L"Не могу открыть такой файл:";
    //     cout << filename << endl;
    //     exit (1);
    // }
    // fclose(file);
    if (system(filename.c_str())){
        wcout << L"Что то короче пошло не так, и файл выдал код возврата отличный от нуля, ну какой смысл продолжать. Завязываем с этим :( " ;
        exit (1);
    }
}