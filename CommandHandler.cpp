#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

enum class Command{
    ls,
    cd,
    path,
    touch,
    mkdir,
    remove,
    show,
    write,
    clear
};

void ls(){
    for(const auto& entry : fs::directory_iterator(".")){
        cout << entry.path() << endl;
    }
}

void cd(const string& args){
    try{
        fs::current_path(args);
    } catch(const fs::filesystem_error& e){
        cerr << e.what() << endl;
    }
}

void path(){
    fs::path path = fs::current_path();
    cout << path << endl;
}

void touch(const string& args){
    try{
        fs::path filename = args;
        ofstream file(filename);
    } catch (const fs::filesystem_error& e){
        cerr << e.what() << endl;
    }
}

void mkdir(const string& args){
    try{
        fs::path dirname = args;
        fs::create_directory(dirname);
        cout << "Directory: " << args << "create" << endl; 
    } catch (const fs::filesystem_error& e){
        cerr << e.what() << endl;
    }
}

void remove(const fs::path& args){
    try{
        if(fs::exists(args)){
            if(fs::is_regular_file(args)){
                fs::remove(args);
                cout << args << " removed" << endl;
            }else if(fs::is_directory(args)){
                fs::remove_all(args);
                cout << args << " removed" << endl;
            }else{
                cerr << args << " undefind type" << endl;
            }
        } else {
            cerr << args << " not found" << endl;
        }
    } catch( const fs::filesystem_error& e){
        cerr << e.what() << endl;   
    }
}

void show(const string& args){
    ifstream file(args);
    if(!(file.is_open())){
        cerr << "cannot open this file " << args << endl;
        return;
    }

    string line;
    while(getline(file,line)){
        cout << line << endl;
    }

    file.close();
}

void write(const string& args){
    ofstream file(args,ios::app);

    if(!file.is_open()){
        cerr << "cannot open file" << endl;
    }

    string line;
    cout << "enter the text(empty line to exit):" << endl;
    while(getline(cin,line) && !line.empty()){
        file << line << endl;
    }

    file.close();
    cout << "text added"<< endl;
}

void clear(){
    system("clear");
}

int main(){
    while(true){
        cout << "> ";
        string input;
        getline(cin,input);
        
        size_t space_pos = input.find(' ');
        string command_str = input.substr(0,space_pos);
        string arg = (space_pos == string::npos) ? "" : input.substr(space_pos + 1);

        Command command;
        if(command_str == "ls"){command = Command::ls;}
        else if(command_str == "cd"){command = Command::cd;}
        else if(command_str == "path"){command = Command::path;}
        else if(command_str == "touch"){command = Command::touch;}
        else if(command_str == "mkdir"){command = Command::mkdir;}
        else if(command_str == "remove"){command = Command::remove;}
        else if(command_str == "show"){command = Command::show;}
        else if(command_str == "write"){command = Command::write;}
        else if(command_str == "clear"){command = Command::clear;}
        else if(command_str == "exit"){break;}
        else{cout << "Undefind command" << endl;}

        switch (command) {
            case Command::ls:ls();break;
            case Command::cd:cd(arg);break;
            case Command::path:path();break;
            case Command::touch:touch(arg);break;
            case Command::mkdir:mkdir(arg);break;
            case Command::remove:remove(arg);break;
            case Command::write:write(arg);break;
            case Command::show:show(arg);break;
            case Command::clear:clear();break;
            default:
                cout << "undefind" << endl;
        }
    }
    return 0;
}
