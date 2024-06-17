#include <iostream>
#include <string>
#include <thread>
using namespace std;

int main() {
    cout <<"Welcome to my student system!"<<endl;//欢迎
    cout <<"please enter your student number!"<<endl;//输入学生数量
    int studentNumber=0;//学生数量
    int classNumber=3;//课程数量
    bool any_student_failed = false;//是否有学生挂科
    cin >> studentNumber;
    //创建一个学生的结构体，信息有名字，性别，年龄，三门课程成绩
    struct Student {
        string name;//姓名
        string sex;//性别
        int age{};//年龄
        int score[3]{};//成绩,语文，数学，英语
        int sum{};//总成绩
        bool fail=false;//是否挂科
    };
    Student student[studentNumber];//创建学生数组
    //循环输入学生信息
    for (int i = 0; i < studentNumber; i++) {
        cout << "please enter "<<i+1<<"th"<<" student information!" << endl;//输入学生信息
        cout << "please enter the name of "<<i+1<<"th "<<" student." << endl;//输入学生姓名
        cin >> student[i].name;
        cout << "please enter the gender of "<<i+1<<"th "<<" student." << endl;//输入学生性别
        cin >> student[i].sex;
        cout << "please enter the age of "<<i+1<<"th "<<" student." << endl;//输入学生年龄
        cin >> student[i].age;
        for (int j = 0; j < classNumber; j++) {
            cout << "please enter "<<j+1<<"th score of "<<i+1<<"th "<<" student." << endl;//输入学生成绩
            cin >> student[i].score[j];
            student[i].sum += student[i].score[j];//计算学生总成绩
            if (student[i].score[j] < 60) {
                cout << "the student is fail!" << endl;
                student[i].fail=true;//挂科
                any_student_failed = true;//有学生挂科
                break;
            }
        }
    }
    cout << "Enter student information completed!" << endl;//录入学生信息完成

    //输出学生信息
    cout << "Student Information:" << endl;
    for (int i = 0; i < studentNumber; i++) {
        cout << "Name: " << student[i].name << ", Sex: " << student[i].sex
             << ", Age: " << student[i].age << ", Scores: ";
        for(int j = 0; j < classNumber; j++)
            cout << student[i].score[j] << (j+1==classNumber ? "" : ", ");
        cout << ", Total Score: " << student[i].sum << ", Fail: " << (student[i].fail?"Yes":"No") << endl;
    }
    //开始选择使用的功能
    cout << "please enter the function you want to use!" << endl;
    cout<<"1.Students search by name"<<endl;//学生按姓名查询功能
    cout<<"2.Students search by name and gender"<<endl;//学生查询功能（按姓名和性别筛选）
    cout<<"3.Students search by age"<<endl;//学生按年龄查询功能
    cout<<"4.Calculate the average score of Chinese class for students"<<endl;//统计学生语文均分
    cout<<"5.Calculate the average score of Math class for students"<<endl;//统计学生数学均分
    cout<<"6.Calculate the average score of English class for students"<<endl;//统计学生英语均分
    cout << "7. Search for failed students" << endl;//查找挂科学生
    int functionChoice;//功能选择
    cin >> functionChoice;//输入功能选择
    switch (functionChoice) {
        case 1: {
            // 学生查询功能（按姓名查询）
            string searchName;
            cout << "Please enter the student name you want to search: " << endl;//输入学生姓名
            cin >> searchName;
            bool found = false;
            for (int i = 0; i < studentNumber; i++) {
                if (student[i].name == searchName) {
                    cout << "Student Found: Name: " << student[i].name
                         << ", Sex: " << student[i].sex
                         << ", Age: " << student[i].age
                         << ", Total Score: " << student[i].sum
                         << ", Fail: " << (student[i].fail ? "Yes" : "No") << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student not found." << endl;//未找到学生
            break;
        }
        case 2: {
            // 学生查询功能（按姓名和性别筛选）
            string searchName;
            string searchSex;
            cout << "Please enter the student name you want to search: " << endl;
            cin >> searchName;
            cout << "Please enter the gender you want to filter (M/F): " << endl;
            cin >> searchSex;
            bool found = false;
            for (int i = 0; i < studentNumber; i++) {
                if (student[i].name == searchName && student[i].sex == searchSex) {
                    cout << "Student Found: Name: " << student[i].name
                         << ", Sex: " << student[i].sex
                         << ", Age: " << student[i].age
                         << ", Total Score: " << student[i].sum
                         << ", Fail: " << (student[i].fail ? "Yes" : "No") << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student not found." << endl;
            break;
        }
        case 3: {
            // 学生查询功能（按年龄筛选）
            int searchAge;
            cout << "Please enter the age you want to filter: " << endl;//输入筛选的学生的年龄
            cin >> searchAge;
            bool found = false;
            cout << "Students Found with Age " << searchAge << ":" << endl;
            for (int i = 0; i < studentNumber; i++) {
                if (student[i].age == searchAge) {
                    cout << "Name: " << student[i].name
                         << ", Sex: " << student[i].sex
                         << ", Age: " << student[i].age
                         << ", Total Score: " << student[i].sum
                         << ", Fail: " << (student[i].fail ? "Yes" : "No") << endl;
                    found = true;
                }
            }
            if (!found) cout << "No students found at this age." << endl;//未找到符合条件的学生
            break;
        }
        case 4: {
            // 计算语文均分
            int chineseTotal = 0;
            for (int i = 0; i < studentNumber; i++) {
                chineseTotal += student[i].score[0]; // 语文是第一门课
            }
            double chineseAverage = static_cast<double>(chineseTotal) / studentNumber;
            cout << "Average score of Chinese: " << chineseAverage << endl;//输出语文均分
            break;
        }
        case 5: {
            // 计算数学均分
            int mathTotal = 0;
            for (int i = 0; i < studentNumber; i++) {
                mathTotal += student[i].score[1]; // 数学是第二门课
            }
            double mathAverage = static_cast<double>(mathTotal) / studentNumber;
            cout << "Average score of Math: " << mathAverage << endl;//输出数学均分
            break;
        }
        case 6: {
            // 计算英语均分
            int englishTotal = 0;
            for (int i = 0; i < studentNumber; i++) {
                englishTotal += student[i].score[1]; // 数学是第二门课
            }
            double englishAverage = static_cast<double>(englishTotal) / studentNumber;
            cout << "Average score of English: " << englishAverage << endl;//输出英语均分
            break;
        }
        case 7: {
            // 统计挂科学生
            cout << "Failed Students:" << endl;
            for (int i = 0; i < studentNumber; i++) {
                if (student[i].fail) {
                    cout << "Name: " << student[i].name
                         << ", Sex: " << student[i].sex
                         << ", Age: " << student[i].age
                         << ", Total Score: " << student[i].sum
                         << endl;
                }
            }
            if (!any_student_failed) cout << "No failed students." << endl; // 如果没有挂科学生
            break;
        }
        default:
            cout << "Please enter the correct function!" << endl;//输入错误
            break;
    }
    cout << "Thank you for using my student system!" << endl;//程序结束
    std::this_thread::sleep_for(std::chrono::seconds(2000)); // 延时2000秒
    return 0;
}


