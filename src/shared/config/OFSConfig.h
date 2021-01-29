//
// Created by Digit on 8/10/2020.
//

#ifndef OFLAUNCHER_STAINLESS_OFSCONFIG_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "OFFilesystem.h"
#include "json.hpp"

#define DEFAULT_CONFIG_TEXT "{}"
#define CONFIG_FILE_NAME ".oflauncher.config"

#if WIN32
#include <windows.h>
#define ENV_DIR "appdata"
#else

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <exception>

#define ENV_DIR "HOME"
#define MAX_PATH PATH_MAX
#endif

#define OFLAUNCHER_STAINLESS_OFSCONFIG_H

/**
 * Example Usage:
 *      OFSConfig* config = new OFSConfig();
 *
 *      config->loadFromDisk();
 *
 *      config->writeValue<const char*>("/test/value/nested/string", "hello_world");
 *      config->writeValue<int>("/test/value/nested/int", 524);
 *      config->writeValue<float>("/test/value/nested/float", 5.64782f);
 *      config->writeValue<bool>("/test/value/nested/bool", true);
 *
 *      config->commitToDisk();
 *
 *      std::string outString;
 *      config->readValue<std::string>("/test/value/nested/string", outString);
 *
 *      config->exists("/i/dont/exist");
 */

class OFSConfig {
public:
	OFSConfig();
	~OFSConfig();

	bool loadFromDisk();
	bool commitToDisk();

	bool exists(const char *path);

    /**
     * Stores a value at a specified path in the JSON config object
     *
     * @tparam ValueType - Type of the value you want to write (int, float, double, string, bool)
     * @param path - Path in the config object you want to store the value at
     * @param valueToWrite - The value you want to store
     */
    template <typename ValueType>
    inline void writeValue(const char *path, const ValueType &valueToWrite) {
        assertDocumentLoaded();

        auto ptr = nlohmann::json::json_pointer(path);
        ensureJsonPtrExists(ptr);

        parsedJsonDocument.at(ptr) = valueToWrite;
	}

    /**
     * Reads a value at a specified path in the JSON config object
     *
     * @tparam ValueType - Type of the value you want to write (int, float, double, string, bool)
     * @param path - Path in the config object you want to store the value at
     * @param valueToWrite - The value you want to store
     */
    template <typename ValueType>
    inline void readValue(const char *path, ValueType &out) {
        assertDocumentLoaded();

        auto ptr = nlohmann::json::json_pointer(path);
        if (!parsedJsonDocument.contains(ptr)) {
            return;
		}

		out = parsedJsonDocument.at(ptr).get<ValueType>();
    }

private:
    bool documentLoaded = false;
    nlohmann::json parsedJsonDocument;
	fs::path configFilePath;

	void assertDocumentLoaded() const;
	void ensureJsonPtrExists(const nlohmann::json::json_pointer& ptr);
	static fs::path getConfigFilePath();
};

#endif // OFLAUNCHER_STAINLESS_OFSCONFIG_H
