#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include "windows.h" 
using namespace std;

class CurrentTime
{
private:
    time_t     now = time(0);
    struct tm  Tstruct;
    char       buf[3];
public:
    int currentTime(int Choice) //This Function Is For Learning The Current Time
    {
        int Time;
#pragma warning(disable: 4996)
        Tstruct = *localtime(&now);
#pragma warning(default: 4996)

        switch (Choice)
        {
        case 1:
            strftime(buf, sizeof(buf), "%H", &Tstruct);
            break;
        case 2:
            strftime(buf, sizeof(buf), "%M", &Tstruct);
            break;
        }

        return stoi(buf);
    }
};

class Marmaray : public CurrentTime
{
private:
    string GtoHStations[43];    //GtoH Means Gebze->Halkalý
    int GtoHRange[42];
    int GtoHTime[42];

    string HtoGStations[43];    //HtoG Means Halkalý->Gebze
    int HtoGRange[42];
    int HtoGTime[42];

    bool Way;   //true->HtoG            false->GtoG
    int StartStation, StopStation;
public:
    Marmaray()  //Define The Stations,Ranges And Times With Constructor
    {
        string TempArr1[43] = { "Gebze","Darica","Osmangazi",
        "Fatih","Cayirova","Tuzla","Icmeler","Aydintepe",
        "Guzelyali","Tersane","Kaynarca","Pendik","Yunus",
        "Kartal","Basak","Atalar","Cevizli","Maltepe","Sureyya Plaji",
        "Idealtepe","Kucukyali","Bostanci","Suadiye","Erenkoy","Goztepe",
        "Feneryolu","Sogutlucesme","Ayrilikcesmesi","Uskudar","Sirkeci",
        "Yenikapi","Kazlicesme","Zeytinburnu","Yenimahalle","Bakirkoy",
        "Atakoy","Yesilyurt","Yesilkoy","Florya Akvaryum","Florya",
        "Kucukcekmece","Mustafa Kemal","Halkali" };

        int TempArr2[42] = { 2,1,2,2,3,3,1,1,1,2,3,2,2,1,1,2,2,1,2,1,2,1,1,1,1,1,1,3,3,2,4,1,2,1,2,5,1,2,1,3,2,2 };
        int TempArr3[42] = { 3,3,3,3,4,3,2,2,2,3,3,3,3,3,2,3,3,2,2,2,3,2,3,3,2,3,5,4,4,3,4,4,3,2,2,3,2,4,2,3,3,3 };
        for (int i = 0, j = 42; i < 43; i++, j--)
        {
            GtoHStations[i] = TempArr1[i];
            HtoGStations[i] = TempArr1[j];

            if (i != 42)
            {
                GtoHRange[i] = TempArr2[i];
                HtoGRange[i] = TempArr2[j - 1];

                GtoHTime[i] = TempArr3[i];
                HtoGTime[i] = TempArr3[j - 1];
            }
        }
    }
    void SetWay(bool _Way)
    {
        Way = _Way;
    }
    int ChoiceStation(int StartIndex = 0) //Print And Choice Function
    {
        int i = StartIndex, Count = 1;

        while (i <= 42)
        {
            if (Way)
                cout << Count << "-> " << HtoGStations[i] << endl;
            else
                cout << Count << "-> " << GtoHStations[i] << endl;
            i++;
            Count++;
        }

        do
        {
            cin >> i;
        } while ((0 >= i) || (i > 43 - StartIndex));

        return i - 1;
    }
    string GetStation(int Index)  
    {
        if (Way)
            return HtoGStations[Index];
        else
            return GtoHStations[Index];
    }
    int GetRange(int StartIndex, int StopIndex)
    {
        int Sum = 0;

        for (int i = StartIndex; i < StopIndex; i++)
        {
            if (Way)
                Sum += HtoGRange[i];
            else
                Sum += GtoHRange[i];
        }

        return Sum;
    }
    int GetTime(int StartIndex, int StopIndex)
    {
        int Sum = 0;

        for (int i = StartIndex; i < StopIndex; i++)
        {
            if (Way)
                Sum += HtoGTime[i];
            else
                Sum += GtoHTime[i];
        }

        return Sum;
    }
};

