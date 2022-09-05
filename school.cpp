#include <cstring>
#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

    int NumberOfStudents;   //global variables
    int NumberOfTeachers;


class Person
{
    public:
        char* name;
        int floornumber;
        int classnumber;
        bool inClassroom;
        int tiredness; 
        int L;
        
        Person(char* pname, int sfloornumber, int sclassnumber, int Lvl)
        {
            name = pname;
            floornumber = sfloornumber;
            classnumber = sclassnumber;
            L = Lvl; 
            inClassroom = 0;
            tiredness = 0;
        }

        virtual int computeTiredness(int N)  //epistrefei to va8mo kourasis (tou atomou) meta ti leitourgia (operate) tou sxoleiou
        {
            tiredness = L*N;
        }

        virtual void print() = 0;
};


class Student : public Person
{
    public:


        Student(char* sname, int sfloornumber, int sclassnumber, int Lvl): Person(sname, sfloornumber, sclassnumber, Lvl)
        {
            
            cout << "A New Student has been created!" << endl;
            cout << "Student's name: " << name << endl;
            cout << "Student's floor: " << floornumber << endl;
            cout << "Student's class: " << classnumber << endl << endl;

        }   

        ~Student()
        {
            cout << "A Student to be destroyed!" << endl;
            cout << "Student's name: " << name << endl;
            cout << "Student's floor: " << floornumber << endl;
            cout << "Student's class: " << classnumber << endl << endl;
           
        }

         // function to print 
        void print() 
        { 
            cout << "student's name is:" << name << endl; 
            cout << "student's floor is:" << floornumber << endl; 
            cout << "student's class is:" << classnumber << endl; 
        }   
};



class Teacher: public Person
{
    public:

        Teacher(char* tname, int tfloornumber, int tclassnumber, int Lvl): Person(tname, tfloornumber, tclassnumber, Lvl)
        {
            cout << "A New Teacher has been created!" << endl;
            cout << "Teacher's name: " << name << endl;
            cout << "Teacher's floor: " << floornumber << endl;
            cout << "Teacher's class: " << classnumber << endl << endl;
        
        }   

        ~Teacher()
        {
            cout << "A Teacher to be destroyed!" << endl;
            cout << "Teacher's name: " << name << endl;
            cout << "Teacher's floor: " << floornumber << endl;
            cout << "Teacher's class: " << classnumber << endl << endl;
           
        }

        // function to print 
        void print() 
        { 
            cout << "teacher's name is:" << name << endl; 
            cout << "teacher's floor is:" << floornumber << endl; 
            cout << "teacher's class is:" << classnumber << endl; 
        }   
};




class Area
{
    public:
        Student* isNow;
        
        virtual void enter(Student*) = 0;
        //virtual void exit() = 0;
        // virtual void print() = 0;
        // virtual void operate() = 0;
};



class Classroom: public Area
{
    public:

        int capacity; //capacity
        bool hasTeacher; //flag that checks if a teacher is in the classroom (0:false, 1:true)
        Student** array; //array that stores students information in the classroom (via pointers)
        Teacher* tPtr; //pointer that points to the teacher that has been entered the classroom
        int i = 0; //Student counter in the classroom. max(i) is capacity - 1, because out 1st place is at [0])
        int hours;

        Classroom(int c, int N)
        {
            capacity = c;
            hours = N;
            hasTeacher = 0;
            array = new Student*[capacity];
            cout <<"     New Classroom have been created!" << endl;
        }

        ~Classroom()
        {
            cout << "Classroom to be destroyed!" << endl;
        }

        void enter(Student* student)
        {   

            if(i <= capacity && hasTeacher == 0)     
            {
                isNow = student;  
                array[i] = student;
                array[i]->inClassroom = 1;
                i++;
                cout << isNow->name <<" enters Classroom!" << endl;
            }
            else if(i > capacity)
            cout << student->name <<" cannot enter Classroom, beacause it it full!" << endl;
            else
            cout << student->name <<" cannot enter Classroom, beacause a teacher is already in!" << endl;

        }

