#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>


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
		string map_ [][];

	public:
		Game() {
			this->board_width_ = 0;
			this->board_height_ = 0;
			this->map_ = {this->board_width_, this->board_height_};
		}

		int loadConfig(std::string cfg_file) {
			std::string line;
			std::ifstream myfile (cfg_file);
			if (myfile.is_open())
			{
			  	int pos = 0;
			  	bool hassize = false;
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
				    	if(line.find("SIZE:") == 0) {
				    		hassize = true;
				    		std::istringstream iss(line);
							std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
							this->board_width_ = std::stoi(results[1]);
							this->board_height_ = std::stoi(results[2]);
				    	}
				    }
			    }
			    myfile.close();
			}
			return 0;
		}
};

int main() {

	Game game;

	game.loadConfig("config.txt");
	return 0;

}