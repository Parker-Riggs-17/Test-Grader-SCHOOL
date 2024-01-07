/**
 *   @file: test-grader.cc
 * @author: Parker Riggs
 *   @date: 03 / 07 / 23
 *  @brief: This program takes the answers from a quiz and grades it based on the correct answers provided.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

///function prototypes
void Layout(string firstName, string lastName, string studentAnswers, string answerKey, ofstream &outStream);
double getScore(string studentAnswers, string answerKey);
char letterGrade(double score);
double classAverage();

int main(int argc, char const *argv[]) {

	// Variables
	string str;
	ifstream inStream;
	ofstream outStream;
	string firstName;
	string lastName;
	string answerKey;
	string studentAnswers;

	inStream.open("exam.txt");
	if(inStream.fail()){
		cout << "ERROR.. FAILED TO OPEN TXT FILE";
		exit(0);
	}

	outStream.open("results.txt");
	if(outStream.fail()){
		cout << "ERROR";
		exit(0);
	}

	inStream >> answerKey;

	inStream >> firstName >> lastName;
	while(!inStream.eof()){
		inStream.ignore();
		getline(inStream, studentAnswers);
		Layout(firstName, lastName, studentAnswers, answerKey, outStream);
		inStream >> firstName >> lastName;
	}


	outStream.close();
	inStream.close();
	return 0;
}

void Layout(string firstName, string lastName, string studentAnswers, string answerKey, ofstream &outStream){
	outStream << endl;
	outStream << lastName << ", " << firstName << endl;
	outStream << "------------------------------------------------------" << endl;
	outStream << "Answers, correct answer in parenthesis" << endl;
	outStream << endl;
	for (size_t i = 0; i < answerKey.length(); i++)
	{
		char sa = tolower(studentAnswers[i]);
		char ak = tolower(answerKey[i]);


		if(studentAnswers[i] == ' '){
			sa = '-';
		}

		outStream << setw(6);
		outStream << i + 1 << ": " << sa << "(" << ak << ")";

		if((i + 1) % 5 == 0){
			outStream << endl;
		}

	}
	
	outStream << endl;	
	outStream << fixed << setprecision(1);
	outStream << "Score: " << getScore(studentAnswers, answerKey) << "% " << letterGrade(getScore(studentAnswers, answerKey)) << endl;
	outStream << "------------------------------------------------------" << endl;
	outStream << endl;
	}

double getScore(string studentAnswers, string answerKey){
	int correct = 0;
	for (size_t i = 0; i < answerKey.length(); i++)
	{
		if(answerKey[i] == toupper(studentAnswers[i])){
			cout << answerKey[i] << toupper(studentAnswers[i]) << endl;
			correct++;
		}
	}
	return (correct / 15.0) * 100;
}

char letterGrade(double score){
	if(score >= 90){
		return 'A';
	}
	if(score < 90 && score >= 80){
		return 'B';
	}
	if(score < 80 && score >= 70){
		return 'C';
	}
	if(score < 70 && score >= 60){
		return 'D';
	}
	if(score < 60){
		return 'F';
	}
}