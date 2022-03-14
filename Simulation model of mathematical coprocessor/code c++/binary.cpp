#include "binary.hpp"

int BYTE_MANTISA  = 10;
int BYTE_PORYADKA = 10;


int PC      = 0;        // для команди.
int TC      = 0;        // для такту в команді.
string PS;              // для знаку в акамуляторі.

int NUM_REGISTER = 8;   // задаєм кількість регістрам
double TOCHNIST = 0.5;  // Точність запису дробової частини числа.

//*******************************************************************************************************************
//                  Допоміжні функції split, landl and output.
//*******************************************************************************************************************


string output(vector<int> vect){
    /*
        Перетворення двійкового числа з вектора в строку.
     */
    
    string str;
    for (auto i = vect.begin(); i != vect.end(); i++){
        string s = to_string(*i);
        str += s;
    }
    return str;
}

vector<string> output_vect(string str){
    /*
        Перетворення двійкового числа з строки в  вектор строку строку.
     */
    
    vector<string> vect;
    string k;
    for (auto i = str.begin(); i != str.end(); i++){
        k = *i;
        vect.push_back(k);
    }
    return vect;
}

vector<int> landl(int number, vector<int> vect_binary_mantisa){
    /*
        циклічний зсув вліво, використовується для видалення першого елемента з вектора,
        бо стандартної функції немає, щоб видалити перший елемент проте є видаленя останнього елемента.
     */
    
    list<int> list_binary_mantisa;
    for (auto i = vect_binary_mantisa.begin(); i != vect_binary_mantisa.end(); i++){
        list_binary_mantisa.push_back(*i);
    }
    
    for (int i = 0; i != number; i++){                                          // Процес зсуву в ліво.
        list_binary_mantisa.push_back(vect_binary_mantisa[i % BYTE_MANTISA]);
        list_binary_mantisa.pop_front();
    }
    
    int j = 0;
    for (auto i = list_binary_mantisa.begin(); i != list_binary_mantisa.end(); i++){
        vect_binary_mantisa[j] = (*i);
        j++;
    }
    return vect_binary_mantisa;
}

string split(string str, string element){
    
    string s;
    string sum;
    vector<string> vect_str;
   
    for (auto i = str.begin(); i != str.end(); i++){
        s = (*i);
        
        if (s == element){
            vect_str.push_back(sum);
            sum = "";
            s = "";
        }
        sum += s;
    }
    vect_str.push_back(sum);
    sum = "";
    for (auto i = vect_str.begin(); i != vect_str.end(); i++){
        sum += (*i);
    }
    return sum;
}

//*******************************************************************************************************************
//                  Переводимо різні числа з двійкового коду в десятковий.
//*******************************************************************************************************************

int with_binary_in_chyslo(vector<int> cod_binary){
    /*
        переводим з двійкового числа в десяткове ціле число.
     */
    
    int x = int(cod_binary.size()) - 1;
    int number;
    int sum = 0;
    for (int i = 0; i != (cod_binary.size()); i++){
        number = cod_binary[i] * pow(2, x);
        sum += number;
        x--;
    }
    return sum;
}

double with_binary_in_chyslo_not_int(vector<int> cod_binary){
    /*
        Перетворюєм з двійкового числа в десяткове дробове число.
     */
    
    int x = 1;
    double number;
    double sum = 0;
    for (int i = 0; i != (cod_binary.size()); i++){
        number = cod_binary[i] * pow(2, -x);
        sum += number;
        x++;
    }
    return sum;
}

double decimal_system(string binary_number){
    /*
        Перетворення числа float з двійкової в десяткову систему числення.
     */
    
    vector<string> vect_str = output_vect(binary_number);
    
    int sign = atoi((vect_str[0]).c_str());
    if (sign == 0){
        sign = 1;
    }
    else{
        sign = -1;
    }
    // +
    vector<int> vect_poryadok;
    
    for (int i = 1; i != (BYTE_PORYADKA + 1); i++){
        int b = atoi((vect_str[i]).c_str());
        vect_poryadok.push_back(b);
        
    }
    
    vector<int> vect_mantisa;
    for (int i = (1 + BYTE_PORYADKA); i != vect_str.size(); i++){
        int b = atoi((vect_str[i]).c_str());
        vect_mantisa.push_back(b);
    }
    
    vector<int> vect_int;
    vector<int> vect_remainder;
    int j = 0;
    int number = with_binary_in_chyslo(vect_poryadok);
    int size_number = pow(2,BYTE_PORYADKA) / 2;
    int poryadok = number - size_number;
    int difference = BYTE_MANTISA - poryadok;
    int copy = BYTE_MANTISA;
    
    if ((poryadok) >= 0){
        vect_int = {1};
        while (poryadok){
            vect_int.push_back(vect_mantisa[j]);
            poryadok--;
            j++;
        }
        
        while (difference){
            vect_remainder.push_back(vect_mantisa[j]);
            difference--;
            j++;
        }
    }
    else{
        vect_int.push_back(0);
        
        poryadok = abs(poryadok);
        while (poryadok){
            vect_remainder.push_back(0);
            poryadok--;
            j++;
        }
        vect_remainder.push_back(1);
        while (copy) {
            vect_remainder.push_back(vect_mantisa[j]);
            copy--;
            j++;
        }
    }
    
    int number_int = with_binary_in_chyslo(vect_int);
    double number_remainder = with_binary_in_chyslo_not_int(vect_remainder);
    
    double sum = (number_int + number_remainder) * sign;
    return sum;
}

