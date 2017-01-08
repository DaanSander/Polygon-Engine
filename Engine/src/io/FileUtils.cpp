#include "FileUtils.h"

namespace engine { namespace io {

	char* readFile(char* path) {
		FILE* file = nullptr;

		fopen_s(&file, path, "rt");

		if (file == nullptr) {
			std::cout << "Error file " << path << " could not be found" << std::endl;
			system("pause");
			return nullptr;
		}

		fseek(file, 0, SEEK_END);

		unsigned int length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, length, sizeof(char), file);

		fclose(file);
		return data;
	}

}}