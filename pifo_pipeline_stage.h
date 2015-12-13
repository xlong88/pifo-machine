#ifndef PIFO_PIPELINE_STAGE_H_
#define PIFO_PIPELINE_STAGE_H_

#include <cstdint>

/// PIFOPipelineStage models a stage of PIFOs
/// ---each of which can be a priority queue or a
/// calendar queue. The constraint is that on any
/// tick you can do at most one enqueue or one dequeue
/// to the PIFOPipelineStage using the enq and deq methods.
/// These enq and deq methods can be external or from
/// previous or succeeding PIFOPipelineStages.
/// This mechanism of muxing the various sources into a port for each PIFOPipelineStage is the interconnect.
/// The configuration of these muxes is handled by the compiler based on
/// the graphviz dot file input describing the scheduling hierarchy.
class PIFOPipelineStage {
 public:
  /// Enqueue
  /// These happen externally from the ingress pipeline
  /// or from a push from a calendar queue/
  void enq(const uint32_t & queue_id, const ElementType & element, const PriorityType & prio, const uint32_t & tick);

  /// Dequeues
  /// Happen implicitly starting from the root PIFO
  Optional<ElementType> deq(const uint32_t & queue_id, const uint32_t & tick);

 private:
  /// Bank of priority queues
  std::vector<PriorityQueue> priority_queue_bank_ = {};

  /// Bank of calendar queues
  std::vector<CalendarQueue> calendar_queue_bank_ = {};
};

#endif  // PIFO_PIPELINE_STAGE_H_
