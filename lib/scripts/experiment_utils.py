
"""
calculate the union of 2 numerical lists
"""
def overlap(l1, l2):
  l1 = sorted(l1)
  l2 = sorted(l2)
  l1Pos = 0
  l2Pos = 0
  maxSize = min(len(l1), len(l2))
  result = 0
  while l1Pos < maxSize and l2Pos < maxSize:
    if l1[l1Pos] == l2[l2Pos]:
      l1Pos += 1
      l2Pos += 1
      result += 1
    elif l1[l1Pos] > l2[l2Pos]:
      l2Pos += 1
    else:
      l1Pos += 1
  return result