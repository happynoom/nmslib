/**
 * Non-metric Space Library
 *
 * Authors: Bilegsaikhan Naidan (https://github.com/bileg), Leonid Boytsov (http://boytsov.info).
 * With contributions from Lawrence Cayton (http://lcayton.com/).
 *
 * For the complete list of contributors and further details see:
 * https://github.com/searchivarius/NonMetricSpaceLib
 *
 * Copyright (c) 2010--2013
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */

#ifndef _INVERTED_INDEX_H_
#define _INVERTED_INDEX_H_

#include <vector>
#include "index.h"
#include "permutation_utils.h"

#define METH_INVERTED_INDEX   "inverted_index"

namespace similarity {

/*
 * Giuseppe Amato and Pasquale Savino,
 * Approximate Similarity Search in Metric Spaces Using Inverted Files,
 * Infoscale (2008)
 */

typedef std::pair<IdType, IdType> IdPosPair;  // <Object,Position>
typedef std::vector<IdPosPair> PostingList;

template <typename dist_t>
class InvertedIndex : public Index<dist_t> {
 public:
  InvertedIndex(const Space<dist_t>* space,
                const ObjectVector& data,
                const size_t num_pivot,
                const size_t num_pivot_index,
                const size_t num_pivot_search,
                const double db_scan_fraction);
  ~InvertedIndex();

  const std::string ToString() const;
  void Search(RangeQuery<dist_t>* query);
  void Search(KNNQuery<dist_t>* query);

 private:
  const ObjectVector& data_;
  const size_t db_scan_;
  const int num_pivot_index_;      // ki in the original paper
  const int num_pivot_search_;     // ks in the original paper
  ObjectVector pivot_;

  std::vector<PostingList> posting_lists_;

  template <typename QueryType> void GenSearch(QueryType* query);

  // disable copy and assign
  DISABLE_COPY_AND_ASSIGN(InvertedIndex);
};

}  // namespace similarity

#endif     // _INVERTED_INDEX_H_
