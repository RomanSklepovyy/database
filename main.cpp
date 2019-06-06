#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;
vector<string> split(string s, string delimiter);
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
        cout << left << setw(2) << i+1 << ") " << left << setw(12) << brand <<" "<< left << setw(10) << model <<" "<< left << setw(10)<< body <<" "<< setw(4) << passengers <<" "<< price <<" " << endl;
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

        int i;
        string line;
        char charline[1024];
        vector<string> words;
        vector<Car> cars;

        ifstream in("CarSource.txt");

        while (getline(in, line)) {
            strcpy(charline, line.c_str());
            words = split(charline, ", ");
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
        cout << left << setw(2) << i+1 << ") " << left << setw(12) << surname <<" "<< left << setw(10) << name <<" "<<setw(8) << year <<" "<< setw(14) << phone <<" "<< addres <<" " << endl;
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

        int i;
        string line;
        char charline[1024];
        vector<string> words;
        vector<Client> clients;

        ifstream in("ClientSource.txt");

        while (getline(in, line)) {
            strcpy(charline, line.c_str());
            words = split(charline, ", ");
            clients.emplace_back(Client(words[0], words[1], atoi(words[2].c_str()), words[3], words[4]));
        }

        in.close();

        return clients;
    }
};

//---------------------------------------------------------------------------------------------------------------------------

class CarReadException : public exception {
public:
    CarReadException(char *msg, int n) : exception(msg)
    {


    }
private:
    int n;
};

//---------------------------------------------------------------------------------------------------------------------------

int main() {

    Car car;
    Client client;
    vector<Car> cars;
    vector<Client> clients;

    cars = car.read_car();
    car.show_cars(cars);
    clients = client.read_clients();
    client.show_clients(clients);

   // car.add_car(&cars);
    //client.add_client(&clients);

    //car.show_cars(cars);
   // client.show_clients(clients);


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
