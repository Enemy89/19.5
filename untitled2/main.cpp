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

        std::cout << std::endl;
        for (int i = 0; i < 13; ++i) {
            std::cout << played_questions[i] << " ";
        }

        //считывание вопроса
        std::fstream quetion;
        std::string number_question = std::to_string(played_questions[index_current_sector]);
        number_question += ".txt";
        quetion.open("C:\\Users\\Rhan\\CLionProjects\\untitled2\\questions\\" + number_question);

        if (quetion.is_open() == 0) {
            std::cout << "Path no valid!";
            return 0;
        }

        std::string str, strh;
        while (!quetion.eof()) {
            getline(quetion, strh);
            str += strh;
            if (!quetion.eof()) {
                str += '\n';
            }
        }
        std::cout << str << std::endl;

        quetion.close();

        //считывание ответа
        std::string player_answer;
        std::cin >> player_answer;

        //открытие файла ответа, сверка
        std::fstream answer;
        answer.open("C:\\Users\\Rhan\\CLionProjects\\untitled2\\answers\\" + number_question);

        if (answer.is_open() == 0) {
            std::cout << "Path no valid!";
            return 0;
        }

        std::string right_answer;
        answer >> right_answer;

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
