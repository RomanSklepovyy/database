#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <time.h>

using namespace std;
vector<string> split(string s, string delimiter);

//----------------------------------------------------------------

class SplitException : public exception {
public:
    SplitException(int line, string file_name) {
        this->line=line;
        this->file_name=file_name;
    }

    string what()
    {
        return "Error in "+file_name+" in line: ";
    }

    int get_line() { return line;}

private:
    int line;
    string file_name;
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

    string getBrand() const {return brand;}
    string getModel() const {return model;}
    string getBody() const {return body;}
    string getTransmission() const {return transmission;}

    int getPassengers()  {return passengers;}

    double getPrice() {return price;}

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
        cout << left << setw(2) << i+1 << ") " << left << setw(10) << brand
        <<" "<< left << setw(11) << model <<" "<< left << setw(10)<< body
        <<" "<<left << setw(7) << transmission << setw(2) << passengers
        <<" "<< price <<" " << endl;
    }

    void show_cars(vector<Car> cars){
        cout<<endl<<"Available cars:"<<endl;
        for(int i=0; i<cars.size(); i++)
            cars[i].show_car(i);
    }

    void add_car(vector<Car> *cars) {
        string s;

        cout<<endl<<"Enter new car info: "<<endl;
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
        getline(cin,s);

        ofstream out("CarSource.txt", std::ios::app);
        out << brand << ", " << model << ", " << body << ", " << transmission << ", " << passengers << ", " << price <<endl;
        out.close();

        cars->emplace_back(Car(brand, model, body, transmission, passengers, price));
        cout<<"Car added successfully!";
        cout<<endl;
    }

    vector<Car> delete_cars(vector<Car> cars){
        int id;
        string s;
        cout<<"\nEnter car's id:";
        cin>>id;
        getline(cin, s);
        if (id<=cars.size()) {
            cars.erase(cars.begin() + (id - 1));

            ofstream out("CarSource.txt");
            for (int i = 0; i < cars.size(); i++)
                out << cars[i].getBrand() << ", " << cars[i].getModel() << ", " << cars[i].getBody() << ", "<< cars[i].getTransmission() << ", "
                    << cars[i].getPassengers() << ", " << cars[i].getPrice() << endl;

            out.close();
            cout << "\nCar successfully deleted!"<<endl;
        } else cout <<"Error id!"<<endl;
        return cars;
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
                throw SplitException(i, "car file");

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
    string lastname;
    int year;
    string phone;
    string addres;
    string password;

public:

    string getSurname() {return surname;}
    string getName() {return name;}
    string getLastname() {return lastname;}
    int getYear() {return year;}
    string getPhone() {return phone;}
    string getAddres() {return addres;}
    string getPassword() {return password;}


    Client() {}

    Client(string surname, string name, string lastname, int year, string phone, string addres, string password) {
        this->surname = surname;
        this->name = name;
        this->lastname = lastname;
        this->year = year;
        this->phone = phone;
        this->addres = addres;
        this->password = password;
    }

    void show_client(int i){
        cout << left << setw(2) << i+1 << ") " << left << setw(10) << surname
        <<" "<< left << setw(9) << name <<" "<<left << setw(13) << lastname
        <<" "<< left << setw(6) << year <<" "<< setw(17) << phone
        <<" "<< left << setw(37) << addres <<" : "<< password << endl;
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
        cout<<"Lastname: ";
        cin>> lastname;
        cout<<"Year: ";
        cin>> year;
        cout<<"Phone: ";
        cin>> phone;
        cout<<"Addres: ";
        cout<<"Password: ";
        cin>> password;
        getline(cin, addres);
        getline(cin, addres);

        ofstream out("ClientSource.txt", std::ios::app);
        out << surname << ", " << name << ", " << lastname << ", " << year << ", " << phone << ", " << addres <<", " << password <<endl;
        out.close();

        clients->emplace_back(Client(surname, name, lastname, year, phone, addres, password));
        cout<<"\nClient added succesfully!";
        cout<<endl;
    }

    vector<Client> delete_client(vector<Client> clients){
        int id;
        string s;
        cout<<"\nEnter client's id:";
        cin>>id;
        getline(cin, s);
        if (id<=clients.size()) {
            clients.erase(clients.begin() + (id - 1));

            ofstream out("ClientSource.txt");
            for (int i = 0; i < clients.size(); i++)
                out << clients[i].getSurname() << ", " << clients[i].getName() << ", "<< clients[i].getLastname()
                << ", "<< clients[i].getYear() << ", "<< clients[i].getPhone() << ", "
                << clients[i].getAddres() << ", " << clients[i].getPassword() << endl;

            out.close();
            cout << "\nClient successfully deleted!"<<endl;
        } else cout <<"Error id!"<<endl;
        return clients;
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

            if(words.size()!=7)
                throw SplitException(i, "client file");

            clients.emplace_back(Client(words[0], words[1], words[2], atoi(words[3].c_str()), words[4], words[5], words[6]));
        }

        in.close();

        return clients;
    }
};
//---------------------------------------------------------------------------------------------------------------------------

class Order {
private:
    string client_surname;
    string client_name;
    string client_phone;
    string car_brand;
    string car_model;
    string time_created;
    int days;
    double pay;

public:
    string getClientSurname()  {return client_surname;}
    string getClientName()  {return client_name;}
    string getClientPhone()  {return client_phone;}
    string getCarBrand()  {return car_brand;}
    string getCarModel()  {return car_model;}
    string getTimeCreated()  {return time_created;}
    int getDays()  {return days;}
    double getPay()  {return pay;}

    Order() {};

    Order(Client client, Car car, int days) {
        client_surname = client.getSurname();
        client_name = client.getName();
        client_phone = client.getPhone();
        car_brand = car.getBrand();
        car_model = car.getModel();
        time_t t=time(NULL);
        time_created=ctime(&t);
        this->days=days;
        pay=car.getPrice()*days;
    }