        void exit()
        {
            cout << isNow->name <<" exits Classroom!" << endl;      //de 8a xreiastei h sunartisi, tin afinw omws panta gia dinatotites mellontikis epektasis
        }

        void place(Teacher* teacher)
        {
            tPtr = teacher;
            hasTeacher = 1;
            teacher->inClassroom = 1;
        }

        void operate()
        {
            for(int w=0; w<i; w++)              //for every student in the classroom
            array[w]->computeTiredness(hours);   //upologizei kai apo8ikevei tin kourasi tou (vasi tou N)

            if(hasTeacher == true)
            tPtr->computeTiredness(hours);       //kanei to idio gia ton daskalo (ean uparxei stin taksi)

        }

        void print()
        {
            for(int j=0; j<i; j++)
            cout <<"           " << array[j]->name <<". Tiredness level is: "<< array[j]->tiredness<< endl;

            if(hasTeacher == true)
            cout <<"           The teacher is: " << tPtr->name <<". Tiredness level is: "<< tPtr->tiredness<< endl;
        }
};




class Corridor: public Area
{
    public:

        Classroom classroom1;
        Classroom classroom2;
        Classroom classroom3;
        Classroom classroom4;
        Classroom classroom5;
        Classroom classroom6;

        Corridor(int c, int N): classroom1(c, N), classroom2(c, N), classroom3(c, N), classroom4(c, N), classroom5(c, N), classroom6(c, N)
        {
            cout <<"    New Corridor have been created!" << endl;
        }

        ~Corridor()
        {
            cout << "Corridor to be destroyed!" << endl;
        }

        void enter(Student* student)
        {         
            isNow = student;  
            cout << isNow->name <<" enters Corridor!" << endl;

            //6 cases (6 floors)
            switch(student->classnumber)
            {
                case 1:
                    classroom1.enter(student);       //enter 1st classroom
                    break;                
                case 2:
                    classroom2.enter(student);       //enter 2nd classroom
                    break;
                case 3:
                    classroom3.enter(student);       //enter 3rd classroom
                    break;
                case 4:
                    classroom4.enter(student);       //enter 4th classroom
                    break;
                case 5:
                    classroom5.enter(student);       //enter 5th classroom
                    break;
                case 6:
                    classroom6.enter(student);       //enter 6th classroom
                    break;
            }
           
        }

        void exit()
        {
            cout << isNow->name <<" exits Corridor!" << endl;  //de 8a xreiastei h sunartisi, tin afinw omws panta gia dinatotites mellontikis epektasis
        }

       void place(Teacher* teacher)
        {
            switch(teacher->classnumber)
            {
                case 1:
                    classroom1.place(teacher);
                    cout << "Teacher has been placed to Classroom 1" << endl;
                    break;
                case 2:
                    classroom2.place(teacher);
                    cout << "Teacher has been placed to Classroom 2" << endl;
                    break;
                case 3:
                    classroom3.place(teacher);
                    cout << "Teacher has been placed to Classroom 3" << endl;
                    break;
                case 4:
                    classroom4.place(teacher);
                    cout << "Teacher has been placed to Classroom 4" << endl;
                    break;
                case 5:
                    classroom5.place(teacher);
                    cout << "Teacher has been placed to Classroom 5" << endl;
                    break;
                case 6:
                    classroom6.place(teacher);
                    cout << "Teacher has been placed to Classroom 6" << endl;
                    break;                             
            }
        }

        void operate()
        {
            classroom1.operate();
            classroom2.operate();
            classroom3.operate();
            classroom4.operate();
            classroom5.operate();
            classroom6.operate();
        }

        void print()
        {
            cout << endl << "       People in classroom 1 are: " << endl;
            classroom1.print();
            cout << endl << "       People in classroom 2 are: " << endl;
            classroom2.print();
            cout << endl << "       People in classroom 3 are: " << endl;
            classroom3.print();
            cout << endl << "       People in classroom 4 are: " << endl;
            classroom4.print();
            cout << endl << "       People in classroom 5 are: " << endl;
            classroom5.print();
            cout << endl << "       People in classroom 6 are: " << endl;
            classroom6.print();
        }
};



