#include <fstream>
#include <iostream>
#include <fcntl.h>
#include "Student.h"
#include "Instructor.h"
using namespace std;


//main method that runs all classes of project
int displayMessage(){
    cout << "User types,"<< endl;
    cout << "\t1 - Instructor " << endl;
OB    cout << "\t2 - Student " << endl;
    cout << "Select a login user type or enter 3 to exit: ";
    int returnValue = 0;
    cin >> returnValue;
    cout << "" << endl;
    return returnValue;
}

int main(int argc, char ** argv){
    Student sList[20];
    Instructor iList[3];
    ifstream inClientFile(argv[1],ios::in);
    if(!inClientFile){
        cout << "Instructor file cannot be opened." << endl;
        exit(1);
    }
    string user;
    string pass;
    string fname;
    string lname;
    int count = 0;
    while(inClientFile >> user >> pass >> fname >> lname){
        Instructor temp(fname, lname, user, pass);
        iList[count] = temp;
        count++;
    }

    ifstream nClientFile(argv[2],ios::in);
    if(!nClientFile){
        cout << "Student file cannot be opened." << endl;
    }
    int proj;
    int quiz;
    int mid;
    int fin;
    count = 0;
    while(nClientFile >> user >> pass >> fname >> lname >> proj >> quiz >> mid >> fin){
        Student temp(fname, lname, user, pass, proj, quiz, mid, fin);
        sList[count] = temp;
        count ++;
    }
    int loginType{0};
    while(loginType!=3){
        loginType = displayMessage();

        while(loginType != 1 && loginType != 2 && loginType != 3){
            cout << "Invalid option. Please enter a valid option." << endl;
            loginType = displayMessage();
        }
        if(loginType == 3){
            exit(0);
        }
        cout << "Enter credentials to login, \n\tEnter username: ";
        string username = "";
        string password = "";
        cin >> username;
        cout << "\tEnter password: ";
        cin >> password;
        cout << "" << endl;
        
        bool loginAttempt = false;
        int successOptions = 0;
        
        if(loginType == 1){
            for(int i = 0; i < 3; i++){
                loginAttempt = iList[i].login(username, password);
                if(loginAttempt == true){
                    cout << "You are now logged in as instructor " + iList[i].getInstructorName() + "." << endl;
                    do{
                        cout << "Query options, " << endl;
                        cout << "\t1 - view grades of a student" << endl;
                        cout << "\t2 - view stats" << endl;
                        cin >> successOptions;
                        cout << "" << endl;
                        if(successOptions != 1 && successOptions !=2){
                            cout << "Invalid option. Please enter a valid option" << endl;
                        }
                    }while(successOptions != 1 && successOptions !=2);
                    if(successOptions == 1){
                        cout << "Enter student username to view grades: " << endl;
                        string sUser;
                        cin >> sUser;
                        cout << "" << endl;
                        for(int i = 0; i < 20; i++){
                            if(sList[i].sameUser(sUser) == true){
                                cout << "Student name: " + sList[i].getStudentName() << endl;
                                cout <<  "Project " << sList[i].getProjectGrade() << "%" << endl;
                                cout <<  "Quiz " << sList[i].getQuizGrade() << "%" << endl;
                                cout <<  "Midterm " << sList[i].getMidtermGrade() << "%" << endl;
                                cout <<  "Final " << sList[i].getFinalGrade() << "%" << endl;                               
                            }
                        }
                    }
                    if(successOptions == 2){
                        int gradeType = 0;
                        while( gradeType < 1 || gradeType > 5){
                            cout << "Grade types, " << endl;
                            cout << "     1 - Project Grade " << endl;
                            cout << "     2 - Quiz Grade" << endl;
                            cout << "     3 - Midterm Grade" << endl;
                            cout << "     4 - Final Grade" << endl;
                            cout << "     5 - Overal Grade" << endl;
                            cout << "Select a grade type to view stats: ";
                            cin >> gradeType;
                            cout << "" << endl;
                            if(gradeType < 1 || gradeType > 5){
                                cout << "Invalid option." << endl;
                            }

                            double min = 0;
                            double max = 0;
                            double avg = 0;
                            double sum = 0;
                            string minName = "";
                            string maxName = "";

                            if(gradeType == 1){
                                min = sList[0].getProjectGrade();
                                max = sList[0].getProjectGrade();
                                minName = sList[0].getStudentName();
                                maxName = sList[0].getStudentName();
                                for(int i = 0; i < 20; i++){
                                    if(min > sList[i].getProjectGrade()){
                                        min = sList[i].getProjectGrade();
                                        minName = sList[i].getStudentName();
                                    }
                                    if(max < sList[i].getProjectGrade()){
                                        max = sList[i].getProjectGrade();
                                        maxName = sList[i].getStudentName();
                                    }
                                    sum += sList[i].getProjectGrade();
                                }
                                avg = sum / 20;
                                cout << "Project grade stats, " << endl;
                                cout << "     min " << min << "% (" << minName << ")" << endl;
                                cout << "     max " << max << "% (" << maxName << ")" << endl;
                                cout << "     avg " << avg << "%" << endl;
                            }

                            if(gradeType == 3){
                                min = sList[0].getQuizGrade();
                                max = sList[0].getQuizGrade();
                                minName = sList[0].getStudentName();
                                maxName = sList[0].getStudentName();
                                for(int i = 0; i < 20; i++){
                                    if(min > sList[i].getQuizGrade()){
                                        min = sList[i].getQuizGrade();
                                        minName = sList[i].getStudentName();
                                    }
                                    if(max < sList[i].getQuizGrade()){
                                        max = sList[i].getQuizGrade();
                                        maxName = sList[i].getStudentName();
                                    }
                                    sum += sList[i].getQuizGrade();
                                }
                                avg = sum / 20;
                                cout << "Quiz grade stats, " << endl;
                                cout << "     min " << min << "% (" << minName << ")" << endl;
                                cout << "     max " << max << "% (" << maxName << ")" << endl;
                                cout << "     avg " << avg << "%" << endl;
                            }
                            if(gradeType == 3){
                                min = sList[0].getMidtermGrade();
                                max = sList[0].getMidtermGrade();
                                minName = sList[0].getStudentName();
                                maxName = sList[0].getStudentName();
                                for(int i = 0; i < 20; i++){
                                    if(min > sList[i].getMidtermGrade()){
                                        min = sList[i].getMidtermGrade();
                                        minName = sList[i].getStudentName();
                                    }
                                    if(max < sList[i].getMidtermGrade()){
                                        max = sList[i].getMidtermGrade();
                                        maxName = sList[i].getStudentName();
                                    }
                                    sum += sList[i].getMidtermGrade();
                                }
                                avg = sum / 20;
                                cout << "Midterm grade stats, " << endl;
                                cout << "     min " << min << "% (" << minName << ")" << endl;
                                cout << "     max " << max << "% (" << maxName << ")" << endl;
                                cout << "     avg " << avg << "%" << endl;
                            }
                            
                            if(gradeType == 4){
                                min = sList[0].getFinalGrade();
                                max = sList[0].getFinalGrade();
                                minName = sList[0].getStudentName();
                                maxName = sList[0].getStudentName();
                                 for(int i = 0; i < 20; i++){
                                     if(min > sList[i].getFinalGrade()){
                                         min = sList[i].getFinalGrade();
                                         minName = sList[i].getStudentName();
                                     }
                                     if(max < sList[i].getFinalGrade()){
                                         max = sList[i].getFinalGrade();
                                         maxName = sList[i].getStudentName();
                                     }
                                     sum += sList[i].getFinalGrade();
                                 }
                                 avg = sum / 20;
                                 cout << "Final grade stats, " << endl;
                                 cout << "     min " << min << "% (" << minName << ")" << endl;
                                 cout << "     max " << max << "% (" << maxName << ")" << endl;
                                 cout << "     avg " << avg << "%" << endl;
                            }
                            
                            if(gradeType == 5){
                                double over = 0;
                                double overSum = 0;
                                for(int i = 0; i < 20; i++){
                                    over = sList[i].getProjectGrade() * .3 +
                                        sList[i].getQuizGrade() * .1 + sList[i].getMidtermGrade() *
                                        .2 + sList[i].getFinalGrade() * .4;
                                    if(i == 0){
                                        min = over;
                                        max = over;
                                        minName = sList[i].getStudentName();
                                        maxName = sList[i].getStudentName();
                                    }
                                    if(min > over){
                                        min = over;
                                        minName = sList[i].getStudentName();
                                    }
                                    if(max < over){
                                        max = over;
                                        maxName = sList[i].getStudentName();
                                    }
                                    overSum += over;
                                }
                                avg = overSum / 20;
                                cout << "Overall grade stats, " << endl;
                                cout << "     min " << min << "% (" << minName << ")" << endl;
                                cout << "     max " << max << "% (" << maxName << ")" << endl;
                                cout << "     avg " << avg << "%" << endl;
                            }
                        }
                        
                    }
                    break;
                }                
            }
            if(loginAttempt==false){
                cout << "Login as instructor failed" << endl;
            }
        }
        
        if(loginType == 2){
            for(int i = 0; i < 20; i++){
                loginAttempt = sList[i].login(username, password);
                if(loginAttempt == true){
                    cout << "You are now logged in as student " + sList[i].getStudentName() + "." << endl;
                    cout << "Do you want to view your grades (y/n)? ";
                    string reply;
                    cin >> reply;
                    if(reply != "y" && reply != "n"){
                        exit(0);
                    }
                    if(reply == "y"){
                        cout << "Student name: " + sList[i].getStudentName() << endl;
                        cout <<  "Project " << sList[i].getProjectGrade() << "%" << endl;
                        cout <<  "Quiz " << sList[i].getQuizGrade() << "%" << endl;
                        cout <<  "Midterm " << sList[i].getMidtermGrade() << "%" << endl;
                        cout <<  "Final " << sList[i].getFinalGrade() << "%" << endl;
                        double overall = 0;
                        overall = sList[i].getProjectGrade() * .3 + sList[i].getQuizGrade() * .1 +
                            sList[i].getMidtermGrade() * .2 + sList[i].getFinalGrade() * .4;
                        cout << "Overall " << overall << "%" << endl;
                    }
                }                        
            }
        }
    }
    return 0;
}
