#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <windows.h>
#include <time.h>

#include "user.cpp"
#include "meal.cpp"
#include "menu.cpp"
#include "product.cpp"
#include "progress.cpp"
#include "food.cpp"
#include "FOODTRACKER.h"
using namespace std;

FoodTracker u;
#define CREATE_USER 1
#define ACCESS_USER 2
#define EDIT_USER   3

#define BREAKFAST_PROCENTAGE 20
#define LUNCH_PROCENTAGE 40
#define DINNER_PROCENTAGE 30
#define SNACKS_PROCENTAGE 10
#define procentage 10

#define USER 1
#define LOG  2
#define DATA 3

int MENU_STATE = USER;

void access_user();
void data_menu();

int calc_cal(User::BMI b, User::metabolism m, User::goal g, double kg)
{
    if (b == 0)
        if (g == 2)
        {
            if (m == 2)
                return 15 * 2.2 * kg + 700;
            else
                if (m == 1)
                    return 15 * 2.2 * kg + 600;
        }
        else
        {
            if (g == 1)
                return 15 * 2.2 * kg + 100;
        }
    else
        if (b == 1)
        {
            if (g == 2)
            {
                if (m == 2)
                    return 15 * 2.2 * kg + 600;
                else
                    if (m == 1)
                        return 15 * 2.2 * kg + 500;
            }
            else
            {
                if (g == 1)
                    return 15 * 2.2 * kg + 100;
                else
                    if (g == 0)
                        if (m == 2)
                            return 15 * 2.2 * kg - 100;
                        else
                            return 15 * 2.2 * kg - 200;
            }
        }
        else
        {
            if (b == 2)
                if (g == 2)
                {
                    if (m == 1)
                        return 15 * 2.2 * kg + 500;
                    else
                        if (m == 0)
                            return 15 * 2.2 * kg + 400;
                }
                else
                {
                    if (g == 1)
                        return 15 * 2.2 * kg + 100;
                    else
                        if (g == 0)
                            if (m == 1)
                                return 15 * 2.2 * kg - 200;
                            else
                                return 15 * 2.2 * kg - 300;
                }

            else
            {
                if (b == 3)
                {
                    if (g == 0)
                        if (m == 1)
                            return 15 * 2.2 * kg - 400;
                        else
                            return 15 * 2.2 * kg - 500;
                }


            }
        }
}
double calc_prot(User::BMI b, User::metabolism m, User::goal g, double kg)
{
    if (b == 0)
        if (g == 2)
        {
            if (m == 2)
                return 1.8 * kg;
            else
                if (m == 1)
                    return 1.7 * kg;
        }
        else
        {
            if (g == 1)
                return 1.5 * kg;
        }
    else
        return 1.5 * kg;
}
double calc_carb(User::BMI b, User::metabolism m, User::goal g, double kg)
{
    if (b == 0)
        if (g == 2)
        {
            if (m == 2)
                return 7 * kg;
            else
                if (m == 1)
                    return 6 * kg;
        }
        else
        {
            if (g == 1)
                return 5 * kg;
        }
    else
        if (b == 1)
            return 4 * kg;
        else
        {
            if (b == 2)
                return 3 * kg;
            else
            {
                if (b == 3)
                {
                    if (g == 0)
                        if (m == 1)
                            return 3 * kg;
                        else
                            return 2 * kg;
                }


            }
        }
}
double calc_fat(int c, double p, double b)
{
    return (c - (p * 4) - (b * 4)) / 9;
}
void see_sex(int a)
{   if(a == 0)
    cout << "Sex: Male" << endl;
    else
    cout << "Sex: Female" << endl;
}
void see_activity(User::activity a)
{
    cout << "Activity: ";
    if (a == 0)
        cout << "Sedentary" << endl;
    else
        if (a == 1)
            cout << "Light" << endl;
        else
            if (a == 2)
                cout << "Moderate" << endl;
            else
                cout << "Intense" << endl;
}
void see_goal(User::goal g)
{
    cout << "Goal: ";
    if (g == 0)
        cout << "Weight loss" << endl;
    else
        if (g == 1)
            cout << "Mentain" << endl;
        else
            cout << "Weight gain" << endl;
}
void see_BMI(User::BMI b)  
{
    cout << "BMI ";
    if (b == 0)
        cout << "Under";
    else
        if (b == 1)
            cout << "Normal";
        else
            if (b == 2)
                cout << "Over";
            else
                if (b == 3)
                    cout << "Obese";
}
void see_metabolism(User::metabolism m)
{
    cout << endl << "Metabolism ";
    if (m == 0)
        cout << "Slow" << endl;
    else
        if (m == 1)
            cout << "Normal" << endl;
        else
            cout << "Fast" << endl;
}
ostream& operator<<(ostream& o, Progress p) {
    o << "<"<< p.getConsumption() << "," << p.getCarbohydrate() << "," << p.getProtein() << "," << p.getFat()<<">" << endl;

    return o;
}

vector<Product> select_food(std::vector<Food> vector, int total_cal)
{
    std::vector<Product> selected_food;

    int actual_cal = 0;

    int min_total_cal = total_cal - total_cal * procentage / 100;
    int max_total_cal = total_cal;

    do {

        Sleep(100);
        clock_t t = clock();

        srand((unsigned)time(0));
        int rand_index = (rand() * t) % vector.size();

        Food aliment = vector[rand_index];

        if (actual_cal + aliment.getCalories() <= max_total_cal) 
        {
            Product aliment2;
            aliment2.foodstuff.setName(aliment.getName());
            aliment2.setQuantity(100);
            aliment2.setServings(1);
            selected_food.push_back(aliment2);
            actual_cal += aliment.getCalories();
        }
    } while (!((actual_cal <= max_total_cal) && (actual_cal >= min_total_cal)));


    return selected_food;
}

void see_menu1()
{
    cout << "--------------------MENU_1--------------------" << endl;
    cout << "Please choose one of the options below:" << endl;
    cout << "1.Create a new user." << endl;
    cout << "2.Access an existing user." << endl;
    cout << "3.Edit an existing user." << endl;
    cout << "4.Exit app." << endl;
}

void see_menu2()
{
    cout << "--------------------MENU_2--------------------" << endl;
    cout << "Please choose one of the options below:" << endl;
    cout << "1.See the entire list of foods." << endl;
    cout << "2.Add a new food." << endl;
    cout << "3.Data view." << endl;
    cout << "4.Back." << endl;
}

void see_menu3()
{
    cout << "--------------------MENU_3--------------------" << endl;
    cout << "1.See your progress." << endl;
    cout << "2.See food." << endl;
    cout << "3.Add new food." << endl;
    cout << "4.Back." << endl;
}

void see_menu_3_1()
{
    cout << "\t1.Real." << endl;
    cout << "\t2.Expected." << endl;
}

void see_menu_3_2()
{
    cout << "\t1.Consumed." << endl;
    cout << "\t2.Suggested." << endl;
}

void see_menu_3_12()
{
    
    cout << "\t1.Breakfast." << endl;
    cout << "\t2.Lunch." << endl;
    cout << "\t3.Dinner." << endl;
    cout << "\t4.Snacks." << endl;
    cout << "\t5.Total" << endl;
}
void see_menu_3_3()
{
    cout << "\t1.Breakfast." << endl;
    cout << "\t2.Lunch." << endl;
    cout << "\t3.Dinner." << endl;
    cout << "\t4.Snacks." << endl;
}

