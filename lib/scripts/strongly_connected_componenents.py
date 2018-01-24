"""
calculate the strongly connected components for undirected graphs.
"""
import sys
sys.setrecursionlimit(10000000)
class Node:
  def __init__(self, value=None, neighbours=None):
    self.value = value
    if neighbours == None:
      self.neighbours =[]
  def __repr__(self):
    return str(self.value)

class ConnectedComponents:
  def __init__(self, nodes):
    self.nodes = nodes
  # def calc(self):
  #   stack = []
  #   for node in self.nodes:
  #     node.visited = False
  #     stack.append(node)
  #   resultStack = []
  #   while len(stack) > 0:
  #     node = stack.pop()
  #     if not node.visited:
  #       node.visited = True
  #       for n in node.neighbours:
  #         if n.visited:
  #           continue
  #         stack.append(n)






  def calc(self):
    stack = []
    self._dfsSortByFinishTime(stack)
    result = []
    for node in self.nodes:
      node.visited = False
    for node in stack:
      if not node.visited:
        ss = []
        self._dfsVisit(node,ss)
        result.append(ss)
    # print("result:")
    # for i in result:
    #   print(i)
    # print()
    return result
  def _dfsSortByFinishTime(self, result):
    for node in self.nodes:
      node.visited = False
    for node in self.nodes:
      self._dfsSortByFinishTimeFrom(node,result)


  def _dfsSortByFinishTimeFrom(self, node, result):
    if not node.visited:
      node.visited = True
      for n in node.neighbours:
        if not node.visited:
          self._dfsSortByFinishTime(result)
      result.append(node)

  def _dfsVisit(self, node, result):
    node.visited = True
    result.append(node)
    for neighbour in node.neighbours:
      if not neighbour.visited:
        self._dfsVisit(neighbour,result)

