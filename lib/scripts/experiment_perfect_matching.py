import collections
import itertools
import sys


class LeftVertex:
  """A vertex on the left side of the graph"""

  def __init__(self, name):
    """
    Construct a left vertex with the given name, no parent, and potential 0.
    :param name: the name of the vertex
    """
    self.name = name
    self.parent = None
    self.potential = 0

  def reset(self):
    """Resets a left vertex, which amounts to making sure it has no parent."""
    self.parent = None

  @property
  def is_explored(self):
    """
    Has the vertex been explored in the current phase?  This is true if and only if the vertex has a parent.
    :return: True if the vertex has been explored
    """
    return bool(self.parent)


class RightVertex(LeftVertex):
  """
  A vertex on the right side of the graph.  Such a vertex stores all the information a left vertex stores plus
  a pointer to its matching partner on the left side (or None) and a slack value (initially 0), which is the minimum
  slack among all edges between this vertex and explored vertices on the left side.
  """

  def __init__(self, name):
    """
    Construct a right vertex with the given name, potential 0, no parent, no matching partner, and slack 0.
    :param name: the name of the vertex.
    """
    super().__init__(name)
    self.match = None
    self.slack = 0

  @property
  def is_matched(self):
    """
    Is this vertex matched?
    :return: True if the vertex is matched.
    """
    return bool(self.match)

  def reset(self):
    """Resets this vertex, which amounts to removing its parent and setting its slack to infinity."""
    super().reset()
    self.slack = sys.float_info.max
    self.potential_parent = None