class Floor: public Area
{
    public:

        Corridor corridor;


        Floor(int c, int N): corridor(c, N)
        {
            cout <<"   New Floor have been created!" << endl;
        }

        ~Floor()
        {
            cout << "Floor to be destroyed!" << endl;
        }

        void enter(Student* student)
        {         
            isNow = student;  
            cout << isNow->name <<" enters Floor!" << endl;

            corridor.enter(isNow);
           
        }

        void exit()
        {
            cout << isNow->name <<" exits Floor!" << endl;  //de 8a xreiastei h sunartisi, tin afinw omws panta gia dinatotites mellontikis epektasis
        }


       void place(Teacher* teacher)
        {
            corridor.place(teacher);
        }

        void operate()
        {
            corridor.operate();
        }


        void print()
        {
            corridor.print();
        }
};


class Stairs: public Area
{
    public:

        Floor floor1;
        Floor floor2;
        Floor floor3; 

        Stairs(int c, int N): floor1(c, N), floor2(c, N), floor3(c, N) 
        {
            cout <<"  New Stairs have been created!" << endl;
        }

        ~Stairs()
        {
            cout << "Stairs to be destroyed!" << endl;
        }

        void enter(Student* student)
        {         
            isNow = student;  
            cout << isNow->name <<" enters Stairs!" << endl;

            this->exit();

            //3 cases(3 floors)
            switch(student->floornumber)
            {
                case 1:
                    floor1.enter(student);       //enter 1st floor
                    break;
                
                case 2:
                    floor2.enter(student);       //enter 2nd floor
                    break;

                case 3:
                    floor3.enter(student);       //enter 3rd floor
                    break;
            }
            
        }

        void exit()
        {
            cout << isNow->name <<" exits Stairs!" << endl;
        }

        void place(Teacher* teacher)
        {
            switch(teacher->floornumber)
            {
                case 1:
                    floor1.place(teacher);
                    break;

                case 2:
                    floor2.place(teacher);
                    break;

                case 3:
                    floor3.place(teacher);
                    break;        
            }
        }

        void operate()
        {
            floor1.operate();
            floor2.operate();
            floor3.operate();
        }

        void print()
        {
            cout << endl << endl << "   Floor number 1 contains: " << endl;
            floor1.print();
            cout << endl << endl << "   Floor number 2 contains: " << endl;
            floor2.print();
            cout << endl << endl << "   Floor number 3 contains: " << endl;
            floor3.print();
        }

};


class Schoolyard: public Area
{
    public:

        Stairs stairs;

        Schoolyard(int c, int N): stairs(c, N)
        {
            cout <<" A New Schoolyard has been created!" << endl;
        }

        ~Schoolyard()
        {
            cout << "A Schoolyard to be destroyed!" << endl;
        }

        void enter(Student* student)
        {         
            isNow = student;  
            cout << isNow->name <<" enters Schoolyard!" << endl;

            this->exit();
            stairs.enter(student);
        }

        void place(Teacher* teacher)
        {
            stairs.place(teacher);
        }

        void exit()
        {
            cout << isNow->name <<" exits Schoolyard!" << endl;
        }

        void operate()
        {
            stairs.operate();
        }

        void print()
        {
            stairs.print();
        }
};

class School: public Area
{
    public: 

        Schoolyard schoolyard;
        
        School(int c,int N): schoolyard(c, N)
        {
            cout <<"A New School has been created!" << endl <<endl;
        }

        ~School()
        {
            cout << "A School to be destroyed!" << endl;
        }

        void enter(Student* student)
        {         
            isNow = student;  
            cout << isNow->name <<" enters School!" << endl;
            schoolyard.enter(isNow);
        }

        void place(Teacher* teacher)
        {
            schoolyard.place(teacher);
        }

        void operate()
        {
            cout << endl << "Operation Process begins.." << endl;
            schoolyard.operate();
        }

