#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;
vector<string> split(string s, string delimiter);

//----------------------------------------------------------------

class SplitException : public exception {
public:
    SplitException(int line) {
        this->line=line;
    }

    virtual const char* what() const throw()
    {
        return "\nError in file line ";
    }

    int get_line() { return line;}

private:
    int line;
};

//----------------------------------------------------------------

class Car {
private:
    string brand;
    string model;
    string body;
    string transmission;
    int passengers;
    double price;
public:
    Car() {}

    Car(string brand, string model, string body, string transmission, int passengers, double price) {
        this->brand = brand;
        this->model = model;
        this->body = body;
        this->transmission = transmission;
        this->passengers = passengers;
        this->price = price;
    }

    void show_car(int i){
        cout << left << setw(2) << i+1 << ") " << left << setw(10) << brand <<" "<< left << setw(7) << model <<" "<< left << setw(10)<< body <<" "<< setw(2) << passengers <<" "<< price <<" " << endl;
    }

    void show_cars(vector<Car> cars){
        cout<<endl<<"Available cars:"<<endl;
        for(int i=0; i<cars.size(); i++)
            cars[i].show_car(i);
    }

    void add_car(vector<Car> *cars) {
        cout<<endl<<"Enter new car info:"<<endl;
        cout<<"Brand: ";
        cin>> brand;
        cout<<"Model: ";
        cin>> model;
        cout<<"Body: ";
        cin>> body;
        cout<<"Transmission: ";
        cin>> transmission;
        cout<<"Passengers: ";
        cin>> passengers;
        cout<<"Price: ";
        cin>>price;

        ofstream out("CarSource.txt", std::ios::app);
        out << brand << ", " << model << ", " << body << ", " << transmission << ", " << passengers << ", " << price <<endl;
        out.close();

        cars->emplace_back(Car(brand, model, body, transmission, passengers, price));
    }

    vector<Car> read_car() {

        int i=0;
        string line;
        char charline[1024];
        vector<string> words;
        vector<Car> cars;

        ifstream in("CarSource.txt");

        while (getline(in, line)) {
            i++;
            strcpy(charline, line.c_str());
            words = split(charline, ", ");

            if(words.size()!=6)
                throw SplitException(i);

            cars.push_back(Car(words[0], words[1], words[2], words[3], atoi(words[4].c_str()), atof(words[5].c_str())));
        }

        in.close();

        return cars;
    }
};

//--------------------------------------------------------------------------------------------------------------------------

class Client {
private:
    string surname;
    string name;
    int year;
    string phone;
    string addres;
public:
    Client() {}

    Client(string surname, string name, int year, string phone, string addres) {
        this->surname = surname;
        this->name = name;
        this->year = year;
        this->phone = phone;
        this->addres = addres;
    }

    void show_client(int i){
        cout << left << setw(2) << i+1 << ") " << left << setw(10) << surname <<" "<< left << setw(7) << name <<" "<< year <<" "<< setw(11) << phone <<" "<< addres <<" " << endl;
    }

    void show_clients(vector<Client> clients){
        cout<<endl<<"All clients:"<<endl;
        for(int i=0; i<clients.size(); i++)
            clients[i].show_client(i);
    }

    void add_client(vector<Client> *clients) {
        cout<<endl<<"Enter new client's info:"<<endl;
        cout<<"Surname: ";
        cin>> surname;
        cout<<"Name: ";
        cin>> name;
        cout<<"Year: ";
        cin>> year;
        cout<<"Phone: ";
        cin>> phone;
        cout<<"Addres: ";
        cin>> addres;

        ofstream out("ClientSource.txt", std::ios::app);
        out << surname << ", " << name << ", " << year << ", " << phone << ", " << addres<<endl;
        out.close();

        clients->emplace_back(Client(surname, name, year, phone, addres));
    }

    vector<Client> read_clients() {

        int i=0;
        string line;
        char charline[1024];
        vector<string> words;
        vector<Client> clients;

        ifstream in("ClientSource.txt");

        while (getline(in, line)) {
            i++;
            strcpy(charline, line.c_str());
            words = split(charline, ", ");

            if(words.size()!=5)
                throw SplitException(i);

            clients.emplace_back(Client(words[0], words[1], atoi(words[2].c_str()), words[3], words[4]));
        }

        in.close();

        return clients;
    }
};

//---------------------------------------------------------------------------------------------------------------------------

int main() {

    Car car;
    Client client;
    vector<Car> cars;
    vector<Client> clients;
    bool exit = false;

    //enum {show_car, show_client, add_car, add_client, delete_car, delete_client} comamd;

    while (!exit) {
        try {
            cars = car.read_car();
        } catch (SplitException &e) {
            cout << e.what() << e.get_line() << "!" << endl;
        }

        try {
            clients = client.read_clients();
        } catch (SplitException &e) {
            cout << e.what() << e.get_line() << "!" << endl;
        }
    }
    return 0;
}







vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
