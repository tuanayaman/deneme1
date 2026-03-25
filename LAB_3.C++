#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;
    Song* prev;
    int ratings[3];
};

Song* head = NULL;
Song* tail = NULL;
Song* current = NULL;


Song* createSong(string title, string artist, int r1, int r2, int r3){
    Song* newSong = new Song;

    newSong->title = title;
    newSong->artist = artist;

    newSong->ratings[0] = r1;
    newSong->ratings[1] = r2;
    newSong->ratings[2] = r3;

    newSong->next = NULL;
    newSong->prev = NULL;

    return newSong;
}

void addSong(string title, string artist, int r1, int r2, int r3) {
    Song* newSong = createSong(title, artist, r1, r2, r3);

    if (head == NULL) {
        head = newSong;
        tail = newSong;
        current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}

void nextSong() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
    } else {
        cout << "No next song available." << endl;
    }
}

void previousSong() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
    } else {
        cout << "No previous song available." << endl;
    }
}

void removeCurrentSong() {
    if (current == NULL) return;

    if (current == head) {
        head = current->next;
        if (head != NULL) head->prev = NULL;
    } else if (current == tail) {
        tail = current->prev;
        if (tail != NULL) tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    Song* temp = current;
    nextSong();
    delete temp;
}

void display() {
    Song* temp = head;

    while (temp != NULL) {
        if (temp == current) {
            cout << "-> ";
        } else {
            cout << "   ";
        }
        cout << temp->title << " by " << temp->artist << " [Ratings: ";
        for (int i = 0; i < 3; i++) {
            cout << temp->ratings[i];
            if (i < 2) cout << ", ";
        }
        cout << "]" << endl;
        temp = temp->next;
    }
}

int main() {
    addSong("Song A", "Artist A", 5, 4, 3);
    addSong("Song B", "Artist B", 4, 5, 4);
    addSong("Song C", "Artist C", 3, 4, 5);

    cout << "Playlist:" << endl;
    display();

    cout << "\nNext song:" << endl;
    nextSong();
    display();

    cout << "\nPrevious song:" << endl;
    previousSong();
    display();

    cout << "\nRemoving current song:" << endl;
    removeCurrentSong();
    display();

    return 0;
}