        void print()
        {
            cout << endl << endl << "School life consists of: " << endl;
            schoolyard.print();
        }

};


int randomFloor()
{
    
    int randFloor = (rand() % 3 + 1);
    return randFloor;
}

int randomClassroom()
{
    
    int randClassroom = (rand() % 6 + 1);
    return randClassroom;
}



Student** StudentsGenerator(int Lj, int Ls)
{
    NumberOfStudents = 15; // attention, this has to be adjusted if the number of students 
    Student** arrayofStudents;
    arrayofStudents = new Student*[NumberOfStudents];
    int RandomClassroom;

    RandomClassroom = randomClassroom(); arrayofStudents[0] = new Student("Thanos", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[1] = new Student("Kostas", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[2] = new Student("Giorgos", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[3] = new Student("Katerina", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[4] = new Student("Vasilis", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[5] = new Student("Elpida", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[6] = new Student("Maria", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[7] = new Student("Despoina", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[8] = new Student("Sofia", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[9] = new Student("Nikos", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[10] = new Student("Giannis", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[11] = new Student("Petros", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[12] = new Student("Nikitas", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[13] = new Student("Georgia", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls
    RandomClassroom = randomClassroom(); arrayofStudents[14] = new Student("Athanasia", randomFloor(),RandomClassroom ,(RandomClassroom<=3) ? Lj : Ls); //random floor, random classroom, determine Lj or Ls

    std::random_shuffle(arrayofStudents, arrayofStudents + NumberOfStudents); //"anakatevw" tuxaia tous ma8ites ston pinaka prokeimenou na mpoyn tyxaia sto sxoleio

    return arrayofStudents; //me tuxaia seira
}


Teacher** TeachersGenerator(int Lt)
{
    NumberOfTeachers = 5;
    Teacher** arrayofTeachers;
    arrayofTeachers = new Teacher*[NumberOfTeachers];
    
    arrayofTeachers[0] = new Teacher("MrAthan", 1, 5, Lt);
    arrayofTeachers[1] = new Teacher("MrGeorge", 2, 6, Lt);
    arrayofTeachers[2] = new Teacher("MsAngeliki", 3, 4, Lt);
    arrayofTeachers[3] = new Teacher("MrPeter", 3 ,3, Lt);
    arrayofTeachers[4] = new Teacher("MsAndrianne", 1, 6, Lt);

    std::random_shuffle(arrayofTeachers, arrayofTeachers + NumberOfTeachers); //"anakatevw" tuxaia tous daskalous ston pinaka prokeimenou na mpoyn tyxaia sto sxoleio

    return arrayofTeachers; //me tuxaia seira
}




int main(int argc, char* argv[])
{

    int Cclass = atoi(argv[1]); //convert char numbers to int numbers
    int Lj = atoi(argv[2]);
    int Ls = atoi(argv[3]);
    int Lt = atoi(argv[4]);
    int N = atoi(argv[5]);

    Student** StudentArray;
    Teacher** TeacherArray;


    // Tasks for main (5 Tasks):
    //_____________________________________________________________________________________________________

    School sxoleio(Cclass, N);                  // 1. School Construction.

    StudentArray = StudentsGenerator(Lj, Ls);   // 2. People Generation (Students and Teachers).
    TeacherArray = TeachersGenerator(Lt);

    for(int f = 0; f < NumberOfStudents; f++)   // 3. People Enter School (Students and Teachers *randomly*).
    {
        sxoleio.enter(StudentArray[f]);    
    }

    for(int g = 0; g < NumberOfTeachers; g++) 
    {
        sxoleio.place(TeacherArray[g]);    
    }

    sxoleio.operate();                          // 4. Operates for N hours.
    sxoleio.print();                            // 5. School's Print.
    //_____________________________________________________________________________________________________


    cout << endl << endl << "Press any button and Enter in order to begin the destruction process:"; 
    getchar(); //to kanw gia pause 

    return 0; //3ekiname tin diadikasia twn destructions
}