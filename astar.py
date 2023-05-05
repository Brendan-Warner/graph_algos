# -*- coding: utf-8 -*-


import random
class node:
  def __init__(self, num, num2, start, end):
    self.node_id = num2
    self.distance = num
    self.start = start
    self.end = end
    self.prev: node
    self.visited = false
    self.huristic = 0
    self.List_neighbors = []
    self.List_neighbors_distance =[]

  def visting():
    self.check_neighbros()
    self.set_visted()
    if self.is_end() == true:
      return false

    return true

  def set_visted(self):
    self.visited = true

  def is_end(self):
    return self.end

  def return_id():
    return self.id

  def check_visted(self):
    return self.visited

  def get_distance(self):
    return self.distance

  def return_prev(self):
    return self.prev

  def set_huristic(self, num):
    self.huristic = num
  def get_huristic(self):
    return self.huristic

  def check_neighbors(self):
    i = 0
    for x in List_neighbors:
      if x.check_visited() == false:
        if x.get_distance() > self.List_neighbros_distance[i] + self.get_distance() + x.get_hurisitc():
          x.set_distance(self.distance+ self.List_neighbros_distance[i])
          x.set_prev(self)
        i++

  def add_neighbors(self, neighbor, num):
    self.List_neighbors.append(neighbor)
    self.List_neighbors_distance.append(num)

i = 2
board = []



p1 = node(0,0,true, false)
board.append(p1)
for x in range (1, 6):
  if x == 5:
    p = node(1000000, x, false, true)
    num = random.randrange(1,4)
    distance = random.randrange(1,6)
    for y in range(5, 5-num):
      p.add_neighbors(board[y], distance)
      board[y].add_neighbors(p,distance)
      
    p.set_hurisitc(0)
    board.append(p)
  else:
    p = node(1000000, x, false, false)
    num2 = random.randrange(1,2)
    for z in range(x, x-num2):
      if z >=0:
        p.add_neighbors(board[z],distance)
        board[z].add_neighbors(p, distance)
        
    p.set_hurisitc(0)
    board.append(p)

board_sorted = []
for x in board:
  board_sorted.append(x)
not_end = true
while not_end:
  board_sorted.sort(key = lamda: p.distance)
  
  current = board_sorted(0)

  if(current.get_distance() == 1000000):
    print("No shortest distance possible")
    break
  
  not_end = current.visting()

  if not_end == false:
    print("End has been reached! the path is")
    print(current.return_id() + ", distance " current.get_distance())
    prev = current.return_prev()
    path = true
    while path:
      print(prev.return_id() + " + " prev.get_distance())
      if(prev.get_distance() != 0):
        prev = prev.return_prev()
        path = false