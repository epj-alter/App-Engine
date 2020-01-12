#include "stdafx.h"
#include "BezierPath.h"

BezierPath::BezierPath()
{
}

BezierPath::~BezierPath()
{
}

void BezierPath::addCurve(BezierCurve curve, int samples)
{
	this->mCurves.push_back(curve);
	this->mSamples.push_back(samples);
}

void BezierPath::sample(std::vector<Vector2>* sampled_path)
{
	for (int i = 0; i < this->mCurves.size(); i++)
	{
		for (float t = 0; t <= 1.0f ; t+= (1.0f / this->mSamples[i]))
		{
			sampled_path->push_back(this->mCurves[i].calculateCurvePoint(t));
		}
	}
}