void create_user()
{
    system("cls");
    ifstream f("account.txt");
    f.seekg(0, f.beg);
    if (f.peek() != EOF)
    {
        cout << "An user has already been created! Do you want to create a new user?" << endl;
        cout << "1.Yes." << endl;
        cout << "2.No." << endl;
        int i;
        cout << "Your option:";
        cin >> i;
        if (i == 1)
        {
            f.close();
            string data;
            int a;
            double b;
            ofstream f("account.txt");
            cout << "Name:";
            cin.ignore(256, '\n');
            getline(cin, data);
            f << data << ",";
            u.acc.setName(data);
            cout << "Age:";
            cin >> a;
            f << a << ",";
            u.acc.setAge(a);
            cout << "Sex(male/female):";
            cin >> data;
            f << data << ",";
            if (data.compare("male") == 0)
                u.acc.setSex(0);
            else
                u.acc.setSex(1);
            cout << "Height:";
            cin >> b;
            f << b << ",";
            u.acc.setHeight(b);
            cout << "Weight:";
            cin >> b;
            f << b << ",";
            u.acc.setWeight(b);
            cout << "Weight_goal:";
            cin >> b;
            f << b << ",";
            u.acc.setWeight_Goal(b);
            cout << "Activity(sedentary/light/moderate/intense):";
            cin >> data;
            f << data << ",";
            if (data.compare("sedentary") == 0)
                u.acc.setActivity(User::Sedentary);
            else
                if (data.compare("light") == 0)
                    u.acc.setActivity(User::Light);
                else
                    if (data.compare("moderate") == 0)
                        u.acc.setActivity(User::Moderate);
                    else
                        u.acc.setActivity(User::Intense);
            cout << "Goal(weight_loss/mentain/weight_gain):";
            cin >> data;
            f << data;
            if (data.compare("weight_loss") == 0)
                u.acc.setGoal(User::Weight_loss);
            else
                if (data.compare("mentain") == 0)
                    u.acc.setGoal(User::Mentain);
                else
                    if (data.compare("weight_gain") == 0)
                        u.acc.setGoal(User::Weight_gain);
            f.close();
            std::ofstream ofs;
            ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
            ofs << "{" << endl << "0.0.0" << endl << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "/" << endl << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl
                << "*" << endl << "*" << endl << "/" << endl << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl << "*" << endl << "*" << endl << "/" << endl
                << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl << "*" << endl << "*" << endl << "/" << endl << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl
                << "*" << endl << "*" << endl << "/"<<endl<<"}";
            ofs.close();
        }
        else

        {
            cout << "Return to main menu. Press any key." << endl;
            (void)_getch();
        }
    }
    else
    {
        f.close();
        string data;
        int a;
        double b;
        ofstream f("account.txt");
        cout << "Create a new user.";
        cout << "Name:";
        cin.ignore(256, '\n');
        getline(cin, data);
        f << data << ",";
        u.acc.setName(data);
        cout << "Age:";
        cin >> a;
        f << a << ",";
        u.acc.setAge(a);
        cout << "Sex(male/female):";
        cin >> data;
        f << data << ",";
        if (data.compare("male") == 0)
            u.acc.setSex(0);
        else
            u.acc.setSex(1);
        cout << "Height:";
        cin >> b;
        f << b << ",";
        u.acc.setHeight(b);
        cout << "Weight:";
        cin >> b;
        f << b << ",";
        u.acc.setWeight(b);
        cout << "Weight_goal:";
        cin >> b;
        f << b << ",";
        u.acc.setWeight_Goal(b);
        cout << "Activity(sedentary/light/moderate/intense):";
        cin >> data;
        f << data << ",";
        if (data.compare("sedentary") == 0)
            u.acc.setActivity(User::Sedentary);
        else
            if (data.compare("light") == 0)
                u.acc.setActivity(User::Light);
            else
                if (data.compare("moderate") == 0)
                    u.acc.setActivity(User::Moderate);
                else
                    u.acc.setActivity(User::Intense);
        cout << "Goal(weight_loss/mentain/weight_gain):";
        cin >> data;
        f << data;
        if (data.compare("weight_loss") == 0)
            u.acc.setGoal(User::Weight_loss);
        else
            if (data.compare("mentain") == 0)
                u.acc.setGoal(User::Mentain);
            else
                if (data.compare("weight_gain") == 0)
                    u.acc.setGoal(User::Weight_gain);
        f.close();
        std::ofstream ofs;
        ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
        ofs << "{" << endl << "0.0.0" << endl << "<0,0,0,0>" << endl<<"<0,0,0,0>" << endl << "/" << endl << "<0,0,0,0>" << endl<< "<0,0,0,0>" << endl << "*" << endl
            <<"*" << endl << "*" << endl << "/" << endl<< "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl << "*" << endl << "*" << endl << "/" << endl
            << "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl << "*" << endl << "*" << endl << "/" << endl<< "<0,0,0,0>" << endl << "<0,0,0,0>" << endl << "*" << endl
            << "*" << endl << "*" << endl << "/"<<endl<<"}";
        ofs.close();
    }

}
void edit_user()
{
    system("cls");
    ifstream f("account.txt");
    int i=2;
    char cuv[10][20];
    char text[100], separator[] = ",";
    f.getline(text, 100);
    strcpy(cuv[1],strtok(text, separator));
    while (i<=8)
    {
        strcpy(cuv[i], strtok(NULL, separator));
        i++;
    }
    cout << "Please select what you want to change." << endl;
    cout << "1.Name." << endl;
    cout << "2.Age." << endl;
    cout << "3.Sex." << endl;
    cout << "4.Height." << endl;
    cout << "5.Weight." << endl;
    cout << "6.Weight goal." << endl;
    cout << "7.Activity." << endl;
    cout << "8.Goal." << endl;
    cout << "9.Return." << endl;
    int j;
    cout << "Your option:";
    cin >> j;
    
    while (j != 9)
    {
        switch (j)
        {
        case 1:
        {   cout << "Please enter your new name:";
            string data;
            cin.ignore(256, '\n');
            getline(cin, data);
            u.acc.setName(data);
            strcpy(cuv[j],data.c_str());
            break;

        }
        case 2:
        {
            cout << "Please enter your new age:";
            char s[4];
            cin >> s;
            strcpy(cuv[j], s);
            u.acc.setAge(atoi(s));
            break;
        }
        case 3:
        {
            cout << "Please enter your new sex:";
            char s[7];
            cin >> s;
            strcpy(cuv[j], s);
            if (strcmp(s, "male") == 0)
                u.acc.setSex(0);
            else
                u.acc.setSex(1);
            break;

        }
        case 4:
        {
            cout << "Please enter your new height:";
            char d[5];
            cin >> d;
            strcpy(cuv[j], d);
            u.acc.setHeight(std::stod(d));
            break;
        }
        case 5:
        {
            cout << "Please enter your new weight:";
            char d[5];
            cin >> d;
            strcpy(cuv[j], d);
            u.acc.setWeight(atof(d));
            break;
        }
        case 6:
        {
            cout << "Please enter your new weight goal:";
            char d[5];
            cin >> d;
            strcpy(cuv[j], d);
            u.acc.setWeight_Goal(atof(d));
            break;
        }
        case 7:
        {
            cout << "Please enter your new activity:";
            char s[20];
            cin >> s;
            strcpy(cuv[j], s);
            if (strcmp(s, "sedentary") == 0)
                u.acc.setActivity(User::Sedentary);
            else
                if (strcmp(s, "light") == 0)
                    u.acc.setActivity(User::Light);
                else
                    if (strcmp(s, "moderate") == 0)
                        u.acc.setActivity(User::Moderate);
                    else
                        u.acc.setActivity(User::Intense);
            break;
        }
        case 8:
        {
            cout << "Please enter your new goal:";
            char s[20];
            cin >> s;
            strcpy(cuv[j], s);
            if (strcmp(s, "weight_loss") == 0)
                u.acc.setGoal(User::Weight_loss);
            else
                if (strcmp(s, "mentain") == 0)
                    u.acc.setGoal(User::Mentain);
                else
                    if (strcmp(s, "weight_gain") == 0)
                        u.acc.setGoal(User::Weight_gain);
            break;
        }
        }
        cout << "Choose new option:";
        cin >> j;
    }
    f.close();
    MENU_STATE = USER;
    ofstream g("account.txt", ios::trunc);
    for (i = 1;i < 8;i++)
        g << cuv[i] << ",";
    g << cuv[8];
    g.close();
    
}
void user_menu() {
    see_menu1();
    ifstream f("account.txt");
    char text1[100], separator[] = ",";
    f.getline(text1, 100);
    u.acc.setName(strtok(text1, separator));
    u.acc.setAge(atoi(strtok(NULL, separator)));
    if (strcmp(strtok(NULL, separator), "male") == 0)
        u.acc.setSex(0);
    else
        u.acc.setSex(1);
    u.acc.setHeight(std::stod(strtok(NULL, separator)));
    u.acc.setWeight(atof(strtok(NULL, separator)));
    u.acc.setWeight_Goal(atof(strtok(NULL, separator)));
    string s;
    s = strtok(NULL, separator);
    if (s.compare("sedentary") == 0)
        u.acc.setActivity(User::Sedentary);
    else
        if (s.compare("light") == 0)
            u.acc.setActivity(User::Light);
        else
            if (s.compare("moderate") == 0)
                u.acc.setActivity(User::Moderate);
            else
                u.acc.setActivity(User::Intense);

    s = strtok(NULL, separator);
    if (s.compare("weight_loss") == 0)
        u.acc.setGoal(User::Weight_loss);
    else
        if (s.compare("mentain") == 0)
            u.acc.setGoal(User::Mentain);
        else
            if (s.compare("weight_gain") == 0)
                u.acc.setGoal(User::Weight_gain);
    f.close();
    int STATE_USER;
    cout << "Your option:";
    cin >> STATE_USER;

    switch (STATE_USER)
    {
    case CREATE_USER:
        create_user();
        MENU_STATE = USER;
        system("cls");
        break;
    case ACCESS_USER:
        MENU_STATE = LOG;
        access_user();
        break;
    case EDIT_USER:
        edit_user();
        MENU_STATE = USER;
        system("cls");
        break;
    case 4:
        exit(0);
        break;
    default:
        MENU_STATE = USER;
        break;
    }
}
void log_menu(){
    see_menu2();

    int STATE_LOG;
    cout << "Your option:";
    cin >> STATE_LOG;
    if (u.vf.empty())
    {
        ifstream f("data.txt");
        char text[100], separator[] = ",";
        while (!f.eof())
        {
            Food a;
            f.getline(text, 100);
            a.setName(strtok(text, separator));
            a.setCalories(atoi(strtok(NULL, separator)));
            a.setCarbohydrates(std::stod(strtok(NULL, separator)));
            a.setProtein(std::stod(strtok(NULL, separator)));
            a.setFat(std::stod(strtok(NULL, separator)));
            u.vf.push_back(a);

        }
        f.close();
    }
    switch (STATE_LOG)
    {
    case 1:
    {
        system("cls");
        ifstream f("data.txt");
        string getcontent;
        cout << "\tTHE LIST OF FOODS"<<endl;
        while (!f.eof())
        {
            getline(f, getcontent);
            cout << getcontent << endl;
        }
        (void)_getch();
        system("cls");
        MENU_STATE = LOG;
        f.close();
        break;
    }
    case 2:
    {
        ofstream f;
        f.open("data.txt", std::ios::app);
        cout << "Please add new food"<<endl;
        string alim;
        int cal;
        double d;
        Food a;
        cout << "Name: ";
        cin.ignore(256, '\n');
        getline(cin, alim);
        f << endl << alim << ",";
        a.setName(alim);
        cout << "Calories: ";
        cin >> cal;
        a.setCalories(cal);
        f << cal << ",";
        cout << "Carbohydrates: ";
        cin >> d;
        a.setCarbohydrates(d);
        f << d << ",";
        cout << "Proteins: ";
        cin >> d;
        a.setProtein(d);
        f << d << ",";
        cout<< "Fats: ";
        cin >> d;
        a.setFat(d);
        f << d;
        u.vf.push_back(a);
        system("cls");
        f.close();
        MENU_STATE = LOG;
        break;
    }
    case 3:
        MENU_STATE = LOG;
        data_menu();
        break;
    case 4:
        MENU_STATE = USER;
        system("cls");
        break;
    default:
        MENU_STATE = LOG;
        break;
    }
}
void access_user() {
    system("cls");
    log_menu();
}
void data_menu()
{
    char text[50];
    if (u.vm.empty())
    {
        ifstream f("log.txt");
        while (!f.eof())
        {
            f.getline(text, 50);
            while (strcmp(text, "}") != 0)
            {
                Meal aux;
                f.getline(text, 50);
                if (strcmp(text, "{") != 0)
                {
                    aux.setDate(text);
                    f.getline(text, 50);
                    aux.expected_total.setConsumption(atoi(strtok(text, "<,>")));
                    aux.expected_total.setCarbohydrate(atof(strtok(NULL, "<,>")));
                    aux.expected_total.setProtein(atof(strtok(NULL, "<,>")));
                    aux.expected_total.setFat(atof(strtok(NULL, "<,>")));
                    f.getline(text, 50);
                    aux.real_total.setConsumption(atoi(strtok(text, "<,>")));
                    aux.real_total.setCarbohydrate(atof(strtok(NULL, "<,>")));
                    aux.real_total.setProtein(atof(strtok(NULL, "<,>")));
                    aux.real_total.setFat(atof(strtok(NULL, "<,>")));
                    f.getline(text, 50);
                    if (strcmp(text, "/") == 0)
                    {
                        f.getline(text, 50);
                        aux.breakfast.p_expected.setConsumption(atoi(strtok(text, "<,>")));
                        aux.breakfast.p_expected.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.breakfast.p_expected.setProtein(atof(strtok(NULL, "<,>")));
                        aux.breakfast.p_expected.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        aux.breakfast.p_real.setConsumption(atoi(strtok(text, "<,>")));
                        aux.breakfast.p_real.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.breakfast.p_real.setProtein(atof(strtok(NULL, "<,>")));
                        aux.breakfast.p_real.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        if (strcmp(text, "*") == 0)
                        {
                            f.getline(text, 50);
                            if (strcmp(text, "*") != 0)
                            {
                                while (strcmp(text, "*") != 0)
                                {
                                    Product p_aux;
                                    p_aux.foodstuff.setName(strtok(text, ","));
                                    p_aux.setQuantity(atof(strtok(NULL, ",")));
                                    p_aux.setServings(atoi(strtok(NULL, ",")));
                                    aux.breakfast.suggested.push_back(p_aux);
                                    f.getline(text, 50);
                                }
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.breakfast.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                            else {
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.breakfast.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                        }
                        f.getline(text, 50);
                    }
                    if (strcmp(text, "/") == 0)
                    {
                        f.getline(text, 50);
                        aux.lunch.p_expected.setConsumption(atoi(strtok(text, "<,>")));
                        aux.lunch.p_expected.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.lunch.p_expected.setProtein(atof(strtok(NULL, "<,>")));
                        aux.lunch.p_expected.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        aux.lunch.p_real.setConsumption(atoi(strtok(text, "<,>")));
                        aux.lunch.p_real.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.lunch.p_real.setProtein(atof(strtok(NULL, "<,>")));
                        aux.lunch.p_real.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        if (strcmp(text, "*") == 0)
                        {
                            f.getline(text, 50);
                            if (strcmp(text, "*") != 0)
                            {
                                while (strcmp(text, "*") != 0)
                                {
                                    Product p_aux;
                                    p_aux.foodstuff.setName(strtok(text, ","));
                                    p_aux.setQuantity(atof(strtok(NULL, ",")));
                                    p_aux.setServings(atoi(strtok(NULL, ",")));
                                    aux.lunch.suggested.push_back(p_aux);
                                    f.getline(text, 50);
                                }
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.lunch.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                            else {
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.lunch.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                        }
                        f.getline(text, 50);
                    }
                    if (strcmp(text, "/") == 0)
                    {
                        f.getline(text, 50);
                        aux.dinner.p_expected.setConsumption(atoi(strtok(text, "<,>")));
                        aux.dinner.p_expected.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.dinner.p_expected.setProtein(atof(strtok(NULL, "<,>")));
                        aux.dinner.p_expected.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        aux.dinner.p_real.setConsumption(atoi(strtok(text, "<,>")));
                        aux.dinner.p_real.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.dinner.p_real.setProtein(atof(strtok(NULL, "<,>")));
                        aux.dinner.p_real.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        if (strcmp(text, "*") == 0)
                        {
                            f.getline(text, 50);
                            if (strcmp(text, "*") != 0)
                            {
                                while (strcmp(text, "*") != 0)
                                {
                                    Product p_aux;
                                    p_aux.foodstuff.setName(strtok(text, ","));
                                    p_aux.setQuantity(atof(strtok(NULL, ",")));
                                    p_aux.setServings(atoi(strtok(NULL, ",")));
                                    aux.dinner.suggested.push_back(p_aux);
                                    f.getline(text, 50);
                                }
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.dinner.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                            else {
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.dinner.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                        }
                        f.getline(text, 50);
                    }
                    if (strcmp(text, "/") == 0)
                    {
                        f.getline(text, 50);
                        aux.snacks.p_expected.setConsumption(atoi(strtok(text, "<,>")));
                        aux.snacks.p_expected.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.snacks.p_expected.setProtein(atof(strtok(NULL, "<,>")));
                        aux.snacks.p_expected.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        aux.snacks.p_real.setConsumption(atoi(strtok(text, "<,>")));
                        aux.snacks.p_real.setCarbohydrate(atof(strtok(NULL, "<,>")));
                        aux.snacks.p_real.setProtein(atof(strtok(NULL, "<,>")));
                        aux.snacks.p_real.setFat(atof(strtok(NULL, "<,>")));
                        f.getline(text, 50);
                        if (strcmp(text, "*") == 0)
                        {
                            f.getline(text, 50);
                            if (strcmp(text, "*") != 0)
                            {
                                while (strcmp(text, "*") != 0)
                                {
                                    Product p_aux;
                                    p_aux.foodstuff.setName(strtok(text, ","));
                                    p_aux.setQuantity(atof(strtok(NULL, ",")));
                                    p_aux.setServings(atoi(strtok(NULL, ",")));
                                    aux.snacks.suggested.push_back(p_aux);
                                    f.getline(text, 50);
                                }
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.snacks.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                            else {
                                f.getline(text, 50);
                                if (strcmp(text, "*") != 0)
                                {
                                    while (strcmp(text, "*") != 0)
                                    {
                                        Product p_aux;
                                        p_aux.foodstuff.setName(strtok(text, ","));
                                        p_aux.setQuantity(atof(strtok(NULL, ",")));
                                        p_aux.setServings(atoi(strtok(NULL, ",")));
                                        aux.snacks.consumed.push_back(p_aux);
                                        f.getline(text, 50);
                                    }
                                }
                            }
                        }
                        f.getline(text, 50);
                    }
                    f.getline(text, 50);
                }
                u.vm.push_back(aux);
            }
        }
    }
    system("cls");
    cout << "Introduce date(dd.mm.yyyy):";
    string d;
    cin >> d;
    see_menu3();
    int STATE_DATA = 0;
    cout << "Your option:";
    cin >> STATE_DATA;
    while (STATE_DATA != 4)
    {
        switch (STATE_DATA)
        {
        case 1:
        {
            int i, ok = 0, dat;
            for (i = 0;i < u.vm.size();i++)
            {
                if (u.vm[i].getDate().compare(d) == 0)
                {
                    ok = 1;
                    dat = i;
                    break;
                }
            }
            if (ok == 0)
            {
                system("cls");
                cout << "The date could not be found in the database." << endl;
                cout << "Creating a new day";
                Meal m_aux;
                m_aux.setDate(d);
                m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                cout << ".";
                m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                m_aux.breakfast.p_expected = m_aux.expected_total % BREAKFAST_PROCENTAGE;
                m_aux.lunch.p_expected =m_aux.expected_total % LUNCH_PROCENTAGE;
                m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                m_aux.snacks.p_expected =m_aux.expected_total % SNACKS_PROCENTAGE;
                cout << ".";
                m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                cout << ".";
                m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                cout << ".";
                m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                cout << ".";
                m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                cout << ".";
                u.vm.push_back(m_aux);
                cout << "."<<endl;
                cout << "Day created! Press any key to return!";
            }
            else
            {
                see_menu_3_1();
                int op1, op2;
                cout << "Choose one: ";
                cin >> op1;
                see_menu_3_12();
                cout << "Choose one: ";
                cin >> op2;
                if (op1 == 2)
                {
                    if (op2 == 1)
                    {
                        cout << "Calories: ";
                        cout << u.vm[dat].breakfast.p_expected.getConsumption();
                        cout << endl << "Carbohydrates: ";
                        cout << u.vm[dat].breakfast.p_expected.getCarbohydrate();
                        cout << endl << "Proteins: ";
                        cout << u.vm[dat].breakfast.p_expected.getProtein();
                        cout << endl << "Fats: ";
                        cout << u.vm[dat].breakfast.p_expected.getFat();
                        cout << endl;
                    }
                    else {
                        if (op2 == 2)
                        {
                            cout << "Calories: ";
                            cout << u.vm[dat].lunch.p_expected.getConsumption();
                            cout << endl << "Carbohydrates: ";
                            cout << u.vm[dat].lunch.p_expected.getCarbohydrate();
                            cout << endl << "Proteins: ";
                            cout << u.vm[dat].lunch.p_expected.getProtein();
                            cout << endl << "Fats: ";
                            cout << u.vm[dat].lunch.p_expected.getFat();
                            cout << endl;
                        }
                        else {
                            if (op2 == 3)
                            {
                                cout << "Calories: ";
                                cout << u.vm[dat].dinner.p_expected.getConsumption();
                                cout << endl << "Carbohydrates: ";
                                cout << u.vm[dat].dinner.p_expected.getCarbohydrate();
                                cout << endl << "Proteins: ";
                                cout << u.vm[dat].dinner.p_expected.getProtein();
                                cout << endl << "Fats: ";
                                cout << u.vm[dat].dinner.p_expected.getFat();
                                cout << endl;
                            }
                            else {
                                if (op2 == 4)
                                {
                                    cout << "Calories: ";
                                    cout << u.vm[dat].snacks.p_expected.getConsumption();
                                    cout << endl << "Carbohydrates: ";
                                    cout << u.vm[dat].snacks.p_expected.getCarbohydrate();
                                    cout << endl << "Proteins: ";
                                    cout << u.vm[dat].snacks.p_expected.getProtein();
                                    cout << endl << "Fats: ";
                                    cout << u.vm[dat].snacks.p_expected.getFat();
                                    cout << endl;
                                }
                                else {
                                    if (op2 == 5)
                                    {
                                        cout << "Calories: ";
                                        cout << u.vm[dat].expected_total.getConsumption();
                                        cout << endl << "Carbohydrates: ";
                                        cout << u.vm[dat].expected_total.getCarbohydrate();
                                        cout << endl << "Proteins: ";
                                        cout << u.vm[dat].expected_total.getProtein();
                                        cout << endl << "Fats: ";
                                        cout << u.vm[dat].expected_total.getFat();
                                        cout << endl;
                                    }
                                }
                            }
                        }
                    }

                }
                else {
                    if (op1 == 1)
                        if (op2 == 1)
                        {
                            cout << "Calories: ";
                            cout << u.vm[dat].breakfast.p_real.getConsumption();
                            cout << endl << "Carbohydrates: ";
                            cout << u.vm[dat].breakfast.p_real.getCarbohydrate();
                            cout << endl << "Proteins: ";
                            cout << u.vm[dat].breakfast.p_real.getProtein();
                            cout << endl << "Fats: ";
                            cout << u.vm[dat].breakfast.p_real.getFat();
                            cout << endl;
                        }
                        else {
                            if (op2 == 2)
                            {
                                cout << "Calories: ";
                                cout << u.vm[dat].lunch.p_real.getConsumption();
                                cout << endl << "Carbohydrates: ";
                                cout << u.vm[dat].lunch.p_real.getCarbohydrate();
                                cout << endl << "Proteins: ";
                                cout << u.vm[dat].lunch.p_real.getProtein();
                                cout << endl << "Fats: ";
                                cout << u.vm[dat].lunch.p_real.getFat();
                                cout << endl;
                            }
                            else {
                                if (op2 == 3)
                                {
                                    cout << "Calories: ";
                                    cout << u.vm[dat].dinner.p_real.getConsumption();
                                    cout << endl << "Carbohydrates: ";
                                    cout << u.vm[dat].dinner.p_real.getCarbohydrate();
                                    cout << endl << "Proteins: ";
                                    cout << u.vm[dat].dinner.p_real.getProtein();
                                    cout << endl << "Fats: ";
                                    cout << u.vm[dat].dinner.p_real.getFat();
                                    cout << endl;
                                }
                                else {
                                    if (op2 == 4)
                                    {
                                        cout << "Calories: ";
                                        cout << u.vm[dat].snacks.p_real.getConsumption();
                                        cout << endl << "Carbohydrates: ";
                                        cout << u.vm[dat].snacks.p_real.getCarbohydrate();
                                        cout << endl << "Proteins: ";
                                        cout << u.vm[dat].snacks.p_real.getProtein();
                                        cout << endl << "Fats: ";
                                        cout << u.vm[dat].snacks.p_real.getFat();
                                        cout << endl;
                                    }
                                    else {
                                        if (op2 == 5)
                                        {
                                            cout << "Calories: ";
                                            cout << u.vm[dat].real_total.getConsumption();
                                            cout << endl << "Carbohydrates: ";
                                            cout << u.vm[dat].real_total.getCarbohydrate();
                                            cout << endl << "Proteins: ";
                                            cout << u.vm[dat].real_total.getProtein();
                                            cout << endl << "Fats: ";
                                            cout << u.vm[dat].real_total.getFat();
                                            cout << endl;
                                        }
                                    }
                                }
                            }
                        }
                }

            }
            (void)_getch();
            system("cls");
            see_menu3();
            cout << "Your option:";
            cin >> STATE_DATA;
            break;
        }
        case 2:
        {
            int i, ok = 0, dat;
            for (i = 0;i < u.vm.size();i++)
            {
                if (u.vm[i].getDate().compare(d) == 0)
                {
                    ok = 1;
                    dat = i;
                    break;
                }
            }
            if (ok == 0)
            {
                system("cls");
                cout << "The date could not be found in the database." << endl;
                cout << "Creating a new day";
                Meal m_aux;
                m_aux.setDate(d);
                m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                cout << ".";
                m_aux.breakfast.p_expected=m_aux.expected_total % BREAKFAST_PROCENTAGE;
                cout << ".";
                m_aux.lunch.p_expected =m_aux.expected_total % LUNCH_PROCENTAGE;
                m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                cout << ".";
                m_aux.snacks.p_expected = m_aux.expected_total % SNACKS_PROCENTAGE;
                cout << ".";
                m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                cout << ".";
                m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                cout << "."<<endl;
                u.vm.push_back(m_aux);
                cout << "Day created! Press any key to return!";
            }
            else
            {
                int o1, o2, j;
                see_menu_3_2();
                cout << "Choose one: ";
                cin >> o1;
                see_menu_3_12();
                cout << "Choose one: ";
                cin >> o2;
                if (o1 == 1)
                {
                    if (o2 == 1)
                    {
                        for (j = 0;j < u.vm[dat].breakfast.consumed.size();j++)
                        {
                            cout << u.vm[dat].breakfast.consumed[j].foodstuff.getName() << "," << u.vm[dat].breakfast.consumed[j].getQuantity() << "," << u.vm[dat].breakfast.consumed[j].getServings() << endl;
                        }
                    }
                    else {
                        if (o2 == 2)
                        {
                            for (j = 0;j < u.vm[dat].lunch.consumed.size();j++)
                            {
                                cout << u.vm[dat].lunch.consumed[j].foodstuff.getName() << "," << u.vm[dat].lunch.consumed[j].getQuantity() << "," << u.vm[dat].lunch.consumed[j].getServings() << endl;
                            }
                        }
                        else {
                            if (o2 == 3)
                            {
                                for (j = 0;j < u.vm[dat].dinner.consumed.size();j++)
                                {
                                    cout << u.vm[dat].dinner.consumed[j].foodstuff.getName() << "," << u.vm[dat].dinner.consumed[j].getQuantity() << "," << u.vm[dat].dinner.consumed[j].getServings() << endl;
                                }
                            }
                            else {
                                if (o2 == 4)
                                {
                                    for (j = 0;j < u.vm[dat].snacks.consumed.size();j++)
                                    {
                                        cout << u.vm[dat].snacks.consumed[j].foodstuff.getName() << "," << u.vm[dat].snacks.consumed[j].getQuantity() << "," << u.vm[dat].snacks.consumed[j].getServings() << endl;
                                    }
                                }
                                else
                                {
                                    if (o2 == 5)
                                    {
                                        cout << "Breakfast:" << endl;
                                        for (j = 0;j < u.vm[dat].breakfast.consumed.size();j++)
                                        {
                                            cout << u.vm[dat].breakfast.consumed[j].foodstuff.getName() << "," << u.vm[dat].breakfast.consumed[j].getQuantity() << "," << u.vm[dat].breakfast.consumed[j].getServings() << endl;
                                        }
                                        cout << "Lunch:" << endl;
                                        for (j = 0;j < u.vm[dat].lunch.consumed.size();j++)
                                        {
                                            cout << u.vm[dat].lunch.consumed[j].foodstuff.getName() << "," << u.vm[dat].lunch.consumed[j].getQuantity() << "," << u.vm[dat].lunch.consumed[j].getServings() << endl;
                                        }
                                        cout << "Dinner:" << endl;
                                        for (j = 0;j < u.vm[dat].dinner.consumed.size();j++)
                                        {
                                            cout << u.vm[dat].dinner.consumed[j].foodstuff.getName() << "," << u.vm[dat].dinner.consumed[j].getQuantity() << "," << u.vm[dat].dinner.consumed[j].getServings() << endl;
                                        }
                                        cout << "Snacks:" << endl;
                                        for (j = 0;j < u.vm[dat].snacks.consumed.size();j++)
                                        {
                                            cout << u.vm[dat].snacks.consumed[j].foodstuff.getName() << "," << u.vm[dat].snacks.consumed[j].getQuantity() << "," << u.vm[dat].snacks.consumed[j].getServings() << endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (o2 == 1)
                    {
                        for (j = 0;j < u.vm[dat].breakfast.suggested.size();j++)
                        {
                            cout << u.vm[dat].breakfast.suggested[j].foodstuff.getName() << "," << u.vm[dat].breakfast.suggested[j].getQuantity() << "," << u.vm[dat].breakfast.suggested[j].getServings() << endl;
                        }
                    }
                    else {
                        if (o2 == 2)
                        {
                            for (j = 0;j < u.vm[dat].lunch.suggested.size();j++)
                            {
                                cout << u.vm[dat].lunch.suggested[j].foodstuff.getName() << "," << u.vm[dat].lunch.suggested[j].getQuantity() << "," << u.vm[dat].lunch.suggested[j].getServings() << endl;
                            }
                        }
                        else {
                            if (o2 == 3)
                            {
                                for (j = 0;j < u.vm[dat].dinner.suggested.size();j++)
                                {
                                    cout << u.vm[dat].dinner.suggested[j].foodstuff.getName() << "," << u.vm[dat].dinner.suggested[j].getQuantity() << "," << u.vm[dat].dinner.suggested[j].getServings() << endl;
                                }
                            }
                            else {
                                if (o2 == 4)
                                {
                                    for (j = 0;j < u.vm[dat].snacks.suggested.size();j++)
                                    {
                                        cout << u.vm[dat].snacks.suggested[j].foodstuff.getName() << "," << u.vm[dat].snacks.suggested[j].getQuantity() << "," << u.vm[dat].snacks.suggested[j].getServings() << endl;
                                    }
                                }
                                else
                                {
                                    if (o2 == 5)
                                    {
                                        cout << "Breakfast:" << endl;
                                        for (j = 0;j < u.vm[dat].breakfast.suggested.size();j++)
                                        {
                                            cout << u.vm[dat].breakfast.suggested[j].foodstuff.getName() << "," << u.vm[dat].breakfast.suggested[j].getQuantity() << "," << u.vm[dat].breakfast.suggested[j].getServings() << endl;
                                        }
                                        cout << "Lunch:" << endl;
                                        for (j = 0;j < u.vm[dat].lunch.suggested.size();j++)
                                        {
                                            cout << u.vm[dat].lunch.suggested[j].foodstuff.getName() << "," << u.vm[dat].lunch.suggested[j].getQuantity() << "," << u.vm[dat].lunch.suggested[j].getServings() << endl;
                                        }
                                        cout << "Dinner:" << endl;
                                        for (j = 0;j < u.vm[dat].dinner.suggested.size();j++)
                                        {
                                            cout << u.vm[dat].dinner.suggested[j].foodstuff.getName() << "," << u.vm[dat].dinner.suggested[j].getQuantity() << "," << u.vm[dat].dinner.suggested[j].getServings() << endl;
                                        }
                                        cout << "Snacks:" << endl;
                                        for (j = 0;j < u.vm[dat].snacks.suggested.size();j++)
                                        {
                                            cout << u.vm[dat].snacks.suggested[j].foodstuff.getName() << "," << u.vm[dat].snacks.suggested[j].getQuantity() << "," << u.vm[dat].snacks.suggested[j].getServings() << endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            (void)_getch();
            system("cls");
            see_menu3();
            cout << "Your option:";
            cin >> STATE_DATA;
            break;
        }
        case 3:
        {
            int i, ok = 0, dat;
            for (i = 0;i < u.vm.size();i++)
            {
                if (u.vm[i].getDate().compare(d) == 0)
                {
                    ok = 1;
                    dat = i;
                    break;
                }
            }
            if (ok == 1)
            {
                see_menu_3_3();
                int o;
                cout << "Your option: ";
                cin >> o;
                if (o == 1)
                {
                    system("cls");
                    ifstream f("data.txt");
                    string getcontent;
                    while (!f.eof())
                    {
                        getline(f, getcontent);
                        cout << getcontent << endl;
                    }
                    cout << "Choose the food you want to add" << endl;
                    f.close();
                    Product aux;
                    string n_aux;
                    double q;
                    int s, n;
                    cout << "Name: ";
                    cin.ignore(256, '\n');
                    getline(cin, n_aux);
                    aux.foodstuff.setName(n_aux);
                    cout << "Quantity: ";
                    cin >> q;
                    aux.setQuantity(q);
                    cout << "Servings: ";
                    cin >> s;
                    aux.setServings(s);
                    u.vm[dat].breakfast.consumed.push_back(aux);
                    for (n = 0;n < u.vf.size();n++)
                    {
                        if (n_aux.compare(u.vf[n].getName()) == 0)
                        {
                            break;
                        }
                    }
                    Progress p_aux;
                    p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                    p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                    p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                    p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                    u.vm[dat].real_total = u.vm[dat].real_total + p_aux;
                    u.vm[dat].breakfast.p_real= u.vm[dat].breakfast.p_real + p_aux;
                }
                else {
                    if (o == 2)
                    {
                        system("cls");
                        ifstream f("data.txt");
                        string getcontent;
                        cout << "\tTHE LIST OF FOODS"<<endl;
                        while (!f.eof())
                        {
                            getline(f, getcontent);
                            cout << getcontent << endl;
                        }
                        cout << endl << "Choose the food you want to add" << endl;
                        f.close();
                        Product aux;
                        string n_aux;
                        double q;
                        int s, n;
                        cout << "Name: ";
                        cin.ignore(256, '\n');
                        getline(cin, n_aux);
                        aux.foodstuff.setName(n_aux);
                        cout << "Quantity: ";
                        cin >> q;
                        aux.setQuantity(q);
                        cout << "Servings: ";
                        cin >> s;
                        aux.setServings(s);
                        u.vm[dat].lunch.consumed.push_back(aux);
                        for (n = 0;n < u.vf.size();n++)
                        {
                            if (n_aux.compare(u.vf[n].getName()) == 0)
                            {
                                break;
                            }
                        }
                        Progress p_aux;
                        p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                        p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                        p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                        p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                        u.vm[dat].real_total = u.vm[dat].real_total + p_aux;
                        u.vm[dat].lunch.p_real = u.vm[dat].lunch.p_real + p_aux;
                    }
                    else {
                        if (o == 3)
                        {
                            system("cls");
                            ifstream f("data.txt");
                            string getcontent;
                            while (!f.eof())
                            {
                                getline(f, getcontent);
                                cout << getcontent << endl;
                            }
                            cout << "Choose the food you want to add" << endl;
                            f.close();
                            Product aux;
                            string n_aux;
                            double q;
                            int s, n;
                            cout << "Name: ";
                            cin.ignore(256, '\n');
                            getline(cin, n_aux);
                            aux.foodstuff.setName(n_aux);
                            cout << "Quantity: ";
                            cin >> q;
                            aux.setQuantity(q);
                            cout << "Servings: ";
                            cin >> s;
                            aux.setServings(s);
                            u.vm[dat].dinner.consumed.push_back(aux);
                            for (n = 0;n < u.vf.size();n++)
                            {
                                if (n_aux.compare(u.vf[n].getName()) == 0)
                                {
                                    break;
                                }
                            }
                            Progress p_aux;
                            p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                            p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                            p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                            p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                            u.vm[dat].real_total = u.vm[dat].real_total + p_aux;
                            u.vm[dat].dinner.p_real= u.vm[dat].dinner.p_real + p_aux;
                        }
                        else
                        {
                            if (o == 4)
                            {
                                system("cls");
                                ifstream f("data.txt");
                                string getcontent;
                                while (!f.eof())
                                {
                                    getline(f, getcontent);
                                    cout << getcontent << endl;
                                }
                                cout << "Choose the food you want to add" << endl;
                                f.close();
                                Product aux;
                                string n_aux;
                                double q;
                                int s, n;
                                cout << "Name: ";
                                cin.ignore(256, '\n');
                                getline(cin, n_aux);
                                aux.foodstuff.setName(n_aux);
                                cout << "Quantity: ";
                                cin >> q;
                                aux.setQuantity(q);
                                cout << "Servings: ";
                                cin >> s;
                                aux.setServings(s);
                                u.vm[dat].snacks.consumed.push_back(aux);
                                for (n = 0;n < u.vf.size();n++)
                                {
                                    if (n_aux.compare(u.vf[n].getName()) == 0)
                                    {
                                        break;
                                    }
                                }
                                Progress p_aux;
                                p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                                p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                                p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                                p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                                u.vm[dat].real_total = u.vm[dat].real_total + p_aux;
                                u.vm[dat].snacks.p_real =u.vm[dat].snacks.p_real + p_aux;
                            }
                        }
                    }
                }
            }
            else
            {
                see_menu_3_3();
                int o;
                cout << "Your option: ";
                cin >> o;
                if (o == 1)
                {
                    cout << "The date could not be found in the database." << endl;
                    cout << "Creating a new day";
                    Meal m_aux;
                    m_aux.setDate(d);
                    m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                    m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                    m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                    m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                    cout << ".";
                    m_aux.breakfast.p_expected = m_aux.expected_total % BREAKFAST_PROCENTAGE;
                    cout << ".";
                    m_aux.lunch.p_expected=m_aux.expected_total % LUNCH_PROCENTAGE;
                    cout << ".";
                    m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                    cout << ".";
                    m_aux.snacks.p_expected =m_aux.expected_total % SNACKS_PROCENTAGE;
                    cout << ".";
                    m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                    cout << ".";
                    m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                    cout << ".";
                    m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                    cout << ".";
                    m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                    cout << ".";
                    system("cls");
                    ifstream f("data.txt");
                    string getcontent;
                    while (!f.eof())
                    {
                        getline(f, getcontent);
                        cout << getcontent << endl;
                    }
                    cout << "Choose the food you want to add" << endl;
                    f.close();
                    Product aux;
                    string n_aux;
                    double q;
                    int s, n;
                    cout << "Name: ";
                    cin.ignore(256, '\n');
                    getline(cin, n_aux);
                    aux.foodstuff.setName(n_aux);
                    cout << "Quantity: ";
                    cin >> q;
                    aux.setQuantity(q);
                    cout << "Servings: ";
                    cin >> s;
                    aux.setServings(s);
                    m_aux.breakfast.consumed.push_back(aux);
                    for (n = 0;n < u.vf.size();n++)
                    {
                        if (n_aux.compare(u.vf[n].getName()) == 0)
                        {
                            break;
                        }
                    }
                    Progress p_aux;
                    p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                    p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                    p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                    p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                    m_aux.real_total = m_aux.real_total + p_aux;
                    m_aux.breakfast.p_real = m_aux.breakfast.p_real + p_aux;
                    u.vm.push_back(m_aux);
                }
                else
                {
                    if (o == 2)
                    {
                        cout << "The date could not be found in the database." << endl;
                        cout << "Creating a new day";
                        Meal m_aux;
                        m_aux.setDate(d);
                        m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                        m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                        m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                        m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                        m_aux.breakfast.p_expected =m_aux.expected_total % BREAKFAST_PROCENTAGE;
                        cout << ".";
                        m_aux.lunch.p_expected =m_aux.expected_total % LUNCH_PROCENTAGE;
                        cout << ".";
                        m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                        cout << ".";
                        m_aux.snacks.p_expected =m_aux.expected_total % SNACKS_PROCENTAGE;
                        cout << ".";
                        m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                        cout << ".";
                        m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                        cout << ".";
                        m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                        cout << ".";
                        m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                        cout << ".";
                        system("cls");
                        ifstream f("data.txt");
                        string getcontent;
                        while (!f.eof())
                        {
                            getline(f, getcontent);
                            cout << getcontent << endl;
                        }
                        cout << "Choose the food you want to add" << endl;
                        f.close();
                        Product aux;
                        string n_aux;
                        double q;
                        int s, n;
                        cout << "Name: ";
                        cin.ignore(256, '\n');
                        getline(cin, n_aux);
                        aux.foodstuff.setName(n_aux);
                        cout << "Quantity: ";
                        cin >> q;
                        aux.setQuantity(q);
                        cout << "Servings: ";
                        cin >> s;
                        aux.setServings(s);
                        m_aux.lunch.consumed.push_back(aux);
                        for (n = 0;n < u.vf.size();n++)
                        {
                            if (n_aux.compare(u.vf[n].getName()) == 0)
                            {
                                break;
                            }
                        }
                        Progress p_aux;
                        p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                        p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                        p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                        p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                        m_aux.real_total = m_aux.real_total + p_aux;
                        m_aux.lunch.p_real = m_aux.lunch.p_real + p_aux;
                        u.vm.push_back(m_aux);
                    }
                    else {
                        if (o == 3)
                        {
                            cout << "The date could not be found in the database." << endl;
                            cout << "Creating a new day";
                            Meal m_aux;
                            m_aux.setDate(d);
                            m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                            m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                            m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                            m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                            m_aux.breakfast.p_expected =m_aux.expected_total % BREAKFAST_PROCENTAGE;
                            cout << ".";
                            m_aux.lunch.p_expected =m_aux.expected_total % LUNCH_PROCENTAGE;
                            cout << ".";
                            m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                            cout << ".";
                            m_aux.snacks.p_expected =m_aux.expected_total % SNACKS_PROCENTAGE;
                            cout << ".";
                            m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                            cout << ".";
                            m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                            cout << ".";
                            m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                            cout << ".";
                            m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                            cout << ".";
                            system("cls");
                            ifstream f("data.txt");
                            string getcontent;
                            while (!f.eof())
                            {
                                getline(f, getcontent);
                                cout << getcontent << endl;
                            }
                            cout << "Choose the food you want to add" << endl;
                            f.close();
                            Product aux;
                            string n_aux;
                            double q;
                            int s, n;
                            cout << "Name: ";
                            cin.ignore(256, '\n');
                            getline(cin, n_aux);
                            aux.foodstuff.setName(n_aux);
                            cout << "Quantity: ";
                            cin >> q;
                            aux.setQuantity(q);
                            cout << "Servings: ";
                            cin >> s;
                            aux.setServings(s);
                            m_aux.dinner.consumed.push_back(aux);
                            for (n = 0;n < u.vf.size();n++)
                            {
                                if (n_aux.compare(u.vf[n].getName()) == 0)
                                {
                                    break;
                                }
                            }
                            Progress p_aux;
                            p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                            p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                            p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                            p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                            m_aux.real_total = m_aux.real_total + p_aux;
                            m_aux.dinner.p_real = m_aux.dinner.p_real + p_aux;
                            u.vm.push_back(m_aux);
                        }
                        else {
                            if (o == 4)
                            {
                                cout << "The date could not be found in the database." << endl;
                                cout << "Creating a new day";
                                Meal m_aux;
                                m_aux.setDate(d);
                                m_aux.expected_total.setConsumption(calc_cal(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                                m_aux.expected_total.setProtein(calc_prot(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                                m_aux.expected_total.setCarbohydrate(calc_carb(u.acc.getBMI(), u.acc.getMetabolism(), u.acc.getGoal(), u.acc.getWeight()));
                                m_aux.expected_total.setFat(calc_fat(m_aux.expected_total.getConsumption(), m_aux.expected_total.getProtein(), m_aux.expected_total.getCarbohydrate()));
                                cout << ".";
                                m_aux.breakfast.p_expected =m_aux.expected_total % BREAKFAST_PROCENTAGE;
                                cout << ".";
                                m_aux.lunch.p_expected =m_aux.expected_total % LUNCH_PROCENTAGE;
                                cout << ".";
                                m_aux.dinner.p_expected =m_aux.expected_total % DINNER_PROCENTAGE;
                                cout << ".";
                                m_aux.snacks.p_expected =m_aux.expected_total % SNACKS_PROCENTAGE;
                                cout << ".";
                                m_aux.breakfast.suggested = select_food(u.vf, m_aux.breakfast.p_expected.getConsumption());
                                cout << ".";
                                m_aux.dinner.suggested = select_food(u.vf, m_aux.dinner.p_expected.getConsumption());
                                cout << ".";
                                m_aux.lunch.suggested = select_food(u.vf, m_aux.lunch.p_expected.getConsumption());
                                cout << ".";
                                m_aux.snacks.suggested = select_food(u.vf, m_aux.snacks.p_expected.getConsumption());
                                cout << ".";
                                system("cls");
                                ifstream f("data.txt");
                                string getcontent;
                                while (!f.eof())
                                {
                                    getline(f, getcontent);
                                    cout << getcontent << endl;
                                }
                                cout << "Choose the food you want to add" << endl;
                                f.close();
                                Product aux;
                                string n_aux;
                                double q;
                                int s, n;
                                cout << "Name: ";
                                cin.ignore(256, '\n');
                                getline(cin, n_aux);
                                aux.foodstuff.setName(n_aux);
                                cout << "Quantity: ";
                                cin >> q;
                                aux.setQuantity(q);
                                cout << "Servings: ";
                                cin >> s;
                                aux.setServings(s);
                                m_aux.snacks.consumed.push_back(aux);
                                for (n = 0;n < u.vf.size();n++)
                                {
                                    if (n_aux.compare(u.vf[n].getName()) == 0)
                                    {
                                        break;
                                    }
                                }
                                Progress p_aux;
                                p_aux.setConsumption((q * s * u.vf[n].getCalories()) / 100);
                                p_aux.setCarbohydrate((q * s * u.vf[n].getCarbohydrates()) / 100);
                                p_aux.setProtein((q * s * u.vf[n].getProtein()) / 100);
                                p_aux.setFat((q * s * u.vf[n].getFat()) / 100);
                                m_aux.real_total = m_aux.real_total + p_aux;
                                m_aux.snacks.p_real = m_aux.snacks.p_real + p_aux;
                                u.vm.push_back(m_aux);
                            }
                        }
                    }
                }
            }
            (void)_getch();
            system("cls");
            see_menu3();
            cout << "Your option:";
            cin >> STATE_DATA;
            break;
        }
        case 4:
        {
            system("cls");
            break;
        }
        default:
        {system("cls");
        see_menu3();
        cout << "Your option:";
        cin >> STATE_DATA;
        break;
        }
        }

    }
    system("cls");
    ofstream g("log.txt");
    //saving in folder
    { 
        for (int i = 0;i < u.vm.size() - 1;i++)
    {
        g << "{" << endl;
        g << u.vm[i].getDate() << endl;
        g << u.vm[i].expected_total;
        g << u.vm[i].real_total;
        g << "/" << endl;
        g << u.vm[i].breakfast.p_expected;
        g << u.vm[i].breakfast.p_real;
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].breakfast.suggested.size();j++)
        {
            g << u.vm[i].breakfast.suggested[j].foodstuff.getName() << "," << u.vm[i].breakfast.suggested[j].getQuantity() << "," << u.vm[i].breakfast.suggested[j].getServings()<<endl;
        }
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].breakfast.consumed.size();j++)
        {
            g << u.vm[i].breakfast.consumed[j].foodstuff.getName() << "," << u.vm[i].breakfast.consumed[j].getQuantity() << "," << u.vm[i].breakfast.consumed[j].getServings()<<endl;
        }
        g << "*" << endl;
        g << "/" << endl;
        g << u.vm[i].lunch.p_expected;
        g << u.vm[i].lunch.p_real;
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].lunch.suggested.size();j++)
        {
            g << u.vm[i].lunch.suggested[j].foodstuff.getName() << "," << u.vm[i].lunch.suggested[j].getQuantity() << "," << u.vm[i].lunch.suggested[j].getServings()<<endl;
        }
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].lunch.consumed.size();j++)
        {
            g << u.vm[i].lunch.consumed[j].foodstuff.getName() << "," << u.vm[i].lunch.consumed[j].getQuantity() << "," << u.vm[i].lunch.consumed[j].getServings() << endl;
        }
        g << "*" << endl;
        g << "/" << endl;
        g << u.vm[i].dinner.p_expected;
        g << u.vm[i].dinner.p_real;
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].dinner.suggested.size();j++)
        {
            g << u.vm[i].dinner.suggested[j].foodstuff.getName() << "," << u.vm[i].dinner.suggested[j].getQuantity() << "," << u.vm[i].dinner.suggested[j].getServings()<<endl;
        }
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].dinner.consumed.size();j++)
        {
            g << u.vm[i].dinner.consumed[j].foodstuff.getName() << "," << u.vm[i].dinner.consumed[j].getQuantity() << "," << u.vm[i].dinner.consumed[j].getServings()<<endl;
        }
        g << "*" << endl;
        g << "/" << endl;
        g << u.vm[i].snacks.p_expected;
        g << u.vm[i].snacks.p_real;
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].snacks.suggested.size();j++)
        {
            g << u.vm[i].snacks.suggested[j].foodstuff.getName() << "," << u.vm[i].snacks.suggested[j].getQuantity() << "," << u.vm[i].snacks.suggested[j].getServings()<<endl;
        }
        g << "*" << endl;
        for (int j = 0;j < u.vm[i].snacks.consumed.size();j++)
        {
            g << u.vm[i].snacks.consumed[j].foodstuff.getName() << "," << u.vm[i].snacks.consumed[j].getQuantity() << "," << u.vm[i].snacks.consumed[j].getServings()<<endl;
        }
        g << "*" << endl;
        g << "/" << endl;
        g << "}"<<endl;
    }
    g << "{" << endl;
    g << u.vm[u.vm.size() - 1].getDate() << endl;
    g << u.vm[u.vm.size() - 1].expected_total;
    g << u.vm[u.vm.size() - 1].real_total;
    g << "/" << endl;
    g << u.vm[u.vm.size() - 1].breakfast.p_expected;
    g << u.vm[u.vm.size() - 1].breakfast.p_real;
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].breakfast.suggested.size();j++)
    {
        g << u.vm[u.vm.size() - 1].breakfast.suggested[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].breakfast.suggested[j].getQuantity() << "," << u.vm[u.vm.size() - 1].breakfast.suggested[j].getServings()<<endl;
    }
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].breakfast.consumed.size();j++)
    {
        g << u.vm[u.vm.size() - 1].breakfast.consumed[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].breakfast.consumed[j].getQuantity() << "," << u.vm[u.vm.size() - 1].breakfast.consumed[j].getServings()<<endl;
    }
    g << "*" << endl;
    g << "/" << endl;
    g << u.vm[u.vm.size() - 1].lunch.p_expected;
    g << u.vm[u.vm.size() - 1].lunch.p_real;
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].lunch.suggested.size();j++)
    {
        g << u.vm[u.vm.size() - 1].lunch.suggested[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].lunch.suggested[j].getQuantity() << "," << u.vm[u.vm.size() - 1].lunch.suggested[j].getServings()<<endl;
    }
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].lunch.consumed.size();j++)
    {
        g << u.vm[u.vm.size() - 1].lunch.consumed[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].lunch.consumed[j].getQuantity() << "," << u.vm[u.vm.size() - 1].lunch.consumed[j].getServings()<<endl;
    }
    g << "*" << endl;
    g << "/" << endl;
    g << u.vm[u.vm.size() - 1].dinner.p_expected;
    g << u.vm[u.vm.size() - 1].dinner.p_real;
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].dinner.suggested.size();j++)
    {
        g << u.vm[u.vm.size() - 1].dinner.suggested[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].dinner.suggested[j].getQuantity() << "," << u.vm[u.vm.size() - 1].dinner.suggested[j].getServings()<<endl;
    }
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].dinner.consumed.size();j++)
    {
        g << u.vm[u.vm.size() - 1].dinner.consumed[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].dinner.consumed[j].getQuantity() << "," << u.vm[u.vm.size() - 1].dinner.consumed[j].getServings()<<endl;
    }
    g << "*" << endl;
    g << "/" << endl;
    g << u.vm[u.vm.size() - 1].snacks.p_expected;
    g << u.vm[u.vm.size() - 1].snacks.p_real;
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].snacks.suggested.size();j++)
    {
        g << u.vm[u.vm.size() - 1].snacks.suggested[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].snacks.suggested[j].getQuantity() << "," << u.vm[u.vm.size() - 1].snacks.suggested[j].getServings()<<endl;
    }
    g << "*" << endl;
    for (int j = 0;j < u.vm[u.vm.size() - 1].snacks.consumed.size();j++)
    {
        g << u.vm[u.vm.size() - 1].snacks.consumed[j].foodstuff.getName() << "," << u.vm[u.vm.size() - 1].snacks.consumed[j].getQuantity() << "," << u.vm[u.vm.size() - 1].snacks.consumed[j].getServings()<<endl;
    }
    g << "*" << endl;
    g << "/" << endl;
    g << "}";
    }
    g.close();
}


int main()
{
    while (true)
    {
        switch (MENU_STATE)
        {
        case USER:
            user_menu();
            break;
        case LOG:
            log_menu();
            break;
        case DATA:
            data_menu();
            break;
        }
    }
    return 0;
}


