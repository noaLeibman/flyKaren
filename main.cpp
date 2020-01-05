#include "Parser.h"

/**
 * This is the main function, it parses the list given by the lexer.
 * @return exit code 0.
 */
int main(int argc, char *argv[]){
lexer *myLexer = new lexer(argv[1]);
MapHolder *map = MapHolder::getMapHolder();
map->setTokens(myLexer->getTokens());
Parser *myParser = new Parser();
myParser->parse();
//The parsing ended, hence the threads need to stop. Sets the flag that tells the threads to end.
MapHolder::getMapHolder()->setStopProgram(true);
std::this_thread::sleep_for(std::chrono::seconds(2));
return 0;
}