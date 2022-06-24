from collections import deque
pages = ["p3","p4","p2","p6","p4","p3","p7","p4","p3","p6","p3","p4","p8","p4","p6"]

class Stack(deque):
    def __init__(self):
        self.hit= 0
        self.miss= 0
        self.count= 0

    def push(self,x):
      if x in self:
         self.remove(x)
         self.hit+=1
      else:
          if len(self)==3:
              print(f"置换页面为： {self.popleft()}")
          self.miss+=1
      self.append(x)
      self.count+=1

def main():
    stack =Stack()
    for page in pages:
        stack.push(page)
    print(f"缺页次数为： {stack.miss}")
    print(f"命中率为： {stack.hit/stack.count:.2f}")


if __name__=="__main__":
    main()


