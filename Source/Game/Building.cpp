#include <Game/Building.h>
#include <Engine/ModelLoader.h>

BuildingCatalogInfo BuildingCatalog;

void initBuildingCatalog(std::string catalogFilePath) {
	BuildingCatalog = {};
	FileReadResult fileResult = readFile(catalogFilePath);
	std::string contents = fileResult.contents;
	int i = 0;
	Building b;
	std::string name = "";
	while (i < contents.size()) {
		if (contents[i] == '#') {
			if (!name.empty())
				BuildingCatalog.buildings.emplace(name, b);
			b = {};
			name = "";
			i++;
			while (contents[i] != '\n') {
				if (contents[i] != ' ' && contents[i] != '\r') 
					name += contents[i];
				i++;
			}
			i++;
		}
		else if(contents[i] == '-') {
			std::string attributeName = "";
			i++;
			while (contents[i] != ':') {
				attributeName += contents[i];
				i++;
			}
			i++; // skip the ':'
			std::string value = "";
			while (contents[i] != '\n') {
				if (contents[i] != ' ' && contents[i] != '\r') 
					value += contents[i];
				i++;
			}
			i++;

			if (attributeName == "size") {
				auto dimensions = splitAt(value, "x");
				b.xSize = stoi(dimensions[0]);
				b.ySize = stoi(dimensions[1]);
			}
			else if (attributeName == "file") {
				b.model = getModelFromLoader(splitAt(value, ".")[0]);
			}
			else if (attributeName == "type") {
				printf("%", value.c_str());
				// @Todo add support for this
			}
		}
		else {
			i++;
		}
	}

	BuildingCatalog.buildings.emplace(name, b);
}

Building getBuildingFromCatalog(std::string name) {
	return BuildingCatalog.buildings[name];
}


void renderBuilding(Building& building, Camera& camera) {
	renderModel(building.model, camera);
}

