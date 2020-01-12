#ifndef BEZIERPATH_H
#define BEZIERPATH_H

using namespace Engine;

class BezierPath
{
private:

	std::vector<BezierCurve> mCurves;
	std::vector<int> mSamples;

public:

	BezierPath();
	~BezierPath();

	void addCurve(BezierCurve curve, int samples);
	void sample(std::vector<Vector2>* sampled_path);

};

#endif