int main()
{
    system("COLOR 3");  

    int StartIndex, StopIndex, TotalTime, Hour, Min;
    char Choice;

    Marmaray Obj;

    while (1)
    {
        system("CLS");

        cout << "H-Halkali->Gebze To Get Information About This Direction" << endl;
        cout << "G-Gebze->Halkali To Get Information About This Direction" << endl << endl;
        cout << "S-To End The Program" << endl;

        do
        {
            Choice = _getch();
        } while ((Choice != 'H') && (Choice != 'h') &&
            (Choice != 'G') && (Choice != 'g') &&
            (Choice != 'S') && (Choice != 's'));

        switch (Choice)
        {
        case 'H':
        case 'h':
            system("CLS");
            Obj.SetWay(true);
            break;
        case 'G':
        case 'g':
            system("CLS");
            Obj.SetWay(false);
            break;
        default:
            return 0;
        }

        cout << "Please Select Your Start Station" << endl;
        Sleep(1000);
        StartIndex = Obj.ChoiceStation();
        system("CLS");

        cout << "Please Select Your Stop Station" << endl;
        Sleep(1000);
        StopIndex = Obj.ChoiceStation(StartIndex) + StartIndex;
        system("CLS");

        cout << Obj.GetStation(StartIndex) << "->" << Obj.GetStation(StopIndex) << endl << endl;
        cout << "Q-Get On The Road With Automatic (Select Your Current Time)" << endl;
        cout << "W-Get On The Road With Manuel" << endl;

        do
        {
            Choice = _getch();
        } while ((Choice != 'Q') && (Choice != 'q') &&
            (Choice != 'W') && (Choice != 'w'));
        system("CLS");

        TotalTime = Obj.GetTime(StartIndex, StopIndex);
        switch (Choice)
        {
        case 'Q':
        case 'q':
            Hour = Obj.currentTime(1);
            Min = Obj.currentTime(2);
            break;
        case 'W':
        case 'w':

            do
            {
                system("CLS");
                cout << "Set A Start Time Between 1-12: ";
                cin >> Hour;
            } while ((1 > Hour) || (Hour > 12));

            do
            {
                system("CLS");
                cout << "Set A Start Minute Between 0-59: ";
                cin >> Min;
            } while ((0 > Min) || (Min > 59));

            break;
        }

        system("CLS");

        cout << Obj.GetStation(StartIndex) << "->" << Obj.GetStation(StopIndex) << endl;
        cout << StopIndex - StartIndex << " Station" << endl;
        cout << Obj.GetRange(StartIndex, StopIndex) << " KM" << endl;
        cout << TotalTime << " Minute" << endl << endl;

        if(Hour<=9)
            if(Min<=9)
                cout << "Time Of Start: 0" << Hour << ":0" << Min << endl;
            else
                cout << "Time Of Start: 0" << Hour << ":" << Min << endl;
        else
            if (Min <= 9)
                cout << "Time Of Start: " << Hour << ":0" << Min << endl;
            else
                cout << "Time Of Start: " << Hour << ":" << Min << endl;

        //Conditions Used For A Beautiful Output (I Mean 02.02 Prevents It From Writing The Timezone As 2.2.)
        if ((Hour + ((Min + TotalTime) / 60)) >= 13)
            if(((Hour + ((Min + TotalTime) / 60)) - 12)<=9)
                if (((Min + TotalTime) % 60) <= 9)
                    cout << "Time Of Arrival: 0" << (Hour + ((Min + TotalTime) / 60)) - 12 << ":0" << (Min + TotalTime) % 60;
                else
                    cout << "Time Of Arrival: 0" << (Hour + ((Min + TotalTime) / 60)) - 12 << ":" << (Min + TotalTime) % 60;
            else
                if (((Min + TotalTime) % 60) <= 9)
                    cout << "Time Of Arrival: " << (Hour + ((Min + TotalTime) / 60)) - 12 << ":0" << (Min + TotalTime) % 60;
                else
                    cout << "Time Of Arrival: " << (Hour + ((Min + TotalTime) / 60)) - 12 << ":" << (Min + TotalTime) % 60;
        else if((Hour + ((Min + TotalTime) / 60))<=9)
            if (((Min + TotalTime) % 60) <= 9)
                cout << "Time Of Arrival: 0" << (Hour + ((Min + TotalTime) / 60)) << ":0" << (Min + TotalTime) % 60;
            else
                cout << "Time Of Arrival: 0" << (Hour + ((Min + TotalTime) / 60)) << ":" << (Min + TotalTime) % 60;
        else
            if (((Min + TotalTime) % 60) <= 9)
                cout << "Time Of Arrival: " << (Hour + ((Min + TotalTime) / 60)) << ":0" << (Min + TotalTime) % 60;
            else
                cout << "Time Of Arrival: " << (Hour + ((Min + TotalTime) / 60)) << ":" << (Min + TotalTime) % 60;

        cout << endl << endl << "Press Any Key To Continue";

        _getch();
    }
}
