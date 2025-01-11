#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept> // For exceptions
#include "exprtk.hpp" // exprtk header easier to code the operations with this library extension

using namespace std;

// Function to display the help menu. Do not want to copy and paste the same thing in if else statements :v
void displayHelpMenu() {
    cout << "_______________________________________________________________________\n"
         << "If you're not sure what to type, here are the Unit Conversions for time:\n" 
         << "*Can only be typed in float numbers and will be rounded as a whole number at the end.*\n"
         << "1 second\n" 
         << "1 minute = 60 seconds\n" 
         << "1 hour = 60 minutes\n" 
         << "1 day = 24 hours\n" 
         << "1 week = 7 days\n" 
         << "1 month = 4.35 weeks (average)\n" 
         << "1 year = 12 months.\n"
         << "EX: How many minutes: \n60 \nYour values will convert it to an hour. Same goes for other units." 
         << "\n==============================Operatorions==============================\n"
         << "You can also use/combine any operator in your input but here are some recommendations"
         << "\n+, -, *, /, and ()\n"
         << "EX: How many hours: \n6*2 or (6+2)/4" 
         << "\nYour math expressions will calculate your values at the end, etc.\n\n";
}

// Function to evaluate mathematical expressions using exprtk
double evaluateExpression(const string& expression) {
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_t expr;
    parser_t parser;

    if (!parser.compile(expression, expr)) {
        throw invalid_argument("Invalid expression");
    }

    return expr.value();
}

// Input function that validates the user input for each unit
double getTimeUnitInput(const string& unit) {
    string input;
    double value = 0;
    
    while (true) {
        //this is a game changer!! before it use to be 200+ lines of code
        //Thank you mr.whileloop for making if else statements less redundant. 
        cout << "How many " << unit << ": \n";
        getline(cin, input);

        if (input.empty()) {
            return 0; // Default value if the user skipped input
        } else if (input == "help") {
            displayHelpMenu();
        } else {
            try {
                value = evaluateExpression(input); // Validate and calculate the expression
                return round(value); // Round the result to the nearest whole number
            } catch (const invalid_argument& e) {
                cout << "Invalid input. Please try again.\n";
            }
        }
    }
}

int main() {
    double seconds, minutes, hours, days, weeks, months, years;

    // Display the prompt message once at the beginning
    cout << "\n\n[Enter] to skip, type help, or [Ctrl] + [C] to exit" << endl;

    // Continuous loop for user input and results
    while (true) {
        // Get all time units from the user
        seconds = getTimeUnitInput("seconds");
        minutes = getTimeUnitInput("minutes");
        hours = getTimeUnitInput("hours");
        days = getTimeUnitInput("days");
        weeks = getTimeUnitInput("weeks");
        months = getTimeUnitInput("months");
        years = getTimeUnitInput("years");

        // Ready for some if else galore? :P
        if (seconds >= 60) {
            minutes += static_cast<int>(seconds) / 60; // Add the extra minutes
            seconds = static_cast<int>(seconds) % 60; // Keep only the remaining seconds
        } else if (seconds >= 3600){
            hours += static_cast<int>(seconds) / 3600;
            seconds = static_cast<int>(seconds) % 3600;
        } else if (seconds >= 86400){
            days += static_cast<int>(seconds) / 86400 ;
            seconds = static_cast<int>(seconds) % 86400;
        } else if (seconds >= 604800){
            weeks += static_cast<int>(seconds) / 604800;
            seconds = static_cast<int>(seconds) % 604800;
        } else if (seconds >= 2629744){
            months += static_cast<int>(seconds) / 2629744;
            seconds = static_cast<int>(seconds) % 2629744;
        } else if (seconds >= 31557600){
            years += static_cast<int>(seconds) / 31557600 ;
            seconds = static_cast<int>(seconds) % 31557600;
        }

        if (minutes >= 60) {
            hours += static_cast<int>(minutes) / 60;
            minutes = static_cast<int>(minutes) % 60;
        } else if (minutes >= 1440){
            days += static_cast<int>(minutes) / 1440;
            minutes = static_cast<int>(minutes) % 1440;
        } else if (minutes >= 10080){
            weeks += static_cast<int>(minutes) / 10080;
            minutes = static_cast<int>(minutes) % 10080;
        } else if (minutes >= 43829.6){
            months += static_cast<int>(round(minutes / 43829.6)); //had to round them because some months have inconsistent days
            minutes = fmod(minutes, 43829.6);
        } else if (minutes >= 525600){
            years += static_cast<int>(minutes) / 525600;
            minutes = static_cast<int>(minutes) % 525600;
        }

        if (hours >= 24) {
            days += static_cast<int>(hours) / 24;
            hours = static_cast<int>(hours) % 24;
        } else if (hours >= 168){
            weeks += static_cast<int>(hours) / 168;
            hours = static_cast<int>(hours) % 168;
        } else if (hours >= 730.56){
            months += static_cast<int>(round(hours / 730.56));
            hours = fmod(hours, 730.56);
        } else if (hours >= 8766){
            years += static_cast<int>(hours) / 8766;
            hours = static_cast <int>(hours)% 8766;
        }

        if (days >= 7) {
            weeks += static_cast<int>(days) / 7;
            days = static_cast<int>(days) % 7;
        } else if (days >= 30.44){
            months += static_cast<int>(round(days / 30.44));
            days = fmod(days, 30.44);
        } else if (days >= 365.25){
            years += static_cast<int>(round(days / 365));
            days = fmod(days, 365.25);
        }

        if (weeks >= 4.35) {
            months += static_cast<int>(round(weeks / 4.35));  // Round to the nearest month
            weeks = fmod(weeks, 4.35);
        } else if (weeks >= 52.18){
            years += static_cast<int>(round(weeks / 52.18));
            weeks = fmod(weeks, 52.18);
        }

        if (months >= 12) {
            years += static_cast<int>(months) / 12;
            months = static_cast<int>(months) % 12;
        }

        // Displaying results
        cout << "\n|years: " << years
             << ", months: " << months
             << ", weeks: " << weeks
             << ", days: " << days
             << ", hours: " << hours
             << ", minutes: " << minutes
             << ", seconds: " << seconds
             << "|";

        // Ask the user if they want to continue or exit
        cout << "\n\n[Enter] to skip, type help, or [Ctrl] + [C] to exit" << endl;
    }

    return 0;
}
