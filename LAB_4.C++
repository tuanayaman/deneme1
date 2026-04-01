#include <iostream>
#include <string>

using namespace std;

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3]; // Length, Width, Height
    Package* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

class PackageStack {
private:
    Package* top;

public:
    PackageStack() : top(nullptr) {}
    ~PackageStack() {
        while (top) {
            Package* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const string& id, const string& city, int l, int w, int h) {
        Package* node = new Package{ id, city, {l, w, h}, top };
        top = node;
        cout << "Pakrt " << id << " yuklendi.\n";
    }

    bool pop(Package& out) {
        if (!top) return false;
        out = *top;
        Package* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    bool isEmpty() const { return top == nullptr; }

    void display() const {
        if (isEmpty()) {
            cout << "Yigin bos.\n";
            return;
        }
        cout << "Yigindaki paketler (ustten alta):\n";
        Package* cur = top;
        while (cur) {
            cout << "  ID=" << cur->packageID
                 << ", Hedef=" << cur->destinationCity
                 << ", Olculer=" << cur->dimensions[0] << "x" << cur->dimensions[1] << "x" << cur->dimensions[2] << "\n";
            cur = cur->next;
        }
    }
};

class CourierQueue {
private:
    static const int MAX_SIZE = 5;
    Courier data[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    CourierQueue(): front(0), rear(0), count(0) {}

    bool enqueue(const string& name, const string& vehicle) {
        if (count == MAX_SIZE) {
            cout << "Kurye kuyruğu dolu.\n";
            return false;
        }
        data[rear] = Courier{name, vehicle};
        rear = (rear + 1) % MAX_SIZE;
        count++;
        cout << "Kurye " << name << " eklendi.\n";
        return true;
    }

    bool dequeue(Courier& out) {
        if (count == 0) return false;
        out = data[front];
        front = (front + 1) % MAX_SIZE;
        count--;
        return true;
    }

    bool isEmpty() const { return count == 0; }

    void display() const {
        if (isEmpty()) {
            cout << "Kurye kuyruğu bos.\n";
            return;
        }
        cout << "Kurye kuyruğu (ondaubas):\n";
        int idx = front;
        for (int i = 0; i < count; ++i) {
            cout << "  " << (i+1) << ". " << data[idx].courierName << " (" << data[idx].vehicleType << ")\n";
            idx = (idx + 1) % MAX_SIZE;
        }
    }
};

int main() {
    PackageStack packageStack;
    CourierQueue courierQueue;

    while (true) {
        cout << "\n=== Lojistik & Kargo Dagitim Sistemi ===\n";
        cout << "1) Paket gelis (push)\n";
        cout << "2) Kurye kayit (enqueue)\n";
        cout << "3) Sevkiyat (pop + dequeue)\n";
        cout << "4) Goster\n";
        cout << "5) Cikis\n";
        cout << "Seciminiz: ";

        int secim;
        if (!(cin >> secim)) {
            cout << "Gecersiz giris.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (secim == 5) {
            cout << "Cikis yapiliyor.\n";
            break;
        }

        switch (secim) {
            case 1: {
                string id, city;
                int l, w, h;
                cout << "Paket ID: ";
                cin >> ws;
                getline(cin, id);
                cout << "Varis sehri: ";
                getline(cin, city);
                cout << "Olculeri gir (L W H): ";
                cin >> l >> w >> h;
                packageStack.push(id, city, l, w, h);
                break;
            }
            case 2: {
                string name, vehicle;
                cout << "Kurye adi: ";
                cin >> ws;
                getline(cin, name);
                cout << "Arac tipi: ";
                getline(cin, vehicle);
                courierQueue.enqueue(name, vehicle);
                break;
            }
            case 3: {
                if (packageStack.isEmpty()) {
                    cout << "Sevkiyat yok: yigin bos.\n";
                    break;
                }
                if (courierQueue.isEmpty()) {
                    cout << "Sevkiyat yok: kurye bulunamadi.\n";
                    break;
                }
                Package pkg;
                Courier c;
                packageStack.pop(pkg);
                courierQueue.dequeue(c);
                cout << "Sevk edildi: Paket " << pkg.packageID << " (" << pkg.destinationCity << ")"
                     << " - Kurye " << c.courierName << " (" << c.vehicleType << ")\n";
                break;
            }
            case 4:
                packageStack.display();
                courierQueue.display();
                break;
            default:
                cout << "Gecersiz secim.\n";
                break;
        }
    }

    return 0;
}
