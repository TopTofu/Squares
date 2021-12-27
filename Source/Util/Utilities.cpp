#include <Util/Utilities.h>


glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY) {
	float x = mouseX / WINDOW_WIDTH * 2.0f - 1.0f;
	float y = mouseY / WINDOW_HEIGHT * -2.0f + 1.0f;

	return glm::vec2(x, y);
}

glm::vec2 getPixelCoords(float normalizedX, float normalizedY) {
	float x = (normalizedX + 1.0f) * 0.5f * WINDOW_WIDTH;
	float y = (1.0f - normalizedY) * 0.5f * WINDOW_HEIGHT;

	return glm::vec2(x, y);
}

std::vector<std::string> splitAt(std::string s, const char* c) {
	std::vector<std::string> result = {};

	int size = s.size();

	for (int i = 0; i < size; i++) {
		size_t index = s.find_first_of(c);

		if (index == -1) {
			result.push_back(s);
			break;
		}

		if (index > 0)
			result.push_back(s.substr(0, index));
		s.erase(0, index + 1);
	}

	return result;
}


std::string getFileNameFromPath(std::string path) {
	return path.substr(0, path.rfind('.')).substr(path.rfind('/') + 1, path.size());
}


FileReadResult readFile(std::string path) {
	FileReadResult result{};

	result.path = path;

	std::ifstream in(path.c_str(), std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		
		result.contents = contents;
	}
	else {
		result.success = false;
	}

	return result;
}