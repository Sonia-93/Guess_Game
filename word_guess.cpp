#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int MAX_CHANCES = 6;

std::map<std::string, std::vector<std::string>> categories = {
    {"Animals",   {"elephant", "giraffe", "penguin", "dolphin", "cheetah", "crocodile", "butterfly", "kangaroo"}},
    {"Teams",     {"arsenal", "chelsea", "barcelona", "juventus", "liverpool", "dolphins", "lakers", "yankees"}},
    {"Districts", {"kigali", "gasabo", "kicukiro", "nyarugenge", "bugesera", "gatsibo", "kayonza", "kirehe", "ngoma", "rwamagana", "burera", "gakenke", "gicumbi", "musanze", "rulindo", "gisagara", "huye", "kamonyi", "muhanga", "nyamagabe", "nyanza", "nyaruguru", "ruhango", "karongi", "ngororero", "nyabihu", "nyamasheke", "rubavu", "rusizi", "rutsiro"}},
    {"Films",     {"inception", "titanic", "avatar", "interstellar", "gladiator", "parasite", "joker", "gravity"}},
    {"Books",     {"dracula", "hamlet", "odyssey", "frankenstein", "gatsby", "dune", "hobbit", "beloved"}},
};

std::string displayWord(const std::string& word, const std::set<char>& guessed) {
    std::string display = "";
    for (char c : word) {
        if (guessed.count(c))
            display += c;
        else
            display += '_';
        display += ' ';
    }
    return display;
}

std::string chooseCategory() {
    std::vector<std::string> names;
    for (auto& pair : categories)
        names.push_back(pair.first);

    std::cout << "\nAvailable categories:\n";
    for (int i = 0; i < (int)names.size(); i++)
        std::cout << "  " << (i + 1) << ". " << names[i] << "\n";

    int choice = 0;
    while (choice < 1 || choice > (int)names.size()) {
        std::cout << "\nChoose a category (number): ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            choice = 0;
        }
    }
    std::cin.ignore(1000, '\n');
    return names[choice - 1];
}

void playGame() {
    std::string category = chooseCategory();
    std::vector<std::string>& wordList = categories[category];
    std::string word = wordList[rand() % wordList.size()];

    std::set<char> guessed;
    int chancesLeft = MAX_CHANCES;

    std::cout << "\nCategory: " << category << "\n";
    std::cout << "The word has " << word.length() << " letters.\n";
    std::cout << "You have " << MAX_CHANCES << " chances.\n\n";

    while (chancesLeft > 0) {
        std::string display = displayWord(word, guessed);
        std::cout << "Word: " << display << "\n";

        // Print guessed letters
        std::cout << "Guessed letters: ";
        if (guessed.empty()) {
            std::cout << "None";
        } else {
            for (char c : guessed) std::cout << c << " ";
        }
        std::cout << "\nChances left: " << chancesLeft << "\n";

        // Check win
        bool won = true;
        for (char c : word)
            if (!guessed.count(c)) { won = false; break; }

        if (won) {
            std::cout << "\nYou win! The word was '" << word << "'.\n";
            return;
        }

        std::cout << "\nGuess a letter (or type 'exit' to quit): ";
        std::string input;
        std::getline(std::cin, input);

        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        // Convert to lowercase
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "exit") {
            std::cout << "Thanks for playing. Goodbye!\n";
            exit(0);
        }

        if (input.length() != 1 || !isalpha(input[0])) {
            std::cout << "Please enter a single letter.\n\n";
            continue;
        }

        char guess = input[0];

        if (guessed.count(guess)) {
            std::cout << "You already guessed '" << guess << "'. Try a different letter.\n\n";
            continue;
        }

        guessed.insert(guess);

        if (word.find(guess) != std::string::npos) {
            std::cout << "Good guess! '" << guess << "' is in the word.\n\n";
        } else {
            chancesLeft--;
            std::cout << "'" << guess << "' is not in the word. " << chancesLeft << " chance(s) left.\n\n";
        }
    }

    std::cout << "Game over! The word was '" << word << "'.\n";
}

int main() {
    srand((unsigned int)time(0));
    std::cout << "=== Word Guess Game ===\n";

    while (true) {
        playGame();

        std::cout << "\nWould you like to play again? (yes/no): ";
        std::string answer;
        std::getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer != "yes" && answer != "y") {
            std::cout << "Thanks for playing. Goodbye!\n";
            break;
        }
    }

    return 0;
}
