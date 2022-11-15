

#include <iostream>
using namespace std;

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From) + From + 1;
    return randNum;
}
enum enGameLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix2 = 5 };

short ReadHowManyQuestions()
{
    short Questions = 1;
    do
    {
        cout << "How Many Qeustions Do You Want To answer? ";
        cin >> Questions;
    } while (Questions <= 0);
    return Questions;
}
enGameLevel ReadGameLevel()
{
    short Number = 1;
    do
    {
        cout << "\nEnter Questions Level [1]:Easy , [2]:Mid , [3]:Hard , [4]:Mix ?";
        cin >> Number;
    } while (Number < 1 || Number>4);
    return (enGameLevel)Number;
}
enOpType ReadOpType()
{
    short Choice = 1;
    do
    {
        cout << "\nEnter Opration type [1]:Add , [2]:Sub , [3]:Mull , [4]:Div , [5]:Mix ?";
        cin >> Choice;
    } while (Choice < 1 || Choice>5);
    return (enOpType)Choice;
}
string GetOpTypeSymbol(enOpType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
        break;
    case Sub:
        return "-";
        break;
    case Mul:
        return "*";
        break;
    case Div:
        return "/";
        break;
    default:
        return "Mix";
        break;
    }
}
string GetQuestionLevelText(enGameLevel GameLevel)
{
    string arrGameLevel[4] = { "Easy","Mid","Hard","Mix" };
    return arrGameLevel[GameLevel - 1];
}
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOpType OpartionType;
    enGameLevel GameLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizz 
{
    stQuestion QuestionList[100];
    short NumberOfQeustions = 0;
    enOpType OpType;
    enGameLevel GameLevel;
    short NumberOfRightAnswer=0;
    short NumberOfWrongAnswer=0;
    bool IsPass = false;
};
int SimpleCalculator(int Number1, int Number2, enOpType OpType)
{
    switch (OpType)
    {
    case enOpType::Add:
        return Number1 + Number2;
        break;
    case enOpType::Sub:
        return Number1 - Number2;
        break;
    case enOpType::Mul:
        return Number1 * Number2;
        break;
    case enOpType::Div:
        return Number1 / Number2;
        break;
    default:
        break;
    }
}
enOpType GetRandomOpType()
{
    int Op = RandomNumber(1, 4);
    return (enOpType)Op;
}
stQuestion GenrateQuestion(enGameLevel GameLevel, enOpType OpType)
{
    stQuestion Question;
    if (GameLevel == enGameLevel::Mix)
    {
        GameLevel = (enGameLevel)RandomNumber(1, 3);
    }
    if (OpType == enOpType::Mix2)
    {
        OpType = GetRandomOpType();
    }
    Question.OpartionType = OpType;
    switch (GameLevel)
    {
    case enGameLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpartionType);
        Question.GameLevel = GameLevel;
        return Question;
    case enGameLevel::Mid:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpartionType);
        Question.GameLevel = GameLevel;
        return Question;
    case enGameLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpartionType);
        Question.GameLevel = GameLevel;
        return Question;
    }
    return Question;
}
void GenrateQuizzQeustions(stQuizz& Quizz)
{
    for (short Qeustion = 0;Qeustion < Quizz.NumberOfQeustions;Qeustion++)
    {
        Quizz.QuestionList[Qeustion] = GenrateQuestion(Quizz.GameLevel, Quizz.OpType);
    }
}
int GetAnswerFromUser()
{
    int answer = 0;
    cin >> answer;
    return answer;
}
void PrintTheQeustion(stQuizz& Quizz, short QeustionNumber)
{
    cout << "\n";
    cout << "Qeustion [" << QeustionNumber + 1 << "/" << Quizz.NumberOfQeustions << "] \n\n";
    cout << Quizz.QuestionList[QeustionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QeustionNumber].Number2 << " " << GetOpTypeSymbol(Quizz.QuestionList[QeustionNumber].OpartionType);
    cout << "\n___________" << endl;
}
void CorrectTheQeustionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :-(\n";
        cout << "The Rigth Answer is " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :-)\n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
    for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQeustions;QuestionNumber++)
    {
        PrintTheQeustion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = GetAnswerFromUser();
        CorrectTheQeustionAnswer(Quizz, QuestionNumber);
    }
    Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}
string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n_____________________________________\n\n";
    cout << "            Final Result is " << GetFinalResultsText(Quizz.IsPass);
    cout << "\n\n_____________________________________\n\n";
    cout << "Number Of Questions      : " << Quizz.NumberOfQeustions << endl;
    cout << "Questions Level          : " << GetQuestionLevelText(Quizz.GameLevel) << endl;
    cout << "OpType                   : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number Of Right Answer   : " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer   : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "_____________________________________\n\n";
}
void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQeustions = ReadHowManyQuestions();
    Quizz.GameLevel = ReadGameLevel();
    Quizz.OpType = ReadOpType();
    GenrateQuizzQeustions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResults(Quizz);
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlatAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << endl << "Do You Want To Play Again ? Y/N? ";
        cin >> PlatAgain;
    } while (PlatAgain == 'Y' || PlatAgain == 'y');
    
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();

}
