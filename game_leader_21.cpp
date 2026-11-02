#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

// MODULE 1: GAME ENTRY CLASS
class GameEntry {
private:
    string name;
    int score;

public:
    GameEntry(string n = "", int s = 0) {
        name = n;
        score = s;
    }

    string getName() {
        return name;
    }

    int getScore() {
        return score;
    }

    void display() {
        cout << name << " - " << score << endl;
    }

    bool isHigherThan(GameEntry other) {
        return score > other.score;
    }
};

// MODULE 2 AND 3: SCOREBOARD CLASS
class Scoreboard {
private:
    static const int CAPACITY = 5;
    GameEntry entries[CAPACITY];
    int count;

public:
    Scoreboard() {
        count = 0;
    }

    // Add player in descending order
    void addEntry(GameEntry newEntry) {

        if (count == CAPACITY &&
            newEntry.getScore() <= entries[count - 1].getScore()) {
            cout << "Score not high enough. Entry rejected." << endl;
            return;
        }

        int position = count;

        if (count == CAPACITY) {
            position = count - 1;
        } else {
            count++;
        }

        while (position > 0 &&
               entries[position - 1].getScore() < newEntry.getScore()) {
            entries[position] = entries[position - 1];
            position--;
        }

        entries[position] = newEntry;

        cout << "Entry added successfully." << endl;
    }

    // Remove player by rank
    void removeEntry(int rank) {

        if (rank < 1 || rank > count) {
            cout << "Invalid rank." << endl;
            return;
        }

        for (int i = rank - 1; i < count - 1; i++) {
            entries[i] = entries[i + 1];
        }

        count--;
        cout << "Entry removed successfully." << endl;
    }

    // Display leaderboard
    void displayBoard() {

        cout << "\n===== GAME LEADERBOARD =====" << endl;

        if (count == 0) {
            cout << "Leaderboard is empty." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". ";
            entries[i].display();
        }
    }

    // MODULE 5: SAVE LEADERBOARD
    void saveToFile() {

        ofstream file("leaderboard.txt");

        if (!file) {
            cout << "Unable to save file." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            file << entries[i].getName() << " "
                 << entries[i].getScore() << endl;
        }

        file.close();
        cout << "Leaderboard saved successfully." << endl;
    }

    // MODULE 5: LOAD LEADERBOARD
    void loadFromFile() {

        ifstream file("leaderboard.txt");

        if (!file) {
            cout << "File not found." << endl;
            return;
        }

        count = 0;

        string name;
        int score;

        while (file >> name >> score) {
            addEntry(GameEntry(name, score));
        }

        file.close();
        cout << "Leaderboard loaded successfully." << endl;
    }

    // MODULE 5: RANDOM SIMULATION
    void simulateScores() {

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(100, 1000);

        cout << "\n===== RANDOM SCORE SIMULATION =====" << endl;

        for (int i = 1; i <= 5; i++) {
            int score = dist(gen);
            string name = "Player" + to_string(i);

            cout << name << " scored " << score << endl;
            addEntry(GameEntry(name, score));
        }

        displayBoard();
    }
};

// MODULE 4: INSERTION SORT
void insertionSort(vector<int>& arr) {

    for (int i = 1; i < (int)arr.size(); i++) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// MODULE 4: SELECTION SORT
void selectionSort(vector<int>& arr) {

    for (int i = 0; i < (int)arr.size() - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < (int)arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

// MODULE 4: SORTING COMPARISON
void sortingComparison() {

    int sizes[] = {100, 1000, 3000};

    cout << "\n===== SORTING PERFORMANCE COMPARISON =====" << endl;

    cout << "Size\tInsertion Sort\tSelection Sort" << endl;

    random_device rd;
    mt19937 gen(rd());

    for (int size : sizes) {

        uniform_int_distribution<> dist(1, 10000);

        vector<int> original;

        for (int i = 0; i < size; i++) {
            original.push_back(dist(gen));
        }

        vector<int> arr1 = original;
        vector<int> arr2 = original;

        auto start1 = chrono::high_resolution_clock::now();
        insertionSort(arr1);
        auto end1 = chrono::high_resolution_clock::now();

        auto start2 = chrono::high_resolution_clock::now();
        selectionSort(arr2);
        auto end2 = chrono::high_resolution_clock::now();

        auto time1 =
            chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

        auto time2 =
            chrono::duration_cast<chrono::microseconds>(end2 - start2).count();

        cout << size << "\t"
             << time1 << " microseconds\t"
             << time2 << " microseconds" << endl;
    }
}

// MAIN FUNCTION
int main() {

    Scoreboard board;

    int choice;

    do {

        cout << "\n===== GAME LEADERBOARD MANAGER =====" << endl;
        cout << "1. Add Player" << endl;
        cout << "2. Remove Player" << endl;
        cout << "3. Display Leaderboard" << endl;
        cout << "4. Sorting Comparison" << endl;
        cout << "5. Save Leaderboard" << endl;
        cout << "6. Load Leaderboard" << endl;
        cout << "7. Random Score Simulation" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            string name;
            int score;

            cout << "Enter player name: ";
            cin >> name;

            cout << "Enter player score: ";
            cin >> score;

            board.addEntry(GameEntry(name, score));
            break;
        }

        case 2: {
            int rank;

            cout << "Enter rank to remove: ";
            cin >> rank;

            board.removeEntry(rank);
            break;
        }

        case 3:
            board.displayBoard();
            break;

        case 4:
            sortingComparison();
            break;

        case 5:
            board.saveToFile();
            break;

        case 6:
            board.loadFromFile();
            break;

        case 7:
            board.simulateScores();
            break;

        case 0:
            cout << "Thank you for using Game Leaderboard Manager!" << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}