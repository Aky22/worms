#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>


enum FieldType {AIR, EARTH, WATER, WORM};

class Worm {
	private:
		enum direction {LEFT, RIGHT};


};

class Field {

	private:
		FieldType type_;

	public:
		Field(FieldType type) {
			this->type_ = type;
		}

		char getCharacter() {
			switch(this->type_) {
				case AIR: return ' '; break;
				case EARTH: return 'E'; break;
				case WATER: return 'W'; break;
				case WORM: return '~'; break;
				default: break;
			}
		}

		FieldType getType() {
			return this->type_;
		}

		void setType(FieldType type) {
			this->type_ = type;
		}
};

class Game {

	private:
		int board_width_;
		int board_height_;
		std::vector<std::vector<Field>> map_;

	public:
		Game() {
			this->board_width_ = 0;
			this->board_height_ = 0;
		}

		int loadConfig(std::string cfg_file) {
			std::string line;
			std::ifstream myfile (cfg_file);
			if (myfile.is_open())
			{
			  	int pos = 0;
			  	bool hassize = false;
			  	bool ismap = false;
			    while ( getline (myfile,line) )
			    {
			    	if(pos == 0) {
			    		if(line == "#SWORMS") {
			    			pos++;
			    			continue;
			    		}else {
			    			throw std::invalid_argument("Invalid syntax!");
			    		}
			    	}
				    if(line[0] != '#'){
				    	if(!ismap) {
					    	if(line.find("SIZE:") == 0) {
					    		hassize = true;
					    		std::istringstream iss(line);
								std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
								this->board_width_ = std::stoi(results[1]);
								this->board_height_ = std::stoi(results[2]);
					    	}
					    	if(line.find("MAP:") == 0) {
					    		ismap = true;
					    	}
					    }else {
					    	if(line.size() == this->board_width_) {
					    		std::vector<Field> mapline;
					    		for(char c : line) {
					    			switch(c) {
					    				case 'A': mapline.push_back(Field(AIR)); break;
					    				case 'E': mapline.push_back(Field(EARTH)); break;
					    				case 'W': mapline.push_back(Field(WATER)); break;
					    				default: std::cout << "Error"; return -1; break;
					    			}
					    		}
					    		this->map_.push_back(mapline);
					    	}else{
					    		std::cout << "Error";
					    	}
					    }
				    }
			    }
			    myfile.close();
			    if(this->map_.size() != this->board_height_) {
			    	std::cout << "error";
			    	return -1;
			    }
			}
			return 0;
		}

		int addWorm(int row, int col) {
			if(this->map_[row][col].getType() != AIR) {
				return -2;
			}else {
				this->map_[row][col].setType(WORM);
				if(canFall(row, col)) {
					std::cout << "Implement fall!";
				}

				if(this->map_[row + 1][col].getType() == WATER) {
					this->map_[row][col].setType(AIR);
				}

			}
		}

		bool canFall(int row, int col) {
			if(row == this->map_.size() || this->map_[row+1][col].getType() != AIR) {
				return false;
			}
			return canFall(row+1, col);
		}

		void printMap() {
			std::cout << "Current Map:" << std::endl;
			int j = 0;
			std::cout << std::setw(3);
			for(int i = 0; i < this->board_width_; i++) {
				if (j == 10) j = 0;
				std::cout << j;
				j++;
			}
			std::cout << std::endl;
			int k = 0;
			for(auto it = this->map_.begin(); it < this->map_.end(); it++) {
				auto field = *it;
				if(k < 10) {
					std::cout << " " << k << " ";
				}else {
					std::cout << k;
				}
				for(Field c : field) {
					std::cout << c.getCharacter(); 
				}
				if(k < 10){
					std::cout << k << std::endl;
				}else {
					std::cout << k << " " << std::endl;
				}
				k++;
			}
			j = 0;
			std::cout << std::setw(3);
			for(int i = 0; i < this->board_width_; i++) {
				if (j == 10) j = 0;
				std::cout << j;
				j++;
			}
			std::cout << std::endl;
		}

};

int main() {

	Game game;

	game.loadConfig("config.txt");
	game.printMap();
	return 0;

}