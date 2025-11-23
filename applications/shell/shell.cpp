#include <shell/shell.hpp>
#include <terminal/terminal.hpp>
#include <fs/fs.hpp>
#include <thinlibcxx/string.hpp>
#include <thinlibcxx/memory.hpp>

using namespace thinlibcxx;

namespace SHELL {

String execute_command(String raw_command) {
	String answer(" ", 1);
	answer.clear();
	Vector<String> tokens = split(raw_command,
							   '\000');

	if (tokens[0] == "ECHO") {
		if (tokens.size() == 2) {
			for (size_t i = 0 ; i < tokens[1].length() ; ++i) {
				answer.push_char(tokens[1][i]);
			}
		}
	}else if(tokens[0] == "LS") {
		for (const auto& fsnode : *root_dir) {
			term1->out("\n\r\0");
			term1->out(fsnode->name());
		}
	}else if(tokens[0] == "MKDIR") {
		if (tokens.size() == 2) {
			unique_ptr<FS::FSNode> new_dir(new FS::RamDir(move(tokens[1])));
			root_dir->mkchild(move(new_dir));
		}
	}else if(tokens[0] == "TOUCH") {
		if (tokens.size() == 2) {
			unique_ptr<FS::FSNode> new_file(new FS::RamFile(move(tokens[1]), ""));
			vfs->mkfile(tokens[1] ,move(new_file));
		} else if ((tokens.size() == 3)) {
			unique_ptr<FS::FSNode> new_file(new FS::RamFile(move(tokens[1]), move(tokens[2])));
			vfs->mkfile(tokens[1] ,move(new_file));
		}
	}else if (tokens[0] == "CAT") {
		if (tokens.size() == 2) {
			FS::RamFile* file = static_cast<FS::RamFile*>(vfs->resolve_path(tokens[1]).get());
			term1->out("\n\r\0");
			term1->out(file->payload_);
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