    Order(string client_surname, string client_name, string client_phone,string car_brand,
            string car_model, string time_created, int days, double pay){

        this->client_surname = client_surname;
        this->client_name =  client_name;
        this->client_phone =  client_phone;
        this->car_brand =  car_brand;
        this->car_model =  car_model;
        this->time_created =  time_created;
        this->days =  days;
        this->pay =  pay;
    }

    void show_order(int i){
        cout << left << setw(2) << i+1 << ") " << left << setw(10) << client_surname
             << " " << left << setw(9) << client_name<<" " << left <<" "<< setw(17) << client_phone
             << " " << left << setw(10) << car_brand<< " " << left << setw(10) << car_model
             << time_created << " " << right << setw(4) << days << " " << right << setw(6) << pay << endl;
    }

    void show_orders(vector<Order> orders){
        cout<<endl<<"All orders:"<<endl;
        for(int i=0; i<orders.size(); i++)
            orders[i].show_order(i);
    }

    void add_order(vector<Order> *orders, vector<Car> cars, vector<Client> clients) {

        int client_id, car_id, order_days;
        string s;

        cout<<endl<<"Enter new order info:"<<endl;
        cout<<"ID of client: ";
        cin>> client_id;
        cout<<"ID of car: ";
        cin>> car_id;
        cout<<"Days: ";
        cin>> order_days;
        getline(cin, s);

        Order order(clients[client_id-1],cars[car_id-1],order_days);
        orders->emplace_back(order);
        s = order.getTimeCreated().substr(0, order.getTimeCreated().size()-1);

        ofstream out("OrderSource.txt", std::ios::app);
        out <<order.getClientSurname()<< ", " << order.getClientName()
        << ", "<< order.getClientPhone() << ", " << order.getCarBrand()
        << ", "<< order.getCarModel() << ", " << s
        <<", " << order.getDays() << ", "<< order.getPay() <<endl;
        out.close();


        cout<<"\nClient added succesfully!";
        cout<<endl;
    }

    vector<Order> delete_order(vector<Order> orders){
        int id;
        string s;
        cout<<"\nEnter order id:";
        cin>>id;
        getline(cin, s);
        if (id<=orders.size()) {
            orders.erase(orders.begin() + (id - 1));

            ofstream out("OrderSource.txt");
            for (int i = 0; i < orders.size(); i++)
                out <<orders[i].getClientSurname()<< ", " << orders[i].getClientName()
                    << ", "<< orders[i].getClientPhone() << ", " << orders[i].getCarBrand()
                    << ", "<< orders[i].getCarModel() << ", " << orders[i].getTimeCreated()
                    <<", " << orders[i].getDays() << ", "<< orders[i].getPay() <<endl;
            out.close();


            out.close();
            cout << "\nOrder successfully deleted!"<<endl;
        } else cout <<"Error id!"<<endl;
        return orders;
    }

    vector<Order> read_orders() {

        int i=0;
        string line;
        char charline[1024];
        vector<string> words;
        vector<Order> orders;

        ifstream in("OrderSource.txt");

        while (getline(in, line)) {
            i++;
            strcpy(charline, line.c_str());
            words = split(charline, ", ");

            if(words.size()!=8)
                throw SplitException(i, "order file");

            orders.emplace_back(Order(words[0], words[1], words[2], words[3], words[4], words[5], atoi(words[6].c_str()), atof(words[7].c_str())));
        }

        in.close();

        return orders;
    }
};

//---------------------------------------------------------------------------------------------------------------------------

int main() {

    Car car;
    Client client;
    Order order;
    vector<Car> cars;
    vector<Client> clients;
    vector<Order> orders;
    bool exit = false;

    enum {show_car, show_client, add_car, add_client, delete_car, delete_client,
            show_orders, make_order, delete_order, exit_program, error_input} command;


    try {
        cars = car.read_car();
        clients = client.read_clients();
        orders = order.read_orders();
    } catch (SplitException &e) {
        cout << e.what() << e.get_line() << "!" << endl;
        exit=true;
    }

    if(!exit)
        cout<<"All commands: \nshow cars, add car, delete car,"
              "\nshow clients, add client, delete client, "
              "\nshow orders, make order, delete order, exit"<<endl;

    while (!exit) {
        string input_command;
        cout<<"\nEnter your command: ";
        getline(cin, input_command);

        if (input_command=="show cars")
            command=show_car;
        else if (input_command=="show clients")
            command=show_client;
        else if (input_command=="add car")
            command=add_car;
        else if (input_command=="add client")
            command=add_client;
        else if (input_command=="delete car")
            command=delete_car;
        else if (input_command=="delete client")
            command=delete_client;
        else if (input_command=="show orders")
            command=show_orders;
        else if (input_command=="make order")
            command=make_order;
        else if (input_command=="delete order")
            command=delete_order;
        else if (input_command=="exit")
            command=exit_program;
        else command=error_input;

        switch (command) {
            case show_car :
                car.show_cars(cars);
                break;
            case show_client:
                client.show_clients(clients);
                break;
            case add_car:
                car.add_car(&cars);
                break;
            case add_client:
                client.add_client(&clients);
                break;
            case delete_car:
                cars=car.delete_cars(cars);
                break;
            case delete_client:
                clients = client.delete_client(clients);
                break;
            case show_orders:
                order.show_orders(orders);
                break;
            case make_order:
                order.add_order(&orders, cars, clients);
                break;
            case delete_order:
                orders=order.delete_order(orders);
                break;
            case exit_program:
                exit=true;
                break;
            default:
                cout<<"\nPlease enter your command again!\n";
                break;
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
