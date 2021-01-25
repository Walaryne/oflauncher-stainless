//
// Created by Digit on 8/10/2020.
//

#include "OFSConfig.h"

OFSConfig::OFSConfig() {
	configFilePath = getConfigFilePath();
	std::cout << "Config path dir: " << configFilePath << std::endl;
}

OFSConfig::~OFSConfig() {
}

/**
 * Loads the config file from disk
 * @return - succeeded
 */
bool OFSConfig::loadFromDisk() {
	if(!std::filesystem::exists(configFilePath)) {
		std::ofstream newFile(configFilePath);
		newFile << DEFAULT_CONFIG_TEXT;
		newFile.close();
		std::cout
			<< "Could not find existing config file, created a default one."
			<< std::endl;
	}

	std::ifstream hdl(configFilePath);
	if(!hdl.is_open()) {
		return false;
	}

	std::stringstream buffer;
	buffer << hdl.rdbuf();

	try {
		buffer >> parsedJsonDocument;
	} catch(std::exception &e) {
		hdl.close();
		std::cerr << e.what() << std::endl;
		throw std::runtime_error(
			"Failed to parse JSON config file, it may be corrupt.");
	}

	hdl.close();

	documentLoaded = true;

	return true;
}

/**
 * Saves the config file to disk
 * @return - succeeded
 */
bool OFSConfig::commitToDisk() {
	assertDocumentLoaded();

	std::ofstream hdl(configFilePath, std::ios::trunc);
	if(!hdl.is_open()) {
		return false;
	}

	hdl << parsedJsonDocument.dump();
	hdl.close();

	return false;
}

/**
 * Tests if a path exits in the current loaded JSON config object
 * @param path - path you want to test
 * @return if path exists in loaded config
 */
bool OFSConfig::exists(const char *path) {
	assertDocumentLoaded();
	auto ptr = nlohmann::json::json_pointer(path);
	return parsedJsonDocument.contains(ptr);
}

/**
 * Gets the destination path for the config file
 * @return - path of config file
 */
std::filesystem::path OFSConfig::getConfigFilePath() {


#if _MSC_VER
	char buffer[MAX_PATH];
	size_t len;
	errno_t error = getenv_s(&len, buffer, sizeof(buffer) - 1, ENV_DIR);
	if(error != 0) {
		throw std::exception("Failed to get env variable for config file path");
	}
#else
	char * buffer = getenv(ENV_DIR);
#endif

	return buffer / std::filesystem::path(CONFIG_FILE_NAME);
}

/**
 * Will throw if a file is not currently loaded
 */
void OFSConfig::assertDocumentLoaded() const {
	if(!documentLoaded) {
		throw std::runtime_error(
			"Config file operator called before the file was opened.");
	}
}

/**
 *
 * @param ptr - JSON_Pointer of the requested JSON path
 * used to fill non-existent keys with null so we don't need to
 * worry about if the key exists before insert into it.
 *
 * It's basically `mkdir -p` for the JSON object
 */
void OFSConfig::ensureJsonPtrExists(const nlohmann::json::json_pointer &ptr) {
	std::stringstream pathString(ptr);
	nlohmann::json *curr = &parsedJsonDocument;
	std::string pathSegment;
	while(std::getline(pathString, pathSegment, '/')) {
		if(pathSegment.empty()) {
			continue; // Skip empty path segments
		}
		curr = &(*curr)[pathSegment];
	}
}
