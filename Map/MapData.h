#pragma once

class MapData {
public:
	MapData();
	virtual ~MapData();

public:
	map<int, pair<int, UINT>> objectMap;
};