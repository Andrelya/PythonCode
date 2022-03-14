#include "processor.hpp"
using namespace
int BYTE    = 20;

int PC_ALL  = 0;        // для команди окремого такту.
int PC      = 0;        // для команди.
int TC      = 0;        // для такту в команді.
string PS;              // для знаку в акамуляторі.

int NUM_REGISTER = 4;   // задаєм кількість регістрам


string output_number(vector<int> vect){
    /*
        Перетворюєм двійкове число в string.
     */
    
    string str;
    for(auto i = vect.begin(); i != vect.end(); i++){
        string s = to_string((*i));
        str += s;
    }
    return str;
}




vector<int> direct_code(int number){
    /*
        прямий код для додатнього і від'ємного числа.
     */
    
    int number_copy = number;
    list<int> list1;
    int remainder;
    number = abs(number);
    
    while (number != 1) {                                       // вираховуєм число за модулем у двійковому коді.
        remainder = number % 2;
        list1.push_front(remainder);
        
        number  /= 2;
    }
    list1.push_front(1);
    
    
    int size_number_byte = int(list1.size());                   // робимо число 19-бітовим.
    for (int i = 0 ; i != ( (BYTE - 1) - size_number_byte); i++){
        list1.push_front(0);
    }
    
    
    if (number_copy < 0){                                      // вираховуєм знак числа (1 --> -) or (0 --> +) у двійковому коді.
        list1.push_front(1);
    }
    else if (number_copy >= 0){
        list1.push_front(0);
    }
    
    
    vector<int> vect;                                          // записуєм число у вектор
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect.push_back(*i);
    }
    return vect;
}



vector<int> complementary_code(vector<int> vect1){
    /*
        доповнюючий код (для відємних чисел). vect1 --> прямий код модля числа
     */
    
    vector<int> vect2;
    vector<int> vect3;
    
    for (auto i = vect1.begin(); i != vect1.end(); i++){        // Інвертуємо всі біти.
        if (int(*i) == 0){
            vect2.push_back(1);
        }
        else if (int(*i) == 1){
            vect2.push_back(0);
        }
    }
    
    for (int i = 0; i != (BYTE - 1); i++){                      //  1 у двійковому коді.
        vect3.push_back(0);
    }
    vect3.push_back(1);
    
    vector<int> vect4 = addition(vect2, vect3);                 // додавання числа і одиниці у 2 с/ч.
    
    return vect4;
}


int with_binary_in_chyslo(vector<int> cod_binary){
    /*
        переводим з двійкового числа в десяткове.
     */
    
    int x = BYTE - 2;
    int number;
    int sum = 0;
    for (int i = 1; i != (BYTE); i++){
        number = cod_binary[i] * pow(2, x);
        sum += number;
        x--;
    }
    
    if (cod_binary[0] == 1)
        sum *= -1;
    //cout << sum;
    return sum;
}

vector<int> addition(vector<int> vect1, vector<int> vect2){
    /*
        додавання двійкових чисел.
     */
    
    int zmina = 0;
    int sum;
    vector<int> vect3;
    
    for (int i = 0; i != BYTE; i++){                                // вектор з нулями.
        vect3.push_back(0);
    }
    
    
    for (int i = int(vect1.size() - 1); i != -1; i--){              // процес додавання.
        
        sum = vect1[i] + vect2[i] + zmina;
        if (sum == 3){
            vect3[i] = 1;
            zmina    = 1;
        }
        else if (sum == 2){
            vect3[i] = 0;
            zmina    = 1;
        }
        else if (sum == 1){
            vect3[i] = 1;
            zmina    = 0;
        }
        else if (sum == 0){
            vect3[i] = 0;
            zmina    = 0;
        }
    }
    
    return vect3;
}

vector<string> split(string str, string element){
    /*
        розбиваєм строку str у вектор без елемента element.
     */
    
    str.pop_back();                             // видаляєм крапку з комою.
    string sum_str = "";
    
    vector<string> vect1;                       // створюєм вектор з строкой.
    for (int i = 0; i != str.size(); i++){
        vect1.push_back("s");
    }
    
    for (int i = 0; i != vect1.size(); i++){    // створюєм вектор з нашої строки.
        vect1[i] = str[i];
    }
    
    vector<string> vect;
    for (int i = 0; i != vect1.size(); i++){    // операція split.
        sum_str += vect1[i];
        if ((vect1[i] == element) or (i == int(vect1.size() - 1))){
            vect.push_back(sum_str);
            sum_str = "";
        }
    }
    vect[0].pop_back();
    return vect;
}

