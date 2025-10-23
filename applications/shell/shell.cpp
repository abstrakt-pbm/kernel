#include <shell/shell.hpp>
#include <terminal/terminal.hpp>

namespace SHELL {

uint32_t execute_command(char* answer, char* command, uint32_t command_size) {
	char lanswer[] = "command not found: ";
	for (size_t i = 0 ; i < sizeof(lanswer) ; ++i) {
		answer[i] = lanswer[i];
	}
	return sizeof(lanswer);
}

int main() {
	term1->out('\n');
	term1->out('\r');
	term1->out("> ",2);
	char char_input;

	char command[200];
	uint32_t command_capacity = 200;
	uint32_t command_cursor = 0;

	char answer[200];

	while(true){
		bool has_input = term1->in(&char_input);
 		if (has_input) {
			if (char_input == '\n'){
				uint32_t answer_size = execute_command(
					reinterpret_cast<char *>(&answer),
					reinterpret_cast<char *>(&command),
					command_cursor);

				term1->out('\n');
				term1->out('\r');
				term1->out("> ",2);
				term1->out(reinterpret_cast<const char *>(&answer), answer_size);
				term1->out('\n');
				term1->out('\r');
				term1->out("> ",2);
			} else if (command_cursor < command_capacity) {
				term1->out(char_input);
				command[command_cursor] = char_input;
				command_cursor++;
			}
		}
	}
	return 0;
}

} // SHELL

