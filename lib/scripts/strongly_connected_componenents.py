"""
calculate the strongly connected components for undirected graphs.
"""
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

  def calc(self):
    stack = self.dfsFinishTime()
    result = []
    for node in self.nodes:
      node.visited = False
    for node in stack:
      if not node.visited:
        result.append([i for i in self.dfsVisit(node)])
    return result

  def dfsFinishTime(self):
    for node in self.nodes:
      node.visited = False
    result = []
    for node in self.nodes:
      if not node.visited:
        for i in self.dfsVisit(node):
          result.append(i)
    return result

  def dfsVisit(self, node):
    result = []
    node.visited = True
    for neighbour in node.neighbours:
      if not neighbour.visited:
        for i in self.dfsVisit(neighbour):
          result.append(i)
    result.append(node)
    return result


n1 = Node("1")
n2 = Node("2")
n3 = Node("3")
n4 = Node("4")
n5 = Node("5")
n1.neighbours = [n2, n5]
n2.neighbours = [n1]
n3.neighbours = [n4]
n4.neighbours = [n5]
n5.neighbours = [n3, n1]

for i in (ConnectedComponents([n1, n2, n3, n4, n5])).calc():
  print(i)