vector<string> rand_regist(){
    /*
        надаєм регістрам та акамуляторі рандомні значення, а також кількість регістрів.
     */
    
    vector<string> vect;
    random_device rd;
    mt19937 mersenne(rd());
    for (int i = 0; i != (NUM_REGISTER + 1); i++){
        int rand_number = mersenne();
        
        int x = rand_number % 524288;
        
        vector<int> vect1 = direct_code(x);
        string s = output_number(vect1);
        vect.push_back(s);
    }
    return vect;
    
}

vector<string> mov(int number, vector<string> vect_regist){
    /*
        додаєм значення в акамулятор.
     */
    
    vector<int> vect = direct_code(number);
    string      str  = output_number(vect);
    vect_regist[0] = str;
    
    return vect_regist;
}

vector<string> add(int number, vector<string> vect_regist){
    /*
        Додавання двійкових чисел.
     */
    
    vector<int> vect_number = direct_code(number);                            // число, яке додаєм у прямому коді
    
    string zero_or_one;
    vector<int> vect_akamulator;
    for (auto i = vect_regist[0].begin(); i != vect_regist[0].end(); i++){    // число, до якого додаєм (у акамуляторі)
        zero_or_one = (*i);
        int chyslo  = atoi(zero_or_one.c_str());
        vect_akamulator.push_back(chyslo);
        
    }
    
    int chyslo1;
    int chyslo2;
    
    chyslo1 = with_binary_in_chyslo(vect_akamulator);
    chyslo2 = with_binary_in_chyslo(vect_number);
    //cout << chyslo1 << " --> " << chyslo2 << endl;
    vector<int> vect3;
    if ((vect_number[0] == 1) and (vect_akamulator[0] == 1)){
        vect_number[0] = 0;
        vect_akamulator[0] = 0;
        vect3 = addition(vect_number, vect_akamulator);
        vect3[0] = 1;
    }
    else if (vect_akamulator[0] == 1){
        
        if (abs(chyslo1) > abs(chyslo2)){
            
            vect_number = complementary_code(vect_number);
            vect3       = addition(vect_number, vect_akamulator);
        }
        else if (abs(chyslo1) <= abs(chyslo2)){
            
            vect_akamulator[0] = 0;
            vect_akamulator    = complementary_code(vect_akamulator);
            vect3              = addition(vect_number, vect_akamulator);
        }
    }
    else if (vect_number[0] == 1){
        if (abs(chyslo1) < abs(chyslo2)){
            
            vect_akamulator = complementary_code(vect_akamulator);
            vect3       = addition(vect_number, vect_akamulator);
        }
        else if (abs(chyslo1) >= abs(chyslo2)){
           
            vect_number[0] = 0;
            vect_number    = complementary_code(vect_number);
            vect3              = addition(vect_number, vect_akamulator);
        }
        
    }
    else{
        vect3 = addition(vect_number, vect_akamulator);
    }
    
    string str;
    str = output_number(vect3);
    vect_regist[0] = str;
    return vect_regist;
}

vector<string> landl(int number, vector<string> vect_regist){
    
    string zero_or_one;
    vector<int> vect_akamulator;
    for (auto i = vect_regist[0].begin(); i != vect_regist[0].end(); i++){      // число, яке зсуваєм.
        zero_or_one = (*i);
        int chyslo  = atoi(zero_or_one.c_str());
        vect_akamulator.push_back(chyslo);
        
    }
    
    list<int> list_akamulator;
    for (auto i = vect_akamulator.begin(); i != vect_akamulator.end(); i++){
        list_akamulator.push_back(*i);
    }
    
    for (int i = 0; i != number; i++){                                          // Процес зсуву в ліво.
        list_akamulator.push_back(vect_akamulator[i % 20]);
        list_akamulator.pop_front();
    }
    
    int j = 0;
    for (auto i = list_akamulator.begin(); i != list_akamulator.end(); i++){
        vect_akamulator[j] = (*i);
        j++;
    }
    string str;
    str = output_number(vect_akamulator);
    vect_regist[0] = str;
    return vect_regist;
}

