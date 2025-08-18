#include <bits/stdc++.h>
using namespace std;

class PasswordGenerator {
    private:
        int length;
        bool useUpper, useLower, useDigit, useSym;
        string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string lower = "abcdefghijklmnopqrstuvwxyz";
        string digit = "0123456789";
        string sym = "!@#$%^&*()-_=+[]{};:,.<>?";
        mt19937 gen;
    public:
        PasswordGenerator():useUpper(false),useLower(false),useDigit(false),useSym(false),length(8) {
            gen=mt19937(random_device{}());
        }
        void setPref(bool uUpper,bool uLower,bool uDigit,bool uSym) {
            useUpper = uUpper;
            useLower = uLower;
            useDigit = uDigit;
            useSym = uSym;  
        }
        void setLength(int len)
        {
            length=len;
        }
        string generate() {
            string allowedChar;
            vector<char> pass;

            if(useUpper) {
                uniform_int_distribution<> ran(0,upper.size()-1);
                pass.push_back(upper[ran(gen)]);
                allowedChar+=upper;
            }
            if(useLower) {
                uniform_int_distribution<> ran(0,lower.size()-1);
                pass.push_back(lower[ran(gen)]);
                allowedChar+=lower;
            }
            if(useDigit) {
                uniform_int_distribution<> ran(0,digit.size()-1);
                pass.push_back(digit[ran(gen)]);
                allowedChar+=digit;
            }
            if(useSym) {
                uniform_int_distribution<> ran(0,sym.size()-1);
                pass.push_back(sym[ran(gen)]);
                allowedChar+=sym;
            }
            uniform_int_distribution<> ranALL(0,allowedChar.size()-1);

            while(pass.size()<length)
            {
                pass.push_back(allowedChar[ranALL(gen)]);
            }
            shuffle(pass.begin(),pass.end(),gen);
            string password(pass.begin(),pass.end());
            return password;
        }
};

int getPassLength()
{
    cout<<"Enter desired password length: ";
    while(true) {
        int length;
        cin>>length;
        if(cin.fail()) {  
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 6 and 100: ";
            continue;
        }
        if(length<6 || length>100)
        {
            cout<<"valid password is of length 6-100"<<endl;
            continue;
        }
        return length;
    }
}

void getUserPref(bool &uUpper,bool &uLower,bool &uDigit,bool &uSym) {
    char ch1,ch2,ch3,ch4;
    cout<<"Include uppercase letters? (y/n): ";
    cin>>ch1;
    while(ch1!='Y'&&ch1!='y'&&ch1!='N'&&ch1!='n')
    {
        cout<<"You can only enter y or n (y/n):";
        cin>>ch1;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout<<"Include lowercase letters? (y/n): ";
    cin>>ch2;
    while(ch2!='Y'&&ch2!='y'&&ch2!='N'&&ch2!='n')
    {
        cout<<"You can only enter y or n (y/n):";
        cin>>ch2;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout<<"Include digits? (y/n): ";
    cin>>ch3;
    while(ch3!='Y'&&ch3!='y'&&ch3!='N'&&ch3!='n')
    {
        cout<<"You can only enter y or n (y/n):";
        cin>>ch3;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout<<"Include symbols? (y/n): ";
    cin>>ch4;
    while(ch4!='Y'&&ch4!='y'&&ch4!='N'&&ch4!='n')
    {
        cout<<"You can only enter y or n (y/n):";
        cin>>ch4;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    uUpper= (ch1=='y'||ch1=='Y');
    uLower= (ch2=='y'||ch2=='Y');
    uDigit= (ch3=='y'||ch3=='Y');
    uSym= (ch4=='y'||ch4=='Y');
}

bool validateInput(bool uUpper,bool uLower,bool uDigit,bool uSym) {
    return uUpper || uLower || uDigit || uSym;
}

string evalStrength(const string &password) {
    int score=0;
    int length=password.length();

    bool hasU=false,hasL=false,hasD=false,hasS=false;
    set<char> uniqueCh;
    string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string digit = "0123456789";
    string sym = "!@#$%^&*()-_=+[]{};:,.<>?";

    for(char c: password)
    {
        uniqueCh.insert(c);
        if (upper.find(c) != string::npos) hasU = true;
        else if (lower.find(c) != string::npos) hasL = true;
        else if (digit.find(c) != string::npos) hasD = true;
        else if (sym.find(c) != string::npos) hasS = true;
    }

    int charsetSize=0;
    if(hasU) charsetSize+=upper.size();
    if(hasL) charsetSize+=lower.size();
    if(hasD) charsetSize+=digit.size();
    if(hasS) charsetSize+=sym.size();

    double entropy=length*log2(charsetSize ? charsetSize : 1);
    score+=(length>=8)+(length>=12)+(length>=16)+(length>=20);
    score+=hasU+hasL+hasD+hasS;

    if(uniqueCh.size()<length/2) {
        score--;
    }
    for(size_t i=1;i<password.size();++i)
    {
        if(password[i]==password[i-1]+1) {
            score--;
            break;
        }
    }

    if(entropy> 50) score++;
    if(entropy> 70) score++;

    vector<string> common={"password","12345678","qwertyui","admin@123"};
    for(auto &s:common)
    {
        if(password.find(s)!=string::npos) 
        {
            score=0;
            break;
        }
    }
    
    string feedback;
    if(score<=2)
    {
        feedback="Weak";
    } else if(score<=4) 
    {
        feedback="Medium";
    }
    else if(score<=6)
    {
        feedback="strong";
    }
    else {
        feedback="Very Strong";
    }

    return "Password Strength: "+feedback + "(Entropy: "+to_string(int(entropy))+"bits)";
}

int main() {
    PasswordGenerator generator;
    char selector;
    while(true) {   
        cout<<"Do you want to check your password strength or generate a new password? (e/g):";
        cin>>selector;
        while(selector!='g'&&selector!='G'&&selector!='E'&&selector!='e')
        {
            cout<<"You can only enter e or g (e/g):";
            cin>>selector;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(selector=='g'||selector=='G') {
            int length=getPassLength();
            bool uUpper,uLower,uDigit,uSym;

            getUserPref(uUpper,uLower,uDigit,uSym);

            while(!validateInput(uUpper,uLower,uDigit,uSym)) {
                cout<< "Error: You have to select atleast one character type!\n";
                getUserPref(uUpper,uLower,uDigit,uSym);

            }

        
            generator.setLength(length);
            generator.setPref(uUpper,uLower,uDigit,uSym);


            string pass=generator.generate();
            cout<< "Your requested password: "<<pass<<endl;
            
            string evalPass= evalStrength(pass);
            cout<<evalPass<<endl;   
        }
    
        else{
            cout <<"Enter the string you wish to evaluate: ";
            cin.ignore(numeric_limits<streamsize>::max(),'\n');  
            string input;
            getline(cin, input); 
            cout<<evalStrength(input)<<endl;
        }

        cout<<"Do you want to check another password's strength or generate another password?(y/n): ";
        char ch;
        cin>>ch;  
        while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n')
        {
            cout<<"You can only enter y or n (y/n):";
            cin>>ch;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(ch!='y'&&ch!='Y')
        {
            break;
        }
    }
    cout<<"Hope youre satisfied with our pass checker/evaluator :0"<<endl;
    return 0;
}