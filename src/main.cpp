#include "Game.h"
#include "Exceptions.h"
#include <iostream>

int main() {
    try{
        Game game;
        game.run();
    }catch(const ResourceException & re ){
        std::cerr << "[ResourceException] : " << re.what() << std::endl; 
    	return EXIT_FAILURE;
    }catch(const GameException & ge){
        std::cerr << "[GameException] : " << ge.what() << std::endl; 
    	return EXIT_FAILURE;
    }catch(const std::exception & e){
        std::cerr << "[Unhandled Exception] : " << e.what() << std::endl; 
        return EXIT_FAILURE;
    }catch(...){
        std::cerr << "[Unknown Exception] Something went wrong.\n"; 
		return EXIT_FAILURE;
    }

    return 0;
}