//*******************************************************************************************************************
//           Перевірка точності запису числа в регістр і запис чисел у двійковий код не залежно від к-сті біт.
//*******************************************************************************************************************

vector<int> direct_code_int_all_number(double number1){
    /*
        перетворюєм у двійковий код цілу частину числа(по модулю)
        усе число не залежно скыльки біт воно займає.
     */
    
    int number = int(number1);
    int copy = number;
    list<int> list1;
    int remainder;
    //number = abs(number);
    
    while ((number != 1) and (number != 0)) {                // вираховуєм число за модулем у двійковому коді.
        remainder = number % 2;
        list1.push_front(remainder);
        
        number  /= 2;
    }
    if (copy == 0)
        list1.push_front(0);
    else
        list1.push_front(1);
    
    vector<int> vect;                                          // записуєм число у вектор
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect.push_back(*i);
    }
    return vect;
}

vector<int> direct_code_remainder_all_number(double number1, vector<int> vect_binary_int){
    /*
        перетворюєм у двійковий код дробову частину числа
        max_bit = BYTE_MANTISA = (vect_binary_int + vect_binary_remainder)
        усе число не залежно скыльки біт воно займає.
     */
    
    vector<int> vect_binary;
    double number = number1 - int(number1);
    //vect_binary.push_back(int(number * 2));
    int k = 0;
    
    while ((number != 1 ) && ((number) != 0) && (k != (BYTE_MANTISA + 1 - vect_binary_int.size()) )){
        vect_binary.push_back(int(number * 2));
        number = number * 2 - int(number * 2);
        k++;
    }
    return vect_binary;
}

int dodatok(double number1){
    vector<int> vect1 = direct_code_int_all_number(number1);
    if (int(vect1.size()) > BYTE_MANTISA+1){
        return 1;
    }
    
    double number2 = number1 - int(number1);
    vector<int> vect2 = direct_code_remainder_all_number(number1, vect1);
    double number3 = with_binary_in_chyslo_not_int(vect2);
    if ((number2 - number3 > TOCHNIST)){

        return 2;
    }
    return  0;
}


//*******************************************************************************************************************
//                  Перетворюєм різні числа у двійковий код залежно від кількості біт у мантисі і порядку
//*******************************************************************************************************************

vector<int> direct_code_int(double number1){
    /*
        перетворюєм у двійковий код цілу частину числа(по модулю).
     */
    
    int number = int(number1);
    int copy = number;
    list<int> list1;
    int remainder;
    //number = abs(number);
    
    while ((number != 1) and (number != 0) and (list1.size() < BYTE_MANTISA)) {                // вираховуєм число за модулем у двійковому коді.
        remainder = number % 2;
        list1.push_front(remainder);
        
        number  /= 2;
    }
    if (copy == 0)
        list1.push_front(0);
    else
        list1.push_front(1);
    
    vector<int> vect;                                          // записуєм число у вектор
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect.push_back(*i);
        
    }
    
    
    return vect;
}

vector<int> direct_code_remainder(double number1, vector<int> vect_binary_int){
    /*
        перетворюєм у двійковий код дробову частину числа
        max_bit = BYTE_MANTISA = (vect_binary_int + vect_binary_remainder).
     */
    
    vector<int> vect_binary;
    double number = number1 - int(number1);
    //vect_binary.push_back(int(number * 2));
    int k = 0;
    
    while ((number != 1 ) && ((number) != 0) && (k != (BYTE_MANTISA - vect_binary_int.size()) + 1)){
        vect_binary.push_back(int(number * 2));
        number = number * 2 - int(number * 2);

        k++;
    }
    return vect_binary;
}



