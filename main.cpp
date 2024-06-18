#include <iostream>
#include <string>
#include <thread>
#include <valarray>
using namespace std;

/* 定义常量MALE，表示男性的性别 */
#define MALE 1
/* 定义常量FEMALE，表示女性的性别 */
#define FEMALE 2

int main() {
    cout <<"Welcome to my student system!"<<endl;//欢迎
    cout <<"please enter your student number!"<<endl;//输入学生数量
    int studentNumber=0;//学生数量
    int classNumber=3;//课程数量
    bool any_student_failed = false;//是否有学生挂科
    double variance[classNumber];//课程方差
    cin >> studentNumber;
    //创建一个学生的结构体，信息有名字，性别，年龄，三门课程成绩
    struct Student {
        string name;//姓名
        int sex;//性别
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
                //break;
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

    // 输出学生信息之后添加的信息检查部分
    cout << "Checking student information consistency..." << endl;
    bool hasIssues = false;
    for (int i = 0; i < studentNumber; ++i) {
      // 检查姓名非空
      if (student[i].name.empty()) {
        cout << "Error: Student " << i + 1 << "'s name is empty." << endl;
        hasIssues = true;
      }
      // 检查性别为男女
      if ((student[i].sex!=MALE)&&(student[i].sex!=FEMALE)) {
        cout << "Error: Student " << i + 1 << "'s sex is wrong." << endl;
        hasIssues = true;
      }
      // 检查年龄合理性
      if (student[i].age <= 0||student[i].age>=130) {
        cout << "Error: Student " << i + 1 << "'s age is invalid (" << student[i].age << ")." << endl;
        hasIssues = true;
      }
      // 检查成绩有效性（假设成绩范围为0-100）
      for (int j = 0; j < classNumber; ++j) {
        if (student[i].score[j] < 0 || student[i].score[j] > 100) {
          cout << "Error: Student " << i + 1 << "'s " << (j+1) << "th score (" << student[i].score[j] << ") is out of range." << endl;
          hasIssues = true;
        }
      }
    }

    if (!hasIssues) {
      cout << "All student information is consistent and valid." << endl;//所有学生信息一致
    } else {
      // 输出学生错误信息
      cout << "There are issues with the entered student information. Please review the errors above." << endl;
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
            int searchSex;
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
            // 计算语文均分和方差
            int chineseTotal = 0;
            for (int i = 0; i < studentNumber; i++) {
                chineseTotal += student[i].score[0]; // 语文是第一门课
            }
            double chineseAverage = static_cast<double>(chineseTotal) / studentNumber;
            cout << "Average score of Chinese: " << chineseAverage << endl;//输出语文均分
            double chineseVariance = 0.0;//语文方差
            for (int i = 0; i < studentNumber; i++) {
              chineseVariance += pow(student[i].score[0] - chineseAverage, 2);
            }
            chineseVariance /= studentNumber;
            cout << "Variance of Chinese scores: " << chineseVariance << endl;//输出语文方差
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
            double mathVariance = 0.0;//数学方差
            for (int i = 0; i < studentNumber; i++) {
              mathVariance += pow(student[i].score[1] - mathAverage, 2);
            }
            mathVariance /= studentNumber;
            cout << "Variance of Math scores: " << mathVariance << endl;//输出数学方差
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
            double englishVariance = 0.0;//英语方差
            for (int i = 0; i < studentNumber; i++) {
              englishVariance += pow(student[i].score[2] - englishAverage, 2);
            }
            englishVariance /= studentNumber;
            cout << "Variance of English scores: " << englishVariance << endl;//输出英语方差
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
    cout << "calculate the variance!" << endl;//计算方差

    cout << "Thank you for using my student system!" << endl;//程序结束
    std::this_thread::sleep_for(std::chrono::seconds(2000)); // 延时2000秒
    return 0;
}
