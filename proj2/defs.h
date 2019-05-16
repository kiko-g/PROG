#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

#include "Agency.h"
#include "Client.h"
#include "Date.h"
#include "Packet.h"
#include "Address.h"
using namespace std;

//DEFINITIONS AND MAIN LIB FOR HELPFUL FUNCTIONS 

#ifdef _WIN32
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif

string pathToFile = "textfiles/";
string limit = "::::::::::";
const string AGENCY_FILE_NAME = "agency.txt";
string CLIENTS_FILE_NAME;
string PacketS_FILE_NAME;

// INSIDE READ.CPP ----> READING AND ORGANIZING
vector<string> read_agency(string agency_file_str);
vector<string> read_clients(string clients_file_str);
vector<string> read_packs(string packs_file_str);
vector<Client> decompose_clients(vector<string> rawCL, string filename);
vector<Packet> decompose_packs(vector<string> rawPK, string filename);
Address string_to_address(string address_str);

/*
// CLIENT MANAGEMENT
void add_client(vector<Client> &CL);
void edit_client(vector<Client> &CL);
void remove_client(vector<Client> &CL);
void change_client_name(vector<Client> &CL);
void change_client_NIF(vector<Client> &CL);
void change_client_famagr(vector<Client> &CL);
void change_client_address(vector<Client> &CL);
void change_client_packs(vector<Client> &CL);

// Packet MANAGEMENT
void add_pack(vector<Packet> &PK);
void edit_pack(vector<Packet> &PK);
void remove_pack(vector<Packet> &PK);
void purchase_pack(vector<Client> &CL, vector<Packet> &PK);

// WRITING TO FILES
void write_clients(vector<Client> CL, string filename);
void write_packs(vector<Packet> PK, string filename);

//SEARCH or BROWSE
//CLIENTS
vector<int> searchClientName(vector<Client> CL);
int searchClientNIF(vector<Client> CL);
void printClient(vector<Client> CL, int i);
void printAllClients(vector<Client> CL);

//SEARCH or BROWSE
//PACKS
int search_pack_ID(vector<Packet> PK);
void print_all_packs(vector<Packet> PK);

//CALC
void determine_packs_money(vector<Packet> PK);
*/
// INPUT DEALING FUNCTIONS
int stoint(const string &str, int &value);
int validate_interface_input(int a, int b);
void readline(string &str);
bool cin_test();

// Other Functions
vector<string> strtok_cpp(string h, string n);
void reset_pathToFile();
int numberOf(string fileName);
int numberOfR(string fileName); //useless for now at least