vector<vector<int>> direct_code_porydok(vector<int> vect_binary_int, vector<int> vect_binary_remainder){
    /*
        перетворюєм у двійковий код порядок числа. на виході весктор цілих чисел(0 чи 1)
        number = 2^(BYTE_PORYADKA)   -->  кількість чисел яких можна отримати.
        до числа (number) додаєм (our_poryadok) утворене число = A.
        якщо (А < number), то (our_poryadok < 0).
        якщо (А > number), то (our_poryadok > 0).
     */
    
    vector<int> vect_binary;
    int sum;
    int size_binary_number;
    int center = pow(2, BYTE_PORYADKA) / 2;
    
    size_binary_number = int(vect_binary_int.size()) - 1;
    
    
    if ((vect_binary_int.size() == 1) and (vect_binary_int[0] == 0)){
        int j = 0;
        int k = vect_binary_remainder[j];
        while (k != 1){
            k = vect_binary_remainder[j];
            j++;
        }
        size_binary_number = -1 * j;
    }
    
    sum              = int(center) + size_binary_number;
    vector<int> vect_porydok = direct_code_int(sum);
    
    // добавляєм нулі на початок двійкового числа
    list<int> list1;
    for (auto i = vect_porydok.begin(); i != vect_porydok.end(); i++){
        list1.push_back(*i);
    }
    while (list1.size() != BYTE_PORYADKA){
        list1.push_front(0);
    }
    vect_porydok.clear();
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_porydok.push_back(*i);
    }
    
    vector<vector<int>> vect = {vect_porydok, {size_binary_number}};
    return vect;
}

//*******************************************************************************************************************
//                  Поступовий запис знаку, мантиси і порядку степеня у двійковий код.
//*******************************************************************************************************************


string sign(double number){
    /*
        перетворюєм у двійковий код знак числа на виході строка.
     */
    
    string sign;
    if (number < 0){
        sign = '1';
    }
    else if (number >= 0){
        sign = '0';
    }
    return sign;
}

string mantisa(double number){
    /*
            перетворюєм у двійковий код мантису  на виході строка.
     */
    
    string str;
    number = abs(number);
    vector<int> vect_binary_int       = direct_code_int(number);
    vector<int> vect_binary_remainder = direct_code_remainder(number, vect_binary_int);
    
    string g = output(vect_binary_remainder);
    
    
    vector<vector<int>> vect = direct_code_porydok(vect_binary_int, vect_binary_remainder);
    
    string s1;
    string s2;
    
    if (vect[1][0] >= 0){
        vect_binary_int = landl(1, vect_binary_int);
        vect_binary_int.pop_back();
    }
    else{
        vect_binary_int.pop_back();
        int k = abs(vect[1][0]);
        vect_binary_remainder = landl(k, vect_binary_remainder);
        while (k){
            vect_binary_remainder.pop_back();
            k--;
        }
    }
    
    s1 = output(vect_binary_int);
    s2 = output(vect_binary_remainder);
    
    
    if (s1.size() != BYTE_MANTISA)
        str = s1 + s2;
    else
        str = s1;
    
    while (str.size() < BYTE_MANTISA) {
        str = str + '0';
    }
    return str;
}

string poryadok(double number){ // +
    /*
        перетворюєм у двійковий код порядок степеня на виході строка.
     */
    
    number = abs(number);
    vector<int> vect_binary_int       = direct_code_int(number);
    vector<int> vect_binary_remainder = direct_code_remainder(number, vect_binary_int);
    
    vector<vector<int>> vect = direct_code_porydok(vect_binary_int, vect_binary_remainder);
    string str;
    str = output(vect[0]);
    return str;
}


string resultat(double number){
    /*
        Записуєм у загальний двійковий код дійсне число, на виході строка
     */
    
    string sign1     = sign(number);
    string mantisa1  = mantisa(number);
    string poryadok1 = poryadok(number);
    
    string str_sum;
    string str;
    
    str_sum = sign1 + " " + poryadok1 + " " + mantisa1;
    
    return str_sum;
}



//*******************************************************************************************************************
//           Функції, які залежать від вибору варіанту роботи. (mov, copy, cos, add, reverse, mult, div)
//*******************************************************************************************************************


vector<vector<string>> regist(){
    /*
        Заносим значення 0.01 в усі початкові регістри
     */
    
    vector<vector<string>> vect_register;
    string binary_cod = resultat(0.01);
    
    string number        = to_string(0.01);
    vector<string> vect  = {binary_cod, number};
    
    for (int i = 0; i != NUM_REGISTER; i++){
        vect_register.push_back(vect);
    }
    
    vect_register.push_back({"0123"});
    
    return vect_register;
}

