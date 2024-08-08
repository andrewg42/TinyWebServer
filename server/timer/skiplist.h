#pragma once

#include <server/std.h>

#define MAX_SKIP_LIST_DEPTH 10

struct SkipListLevel {
  SkipListLevel *m_forward;
  std::size_t m_span;
};

template <class T> struct SkipListNode {
  SkipListLevel m_level[MAX_SKIP_LIST_DEPTH];

  SkipListNode *m_backward;

  std::chrono std::function<void()> m_cb;
};