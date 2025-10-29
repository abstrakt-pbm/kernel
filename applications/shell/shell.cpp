#include <shell/shell.hpp>
#include <terminal/terminal.hpp>
#include <thinlibcxx/string.hpp>

using namespace thinlibcxx;

namespace SHELL {

uint32_t execute_command(char* answer, char* command, uint32_t command_size) {
	char lanswer[] = "command not found: ";
	for (size_t i = 0 ; i < sizeof(lanswer) ; ++i) {
		answer[i] = lanswer[i];
	}
	return sizeof(lanswer);
}

String execute_command(String raw_command) {
	String answer(" ", 1);
	answer.clear();
	Vector<String> tokens = split(raw_command,
							   '\000');

	if (tokens[0] == "ECHO") {
		for (size_t i = 0 ; i < tokens[1].length() ; ++i) {
			answer.push_char(tokens[1][i]);
		}
	} else {
		String command_not_found("command not found: ");
		for (size_t i = 0 ; i < command_not_found.length() ; ++i) {
			answer.push_char(command_not_found[i]);
		}

		for (size_t i = 0 ; i < raw_command.length() ; ++i) {
			answer.push_char(raw_command[i]);
		}
	}
	return answer;
}

int main() {
	term1->out('\n');
	term1->out('\r');
	term1->out("> ",2);
	char char_input;
	String command(" ",1);
	command.clear();

	while(true){
		bool has_input = term1->in(&char_input);
 		if (has_input) {
			if (char_input == '\n'){
				String ans = execute_command(command);
				term1->out('\n');
				term1->out('\r');
				term1->out("> ",2);
				term1->out(ans.data(), ans.length());
				term1->out('\n');
				term1->out('\r');
				term1->out("> ",2);
				command.clear();
			} else {
				term1->out(char_input);
				command.push_char(char_input);
			}
		}
	}
	return 0;
}

} // SHELL

