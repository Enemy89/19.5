#include <iostream>
#include <fstream>
#include <string>

int main() {
    int score_player = 0, score_TV = 0;
    int played_questions[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int index_current_sector = 0;
    while (score_TV != 6 && score_player != 6) {
        int offset;
        std::cout << "Enter offset (offset) whirligig: +";
        std::cin >> offset;
        //определение индекса выпавшего вопроса (если волчок прошел несколько оборотов)
        while (index_current_sector > 12) {
            if (index_current_sector + offset < 13) {
                index_current_sector += offset;
            } else {
                index_current_sector = index_current_sector + offset - 13;
            }
        }
        //проверка, что вопроса ранее не было
        while (played_questions[index_current_sector] == -1) {
            if (index_current_sector < 12) {
                index_current_sector += 1;
            } else {
                index_current_sector = 0;
            }
        }

        //считывание вопроса
        std::fstream quetion;
        quetion.open("..\\que.txt");

        if (quetion.is_open() == 0) {
            std::cout << "Path no valid!";
            return 0;
        }

        std::string str;
        int count=0;
        while (count<played_questions[index_current_sector])
        {
            count++;
            std::getline(quetion, str);
        }
        std::cout << str << std::endl;

        quetion.close();

        //считывание ответа
        std::string player_answer;
        std::cin >> player_answer;

        //открытие файла ответа, сверка
        std::fstream answer;
        answer.open("..\\ans.txt");

        if (answer.is_open() == 0) {
            std::cout << "Path no valid!";
            return 0;
        }

        std::string right_answer;

        int count_a=0;
        while (count_a<played_questions[index_current_sector])
        {
            count_a++;
            std::getline(answer, right_answer);
        }

        if (right_answer == player_answer) {
            score_player += 1;
            std::cout << "Point to the player!" << std::endl;
        } else {
            score_TV += 1;
            std::cout << "Point to the viewers!" << std::endl;
        }

        //вопрос отыгран, замена на -1
        played_questions[index_current_sector] = -1;
    }
    //определение победителя
    if (score_TV == 6) {
        std::cout << "Viewers win!" << std::endl;
    } else
        std::cout << "Player win!";
}