vector<string> landr(int number, vector<string> vect_regist){
    
    string zero_or_one;
    vector<int> vect_akamulator;
    for (auto i = vect_regist[0].begin(); i != vect_regist[0].end(); i++){      // число, яке зсуваєм.
        zero_or_one = (*i);
        int chyslo  = atoi(zero_or_one.c_str());
        vect_akamulator.push_back(chyslo);
        
    }
    
    list<int> list_akamulator;
    for (auto i = vect_akamulator.begin(); i != vect_akamulator.end(); i++){
        list_akamulator.push_back(*i);
    }
    
    int size_vect = int(vect_akamulator.size() - 1);
    for (int i = 0; i != number; i++){                                          // Процес зсуву в право.
        list_akamulator.push_front(vect_akamulator[size_vect]);
        list_akamulator.pop_back();
        size_vect--;
    }
    
    int j = 0;
    for (auto i = list_akamulator.begin(); i != list_akamulator.end(); i++){
        vect_akamulator[j] = (*i);
        j++;
    }
    string str;
    str = output_number(vect_akamulator);
    vect_regist[0] = str;
    return vect_regist;
}

vector<string> save(vector<string> vect_command, vector<string> vect_regist){
    /*
        Зберегти значення в регістр з акамулятора.
     */
    
    for (int i = 1; i <= NUM_REGISTER; i++){
        string nomer  = to_string(i);
        string regist = "R" + nomer;
        if (vect_command[1] == regist){
            vect_regist[i] = vect_regist[0];
        }
    }
    return vect_regist;
}

void instruction(){
    cout << "Команди: " << endl;
    cout << "\t\tmov {number}" << "\t\t-->     " << "Зберегти значення в акамулятор." << endl;
    cout << "\t\tadd {number}" << "\t\t-->     " << "Додати значення до значення в акамуляторі." << endl;
    cout << "\t\tlandl {number}" << "\t\t-->     " << "Зсув в ліво на {number} одиниць." << endl;
    cout << "\t\tlandr {number}" << "\t\t-->     " << "Зсув в вправо на {number} одиниць." << endl;
    cout << "\t\tsave {register}" << "\t\t-->     " << "Зберегти значення в register={R1, R2, R3...}." << endl;
    cout << "\t\tfile" << "\t\t\t\t-->     " << "Зчитати команди з файла." << endl;
    cout << "\t\thelp" << "\t\t\t\t-->     " << "Переглянути команди." << endl;
    cout << "\t\texit" << "\t\t\t\t-->     " << "Закінчити ввод даних." << endl;
    cout << "Кожна команда повинна закінчуватися крапкою з комою(;)" << endl;
    cout << endl;
}

void output(vector<string> vect_command, vector<string> vect_regist){
    /*
        Вивід результату.
     */
    
    string  str;
    PC_ALL++;
    TC++;
    
    str  = vect_regist[0];
    if ((vect_command[1] != "R1") and (vect_command[1] != "R2") and (vect_command[1] != "R3") and (vect_command[1] != "R4")){         // перевод числа у двійкову с/ч
        int number = atoi(vect_command[1].c_str());
        vector<int> vect = direct_code(number);
        str  = output_number(vect);
    }
    
    cout << "\n(Подаємо ззовні " << PC_ALL << "-й такт – це " << TC << "-й такт, " << PC <<"-ї команди)" << endl;
    cout << "Команда = " << vect_command[0] << " " << vect_command[1] << ";" << endl;
    cout << "A  = " << vect_regist[0] << "      Ins = "<< vect_command[0] << " | " << str << endl;
    cout << "R1 = " << vect_regist[1] << "      PC = " << PC << endl;
    cout << "R2 = " << vect_regist[2] << "      TC = " << TC << endl;
    cout << "R3 = " << vect_regist[3] << "      PS = " << PS << endl;
    
    int j = 4;
    for (int i = 0; i != (NUM_REGISTER - 3); i++){
        cout << "R"<< j <<" = " << vect_regist[j] << endl;
        j++;
    }
}

