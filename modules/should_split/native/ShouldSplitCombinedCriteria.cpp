#include "unused.h" 
#include "BufferCollectionUtils.h"
#include "ShouldSplitCombinedCriteria.h"

ShouldSplitCombinedCriteria::ShouldSplitCombinedCriteria(std::vector<ShouldSplitCriteriaI*> criterias)
: mCriterias()
{
    // Create a copy of each criteria
    for (std::vector<ShouldSplitCriteriaI*>::const_iterator it = criterias.begin(); it != criterias.end(); ++it)
    {
        mCriterias.push_back( (*it)->Clone() );
    }
}

ShouldSplitCombinedCriteria::~ShouldSplitCombinedCriteria()
{
    // Free each critieria
    for (std::vector<ShouldSplitCriteriaI*>::iterator it = mCriterias.begin(); it != mCriterias.end(); ++it)
    {
        delete (*it);
    }
}

ShouldSplitCriteriaI* ShouldSplitCombinedCriteria::Clone() const
{
    ShouldSplitCriteriaI* clone = new ShouldSplitCombinedCriteria(mCriterias);
    return clone;
}

bool ShouldSplitCombinedCriteria::ShouldSplit(int depth, float impurity,
                                      int numberOfDatapoints, int leftNumberOfDataponts, int rightNumberOfDatapoints,
                                      BufferCollection& extraInfo, int nodeIndex, bool recordInfo) const
{
    bool shouldSplit = true;
    for (std::vector<ShouldSplitCriteriaI*>::const_iterator it = mCriterias.begin(); it != mCriterias.end() && shouldSplit; ++it)
    {
        shouldSplit = shouldSplit && (*it)->ShouldSplit(depth, impurity, numberOfDatapoints, leftNumberOfDataponts, rightNumberOfDatapoints, extraInfo, nodeIndex, recordInfo);
    }
    if(recordInfo)
    {
        WriteValue<int>(extraInfo, "ShouldSplit-CombinedCriteria", nodeIndex, shouldSplit ? SHOULD_SPLIT_TRUE : SHOULD_SPLIT_FALSE);
    }
    return shouldSplit;

}