class HungarianAlgorithm:
  """
  Implementation of the Hungarian algorithm wrapped in a class so we can break it into small methods that share
  the necessary state.
  """

  def __init__(self, matrix):
    """
    Constructs an instance of this algorithm from a given matrix of edge weights
    :param matrix: the edge weight matrix
    """
    n = len(matrix)
    self.left = [LeftVertex(i) for i in range(n)]
    self.right = [RightVertex(i) for i in range(n)]
    self.queue = collections.deque()
    self.matrix = matrix

  def solve(self):
    """
    Computes a minimum-weight perfect matching for this graph.
    :return: the matching in the form of a list of pairs of matched vertices
    """

    # Each iteration starts from the next vertex on the left and searches for an augmenting path starting at this
    # vertex.  It then augments the matching using this augmenting path.
    for u in self.left:
      print("solving: ", u.name)
      path = self.find_augmenting_path_from(u)
      self.augment_matching(path)

    # All vertices are matched.  Construct the matching.
    return [(v.match.name, v.name) for v in self.right]

  def find_augmenting_path_from(self, u):
    print("finding augmenting path from.")
    """
    Computes an augmenting path from u to some vertex on the right side consisting of only tight edges, possibly
    after adjusting the vertex potentials to create more tight edges.
    :param u: the start vertex of the search
    :return: an iterator over the constructed path from the tail back to u
    """

    # Reset the queue, parents, and slack values.
    self.start_phase(u)

    # Loop forever until an augmenting path is found and we break out of the loop by returning from this method.
    while True:

      # Try to find an augmenting path by exploring tight edges.
      tail = self.explore_tight_edges()

      # If no augmenting path is found, adjust vertex potentials to create more tight edges.  In the process,
      # we may find an augmenting path.
      if not tail:
        tail = self.adjust_potentials()

      # If we found an augmenting path either while exploring tight edges or while adjusting vertex potentials,
      # return an iterator over the path.
      if tail:
        return self.path_generator(tail)

  def start_phase(self, u):
    print("starting phase")
    """
    Initialize the current phase.  No vertex except u has a parent.  u is its own parent, to recognize it as
    the root, and the queue contains u.  All right vertices have infinite slack for now.
    :param u: the start vertex of the current phase
    """
    for v in itertools.chain(self.left, self.right):
      v.reset()
    u.parent = u
    self.queue.clear()
    self.queue.append(u)

  def explore_tight_edges(self):
    # print("explore tight edges")
    """
    Explore tight edges to discover so far unexplored vertices starting from vertices in the queue.
    :return: the tail of an augmenting path if such a path is found, None otherwise
    """

    # Loop while the queue isn't empty
    while self.queue:

      # Get the next vertex and explore tight edges from this vertex
      u = self.queue.pop()
      tail = self.explore_tight_edges_from(u)

      # If this produced an augmenting path, return its tail
      if tail:
        return tail

    # Exhausted the queue without finding an augmenting path.  Return None to force a potential update.
    return None

  def explore_tight_edges_from(self, u):
    print("explore tight edges from Vertex =", u.name)
    """
    Explore tight edges from the given vertex
    :param u: the vertex whose incident edges are to be explored
    :return: the tail of an augmenting path if one is found.  None otherwise.
    """

    # Iterate over all unexplored right vertices
    for v in self.right:
      if u.name == 6:
        print("fuck")
      if not v.is_explored:
        # Compute the slack of the edge between u and v.
        uv_slack = self.slack(u, v)

        if uv_slack == 0:
          # If the slack is 0, the edge is tight.  We follow it, make u the parent of v and do extra work
          # to explore v depending on whether it is matched or not.
          v.parent = u
          tail = self.explore_right_vertex(v)

          # If v is not matched, self.explore_right_vertex(v) returns v as the tail of an augmenting path
          # and we can terminate the search.
          if tail:
            return tail
        else:
          # If the slack is positive, then we cannot explore v yet, but we need to update its slack because
          # u is an explored in-neighbour of v.
          if uv_slack < v.slack:
            v.slack = uv_slack
            v.potential_parent = u

    # No unexplored, unmatched neighbour of u found that is connected to u via a tight edge.  Thus, we didn't
    # find an augmenting path.
    return None

  def adjust_potentials(self):
    """
    Adjust vertex potentials to create at least one new tight edge while ensuring we still have a valid
    potential function.
    :return: The tail of an augmenting path if we find one in the process.  None otherwise.
    """

    # Find the minimum slack of all unexplored vertices on the right
    min_slack = sys.float_info.max
    for v in self.right:
      if not v.is_explored:
        min_slack = min(min_slack, v.slack)

    # Increase the potential of every explored vertex on the left by the minimum slack
    for u in self.left:
      if u.is_explored:
        u.potential += min_slack

    tail = None

    # Decrease the potential or slack of every vertex on the right by the minimum slack, depending on whether
    # the vertex is explored or not.
    for v in self.right:

      if v.is_explored:
        # Explored vertices decrease their potential
        v.potential -= min_slack
      else:
        # Unexplored vertices decrease their slack
        v.slack -= min_slack

        if v.slack == 0:
          v.parent = v.potential_parent

          # Next we check whether being able to reach v leads us to either discover an augmenting path,
          # whose tail we return, or to more matched vertices we can enqueue to explore more tight edges
          # in the next iteration.
          tail = self.explore_right_vertex(v)
    if tail:
      return tail
    return None

  def explore_right_vertex(self, v):
    print("exploring right vertex")
    """
    Explore the right vertex.  If it's unmatched, all we do is return it as the tail of an augmenting path.
    If it's matched, we make it the parent of its matching partner, enqueue the matching partner, and return
    None to indicate we didn't find an augmenting path.
    :param v: the vertex to explore
    :return: v if its unmatched, None otherwise
    """
    if v.is_matched:
      v.match.parent = v
      self.queue.append(v.match)
      return None
    else:
      return v

  def slack(self, u, v):
    print("calculating slack")
    """
    Computes the slack between u and v based on the current vertex potentials.
    :param u: a left vertex
    :param v: a right vertex
    :return: the slack of the edge (u, v)
    """
    return self.matrix[u.name][v.name] - u.potential - v.potential

  @staticmethod
  def path_generator(v):
    print("entered path generator")
    """
    Returns an iterator over the path with tail v.
    :param v: the tail of the path
    :return: an iterator over the path
    """
    while v:
      # Generate the current vertex
      print("Getting vertex", v.name)
      yield v

      # If the current vertex has itself as the parent, it is the root, and we exit the loop.  Otherwise,
      # we advance to v's parent.
      if v == v.parent:
        v = None
      else:
        v = v.parent

  @staticmethod
  def augment_matching(path):
    """
    Augments the matching using the given augmenting path.  It is important that the path is provided as an
    iterator due to some magic in how the matching is calculated that wouldn't work if path were for instance
    a list.
    :param path: an iterator over an augmenting path
    """

    print("Augmenting matching")
    for (u, v) in zip(path, path):
      u.match = v
    print("Done augmenting")


def minimum_weight_perfect_matching(matrix):
  """
  Computes a minimum-weight perfect matching using the Hungarian algorithm in O(n^3) time.

  :param matrix: the input matrix represented as a list of lists
  :return: the computed matching in the form of pairs of (0-based) row index and column index that are paired
           in the matching.
  """
  return HungarianAlgorithm(matrix).solve()