void file_input(vector<string> vect_regist){
    vector<string> lines;
    string strInput;
    ifstream file;
    
    file.open("/Users/andrejlasuk/Desktop/AOS2.txt");
    while (file)
        {
            // то переміщуємо ці дані в рядок, який потім виводимо на екран
        
            getline(file, strInput);
            lines.push_back(strInput);
        }
    file.close();
    lines.pop_back();
    
    cmatch result;
    string str;
    regex regular1("((mov{1,1})(\\s)([0-9]{1,6})(;{1,1}))|((mov{1,1})(\\s)-([0-9]{1,6})(;{1,1}))");
    regex regular2("((add{1,1})(\\s)([0-9]{1,6})(;{1,1}))|((add{1,1})(\\s)-([0-9]{1,6})(;{1,1}))");
    regex regular3("((save{1,1})(\\s)(R{1,1})([1-9])(;{1,1}))");
    regex regular4("((landl{1,1})(\\s)([0-9]{1,})(;{1,1}))");
    regex regular5("((landr{1,1})(\\s)([0-9]{1,})(;{1,1}))");
    
    for (auto i = lines.begin(); i != lines.end(); i++){
        str = *i;
        
        if (regex_match(str.c_str(),  regular1)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            if ((number < 524288) and (number > -524287)){
                PC++;
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                
                vect_regist = mov(number, vect_regist);
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                TC = 0;
            }
        }
        else if (regex_match(str.c_str(), result, regular2)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            if ((number < 524288) and (number > -524287)){
                PC++;
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                
                vect_regist = add(number, vect_regist);
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                TC = 0;
            }
        }
        else if (regex_match(str.c_str(), result, regular3)){
            
            vector<string> vect_command = split(str, " ");
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = save(vect_command, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
            
        }
        else if (regex_match(str.c_str(), result, regular4)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = landl(number, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
        }
        else if (regex_match(str.c_str(), result, regular5)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = landr(number, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
        }
        cout << endl;
    }
}

bool processor(vector<string> vect_regist){
    bool zmina = false;
    string str;
    cmatch result;
    regex regular1("((mov{1,1})(\\s)([0-9]{1,6})(;{1,1}))|((mov{1,1})(\\s)-([0-9]{1,6})(;{1,1}))");
    regex regular2("((add{1,1})(\\s)([0-9]{1,6})(;{1,1}))|((add{1,1})(\\s)-([0-9]{1,6})(;{1,1}))");
    regex regular3("((save{1,1})(\\s)(R{1,1})([1-9])(;{1,1}))");
    regex regular4("((landl{1,1})(\\s)([0-9]{1,})(;{1,1}))");
    regex regular5("((landr{1,1})(\\s)([0-9]{1,})(;{1,1}))");
    regex regular6("((help{1,1})(;{1,1}))");
    regex regular7("((exit{1,1})(;{1,1}))");
    regex regular8("((file{1,1})(;{1,1}))");
    
    //vector<string> vect_lines = file_input();
    
    instruction();
    while (not (regex_match(str.c_str(),  regular7))){

        cout << "Введи команду: ";
        getline(cin, str);
        
        if (regex_match(str.c_str(),  regular1)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            if ((number < 524288) and (number > -524287)){
                PC++;
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                
                vect_regist = mov(number, vect_regist);
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                TC = 0;
            }
        }
        else if (regex_match(str.c_str(), result, regular2)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            if ((number < 524288) and (number > -524287)){
                PC++;
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                
                vect_regist = add(number, vect_regist);
                PS = vect_regist[0][0];
                output(vect_command, vect_regist);
                TC = 0;
            }
        }
        else if (regex_match(str.c_str(), result, regular3)){
            
            vector<string> vect_command = split(str, " ");
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = save(vect_command, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
            
        }
        else if (regex_match(str.c_str(), result, regular4)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = landl(number, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
        }
        else if (regex_match(str.c_str(), result, regular5)){
            
            vector<string> vect_command = split(str, " ");
            int number = atoi(vect_command[1].c_str());
            
            PC++;
            PS = vect_regist[0][0];
            
            output(vect_command, vect_regist);
            
            vect_regist = landr(number, vect_regist);
            PS = vect_regist[0][0];
            output(vect_command, vect_regist);
            TC = 0;
        }
        else if (regex_match(str.c_str(), result, regular6)){
            instruction();
            
        }
        else if (regex_match(str.c_str(), result, regular8)){
            zmina = true;
            break;
        }
        else if (not (regex_match(str.c_str(),  regular7))){
            cout << "НЕ ВІРНА КОМАНДА" << endl;
            cout << "Введіте команду 'help' для перегляду всіх команд." << endl;
        }
        cout << endl;
    }
    return zmina;
}



void input(){
    
    vector<string> vect_regist = rand_regist();
   
    bool zmina = processor(vect_regist);
    if (zmina){
        file_input(vect_regist);
    }
}
