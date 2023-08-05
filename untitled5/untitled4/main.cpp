#include <iostream>
#include <fstream>
#include <string>

int main() {
    int count=0;
    std::ifstream text;
    std::string path_user;
    std::cout<<"Enter the full path to the file using a double slash"
               "(for example, C:\\\\Users\\\\words.txt)"<<std::endl;
    std::cin>>path_user;
    text.open(path_user, std::ios::binary);
    if (text.is_open()==0) {
        std::cout<<"Path no valid!";
        return 0;
    }

    if (path_user.substr(path_user.length()-3,3)=="png") {
        count++;
    }

    char png1=0;
    text.read(&png1,sizeof(png1));
    if (png1==-119){
        count++;
    }

    char png[10];
    text.read(png,sizeof(png));
    std::string sub_str=png;
    if (sub_str.substr(0,3)=="PNG") {
        count++;
    }

    if (count==3) {
        std::cout<<"PNG file selected";
    }
    else
        std::cout<<"No png file selected";

    text.close();
}
