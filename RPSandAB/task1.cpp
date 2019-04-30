#include <iostream>
#include "time.h"
using namespace std;

class Tool{
public:
    Tool();
    ~Tool();
    void setType(char pType);
    void setStrength(int pStrength);
    char getType();
    int getStrength();
    virtual bool fight(Tool);
protected:
    int strength;
    char type ;
};
class Rock : public Tool{
public:
    Rock();
    Rock(int);
    bool fight(Tool);
};
class Paper : public Tool{
public:
    Paper();
    Paper(int);
    bool fight(Tool);
};
class Scissor : public Tool{
public:
    Scissor();
    Scissor(int);
    bool fight(Tool);
};
class RPSPlay{
private:
    Tool * human;
    Tool * computer;
    int human_wins;
    int computer_wins;
    int ties;
    Tool * computerSelect();
    Tool * humanSelect();
    void printChoice(string, char);
public:
    RPSPlay();
    void run();
};
RPSPlay::RPSPlay(){
    this->human_wins = 0;
    this->computer_wins = 0;
    this->ties = 0;
    this->human = 0;
    this->computer = 0;
}
Tool * RPSPlay::computerSelect(){
    int selectNumber = rand() % 3;
    if(selectNumber == 0){
        return new Rock(15);
    } else if(selectNumber == 1){
        return new Paper(7);
    } else{
        return new Scissor(5);
    }
}
Tool * RPSPlay::humanSelect(){
    cout << "Please Choose Rock(R), Paper(P) or Scissor(S)" << endl;
    char selectChar = 0;
    cin >> selectChar;
    if(selectChar == 'S' || selectChar == 's'){
        return new Scissor(5);
    } else if(selectChar == 'R' || selectChar == 'r'){
        return new Rock(15);
    } else if(selectChar == 'P' || selectChar == 'p'){
        return new Paper(7);
    } else{
        cout << "Error" << endl;
        exit(1);
    }
}
void RPSPlay::run(){
    srand(time(0));
    while(1){
        human = this->humanSelect();
        computer = this->computerSelect();
        printChoice("Human",human->getType());
        printChoice("Computer",computer->getType());
        if(human->getType()==computer->getType()){
            ties++;
        } else if(human->fight(*computer)){
            human_wins++;
        } else{
            computer_wins++;
        }
        cout << "Human Wins: " << human_wins << " Computer Wins: " << computer_wins << " Ties: " << ties << endl;
    }
}
void RPSPlay::printChoice(string obj, char type){
    string strType = "";
    if(type == 'r'){
        strType = "Rock";
    } else if (type == 'p'){
        strType = "Paper";
    } else {
        strType = "Scissor";
    }
    cout << obj << " choose " << strType << endl;
}
Tool::Tool(){
    strength = 0;
    type = 0;
}
Tool::~Tool(){
    return;
}
bool Tool::fight(Tool otherTool){
    return true;
}
void Tool::setStrength(int pStrength){
    strength = pStrength;
}
void Tool::setType(char pType){
    type = pType;
}
int Tool::getStrength(){
    return strength;
}
char Tool::getType(){
    return type;
} 
Rock::Rock(){
    Tool::setStrength(1);
    Tool::setType('r');
}
Rock::Rock(int pStrength){
    Tool::setStrength(pStrength);
    Tool::setType('r');
}
bool Rock::fight(Tool otherTool){
    int strength = this->getStrength();
    if(otherTool.getType()=='s'){
        strength*=2;
    } else if(otherTool.getType()=='p'){
        strength/=2;
    }
    if(strength>otherTool.getStrength()){
        return true;
    } else{
        return false;
    }
}
Paper::Paper(){
    Tool::setStrength(1);
    Tool::setType('p');
}
Paper::Paper(int pStrength){
    Tool::setStrength(pStrength);
    Tool::setType('p');
}
bool Paper::fight(Tool otherTool){
    int strength = this->getStrength();
    if(otherTool.getType()=='r'){
        strength*=2;
    } else if(otherTool.getType()=='s'){
        strength/=2;
    }
    if(strength>otherTool.getStrength()){
        return true;
    } else{
        return false;
    }
}
Scissor::Scissor(){
    Tool::setStrength(1);
    Tool::setType('s');
}
Scissor::Scissor(int pStrength){
    Tool::setStrength(pStrength);
    Tool::setType('s');
}
bool Scissor::fight(Tool otherTool){
    int strength = this->getStrength();
    if(otherTool.getType()=='p'){
        strength*=2;
    } else if(otherTool.getType()=='r'){
        strength/=2;
    }
    if(strength>otherTool.getStrength()){
        return true;
    } else{
        return false;
    }
}

int main(){
    RPSPlay play;
    play.run();
    return 0;
}