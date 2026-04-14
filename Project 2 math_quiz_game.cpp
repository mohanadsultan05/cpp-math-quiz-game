#include <iostream>
#include <ctime>

using namespace std;

enum enQuestionlevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationlevel { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short HowManyQuestions()
{
    short NumberOfQuestions;

    do
    {
        cout << "How many questions do you want to answer? (1 - 10): ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

int AskQuestionLevel()
{
    int level;
    cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix: ";
    cin >> level;
    return level;
}

int AskOperationType()
{
    int type;
    cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix: ";
    cin >> type;
    return type;
}

char ChooseOperationType(int OperationType)
{
    switch (OperationType)
    {
    case enOperationlevel::Add: return '+';
    case enOperationlevel::Sub: return '-';
    case enOperationlevel::Mul: return '*';
    case enOperationlevel::Div: return '/';

    case enOperationlevel::MixOp:
    {
        int RandOp = RandomNumber(1, 4);
        return ChooseOperationType(RandOp);
    }

    default:
        return '+';
    }
}

int ChooseQuestionLevel(int QuestionLevel)
{
    switch (QuestionLevel)
    {
    case enQuestionlevel::Easy:
        return RandomNumber(1, 10);

    case enQuestionlevel::Med:
        return RandomNumber(1, 50);

    case enQuestionlevel::Hard:
        return RandomNumber(1, 100);

    case enQuestionlevel::Mix:
    {
        int RandLevel = RandomNumber(1, 3);
        return ChooseQuestionLevel(RandLevel);
    }

    default:
        return RandomNumber(1, 10);
    }
}

string GetQuestionLevelName(int level)
{
    switch (level)
    {
    case Easy: return "Easy";
    case Med: return "Medium";
    case Hard: return "Hard";
    case Mix: return "Mix";
    default: return "Unknown";
    }
}

string GetOperationTypeName(int type)
{
    switch (type)
    {
    case Add: return "Addition";
    case Sub: return "Subtraction";
    case Mul: return "Multiplication";
    case Div: return "Division";
    case MixOp: return "Mix";
    default: return "Unknown";
    }
}

int Calculation(int Num1, int Num2, char Op)
{
    switch (Op)
    {
    case '+': return Num1 + Num2;
    case '-': return Num1 - Num2;
    case '*': return Num1 * Num2;
    case '/':
        if (Num2 == 0) return 0;
        return Num1 / Num2;

    default:
        return 0;
    }
}

bool CheckAnswer(int Num1, int Num2, char Op, int UserAnswer)
{
    return UserAnswer == Calculation(Num1, Num2, Op);
}

string PassOrFail(int right, int wrong)
{
    return (right >= wrong) ? "Pass" : "Fail";
}

void PrintFinalResult(string result, int questions, string level,
                      string opType, int right, int wrong)
{
    cout << "\n\n----------------------------------------\n";
    cout << "Final Result: " << result << "\n";
    cout << "----------------------------------------\n";

    cout << "Questions       : " << questions << endl;
    cout << "Level           : " << level << endl;
    cout << "Operation Type  : " << opType << endl;
    cout << "Right Answers   : " << right << endl;
    cout << "Wrong Answers   : " << wrong << endl;
}

void PrintQuestions()
{
    int userAnswer = 0;
    int correct = 0;
    int wrong = 0;

    int numberQuestions = HowManyQuestions();
    int levelChoice = AskQuestionLevel();
    int opChoice = AskOperationType();

    for (int i = 1; i <= numberQuestions; i++)
    {
        int Num1 = ChooseQuestionLevel(levelChoice);
        int Num2 = ChooseQuestionLevel(levelChoice);
        char Op = ChooseOperationType(opChoice);

        cout << "\nQuestion [" << i << "/" << numberQuestions << "]\n";
        cout << Num1 << " " << Op << " " << Num2 << " = ?\n";
        cout << "Answer: ";
        cin >> userAnswer;

        if (CheckAnswer(Num1, Num2, Op, userAnswer))
        {
            cout << "Correct!\n";
            correct++;
            system("color 2F");
        }
        else
        {
            cout << "Wrong!\n";
            cout << "Correct Answer: " << Calculation(Num1, Num2, Op) << endl;
            wrong++;
            system("color 4F");
        }

        cout << "----------------------------------\n";
    }

    string result = PassOrFail(correct, wrong);

    system((result == "Pass") ? "color 2F" : "color 4F");

    PrintFinalResult(
        result,
        numberQuestions,
        GetQuestionLevelName(levelChoice),
        GetOperationTypeName(opChoice),
        correct,
        wrong
    );
}

void Reset()
{
    system("cls");
    system("color 07");
}

void StartQuiz()
{
    char again = 'Y';

    do
    {
        Reset();
        PrintQuestions();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;

    } while (again == 'Y' || again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartQuiz();
}
