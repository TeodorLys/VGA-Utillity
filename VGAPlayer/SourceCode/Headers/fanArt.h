#pragma once
class fanArt {
private:
	float oriWidth;
	float oriHeight;
	bool doonce;
	float wantedWidth;
	float wantedHeight;
	float newWidth;
	float newHeight;
	float buffx;
	float buffy;
public:
	fanArt();
	~fanArt();
	void download();
	int Random();
	void scale();
};

