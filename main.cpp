#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

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

    void show_car(){
        cout << brand <<" "<< model <<" "<< body <<" "<< transmission <<" "<< passengers <<" "<< price << endl;
    }

    void show_cars(vector<Car> cars){
        cout<<endl<<"Available cars:"<<endl;
        for(int i=0; i<cars.size(); i++)
            cars[i].show_car();
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

    void show_client(){
        cout << surname <<" "<< name <<" "<< year <<" "<< phone <<" "<< addres <<" " << endl;
    }

    void show_clients(vector<Client> clients){
        cout<<endl<<"All clients:"<<endl;
        for(int i=0; i<clients.size(); i++)
            clients[i].show_client();
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

int main()
{
    int i=0;
    Car car;
    Client client;
    vector<Car> cars;
    vector<Client> clients;

    cars = car.read_car();
    car.show_cars(cars);

    clients = client.read_clients();
    client.show_clients(clients);

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