vector<vector<string>> mov(vector<vector<string>> vect_regist, double number){
    /*
        добавляєм значення в перший регістр.
     */
    
    string binary_cod   = resultat(number);
    string number_str   = to_string(number);
    vector<string> vect = {binary_cod, number_str};
    
    list<vector<string>> list1;
    for (auto i = vect_regist.begin(); i != vect_regist.end(); i++){
        list1.push_back(*i);
    }
    list1.push_front(vect);
    list1.pop_back();
    int j = 0;
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_regist[j] = *i;
        j++;
    }
 
    return vect_regist;
}

vector<vector<string>> copy(vector<vector<string>> vect_regist){
    /*
        Копіюєм значення в регістр і заносим в перший регістр переносячи перший в другий регістр.
     */
    
    vector<string> vect = vect_regist[0];
    
    list<vector<string>> list1;
    for (auto i = vect_regist.begin(); i != vect_regist.end(); i++){
        list1.push_back(*i);
    }
    list1.push_front(vect);
    list1.pop_back();
    int j = 0;
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_regist[j] = *i;
        j++;
    }
    
    return vect_regist;
}

vector<vector<string>> cos(vector<vector<string>> vect_regist){
    /*
        Коcинус першого числа пешого регістра, який зберігається в першому регістрі.
     */
    
    double number = atof(vect_regist[0][1].c_str());
    double function_cos = cos(number);
    
    string binary_cod   = resultat(function_cos);
    string number_str   = to_string(function_cos);
    
    vector<string> vect = {binary_cod, number_str};
    vect_regist[0] = vect;
    
    return vect_regist;
}

vector<vector<string>> add(vector<vector<string>> vect_regist){
    /*
        Додаєм значення першого регістра із значенням другого ресгістру і зберігаєм в першому регістрі.
     */
    
    string binary_cod1 = resultat(0.01);
    string numberr     = to_string(0.01);
    vector<string> vect_start = {binary_cod1, numberr};
    
    
    double number1 = atof(vect_regist[0][1].c_str());
    double number2 = atof(vect_regist[1][1].c_str());
    double sum = number1 + number2;
    
    string binary_cod   = resultat(sum);
    string number_str   = to_string(sum);
    vector<string> vect = {binary_cod, number_str};
    vect_regist[1] = vect;
    
    list<vector<string>> list1;
    vector<string> ostaniy = vect_regist[int(vect_regist.size() - 1)];
    
    for (int i = 0; i != int(vect_regist.size() - 1); i++){
        list1.push_back(vect_regist[i]);
    }
    list1.pop_front();
    list1.push_back(vect_start);
    
    int j = 0;
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_regist[j] = *i;
        j++;
    }
    list1.push_back(ostaniy);
    
    return vect_regist;
}

vector<vector<string>> reverse(vector<vector<string>> vect_regist){
    /*
        Робимо реверсування R1 --> R2, a R2 --> R1.
     */
    
    vector<string> vect_copy = vect_regist[0];
    vect_regist[0] = vect_regist[1];
    vect_regist[1] = vect_copy;
    
    return vect_regist;
}

vector<vector<string>> mult(vector<vector<string>> vect_regist){
    /*
        Множення значення першого регістра із значенням другого регістра зберігаєм в першому регістрі.
     */
    
    string binary_cod1 = resultat(0.01);
    string numberr     = to_string(0.01);
    vector<string> vect_start = {binary_cod1, numberr};
    
    double number1 = atof(vect_regist[0][1].c_str());
    double number2 = atof(vect_regist[1][1].c_str());
    double sum = number1 * number2;
    
    string binary_cod   = resultat(sum);
    string number_str   = to_string(sum);
    vector<string> vect = {binary_cod, number_str};
    vect_regist[1] = vect;
    
    list<vector<string>> list1;
    vector<string> ostaniy = vect_regist[int(vect_regist.size() - 1)];
    
    for (int i = 0; i != int(vect_regist.size() - 1); i++){
        list1.push_back(vect_regist[i]);
    }
    list1.pop_front();
    list1.push_back(vect_start);
    
    
    int j = 0;
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_regist[j] = *i;
        j++;
    }
    list1.push_back(ostaniy);

    return vect_regist;
}

