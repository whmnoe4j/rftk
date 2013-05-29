#pragma once

#include <cmath>

#include "VectorBuffer.h"
#include "MatrixBuffer.h"

#include "Constants.h"

// ----------------------------------------------------------------------------
//
// Compute the expected decrease in variance
//
// ----------------------------------------------------------------------------
template <class FloatType>
class SumOfVarianceImpurity
{
public:
    FloatType Impurity(int feature, int splitpoint,
                      const Tensor3BufferTemplate<FloatType>& childCounts,
                      const Tensor3BufferTemplate<FloatType>& leftStats,
                      const Tensor3BufferTemplate<FloatType>& rightStats) const;

    typedef FloatType Float;
};

template <class FloatType>
FloatType SumOfVarianceImpurity<FloatType>::Impurity(int feature, int splitpoint,
                                                    const Tensor3BufferTemplate<FloatType>& childCounts,
                                                    const Tensor3BufferTemplate<FloatType>& leftStats,
                                                    const Tensor3BufferTemplate<FloatType>& rightStats) const
{
    const FloatType countsLeft = childCounts.Get(feature, splitpoint, LEFT_CHILD);
    const FloatType countsRight = childCounts.Get(feature, splitpoint, RIGHT_CHILD);
    const FloatType countsTotal = countsLeft+countsRight;

    FloatType startSumOfVariance = FloatType(0);
    FloatType leftSumOfVariance = FloatType(0);
    FloatType rightSumOfVariance = FloatType(0);

    const int yDim = leftStats.GetN()/2;
    for(int d=0; d<yDim; d++)
    {
        // old unstable sufficient stats 
        // const FloatType leftY = leftStats.Get(feature, splitpoint, d);
        // const FloatType leftYSquared = leftStats.Get(feature, splitpoint, d+yDim);
        // const FloatType rightY = rightStats.Get(feature, splitpoint, d);
        // const FloatType rightYSquared = rightStats.Get(feature, splitpoint, d+yDim);

        // startSumOfVariance += (leftYSquared + rightYSquared)/countsTotal -  pow((leftY + rightY) / countsTotal, 2);
        // leftSumOfVariance += (countsLeft>0.0) ? leftYSquared/countsLeft -  pow(leftY/countsLeft, 2) : 0.0;
        // rightSumOfVariance += (countsRight>0.0) ? rightYSquared/countsRight -  pow(rightY/countsRight, 2) : 0.0;

        const FloatType leftY1 = leftStats.Get(feature, splitpoint, d);
        const FloatType leftY2 = leftStats.Get(feature, splitpoint, d+yDim);
        const FloatType rightY1 = rightStats.Get(feature, splitpoint, d);
        const FloatType rightY2 = rightStats.Get(feature, splitpoint, d+yDim);

        const FloatType leftVariance = (countsLeft>0.0) ? leftY2/countsLeft : 0.0;
        const FloatType rightVariance = (countsRight>0.0) ? rightY2/countsRight : 0.0;

        const FloatType startMean = (countsLeft/countsTotal)*leftY1 + (countsRight/countsTotal)*rightY1;
        const FloatType startVariance = (countsLeft/countsTotal)*(leftVariance+leftY1*leftY1)
                                        + (countsRight/countsTotal)*(rightVariance+rightY1*rightY1)
                                        - (startMean*startMean);

        startSumOfVariance += startVariance;
        leftSumOfVariance += leftVariance;
        rightSumOfVariance += rightVariance;
    }

    const FloatType varianceGain = startSumOfVariance
                                  - ((countsLeft / countsTotal) * leftSumOfVariance)
                                  - ((countsRight / countsTotal) * rightSumOfVariance);
    return varianceGain;
}