vector<vector<string>> div(vector<vector<string>> vect_regist){
    /*
        Ділення значення першого регістра на значення другого регітсра.
     */
    
    string binary_cod1 = resultat(0.01);
    string numberr     = to_string(0.01);
    vector<string> vect_start = {binary_cod1, numberr};
    
    
    double number1 = atof(vect_regist[0][1].c_str());
    double number2 = atof(vect_regist[1][1].c_str());
    double sum = number1 / number2;
    
    string binary_cod   = resultat(sum);
    string number_str   = to_string(sum);
    vector<string> vect = {binary_cod, number_str};
    vect_regist[1] = vect;
    
    
    list<vector<string>> list1;
    
    vector<string> ostaniy = vect_regist[int(vect_regist.size() - 1)];
    
    for (int i = 0; i != int(vect_regist.size() - 1); i++){
        list1.push_back(vect_regist[i]);
    }
    list1.pop_front();
    list1.push_back(vect_start);
    
    
    int j = 0;
    for (auto i = list1.begin(); i != list1.end(); i++){
        vect_regist[j] = *i;
        j++;
    }
    list1.push_back(ostaniy);
    return vect_regist;
}

//*******************************************************************************************************************
//           Вивід результату і умови варіанту.
//*******************************************************************************************************************

void output_register(vector<vector<string>> vect_regist){
    /*
        Вивід результату.
     */
    
    TC++;
    
    cout << "R1 = " << vect_regist[0][0] << "      IR:  " << vect_regist[NUM_REGISTER][0] << endl;
    cout << "R2 = " << vect_regist[1][0] << "      PC = " << PC << endl;
    cout << "R3 = " << vect_regist[2][0] << "      TC = " << TC << endl;
    cout << "R4 = " << vect_regist[3][0] << "      PS = " << PS << endl;
    
    int j = 4;
    for (int i = 0; i != (NUM_REGISTER - 4); i++){
        cout << "R" << j + 1 <<" = " << vect_regist[j][0] << endl;
        j++;
    }
}

void instruction(){
    cout << "Формула: " << endl;
    cout << "\tx^2 / (cos(x) + y)" << endl;
    cout << "Кількість бітів порядку степеня: " << BYTE_PORYADKA << endl;
    cout << "Кількість бітів мантиси:         " << BYTE_PORYADKA << endl;
}


//*******************************************************************************************************************
//           Процес обчислення форумули.
//*******************************************************************************************************************

void NuN(){
    
    cout << "Визначає відносно цього числа порядок: "<<int(pow(2, BYTE_MANTISA) / 2) << endl;
    cout << "0 0000000000 1 0000000000  ---> мінімальна додатнє число(не нуль)" << endl;
    cout << "0 1111111110 1 1111111111  ---> максимальне додатнє число" << endl; // 10 знаків після коми
    
    cout << "1 1111111110 1 1111111111  ---> мінімальне відємне число" << endl;
    cout << "1 0000000000 1 0000000000  ---> максимальне відємне число" << endl;
    cout << "0 1000000000 1 0000000000  ---> +1,0E0" << endl;
    
    cout << "0 1111111111 1 0000000000  ---> + нескінченність" << endl;
    cout << "1 1111111111 1 0000000000  ---> + нескінченність" << endl;
    
    cout << "1 1111111111 1 0000000000  ---> NuN" << endl;
}


void input(){
    vector<vector<string>> vect_regist = regist();
    
    double x;
    double y;
    int k;
    double number;
    string res;
    
    instruction();
    cout << endl;
    NuN();
    while (true) {
        cout << "\n\nВведи значення х: ";
        cin >> x;
        cout << "Введи значення y: ";
        cin >> y;
        
        
        res = "mov |" + to_string(x) + "|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = mov(vect_regist, x);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "|copy|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = copy(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "|cos|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = cos(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "mov |" + to_string(y) + "|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = mov(vect_regist, y);
        vect_regist[NUM_REGISTER ][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "|add|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = add(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "|reverse|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = reverse(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        res = "|copy|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = copy(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        
        cout << "\n*****************************************************************************************************************************\n" << endl;
        res = "|mult|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = mult(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        cout << "\n*****************************************************************************************************************************\n" << endl;
        
        res = "|div|";
        
        vect_regist[NUM_REGISTER][0] = res;
        PC++;
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        vect_regist = div(vect_regist);
        vect_regist[NUM_REGISTER][0] = res;
        cout << "\n";
        PS = vect_regist[0][0][0];
        output_register(vect_regist);
        TC = 0;
        number = atof(vect_regist[0][1].c_str());
        k = dodatok(number);
    
        if (k == 1){
            cout << "Не можливо записати цілу частину у регістр, дуже велике(+ or - безкінченність)" << endl;
            continue;
        }
        else if (k == 2){
            cout << "Не можливо записати дробову частину у регістр не хватає біт для запису (NuN)" << endl;
            continue;
        }
        
        
        
        string s = split(vect_regist[0][0], " ");
        
        double vidpovid_binari = decimal_system(s);
        
        
        cout << "Відповідь: " << vect_regist[0][1] << endl;
        
        
    }
}

